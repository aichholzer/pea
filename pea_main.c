#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define PEA_CPP 1

#include "pea.h"
#include "pea_op.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_segment.h"
#include "pea_class.h"
#include "pea_function.h"
#include "pea_object.h"
#include "pea_map.h"
#include "pea_stack.h"
#include "pea_variable.h"
#include "pea_rtl.h"

#ifdef _DEBUG

// debug output file used during parsing
FILE* dbgout;

// debug flags for the parser
extern int yydebug;

#endif

// yyin is the input stream to the lexer
extern FILE*  yyin;



int main(int argc, char* argv[],char** env)
{
  char*           script;
  pea_interpreter*  interpreter;
  pea_string*       s_script;
  pea_string*       s_path;
  pea_string*       s_dir;

#ifdef _DEBUG
  yydebug = 1;
#endif

  // Allocate main interpreter object
  interpreter = pea_interpreter_alloc();

   // Get script from environment variable
  script = getenv("PATH_TRANSLATED");
  if (script == NULL) {
    if (argc < 2) {
      fprintf(stdout,"Usage: pea.exe <filename.pea>\n");
      fprintf(stdout," pea.exe can be used as an Action for Apache or a stand alone scripting engine\n");
      exit(1);
    } 
    
    script = argv[1];
  }

  // Open the input file
  yyin = fopen(script,"r");
  if (yyin == NULL) {
    fprintf(stdout,"Can't open input script: %s\n",script);
    exit(1);
  }
  interpreter->m_current_file = script;
  interpreter->m_current_line = 1;

  // Locate the full path to the script
  s_script = pea_string_alloc(interpreter,0,script);

  s_path = pea_realpath(interpreter,s_script);

  // Get and save the base path of this script, all relative include will be done
  // against this path
  s_dir = pea_dirname(interpreter,s_path);

  interpreter->m_base_path = s_dir->value;

#ifdef _DEBUG
  dbgout = fopen("pea_parse.txt","w");
  if (dbgout == NULL) {
    perror("Failed to open debug output\n");
    exit(1);
  }
#endif

  interpreter->m_main_segment = pea_segment_alloc(interpreter);
  interpreter->m_func_segment = pea_segment_alloc(interpreter);
  interpreter->m_temp_segment = pea_segment_alloc(interpreter);

  pea_rtl_lang(interpreter);
  pea_rtl_cgi(interpreter,env);
  pea_rtl_db(interpreter);
  pea_rtl_io(interpreter);
  pea_rtl_socket(interpreter);

  pea_parser_init(interpreter);

  //
  // Parse the script, the yyparse function will call yylex to get a token and will use a big state-machine to parse the input
  //
  yyparse(interpreter);

  fclose(yyin);

#ifdef _DEBUG
  // Close the debug outputfile for the parse stage
  fclose(dbgout);

  // Open debug file dumping the result of the lex/parse stages
  dbgout = fopen("pea_prog.txt","w");
  if (dbgout == NULL) {
    perror("Failed to open debug output\n");
    exit(1);
  }
  
  // write out the parsed program
  pea_segment_dump(interpreter,interpreter->m_main_segment,dbgout);

  fclose(dbgout);

  // Open the debug output for the execution
  dbgout = fopen("pea_exec.txt","w");
#endif

  // Execute the script
  pea_interpreter_exec(interpreter,interpreter->m_main_segment);

#ifdef _DEBUG
  fclose(dbgout);
#endif

  return 0;
}

pea_interpreter* pea_interpreter_alloc() {
  pea_interpreter*  interpreter;
  pea_map*          frame;

  interpreter = (pea_interpreter*)calloc(1,sizeof(struct pea_interpreter_struct));

  interpreter->m_globals = pea_map_alloc(interpreter,sizeof(pea_atom),sizeof(pea_variable));
  interpreter->m_locals = pea_stack_alloc(interpreter,sizeof(pea_map*));

  frame = pea_map_alloc(interpreter,sizeof(pea_atom),sizeof(pea_variable));

  pea_stack_push(interpreter->m_locals,&frame);

  interpreter->m_functions = pea_map_alloc(interpreter,sizeof(pea_atom),sizeof(pea_function*));
  interpreter->m_classes = pea_map_alloc(interpreter,sizeof(pea_atom),sizeof(pea_class*));

  interpreter->m_call_stack = pea_stack_alloc(interpreter,sizeof(ulong));
  
  interpreter->m_value_stack = pea_stack_alloc(interpreter,sizeof(pea_variable));

  pea_atom_init(interpreter);

  pea_string_init(interpreter);

  return interpreter;
}



void  pea_call_stack_push(pea_interpreter* interpreter,ulong pos) {
  pea_stack_push(interpreter->m_call_stack,&pos);
}

ulong pea_call_stack_pop(pea_interpreter* interpreter) {
  ulong pos;

  pea_stack_pop(interpreter->m_call_stack,&pos);
  return pos;
}

void pea_globalvar_get(pea_interpreter* interpreter,pea_atom var,pea_variable* v) {

  v->m_type = &pea_variable_type;

  if (pea_map_find_ref(interpreter->m_globals,&var,(void**)&v->m_value.v) < 0) {
    pea_map_insert_ref(interpreter->m_globals,&var,(void**)&v->m_value.v);
    v->m_value.v->m_type = &pea_undefined_type;
  }
}

void pea_localvar_push(pea_interpreter* interpreter) {
  pea_map*  frame;

  frame = pea_map_alloc(interpreter,sizeof(pea_atom),sizeof(pea_variable));

  pea_stack_push(interpreter->m_locals,&frame);
}

void pea_localvar_get(pea_interpreter* interpreter,pea_atom var,pea_variable* v) {
  pea_map*  frame;

  v->m_type = &pea_variable_type;

  pea_stack_top(interpreter->m_locals,&frame);

  if (pea_map_find_ref(frame,&var,(void**)&v->m_value.v) < 0) {
    pea_map_insert_ref(frame,&var,(void**)&v->m_value.v);
    v->m_value.v->m_type = &pea_undefined_type;
  }
}


void pea_localvar_clear(pea_interpreter* interpreter) {
  pea_map*  frame;

  pea_stack_pop(interpreter->m_locals,&frame);

  pea_map_free(interpreter,frame);
}

int pea_print(pea_interpreter* interpreter,FILE* f,char* fmt,...) {
  va_list     marker;
  pea_atom    a;
  pea_string* s;
  char        t[4];
  int         wlen = 0;
  int         error =0;

  va_start(marker,fmt);
  
  while(*fmt) {
    if (*fmt == '%') {
      fmt++;
      switch(*fmt) {
      case 'a':
        a = va_arg(marker,pea_atom);
        wlen += pea_atom_write(interpreter,a,f);
        break;
      case 'S':
        s = va_arg(marker,pea_string*);
        wlen += pea_string_write(s,f);
        break;
      case 'E':
        wlen += fprintf(f,"<br />Error: %s (%d) : ",interpreter->m_current_file,interpreter->m_current_line);
        error = 1;
        break;
      default:
        t[0] = '%';
        t[1] = *fmt;
        t[2] = 0;
        wlen += fprintf(f,t,va_arg(marker,void*));
        break;
      }
    } else {
      fwrite(fmt,1,1,f);
      wlen++;
    }
    fmt++;
  }

  if (error) {
    wlen += fprintf(f,"<br />\n");
  }
  return wlen;
}

void pea_flush(pea_interpreter* interpreter,FILE* f) {
  fflush(f);
}
