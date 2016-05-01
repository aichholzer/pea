#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#ifndef WIN32
#include <sys/param.h>
#else
#define MIN min
#endif

#include "pea.h"
#include "pea_string.h"
#include "pea_mem.h"
#include "pea_atom.h"
#include "pea_variable.h"
#include "pea_class.h"
#include "pea_function.h"
#include "pea_map.h"
#include "pea_object.h"
#include "pea_array.h"

pea_class*    cls_string;
pea_function* pfn_substr;
pea_function* pfn_explode;

pea_string* pea_string_alloc(pea_interpreter* interpreter,size_t size,const char* data) {
  pea_string*   r;

  if (data && !size) {
    size = strlen(data);
  }

  r = pea_malloc(interpreter,sizeof(struct pea_string_struct) + size + 1);

  r->length = size;

  if (data) {
    memcpy(r->value,data,size);
  }
  r->value[size] = 0;

  return r;
}

pea_string* pea_string_concat(pea_interpreter* interpreter,pea_string* a,pea_string* b) {
  pea_string*   r;
  ulong         size;

  size = a->length + b->length;

  r = pea_malloc(interpreter,sizeof(struct pea_string_struct) + size + 1);
  r->length = size;

  memcpy(r->value,a->value,a->length);
  memcpy(r->value + a->length,b->value,b->length);
  r->value[size] = 0;

  return r;
}

size_t pea_string_length(pea_string* string) {
  return string->length;
}

ulong pea_string_get(pea_string* string,char* buff,size_t buffsize) {
  unsigned l;
  
  l = MIN(buffsize,string->length);

  memcpy(buff,string->value,l);
  
  buff += l;

  buff[0] = 0;

  return l;
}

int pea_string_write(pea_string* string,FILE* f) {
  int wlen = 0;

  fwrite(string->value,string->length,1,f);

  return wlen;
}

int pea_string_compare(pea_string* a,pea_string* b) {
  return strcmp(a->value,b->value);
}

int pea_string_compare_cs(pea_string* a,const char* b) {
  return strcmp(a->value,b);
}

int pea_string_get_attr(pea_interpreter* interpreter,pea_string* a,pea_atom attr,pea_variable* v) {
  
  /*
   * Check if this is a member function
   */
  if (pea_map_find(cls_string->m_functions,&attr,&v->m_type) >= 0) {
    v->m_value.o = (pea_object*)a;
    return 1;
  }

  if (attr == pea_atom_add_cs(interpreter,"largo")) {
    v->m_type = &pea_integer_type;
    v->m_value.i = a->length;
    return 0;
  }
  return -1;
}

pea_string* pea_string_urldecode(pea_interpreter* interpreter,pea_string* a) {
  pea_string* r;

  // Allocate a new string of the same size, urldecode will shrink the string
  r = pea_malloc(interpreter,sizeof(struct pea_string_struct) + a->length + 1);

  r->length = pea_urldecode(a->value,r->value,r->length);

  return r;
}

pea_string* pea_string_substr(pea_interpreter* interpreter,int start,int length,pea_string* a) {
  ulong l;

  if (start < 0) {
    start = a->length + start;
  }
  if (length == 0) {
    length = a->length;
  }

  if ((ulong)start > a->length) {
    return pea_string_alloc(interpreter,0,NULL);
  }

  l = MIN(a->length - (ulong)start,(ulong)length);

  return pea_string_alloc(interpreter,l,&a->value[start]);
}

pea_array* pea_string_explode(pea_interpreter* interpreter,pea_string* delim,int limit,pea_string* a) {
  pea_array*    r;
  char*         s;
  ulong         l;
  pea_variable  v;
  char*         ts;
  ulong         tl;
  ulong         index = 0;
  ulong         m;

  // Allocate the result array
  r = pea_array_alloc(interpreter);

  // Init the array element type
  v.m_type = &pea_string_type;

  // Get the string data to explode
  s = a->value;
  l = a->length;
  
  // Start with a empty substring
  ts = s;
  tl = 0;

  // Scan until end of string
  while(l) {

    // Quick check, string will not match delimiter
    if (*s != delim->value[0]) {
      s++;
      l--;
      tl++;
      continue;
    }

    // Match whole delimiter
    m = 0;
    while(delim->value[m] && s[m] == delim->value[m] && m < l) {
      m++;
    }

    // If more delimiter chars, no match
    if (delim->value[m]) {
      s++;
      l--;
      tl++;
      continue;
    }

    // Set the array value
    v.m_value.s = pea_string_alloc(interpreter,tl,ts);

    // Add to the array
    pea_array_set_int(interpreter,r,index++,&v);

    // Skip past the matched delimiter
    s += m;
    l -= m;

    // Start again with a new substring
    ts = s;
    tl = 0;
  
    // Check for limit of number of exploded substrings
    if (limit) {
      limit--;
      if (!limit) {
        // Last substring is the rest of the string
        tl = l;
        break;
      }
    }
  }

  // Set rest of string to the array
  if (tl) {
    v.m_value.s = pea_string_alloc(interpreter,tl,ts);

    // Add to the array
    pea_array_set_int(interpreter,r,index++,&v);
  }

  return r;
}

void pea_string_init(pea_interpreter* interpreter) {
  
  cls_string = pea_class_alloc(interpreter,pea_atom_add_cs(interpreter,"cadena"));

  pfn_substr = pea_function_alloc_native(interpreter,cls_string,"subcadena","siin",pea_string_substr);
  pfn_explode = pea_function_alloc_native(interpreter,cls_string,"corte","rsin",pea_string_explode);

}
