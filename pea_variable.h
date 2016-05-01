

typedef union pea_value_union {
  unsigned char*              p;  
  pea_string*                 s;
  int                         i;
  pea_atom                    a;
  struct pea_object_struct*   o;
  struct pea_variable_struct* v;
  struct pea_struct_struct*   t;
  struct pea_array_struct*    r;
  struct pea_enum_struct*     e;
} pea_value;

struct pea_variable_struct {
  pea_type*       m_type;
  pea_value       m_value;
};

void	pea_variable_copy(pea_interpreter* interpreter,pea_variable* d,pea_variable* s);
void	pea_variable_assign(pea_interpreter* interpreter,pea_variable* d,pea_variable* s);
int 	pea_variable_compare(pea_interpreter* interpreter,pea_variable* a,pea_variable* b);
void  pea_variable_tovalue(pea_interpreter* interpreter,pea_variable* v);
void  pea_variable_toint(pea_interpreter* interpreter,pea_variable* v);
void  pea_variable_tostring(pea_interpreter* interpreter,pea_variable* v);
void  pea_variable_toobject(pea_interpreter* interpreter,pea_variable* v);
void  pea_variable_toatom(pea_interpreter* interpreter,pea_variable* v);
void  pea_variable_toarray(pea_interpreter* interpreter,pea_variable* v);

ulong pea_variable_stack_size(pea_interpreter* interpreter);
void  pea_variable_stack_push(pea_interpreter* interpreter,pea_variable* v);
void  pea_variable_stack_pop(pea_interpreter* interpreter,pea_variable* v);
void  pea_variable_stack_pop_ex(pea_interpreter* interpreter,pea_variable* v,ulong back);
void  pea_variable_stack_top(pea_interpreter* interpreter,pea_variable* v);
void  pea_variable_stack_push_native(pea_interpreter* interpreter,char type,ulong v);
void  pea_variable_stack_pop_native(pea_interpreter* interpreter,char type,ulong* v);
void  pea_variable_stack_arg_start(pea_interpreter* interpreter,ulong count);
void  pea_variable_stack_arg_next(pea_interpreter* interpreter,pea_variable* v);
