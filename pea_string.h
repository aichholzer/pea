
struct pea_string_struct {
  size_t                    length;
  char                      value[4];
};

pea_string* pea_string_alloc(pea_interpreter* interpreter,size_t size,const char* data);
pea_string* pea_string_concat(pea_interpreter* interpreter,pea_string* a,pea_string* b);
void        pea_string_concat_cs(pea_interpreter* interpreter,pea_string* a,const char* b);
void        pea_string_concat_atom(pea_interpreter* interpreter,pea_string* a,pea_atom b);
int         pea_string_compare(pea_string* a,pea_string* b);
int         pea_string_compare_cs(pea_string* a,const char* b);
pea_string* pea_string_urldecode(pea_interpreter* interpreter,pea_string* a);
size_t      pea_string_length(pea_string* string);
ulong       pea_string_get(pea_string* string,char* buff,size_t buffsize);
int         pea_string_write(pea_string* string,FILE* f);
int         pea_string_get_attr(pea_interpreter* interpreter,pea_string* a,pea_atom attr,pea_variable* v);
void        pea_string_init(pea_interpreter* interpreter);
