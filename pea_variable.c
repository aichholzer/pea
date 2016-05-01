#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pea.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_class.h"
#include "pea_function.h"
#include "pea_object.h"
#include "pea_variable.h"
#include "pea_stack.h"
#include "pea_array.h"

#ifdef _DEBUG

// Debug trace file
FILE* dbgout;
#endif

//
// pea_variable_tovalue - dereference the variable 
//
void  pea_variable_tovalue(pea_interpreter* interpreter,pea_variable* v) {
  if (v->m_type->m_type_id == PEA_TYPE_VARIABLE) {
    *v = *v->m_value.v;
    pea_variable_tovalue(interpreter,v);
    return;
  }
}

//
// pea_variable_toint - convert a value to an integer
//
void pea_variable_toint(pea_interpreter* interpreter,pea_variable* v) {
  char  buff[32];
  if (v->m_type->m_type_id == PEA_TYPE_INTEGER) {
    return;
  }
  if (v->m_type->m_type_id == PEA_TYPE_STRING) {
    pea_string_get(v->m_value.s,buff,sizeof(buff));
    v->m_value.i = atoi(buff);
    v->m_type = &pea_integer_type;
    return;
  }
  if (v->m_type->m_type_id == PEA_TYPE_UNDEFINED) {
    v->m_value.i = 0;
    v->m_type = &pea_integer_type;
    return;
  }
  if (v->m_type->m_type_id == PEA_TYPE_VARIABLE) {
    *v = *v->m_value.v;
    pea_variable_toint(interpreter,v);
    return;
  }
  NYI;
}

//
// pea_variable_tostring - convert a value to a string
//
void pea_variable_tostring(pea_interpreter* interpreter,pea_variable* v) {
  if (v->m_type == NULL) {
    v->m_value.s = pea_string_alloc(interpreter,0,"sin_definir");
    v->m_type = &pea_string_type;
    return;
  }

  if (v->m_type->m_type_id == PEA_TYPE_STRING) {
    return;
  }
  if (v->m_type->m_type_id == PEA_TYPE_ATOM) {
    pea_atom_tostring(interpreter,v->m_value.a,v);
    return;
  }
  if (v->m_type->m_type_id == PEA_TYPE_INTEGER) {
    char  buff[11];
    sprintf(buff,"%d",v->m_value.i);
    v->m_value.s = pea_string_alloc(interpreter,0,buff);
    v->m_type = &pea_string_type;
    return;
  }
  if (v->m_type->m_type_id == PEA_TYPE_UNDEFINED) {
    v->m_value.s = pea_string_alloc(interpreter,0,"sin_definir");
    v->m_type = &pea_string_type;
    return;
  }
  if (v->m_type->m_type_id == PEA_TYPE_VARIABLE) {
    *v = *v->m_value.v;
    pea_variable_tostring(interpreter,v);
    return;
  }
  if (v->m_type->m_type_id == PEA_TYPE_ARRAY) {
    v->m_type = &pea_string_type;
    v->m_value.s = pea_array_tostring(interpreter,v->m_value.r);
    return;
  }
  NYI;
}

//
// pea_variable_toatom - convert a value to an atom
//
void pea_variable_toatom(pea_interpreter* interpreter,pea_variable* v) {
  if (v->m_type->m_type_id == PEA_TYPE_ATOM) {
    return;
  }
  if (v->m_type->m_type_id == PEA_TYPE_STRING) {
    v->m_value.a = pea_atom_add(interpreter,v->m_value.s);
    v->m_type = &pea_atom_type;
    return;
  }
  if (v->m_type->m_type_id == PEA_TYPE_VARIABLE) {
    *v = *v->m_value.v;
    pea_variable_toatom(interpreter,v);
    return;
  }
  NYI;
}

//
// pea_variable_toobject - convert a value to an object
//
void pea_variable_toobject(pea_interpreter* interpreter,pea_variable* v) {
  if (v->m_type->m_type_id == PEA_TYPE_CLASS) {
    return;
  }

  if (v->m_type->m_type_id == PEA_TYPE_ARRAY) {
    return;
  }

  if (v->m_type->m_type_id == PEA_TYPE_VARIABLE) {
    *v = *v->m_value.v;
    pea_variable_toobject(interpreter,v);
    return;
  }

  NYI;

  return;
}

//
// pea_variable_toarray - convert a value to an array
//
void pea_variable_toarray(pea_interpreter* interpreter,pea_variable* v) {

  if (v->m_type->m_type_id == PEA_TYPE_ARRAY) {
    return;
  }
  
  if (v->m_type->m_type_id == PEA_TYPE_VARIABLE) {
    if (v->m_value.v->m_type->m_type_id == PEA_TYPE_UNDEFINED) {
      v->m_value.v->m_type = &pea_array_type;
      v->m_value.v->m_value.r = pea_array_alloc(interpreter);
    }
    *v = *v->m_value.v;
    pea_variable_toarray(interpreter,v);
    return;
  }

  return;
}

void pea_variable_copy(pea_interpreter* interpreter,pea_variable* d,pea_variable* s) {
  if (d) {
    *d = *s;
  }
}

void pea_variable_assign(pea_interpreter* interpreter,pea_variable* d,pea_variable* s) {
  if (d->m_type->m_type_id == PEA_TYPE_VARIABLE) {
    pea_variable_assign(interpreter,d->m_value.v,s);
  } else {
    *d = *s;
  }
}

ulong pea_variable_stack_size(pea_interpreter* interpreter) {
  return pea_stack_size(interpreter->m_value_stack);
}

void  pea_variable_stack_push(pea_interpreter* interpreter,pea_variable* v) {
  pea_variable t;

  pea_variable_copy(interpreter,&t,v);

  pea_stack_push(interpreter->m_value_stack,&t);
}

void  pea_variable_stack_pop(pea_interpreter* interpreter,pea_variable* v) {
  pea_variable t;

  pea_stack_pop(interpreter->m_value_stack,&t);

  pea_variable_copy(interpreter,v,&t);

}

void pea_variable_stack_pop_ex(pea_interpreter* interpreter,pea_variable* v,ulong back) {

  pea_variable t;

  pea_stack_pop_ex(interpreter->m_value_stack,back,&t);

  pea_variable_copy(interpreter,v,&t);
}

void  pea_variable_stack_top(pea_interpreter* interpreter,pea_variable* v) {
  pea_variable t;

  pea_stack_top(interpreter->m_value_stack,&t);

  pea_variable_copy(interpreter,v,&t);
}

void pea_variable_stack_push_native(pea_interpreter* interpreter,char type,ulong v) {
  pea_variable  v1;

  switch(type) {
  case 'i':
    v1.m_type = &pea_integer_type;
    v1.m_value.i = v;
    break;
  case 's':
    v1.m_type = &pea_string_type;
    v1.m_value.s = (pea_string*)v;
    break;
  case 'S':
    v1.m_type = &pea_string_type;
    v1.m_value.s = pea_string_alloc(interpreter,0,(char*)v);
    break;
  case 'a':
    v1.m_type = &pea_atom_type;
    v1.m_value.s = pea_string_alloc(interpreter,0,(char*)v);
    v1.m_value.a = pea_atom_add(interpreter,v1.m_value.s);
    break;
  case 'o':
    v1.m_type = (pea_type*)((pea_object*)v)->m_class;
    v1.m_value.o = (pea_object*)v;
    break;
  case 'r':
    v1.m_type = &pea_array_type;
    v1.m_value.r = (pea_array*)v;
    break;
  default:
  NYI;
    v1.m_type = &pea_undefined_type;
    break;
  }
  pea_stack_push(interpreter->m_value_stack,&v1);
}

void pea_variable_stack_pop_native(pea_interpreter* interpreter,char type,ulong* v) {
  pea_variable  v1;
  ulong         size;

  pea_variable_stack_pop(interpreter,&v1);
  switch(type) {
  case 'n': // native
    *v = v1.m_value.i;
    break;
  case 'i':
    pea_variable_toint(interpreter,&v1);
    *v = v1.m_value.i;
    break;
  case 's':
    pea_variable_tostring(interpreter,&v1);
    *v = (ulong)v1.m_value.s;
    break;
  case 'S':
    pea_variable_tostring(interpreter,&v1);
    size = pea_string_length(v1.m_value.s);
    *v = (ulong)malloc(size + 1);
    pea_string_get(v1.m_value.s,(char*)*v,size);
    break;
  case 'a':
    pea_variable_toatom(interpreter,&v1);
    *v = (ulong)v1.m_value.a;
    break;
  case 'o':
   pea_variable_toobject(interpreter,&v1);
    *v = (ulong)v1.m_value.o;
  default:
    NYI;
    *v = 0;
    break;
  }
}

void pea_variable_stack_arg_start(pea_interpreter* interpreter,ulong count) {

  interpreter->m_value_stack_arg_frame = pea_stack_size(interpreter->m_value_stack) - count;

}

void pea_variable_stack_arg_next(pea_interpreter* interpreter,pea_variable* v) {
  pea_variable t;

  pea_stack_get(interpreter->m_value_stack,interpreter->m_value_stack_arg_frame,&t);

  interpreter->m_value_stack_arg_frame++;

  pea_variable_copy(interpreter,v,&t);
}

int pea_variable_compare(pea_interpreter* interpreter,pea_variable* a,pea_variable* b) {

  pea_variable_tovalue(interpreter,a);
  pea_variable_tovalue(interpreter,b);

  if (a->m_type->m_type_id == PEA_TYPE_INTEGER) {
    pea_variable_toint(interpreter,b);
    if (b->m_type->m_type_id == PEA_TYPE_INTEGER) {
      return a->m_value.i - b->m_value.i;
    }
    pea_variable_tostring(interpreter,a);
  }
  if (a->m_type->m_type_id == PEA_TYPE_STRING) {
    pea_variable_tostring(interpreter,b);
    if (b->m_type->m_type_id == PEA_TYPE_STRING) {

      pea_print(interpreter,dbgout," %s == %s",a->m_value.s->value,b->m_value.s->value);

      return pea_string_compare(a->m_value.s,b->m_value.s);
    }
  }

  return 1;
}
