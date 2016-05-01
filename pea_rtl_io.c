#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <io.h>
#include <fcntl.h>
#ifdef WIN32  // for getcwd
#include <direct.h>
#endif

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

int pea_open(pea_interpreter* interpreter,char* file) {
  return open(file,_O_RDONLY);
}

int pea_close(pea_interpreter* interpreter,int fh) {
  return 0;
}

pea_string* pea_realpath(pea_interpreter* interpreter,pea_string* file) {
  char  buff[PEA_MAX_PATH];
  char* d;
  char* dir;
  char* lastDir;

  //
  // Check if the file path is absolute
  //
#ifdef WIN32
  if (file->value[0] == '/' || file->value[0] == '\\' || (file->value[1] == ':' && file->value[2] == '/') || (file->value[1] == ':' && file->value[2] == '\\') ) {
#else
  if (file->value[0] == '/') {
#endif

    strcpy(buff,file->value);
    
  } else {

    // Get cwd, if m_base_path is null we are starting up
    // pea and need to get the application cwd
    //
    if (interpreter->m_base_path == NULL) {
      getcwd(buff,PEA_MAX_PATH);
    } else {
      strcpy(buff,interpreter->m_base_path);
    }

    // Remove trailing /
    d = &buff[strlen(buff)];
    if (d > buff && (*d == '/' || *d == '\\')) {
      d--;
      *d = 0;
    }

    // Parse the input path end build the real path
    dir = pea_strtok(file->value,"/",&lastDir);
    while(dir) {
      // Handle ..
      if (dir[0] == '.' && dir[1] == '.' && dir[2]=='\0') {
        while(d > buff) {
          if (*d == '/' || *d == '\\') {
            d++;
            break;
          } else {
            d--;
          }
        }

        
      // Handle .
      } else if (dir[0] == '.' && dir[1] == '\0') {
        // Ignore
      } else {
        strcat(buff,"/");
        strcat(buff,dir);
      }
      dir = pea_strtok(NULL,"/",&lastDir);
    }
  }

  return pea_string_alloc(interpreter,0,buff);
}

pea_string* pea_dirname(pea_interpreter* interpreter,pea_string* file) {
  char  buff[PEA_MAX_PATH];
  char* d;
  ulong len;

  len = pea_string_get(file,buff,PEA_MAX_PATH);

  // reverse d until we find a / or \ 
  d = &buff[len];
  while (len && (*d != '/' && *d != '\\')) {
    d--;
    len--;
  }

  return pea_string_alloc(interpreter,len,buff);
}

pea_string* pea_searchenv(pea_interpreter* interpreter,pea_string* file,pea_string* path) {
  pea_variable  v;
  char*         p;
  char*         lastPath;
  char*         dir;
  char*         lastDir;
  char          name[PEA_MAX_PATH];
  char          buff[PEA_MAX_PATH];
  char*         d;
  FILE*         f;

  if (path == NULL) {
    // Get the path from the global var include_path
    pea_globalvar_get(interpreter,pea_atom_add_cs(interpreter,"include_path"),&v);
    pea_variable_tovalue(interpreter,&v);
    if (v.m_type->m_type_id != PEA_TYPE_STRING) {
      p = pea_strtok(".",";",&lastPath);
    } else {
      p = pea_strtok(v.m_value.s->value,";",&lastPath);
    }
  } else {
    p = pea_strtok(path->value,";",&lastPath);
  }

  while(p) {
    if (p[0] == '.' && p[1]=='\0') {
      p = interpreter->m_base_path;
    }

    strcpy(buff,p);

    // Remove trailing /
    d = &buff[strlen(buff) -1];
    if (d > buff && (*d == '/' || *d == '\\')) {
      d--;
      *d = 0;
    }

    // Parse the input path end build the real path
    strcpy(name,file->value);
    dir = pea_strtok(name,"/",&lastDir);
    while(dir) {
      // Handle ..
      if (dir[0] == '.' && dir[1] == '.' && dir[2]=='\0') {
        while(d > buff) {
          if (*d == '/' || *d == '\\') {
            *d = 0;
            break;
          } else {
            d--;
          }
        }

        
      // Handle .
      } else if (dir[0] == '.' && dir[1] == '\0') {
        // Ignore
      } else {
        strcat(buff,"/");
        strcat(buff,dir);
      }
      dir = pea_strtok(NULL,"/",&lastDir);
    }

    //
    // Check if file is found
    //
    f = fopen(buff,"r");
    if (f != NULL) {
      fclose(f);
      return pea_string_alloc(interpreter,0,buff);
    }


    p = pea_strtok(NULL,";",&lastPath);
  }

  return NULL;
}

int pea_rtl_io(pea_interpreter* interpreter) {
  pea_function_alloc_native(interpreter,NULL,"abrir","iS",pea_open);
  pea_function_alloc_native(interpreter,NULL,"cerrar","ii",pea_close);
  pea_function_alloc_native(interpreter,NULL,"realpath","ss",pea_realpath);
  pea_function_alloc_native(interpreter,NULL,"dirname","ss",pea_dirname);
  pea_function_alloc_native(interpreter,NULL,"searchenv","sss",pea_searchenv);
  return 0;
}
