

struct pea_class_struct {
	pea_type    m_type;
  pea_atom    m_name;
  pea_map*    m_functions;
};

pea_class*  pea_class_alloc(pea_interpreter* interpreter,pea_atom name);
pea_class*  pea_class_find(pea_interpreter* interpreter,pea_atom name);
void        pea_class_offset(pea_interpreter* interpreter,ulong offset_func);
