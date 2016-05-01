
struct pea_stack_struct {
	ulong	                    m_count;
  ulong                     m_elem_size;
	void*	                    m_vector;
  ulong                     m_page;
  struct pea_stack_struct*  m_prev;
  struct pea_stack_struct*  m_top;
};

pea_stack*	pea_stack_alloc(pea_interpreter* interpreter,ulong elem_size);
void		    pea_stack_free(pea_interpreter* interpreter,pea_stack* stack);
void		    pea_stack_push(pea_stack* stack,void* elem);
int         pea_stack_pop(pea_stack* stack,void* elem);
void		    pea_stack_pop_ex(pea_stack* stack,ulong back,void* elem);
ulong       pea_stack_size(pea_stack* stack);
void		    pea_stack_top(pea_stack* stack,void* elem);
void		    pea_stack_get(pea_stack* stack,ulong index,void* elem);
