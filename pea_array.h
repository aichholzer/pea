

typedef struct pea_array_struct {
  pea_map*         m_int_members;
  pea_map*         m_atom_members;
} pea_array;

typedef struct pea_enum_struct {
  pea_array*      m_arr;
  ulong           m_index;
  int             m_phase;
} pea_enum;

pea_array*  pea_array_alloc(pea_interpreter* interpreter);
void        pea_array_append(pea_interpreter* interpreter,pea_array* arr,pea_variable* v);
void        pea_array_set_atom(pea_interpreter* interpreter,pea_array* arr,pea_atom a,pea_variable* v);
void        pea_array_set_int(pea_interpreter* interpreter,pea_array* arr,int i,pea_variable* v);
void        pea_array_get(pea_interpreter* interpreter,pea_array* arr,pea_variable* i,pea_variable* v);
int         pea_array_get_atom(pea_interpreter* interpreter,pea_array* arr,pea_atom a,pea_variable* v);
int         pea_array_get_int(pea_interpreter* interpreter,pea_array* arr,int i,pea_variable* v);
int         pea_array_get_attr(pea_interpreter* interpreter,pea_array* arr,pea_atom a,pea_variable* v);

pea_enum*   pea_array_enum_create(pea_interpreter* interpreter,pea_array* arr);
int         pea_array_enum_next(pea_interpreter* interpreter,pea_enum* e,pea_variable* key,pea_variable* value);
void        pea_array_enum_close(pea_interpreter* interpreter,pea_enum* e);
pea_string* pea_array_tostring(pea_interpreter* interpreter,pea_array* arr);
