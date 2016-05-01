#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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
#include "pea_array.h"

int pea_header(pea_interpreter* interpreter,char* s) {
  return 0;
}

int pea_rtl_cgi(pea_interpreter* interpreter,char** env) {
  int           i;
  char*         pRequestMethod = "GET";
  char*         pQueryString = "";
  char*         pContLength = "0";
  char*         pContType = "0";
  pea_variable  v;
  char*         ks;
  char*         lastPair;
  char*         vs;
  pea_atom      key;
  pea_string*   value_raw;
  pea_string*   value;
  pea_array*    get;
  pea_array*    post;

  pea_function_alloc_native(interpreter,NULL,"cabecera","iS",pea_header);

  // Output content type to follow CGI specification
  printf("Content-type: text/html\r\n\r\n");

  // Locate REQUEST_METHOD and QUERY_STRING
  for(i=0;env[i] != NULL;i++) {
    if (strncmp(env[i],"REQUEST_METHOD=",15) == 0) {
      pRequestMethod = &env[i][15];
    }
    if (strncmp(env[i],"QUERY_STRING=",13) == 0) {
      pQueryString = &env[i][13];
    }
    if (strncmp(env[i],"CONTENT_LENGTH=",15) == 0) {
      pContLength = &env[i][15];
    }
    if (strncmp(env[i],"CONTENT_TYPE=",13) == 0) {
      pContType = &env[i][13];
    }
//    printf("%s\n",env[i]);
  }

  // Handle GET and POST variable

  // Allocate GET array
  get = pea_array_alloc(interpreter);

  // Store in global var GET
  pea_globalvar_get(interpreter,pea_atom_add_cs(interpreter,"GET"),&v);

  v.m_value.v->m_type = &pea_array_type;
  v.m_value.v->m_value.r = get;

  // Allocate POST array
  post = pea_array_alloc(interpreter);

  // Store in global var POST
  pea_globalvar_get(interpreter,pea_atom_add_cs(interpreter,"POST"),&v);

  v.m_value.v->m_type = &pea_array_type;
  v.m_value.v->m_value.r = post;

  if (strcmp(pRequestMethod,"POST") == 0) {
    char* buff;
    int   len;

    len = atoi(pContLength);
    if (len > 0) {
      // FIX: Implement max-post?
      
      // FIX: Rewrite to use pea_stream
      buff = malloc(len);

      fread(buff,1,len,stdin);
      
      buff[len] = 0;

      if (strcmp(pContType,"application/x-www-form-urlencoded")==0) {

        // Parse query string and add POST[key] = value
        ks = pea_strtok(buff,"&",&lastPair);
        while(ks) {
          vs = strchr(ks,'=');
          if (vs) {
            *vs++ = 0;

            key = pea_atom_add_cs(interpreter,ks);
            value_raw = pea_string_alloc(interpreter,0,vs);
    
            value = pea_string_urldecode(interpreter,value_raw);

            v.m_type = &pea_string_type;
            v.m_value.s = value;

            pea_array_set_atom(interpreter,post,key,&v);
          }

          ks = pea_strtok(NULL,"&",&lastPair);
        }
      } else {
        NYI;
      }
    }
  } 
    
  // Parse query string and add GET[key] = value
  ks = pea_strtok(pQueryString,"&",&lastPair);
  while(ks) {
    vs = strchr(ks,'=');
    if (vs) {
      *vs++ = 0;

      key = pea_atom_add_cs(interpreter,ks);
      value_raw = pea_string_alloc(interpreter,0,vs);

      value = pea_string_urldecode(interpreter,value_raw);
      
      v.m_type = &pea_string_type;
      v.m_value.s = value;

      pea_array_set_atom(interpreter,get,key,&v);
    }

    ks = pea_strtok(NULL,"&",&lastPair);
  }

  return 0;
}
