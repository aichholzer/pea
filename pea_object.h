
typedef struct pea_object_struct {
	pea_class*  m_class;
  pea_map*    m_members;
} pea_object;

pea_object* pea_object_alloc(pea_interpreter* interpreter,pea_class* cls);
void        pea_object_var_get(pea_interpreter* interpreter,pea_object* obj,pea_variable* var,pea_variable* value);
