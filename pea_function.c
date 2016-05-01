#include <stdio.h>
#include <stdlib.h>

#include "pea.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_class.h"
#include "pea_function.h"
#include "pea_map.h"
#include "pea_mem.h"

pea_function* pea_function_alloc(pea_interpreter* interpreter,pea_class* cls,pea_atom name) {
  pea_function* func;

  /*
   * Check for redeclare
   */
  if (cls) {
    if (pea_map_find(cls->m_functions,&name,NULL) >= 0) {
      return NULL;
    }
  } else {
    if (pea_map_find(interpreter->m_functions,&name,NULL) >= 0) {
      return NULL;
    }
  }

  func = pea_calloc(interpreter,1,sizeof(struct pea_function_struct));
  
  func->m_type.m_type_id = PEA_TYPE_FUNCTION;
  func->m_name = name;
  func->m_globals = pea_map_alloc(interpreter,sizeof(pea_atom),0);

  if (cls) {
    pea_map_insert(cls->m_functions,&name,&func);
  } else {
    pea_map_insert(interpreter->m_functions,&name,&func);
  }
  return func;
}

pea_function*	pea_function_alloc_native(pea_interpreter* interpreter,pea_class* cls,const char* str_name,const char* args,void* p_func) {
  pea_function* func;
  pea_string*   str;
  pea_atom      name;

  str = pea_string_alloc(interpreter,0,str_name);

  name = pea_atom_add(interpreter,str);

  func = pea_calloc(interpreter,1,sizeof(struct pea_function_struct));

  func->m_type.m_type_id = PEA_TYPE_FUNCTION;
  func->m_name = name;
  func->m_globals = pea_map_alloc(interpreter,sizeof(pea_atom),0);
  func->m_args = args;
  func->m_func = p_func;

  if (cls) {
    pea_map_insert(cls->m_functions,&name,&func);
  } else {
    pea_map_insert(interpreter->m_functions,&name,&func);
  }

  return func;
}

pea_function*	pea_function_find(pea_interpreter* interpreter,pea_class* cls,pea_atom name) {
  pea_function* func;
  
  if (cls) {
    if (pea_map_find(cls->m_functions,&name,&func) < 0) {
      return NULL;
    }
  } else {
    if (pea_map_find(interpreter->m_functions,&name,&func) < 0) {
      return NULL;
    }
  }
  
  return func;
}

void pea_function_offset(pea_interpreter* interpreter,ulong offset_func) {
  pea_function*  func;
  ulong         index = 0;

  while (pea_map_list(interpreter->m_functions,index++,NULL,&func)) {
    // Ignore native functions
    if (func->m_func) {
      continue;
    }
    // Ignore function if we have relocated this function already
    if (func->m_flags & PEA_FUNCTION_RELOCATE) {
      continue;
    }

    // Relocate the function
    func->m_address += offset_func;
  
    func->m_flags |= PEA_FUNCTION_RELOCATE;
  }
}

void pea_function_add_global(pea_function* func,pea_atom glob) {

  pea_map_insert(func->m_globals,&glob,NULL);

}

int pea_function_is_global(pea_function* func,pea_atom glob) {
  
  if (func == NULL) {
    return 1;
  }

  if (pea_map_find(func->m_globals,&glob,NULL) >= 0) {
    return 1;
  }

  return 0;
}

