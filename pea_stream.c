#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pea.h"
#include "pea_stream.h"
#include "pea_string.h"
#include "pea_mem.h"
#include "pea_variable.h"
#include "pea_atom.h"

pea_stream* pea_stream_alloc(pea_interpreter* interpreter) {
  pea_stream* strm;

  strm = pea_calloc(interpreter,1,sizeof(struct pea_stream_struct));
  
  strm->m_size = 100;
  strm->m_vector = pea_malloc(interpreter,strm->m_size * sizeof(pea_stream_node));

  return strm;
}

void pea_stream_free(pea_interpreter* interpreter,pea_stream* stream) {
  pea_free(interpreter,stream->m_vector);
  pea_free(interpreter,stream);
}

void pea_stream_write(pea_interpreter* interpreter,pea_stream* stream,pea_variable* v) {
  
  switch(v->m_type->m_type_id) {
  case PEA_TYPE_ATOM:
    pea_stream_write_atom(interpreter,stream,v->m_value.a);
    break;
  case PEA_TYPE_STRING:
    pea_stream_write_string(interpreter,stream,v->m_value.s);
    break;
  default:
    NYI;
  }
}

void pea_stream_write_atom(pea_interpreter* interpreter,pea_stream* stream,pea_atom a) {
  
  if (stream->m_count > stream->m_size) {
    NYI;
  }

  stream->m_length += pea_atom_length(interpreter,a);

  stream->m_vector[stream->m_count].m_typeid = PEA_TYPE_ATOM;
  stream->m_vector[stream->m_count++].m_value = (void*)a;

}

void pea_stream_write_string(pea_interpreter* interpreter,pea_stream* stream,pea_string* s) {
  if (stream->m_count > stream->m_size) {
    NYI;
  }

  stream->m_length += pea_string_length(s);

  stream->m_vector[stream->m_count].m_typeid = PEA_TYPE_STRING;
  stream->m_vector[stream->m_count++].m_value = s;
}

void pea_stream_write_int(pea_interpreter* interpreter,pea_stream* stream,int i) {
  char  buff[32];

  sprintf(buff,"%d",i);

  if (stream->m_count > stream->m_size) {
    NYI;
  }

  stream->m_length += strlen(buff);

  stream->m_vector[stream->m_count].m_typeid = PEA_TYPE_INTEGER;
  stream->m_vector[stream->m_count++].m_value = (void*)i;
}

void pea_stream_write_cs(pea_interpreter* interpreter,pea_stream* stream,const char* s) {
  if (stream->m_count > stream->m_size) {
    NYI;
  }

  stream->m_length += strlen(s);

  stream->m_vector[stream->m_count].m_typeid = PEA_TYPE_CHARSTR;
  stream->m_vector[stream->m_count++].m_value = (void*)s;
}

pea_string* pea_stream_tostring(pea_interpreter* interpreter,pea_stream* stream) {
  pea_string* res;
  char*       d;
  ulong       i,len,t;

  res = pea_string_alloc(interpreter,stream->m_length,NULL);

  len = stream->m_length;
  d = res->value;

  for(i=0;i<stream->m_count;i++) {
    switch(stream->m_vector[i].m_typeid) {
    case PEA_TYPE_ATOM:
      t = pea_atom_get(interpreter,(pea_atom)stream->m_vector[i].m_value,d,len);
      d += t;
      len -= t;
      break;
    case PEA_TYPE_STRING:
      t = pea_string_get((pea_string*)stream->m_vector[i].m_value,d,len);
      d += t;
      len -= t;
      break;
    case PEA_TYPE_CHARSTR:
      t = strlen((const char*)stream->m_vector[i].m_value);
      strncpy(d,(const char*)stream->m_vector[i].m_value,len);
      d += t;
      len -= t;
      break;
    case PEA_TYPE_INTEGER:
      t = sprintf(d,"%d",stream->m_vector[i].m_value);
      d += t;
      len -= t;
      break; 
    }
  }

  return res;
}
