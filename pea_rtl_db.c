#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef WIN32
#include <winsock.h>
#endif
#include "mysql.h"

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

MYSQL*  myCursor = NULL;

int pea_db_open(pea_interpreter* interpreter,char* driver,char* config) {
  char*   attr;
  char*   value;
  char*   servidor = "localhost";	//HOST
  char*   usuario = "";				//USER
  char*   clave = "";				//PASS
  char*   bd = "";					//DATABASE

  // FIX: Move kode to pea_mysql.dll and load based on driver value
  
  /*
   * Parse the config
   */
  attr = strtok(config,";="); // FIX: Should be strtok_r
  while(attr != NULL) {
    value = strtok(NULL,";=");
    if (value == NULL) {
      break;
    }

    if (stricmp(attr,"servidor") == 0) {
      servidor = value;
    }
    if (stricmp(attr,"usuario") == 0) {
      usuario = value;
    }
    if (stricmp(attr,"clave") == 0) {
      clave = value;
    }
    if (stricmp(attr,"bd") == 0) {
      bd = value;
    }

    attr = strtok(NULL,";=");
  }

  myCursor = mysql_init((MYSQL*) 0);
  if (myCursor == NULL) {
    pea_print(interpreter,stdout,"%E MYSQL: init failed");
    return -1;
  }

  if(mysql_real_connect(myCursor,servidor,usuario,clave,bd, 0, NULL, 0) == NULL) {
    pea_print(interpreter,stdout,"%E MYSQL: connect failed");
    return -1;
  }

  if (mysql_select_db(myCursor,bd) < 0 ) {
    pea_print(interpreter,stdout,"%E MYSQL: select bd failed");
    return -1;
  }

  return 0;
}

pea_array* pea_db_query(pea_interpreter* interpreter,int handle,char* query) {
  int               rc;
  MYSQL_RES*        result;
  MYSQL_ROW	        row;
  unsigned int      cols,i;
  MYSQL_FIELD*      col_names;
  pea_string*       s;
  pea_atom          a;
  pea_array*        res_arr;
  pea_array*        row_arr;
  pea_variable      v;

  if (myCursor == NULL) {
    pea_print(interpreter,stdout,"%E MYSQL: no db open");
    return NULL;
  }

  /*
   * Run the query
   */
  rc = mysql_query(myCursor, query);
  if (rc) {
    return NULL;
  }

  /* 
   * Ask MySQL to fetch the result into memory
   */
  result = mysql_store_result(myCursor);
  if (result == NULL) {
    return NULL;
  }

  /*
   * Locate the number of colums we have in the result set
   */
  cols = mysql_num_fields(result);

  /*
   * Get the names of the colums to be able to create a struct
   */
  col_names = mysql_fetch_fields(result);

  res_arr = pea_array_alloc(interpreter);

  /*
   * Fetch the result from MYSQL one row at a time
   */
  while((row  = mysql_fetch_row(result)) != NULL) {
    /*
     * Get the length of the differnet colums of the row
     */
    unsigned long *lengths = mysql_fetch_lengths(result);

    /*
     * Allocate a array for the result row
     */
    row_arr = pea_array_alloc(interpreter);

    /*
     * Add all cols to the array
     */
    for(i = 0; i < cols; i++) {
    
      s = pea_string_alloc(interpreter,0,col_names[i].name);

      a = pea_atom_add(interpreter,s);

      s = pea_string_alloc(interpreter,lengths[i],row[i]);

      v.m_type = &pea_string_type;
      v.m_value.s = s;

      pea_array_set_atom(interpreter,row_arr,a,&v);
    }

    v.m_type = &pea_array_type;
    v.m_value.r = row_arr;

    pea_array_append(interpreter,res_arr,&v);
  }

  return res_arr;
}

int pea_db_affected_rows(pea_interpreter* interpreter,int handle) {

  if (myCursor == NULL) {
    pea_print(interpreter,stdout,"%E MYSQL: no db open");
    return 0;
  }

  return (int)mysql_affected_rows(myCursor);
}

pea_string* pea_db_escape_string(pea_interpreter* interpreter,char* str) {
  size_t      len;
  pea_string* r;

  if (myCursor == NULL) {
    pea_print(interpreter,stdout,"%E MYSQL: no db open");
    return NULL;
  }

  len = strlen(str);

  r = pea_string_alloc(interpreter,len*2 + 1,NULL);

  r->length = mysql_real_escape_string(myCursor,r->value,str,len);

  return r;
}

int pea_db_insert_id(pea_interpreter* interpreter,int handle) {

  if (myCursor == NULL) {
    pea_print(interpreter,stdout,"%E MYSQL: no db open");
    return 0;
  }

  return (int)mysql_insert_id(myCursor);
}

pea_string* pea_db_error(pea_interpreter* interpreter,int handle) {
  const char* err = mysql_error(myCursor);
  return pea_string_alloc(interpreter,0,err);
}

int pea_rtl_db(pea_interpreter* interpreter) {
  pea_function_alloc_native(interpreter,NULL,"bd_abrir","iSS",pea_db_open);
  pea_function_alloc_native(interpreter,NULL,"bd_consulta","riS",pea_db_query);
  pea_function_alloc_native(interpreter,NULL,"bd_afectadas","ii",pea_db_affected_rows);
  pea_function_alloc_native(interpreter,NULL,"bd_escapar_cadena","SS",pea_db_escape_string);
  pea_function_alloc_native(interpreter,NULL,"bd_insertar_id","ii",pea_db_insert_id);
  pea_function_alloc_native(interpreter,NULL,"bd_error","si",pea_db_error);
  return 0;
}
