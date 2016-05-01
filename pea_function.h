

struct pea_function_struct {
  pea_type    m_type;
  pea_atom	  m_name;
  size_t      m_address;
  ulong       m_argument_count;
  int         m_argument_first_default;
  pea_map*    m_globals;
  const char* m_args;
  void*       m_func;
  ulong       m_flags;
};

#define PEA_FUNCTION_RELOCATE 1

pea_function*	pea_function_alloc(pea_interpreter* interpreter,pea_class* cls,pea_atom name);
pea_function*	pea_function_alloc_native(pea_interpreter* interpreter,pea_class* cls,const char* name,const char* args,void* func);
pea_function*	pea_function_find(pea_interpreter* interpreter,pea_class* cls,pea_atom name);
void          pea_function_offset(pea_interpreter* interpreter,ulong offset_func);

void          pea_function_add_global(pea_function* func,pea_atom glob);
int           pea_function_is_global(pea_function* func,pea_atom glob);
