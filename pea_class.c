#include <stdio.h>
#include <stdlib.h>

#include "pea.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_class.h"
#include "pea_function.h"
#include "pea_map.h"
#include "pea_mem.h"

pea_class* pea_class_alloc(pea_interpreter* interpreter,pea_atom name) {
  pea_class* cls;

  cls = pea_calloc(interpreter,1,sizeof(struct pea_class_struct));
  
  cls->m_type.m_type_id = PEA_TYPE_CLASS;
  cls->m_name = name;
  cls->m_functions = pea_map_alloc(interpreter,sizeof(pea_atom),sizeof(pea_function*));

  pea_map_insert(interpreter->m_classes,&name,&cls);

  return cls;
}

pea_class*	pea_class_find(pea_interpreter* interpreter,pea_atom name) {
  pea_class* cls;
  
  if (pea_map_find(interpreter->m_classes,&name,&cls) < 0) {
    return NULL;
  }
 
  return cls;
}

void pea_class_offset(pea_interpreter* interpreter,ulong offset_func) {
  pea_class*    cls;
  pea_function* func;
  ulong         c_index = 0;
  ulong         f_index = 0;

  while (pea_map_list(interpreter->m_classes,c_index++,NULL,&cls)) {
    f_index = 0;
    while (pea_map_list(cls->m_functions,f_index++,NULL,&func)) {

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
}

