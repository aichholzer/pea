

#ifdef pea__CPP
#define EXTERN
#else
#define EXTERN extern
#endif

#define PEA_MAX_PATH  1024

typedef unsigned long ulong;

typedef int pea_atom;

typedef struct pea_map_struct pea_map;
typedef struct pea_stack_struct pea_stack;
typedef struct pea_stream_struct pea_stream;
typedef struct pea_string_struct pea_string;

typedef struct pea_variable_struct pea_variable;

typedef struct pea_segment_struct pea_segment;

typedef struct pea_function_struct pea_function;
typedef struct pea_class_struct pea_class;

typedef struct pea_label_struct {
	size_t			  l_skip_if;
	size_t			  l_skip_else;
	size_t			  l_begin_while;
	size_t			  l_skip_while;
	size_t			  l_begin_do;
	size_t			  l_begin_for;
	size_t			  l_skip_for;
  size_t        l_break;
  size_t        l_skip_case;
	pea_segment*	s_for;
	pea_segment*	s_func;
  pea_stack*    s_breaks;
} pea_label;		/* label info */

typedef struct pea_interpreter_struct {
  char*         m_current_file;
  int           m_current_line;
  char*         m_base_path;
  pea_segment*  m_curr_segment;
  pea_segment*  m_main_segment;
  pea_segment*  m_func_segment;
  pea_segment*  m_temp_segment;
  pea_function*	m_current_function;   // Keeps track if we are parsing a function or if we are on global context
  pea_class*		m_current_class;      // Keeps track if we are parsing a class or if we are on global context
  pea_atom      m_atom_this;
  pea_stack*    m_value_stack;
  ulong         m_value_stack_arg_frame;
  pea_stack*    m_call_stack;
  pea_map*      m_globals;
  pea_stack*    m_locals;
  pea_map*      m_functions;
  pea_map*      m_classes;
  pea_stack*    m_curr_breaks;
} pea_interpreter;

/* 
 * A common type header, this struct is used on all individual type object and shoule be placed as first
 * member in the struct
 */
typedef struct pea_type_struct {
  int           m_type_id;
} pea_type;

#define PEA_TYPE_UNDEFINED  0
#define PEA_TYPE_INTEGER    1
#define PEA_TYPE_STRING     2
#define PEA_TYPE_ATOM       3 
#define PEA_TYPE_CLASS      4
#define PEA_TYPE_FUNCTION   5
#define PEA_TYPE_VARIABLE   6
#define PEA_TYPE_ARRAY      7
#define PEA_TYPE_ENUM       8
#define PEA_TYPE_CHARSTR    9

extern pea_type pea_undefined_type;
extern pea_type pea_integer_type;
extern pea_type pea_string_type;
extern pea_type pea_atom_type;
extern pea_type pea_variable_type;
extern pea_type pea_array_type;
extern pea_type pea_enum_type;

// the FLEX generated tokenizer
int yylex();

// The BISON generated parser is called by the yyparse function 
int yyparse(void* interpreter);

void pea_parser_init(pea_interpreter* interpreter);
int pea_parser_include(pea_interpreter* interpreter,const char* file);

pea_interpreter* pea_interpreter_alloc();

// The execution module executes a program written in byte-code
void pea_interpreter_exec(pea_interpreter* interpreter,struct pea_segment_struct* prog);

void  pea_call_stack_push(pea_interpreter* interpreter,ulong pos);
ulong pea_call_stack_pop(pea_interpreter* interpreter);

void pea_globalvar_get(pea_interpreter* interpreter,pea_atom var,pea_variable* v);
void pea_localvar_push(pea_interpreter* interpreter);
void pea_localvar_get(pea_interpreter* interpreter,pea_atom var,pea_variable* v);
void pea_localvar_clear(pea_interpreter* interpreter);


typedef ulong (*PFN_NATIVE_0)(pea_interpreter* interpreter);
typedef ulong (*PFN_NATIVE_1)(pea_interpreter* interpreter,ulong a);
typedef ulong (*PFN_NATIVE_2)(pea_interpreter* interpreter,ulong a,ulong b);
typedef ulong (*PFN_NATIVE_3)(pea_interpreter* interpreter,ulong a,ulong b,ulong c);
typedef ulong (*PFN_NATIVE_4)(pea_interpreter* interpreter,ulong a,ulong b,ulong c,ulong d);
typedef ulong (*PFN_NATIVE_V)(pea_interpreter* interpreter,ulong arg_count);

int pea_print(pea_interpreter* interpreter,FILE* f,char* fmt,...);
void pea_flush(pea_interpreter* interpreter,FILE* f);

#define NYI // _asm int 3

char * pea_strtok(char *s, const char *delim, char **last);
ulong pea_urldecode(const char *src,char *dst,ulong maxlen);
