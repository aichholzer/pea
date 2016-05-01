

void* pea_malloc(pea_interpreter* interpreter,size_t size);
void* pea_calloc(pea_interpreter* interpreter,size_t size,size_t count);
void* pea_realloc(pea_interpreter* interpreter,void* mem,size_t size);
void pea_free(pea_interpreter* interpreter,void* mem);
