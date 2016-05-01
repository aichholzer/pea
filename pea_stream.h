


typedef struct pea_stream_node_struct {
  ulong   m_typeid;
  void*   m_value;
} pea_stream_node;

struct pea_stream_struct {
  ulong             m_length;
  ulong	            m_size;
  ulong	            m_count;
  pea_stream_node*  m_vector;
};


pea_stream* pea_stream_alloc(pea_interpreter* interpreter);
void        pea_stream_free(pea_interpreter* interpreter,pea_stream* stream);

void pea_stream_write(pea_interpreter* interpreter,pea_stream* stream,pea_variable* v);
void pea_stream_write_atom(pea_interpreter* interpreter,pea_stream* stream,pea_atom a);
void pea_stream_write_string(pea_interpreter* interpreter,pea_stream* stream,pea_string* s);
void pea_stream_write_cs(pea_interpreter* interpreter,pea_stream* stream,const char* s);
void pea_stream_write_int(pea_interpreter* interpreter,pea_stream* stream,int i);

pea_string* pea_stream_tostring(pea_interpreter* interpreter,pea_stream* stream);
