#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pea.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_class.h"
#include "pea_function.h"
#include "pea_map.h"
#include "pea_mem.h"

pea_map* pea_map_alloc(pea_interpreter* interpreter,size_t key_size,size_t value_size) {
  pea_map* map;
  
  map = pea_calloc(interpreter,1,sizeof(struct pea_map_struct));

  map->m_value_size = value_size;
  map->m_key_size = key_size;
  map->m_size = 50;
  map->m_vector = calloc(map->m_size,map->m_key_size + map->m_value_size);
  
  return map;
}

void pea_map_free(pea_interpreter* interpreter,pea_map* map) {
  pea_free(interpreter,map->m_vector);
  pea_free(interpreter,map);
}

void pea_map_insert(pea_map* map,void* key,void* value) {
  int index;

  index = pea_map_find(map,key,NULL);
  if (index >= 0) {
    memcpy((char*)map->m_vector + index * (map->m_key_size + map->m_value_size) + map->m_key_size,value,map->m_value_size);
    return;
  }

  if (map->m_count >= map->m_size) {
    map->m_size *= 2;

    map->m_vector = realloc(map->m_vector,map->m_size * (map->m_key_size + map->m_value_size));
  }

  memcpy((char*)map->m_vector + map->m_count * (map->m_key_size + map->m_value_size)                  ,key  ,map->m_key_size);
  memcpy((char*)map->m_vector + map->m_count * (map->m_key_size + map->m_value_size) + map->m_key_size,value,map->m_value_size);

  map->m_count++;
}

void pea_map_insert_ref(pea_map* map,void* key,void** value) {
  int index;

  index = pea_map_find_ref(map,key,value);
  if (index >= 0) {
    return;
  }

  if (map->m_count >= map->m_size) {
    map->m_size *= 2;

    map->m_vector = realloc(map->m_vector,map->m_size * (map->m_key_size + map->m_value_size));
  }

  memcpy((char*)map->m_vector + map->m_count * (map->m_key_size + map->m_value_size)                  ,key  ,map->m_key_size);
  
  *value = (char*)map->m_vector + map->m_count * (map->m_key_size + map->m_value_size) + map->m_key_size;

  map->m_count++;
}

int pea_map_find(pea_map* map,void* key,void* result) {
  ulong i;

  for(i=0;i<map->m_count;i++) {
    
    if (memcmp((char*)map->m_vector + i * (map->m_key_size + map->m_value_size),key,map->m_key_size) == 0) {
      
      if (result) {
        memcpy(result,(char*)map->m_vector + i * (map->m_key_size + map->m_value_size) + map->m_key_size,map->m_value_size);
      }
      return i;
    }
  }
  return -1;
}

int pea_map_find_ref(pea_map* map,void* key,void** result) {
  ulong i;

  for(i=0;i<map->m_count;i++) {
    
    if (memcmp((char*)map->m_vector + i * (map->m_key_size + map->m_value_size),key,map->m_key_size) == 0) {
      
      if (result) {
        *result = (char*)map->m_vector + i * (map->m_key_size + map->m_value_size) + map->m_key_size;
      }
      return i;
    }
  }
  return -1;
}

int pea_map_list(pea_map* map,ulong index,void* key,void* value) {
  
  if (index >= map->m_count) {
    return 0;
  }

  if (key) {
    memcpy(key,(char*)map->m_vector + index * (map->m_key_size + map->m_value_size),map->m_key_size);
  }
  if (value) {
    memcpy(value,(char*)map->m_vector + index * (map->m_key_size + map->m_value_size) + map->m_key_size,map->m_value_size);
  }

  return 1;
}

ulong pea_map_count(pea_map* map) {
  return map->m_count;
}
