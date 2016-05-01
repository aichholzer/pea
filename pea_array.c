#include <stdio.h>
#include <stdlib.h>

#include "pea.h"
#include "pea_mem.h"
#include "pea_string.h"
#include "pea_variable.h"
#include "pea_array.h"
#include "pea_map.h"
#include "pea_atom.h"
#include "pea_stream.h"

pea_array* pea_array_alloc(pea_interpreter* interpreter) {
  pea_array* arr;

  arr = pea_calloc(interpreter,1,sizeof(struct pea_array_struct));

  arr->m_int_members = pea_map_alloc(interpreter,sizeof(int),sizeof(pea_variable));
  arr->m_atom_members = pea_map_alloc(interpreter,sizeof(pea_atom),sizeof(pea_variable));

  return arr;
}

void pea_array_append(pea_interpreter* interpreter,pea_array* arr,pea_variable* v) {
  
  int next = pea_map_count(arr->m_int_members);

  pea_array_set_int(interpreter,arr,next,v);

}

void pea_array_set_atom(pea_interpreter* interpreter,pea_array* arr,pea_atom a,pea_variable* v) {
  pea_map_insert(arr->m_atom_members,&a,v);
}

void pea_array_set_int(pea_interpreter* interpreter,pea_array* arr,int i,pea_variable* v) {
  pea_map_insert(arr->m_int_members,&i,v);
}

void pea_array_get(pea_interpreter* interpreter,pea_array* arr,pea_variable* i,pea_variable* v) {

  if (i->m_type->m_type_id == PEA_TYPE_VARIABLE) {
    pea_array_get(interpreter,arr,i->m_value.v,v);
  } else if (i->m_type->m_type_id == PEA_TYPE_ATOM) {
    pea_array_get_atom(interpreter,arr,i->m_value.a,v);
  } else if (i->m_type->m_type_id == PEA_TYPE_INTEGER) {
    pea_array_get_int(interpreter,arr,i->m_value.a,v);
  } else if (i->m_type->m_type_id == PEA_TYPE_STRING) {

    pea_atom a = pea_atom_add(interpreter,i->m_value.s);
    
    pea_array_get_atom(interpreter,arr,a,v);

  } else {

     NYI;
  }
}

int pea_array_get_atom(pea_interpreter* interpreter,pea_array* arr,pea_atom a,pea_variable* v) {
  int r;

  r = pea_map_find_ref(arr->m_atom_members,&a,(void**)&v->m_value.v);
  if (r < 0) {
    pea_map_insert_ref(arr->m_atom_members,&a,(void**)&v->m_value.v);
    v->m_value.v->m_type = &pea_undefined_type;  
  }

  v->m_type = &pea_variable_type;

  return r;
}

int pea_array_get_attr(pea_interpreter* interpreter,pea_array* arr,pea_atom attr,pea_variable* v) {
  if (attr == pea_atom_add_cs(interpreter,"largo")) {
    v->m_type = &pea_integer_type;
    v->m_value.i = pea_map_count(arr->m_atom_members) + pea_map_count(arr->m_int_members);
    return 0;
  }
  return pea_array_get_atom(interpreter,arr,attr,v);
}

int pea_array_get_int(pea_interpreter* interpreter,pea_array* arr,int i,pea_variable* v) {
  int r;

  r = pea_map_find_ref(arr->m_int_members,&i,(void**)&v->m_value.v);
  if (r < 0) {
    pea_map_insert_ref(arr->m_int_members,&i,(void**)&v->m_value.v);
    v->m_value.v->m_type = &pea_undefined_type;  
  }

  v->m_type = &pea_variable_type;

  return r;
}

pea_enum* pea_array_enum_create(pea_interpreter* interpreter,pea_array* arr) {
  pea_enum* e;

  if (arr == NULL) {
    return NULL;
  }

  e = pea_calloc(interpreter,1,sizeof(struct pea_enum_struct));
  
  e->m_arr = arr;
  e->m_phase = 1;
  e->m_index = 0;

  return e;
}

int pea_array_enum_next(pea_interpreter* interpreter,pea_enum* e,pea_variable* key,pea_variable* value) {
  int           r;
  pea_atom      a;
  int           i;
  pea_variable  t;

  if (e->m_phase == 1) {
    r = pea_map_list(e->m_arr->m_atom_members,e->m_index++,&a,&t);
    if (r) {
      if (key) {
        key->m_type = &pea_atom_type;
        key->m_value.a = a;
      }
      pea_variable_copy(interpreter,value,&t);
    } else {
      e->m_phase = 2;
      e->m_index = 0;
    }
  } 
  if (e->m_phase == 2) {
    r = pea_map_list(e->m_arr->m_int_members,e->m_index++,&i,&t);
    if (r) {
      if (key) {
        key->m_type = &pea_integer_type;
        key->m_value.i = i;
      }
      pea_variable_copy(interpreter,value,&t);
    }
  }
  
  return r;
}

void  pea_array_enum_close(pea_interpreter* interpreter,pea_enum* e) {
  pea_free(interpreter,e);
}

pea_string* pea_array_tostring(pea_interpreter* interpreter,pea_array* arr) {
  pea_stream*   strm;
  pea_string*   res;
  pea_atom      a;
  pea_variable  t;
  int           i;
  int           index;

  if (arr == NULL) {
	  return pea_string_alloc(interpreter,0,"null");
  }

  strm = pea_stream_alloc(interpreter);

  pea_stream_write_cs(interpreter,strm,"array(");

  for(i=0;;i++) {
    if (!pea_map_list(arr->m_atom_members,i,&a,&t)) {
      break;
    }
    if (i) {
      pea_stream_write_cs(interpreter,strm,",");
    }
    pea_stream_write_atom(interpreter,strm,a);
    pea_stream_write_cs(interpreter,strm,"=>");
    pea_stream_write(interpreter,strm,&t);
  }

  for(i=0;;i++) {
    if (!pea_map_list(arr->m_int_members,i,&index,&t)) {
      break;
    }
    if (i) {
      pea_stream_write_cs(interpreter,strm,",");
    }
    pea_stream_write_int(interpreter,strm,index);
    pea_stream_write_cs(interpreter,strm,"=>");
    pea_stream_write(interpreter,strm,&t);
  }

  pea_stream_write_cs(interpreter,strm,")");

  res = pea_stream_tostring(interpreter,strm);

  pea_stream_free(interpreter,strm);

  return res;
}
