
struct pea_map_struct {
  ulong   m_value_size;
  ulong   m_key_size;
  void*   m_vector;
  ulong   m_size;
  ulong   m_count;
};

pea_map* pea_map_alloc(pea_interpreter* interpreter,size_t key_size,size_t elem_size);
void     pea_map_free(pea_interpreter* interpreter,pea_map* map);
void    pea_map_insert(pea_map* map,void* key,void* value);
void    pea_map_insert_ref(pea_map* map,void* key,void** value);
int     pea_map_find(pea_map* map,void* key,void* result);
int     pea_map_find_ref(pea_map* map,void* key,void** result);
int     pea_map_list(pea_map* map,ulong index,void* key,void* result);
ulong   pea_map_count(pea_map* map);
