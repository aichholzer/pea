#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pea.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_hash.h"
#include "pea_mem.h"
#include "pea_variable.h"

#define ATOM_COUNT 1000
#define ATOM_HASH_SIZE  hashsize(8)
#define ATOM_HASH_MASK  hashmask(8)

typedef struct pea_atom_entry_struct {
  pea_string*                     m_string;
  struct pea_atom_entry_struct*   m_next;
} pea_atom_entry;

pea_atom_entry**  m_atom_hash_table;
pea_atom_entry*   m_atom_table;
pea_atom_entry*   m_first_free_atom;

void pea_atom_init(pea_interpreter* interpreter) {
  int i;

  /*
   * Allocate the atom table, the index into this table is the atom value
   * 
   */
  m_atom_table = pea_malloc(interpreter,sizeof(pea_atom_entry) * ATOM_COUNT);

  /*
   * Link the atom together in a free list
   */ 
  for(i=0;i<(ATOM_COUNT-1);i++) {
    m_atom_table[i].m_next = &m_atom_table[i+1];
  }

  m_first_free_atom = &m_atom_table[0];
  m_atom_table[ATOM_COUNT-1].m_next = NULL;

  /*
   * Allocate the hash table
   */
  m_atom_hash_table = pea_calloc(interpreter,ATOM_HASH_SIZE , sizeof(pea_atom_entry*));


}

pea_atom pea_atom_add(pea_interpreter* interpreter,pea_string* string) {
  ulong           hv;
  pea_atom_entry* ae;
  pea_atom_entry* le;

  hv = hash(string->value,string->length,0) & ATOM_HASH_MASK;
  
  le = ae = m_atom_hash_table[hv];
  while (ae) {
    if (pea_string_compare(ae->m_string,string) == 0) {
      return ae - m_atom_table;
    }
    le = ae;
    ae = ae->m_next;
  }

  ae = m_first_free_atom;
  m_first_free_atom = ae->m_next;

  ae->m_string = string;
  ae->m_next = NULL;

  if (le) {
    le->m_next = ae;
  } else  {
    m_atom_hash_table[hv] = ae;
  }
  
  return ae - m_atom_table;
}

pea_atom pea_atom_add_cs(pea_interpreter* interpreter,const char* string) {
  ulong           hv;
  pea_atom_entry* ae;
  pea_atom_entry* le;

  hv = hash((char*)string,strlen(string),0) & ATOM_HASH_MASK;
  
  le = ae = m_atom_hash_table[hv];
  while (ae) {
    if (pea_string_compare_cs(ae->m_string,string) == 0) {
      return ae - m_atom_table;
    }
    le = ae;
    ae = ae->m_next;
  }

  ae = m_first_free_atom;
  m_first_free_atom = ae->m_next;

  ae->m_string = pea_string_alloc(interpreter,0,string);
  ae->m_next = NULL;

  if (le) {
    le->m_next = ae;
  } else  {
    m_atom_hash_table[hv] = ae;
  }
  
  return ae - m_atom_table;
}

pea_atom pea_atom_concat(pea_interpreter* interpreter,pea_atom a,pea_atom b) {
  NYI;
  return 0;
}

pea_atom pea_atomConcatString(pea_interpreter* interpreter,pea_atom a,const char* string) {
  NYI;
  return 0;
}

ulong pea_atom_length(pea_interpreter* interpreter,pea_atom a) {
  return pea_string_length(m_atom_table[a].m_string);
}

int pea_atom_write(pea_interpreter* interpreter,pea_atom a,FILE* f) {
  return pea_string_write(m_atom_table[a].m_string,f);
}

void pea_atom_tostring(pea_interpreter* interpreter,pea_atom a,pea_variable* v) {
  v->m_type = &pea_string_type;
  v->m_value.s = m_atom_table[a].m_string;
}

ulong pea_atom_get(pea_interpreter* interpreter,pea_atom a,char* d,ulong len) {
  
  if (m_atom_table[a].m_string->length < len) {
    len = m_atom_table[a].m_string->length;
  }
  
  memcpy(d,m_atom_table[a].m_string->value,len);
  
  return len;
}

