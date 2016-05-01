#include <stdio.h>
#include <stdlib.h>

#include "pea.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_class.h"
#include "pea_function.h"
#include "pea_object.h"
#include "pea_map.h"
#include "pea_variable.h"

pea_object* pea_object_alloc(pea_interpreter* interpreter,pea_class* cls) {
  pea_object*  obj;

  obj = calloc(1,sizeof(struct pea_object_struct));

  obj->m_class = cls;

  obj->m_members = pea_map_alloc(interpreter,sizeof(pea_atom),sizeof(pea_function*));

  return obj;
}

void pea_object_var_get(pea_interpreter* interpreter,pea_object* obj,pea_variable* var,pea_variable* v) {

  /*
   * Check if this is a member function
   */
  if (pea_map_find(obj->m_class->m_functions,&var->m_value.a,(void**)&v->m_type) >= 0) {
    v->m_value.o = obj;

  } else {

    v->m_type = &pea_variable_type;

    if (pea_map_find_ref(obj->m_members,&var->m_value.a,(void**)&v->m_value.v) < 0) {
      pea_map_insert_ref(obj->m_members,&var->m_value.a,(void**)&v->m_value.v);
      v->m_value.v->m_type = &pea_undefined_type;  
    }
  }
}
