


typedef struct pea_atom__struct {
  char*     m_name;
  pea_atom  m_atom;
} pea_atom_object;

void          pea_atom_init(pea_interpreter* interpreter);
pea_atom			pea_atom_add(pea_interpreter* interpreter,pea_string* string);
pea_atom			pea_atom_add_cs(pea_interpreter* interpreter,const char* string);
pea_atom			pea_atom_concat(pea_interpreter* interpreter,pea_atom a,pea_atom b);
pea_atom			pea_atom_concat_string(pea_interpreter* interpreter,pea_atom a,pea_string* string);
int		        pea_atom_write(pea_interpreter* interpreter,pea_atom a,FILE* f);
ulong         pea_atom_length(pea_interpreter* interpreter,pea_atom a);
void          pea_atom_tostring(pea_interpreter* interpreter,pea_atom a,pea_variable* v);
ulong         pea_atom_get(pea_interpreter* interpreter,pea_atom a,char* d,ulong len);
