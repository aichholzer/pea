
int pea_rtl_lang(pea_interpreter* interpreter);

int pea_rtl_cgi(pea_interpreter* interpreter,char** env);

int pea_rtl_db(pea_interpreter* interpreter);

int pea_rtl_io(pea_interpreter* interpreter);
pea_string* pea_realpath(pea_interpreter* interpreter,pea_string* file);
pea_string* pea_dirname(pea_interpreter* interpreter,pea_string* file);
pea_string* pea_searchenv(pea_interpreter* interpreter,pea_string* file,pea_string* path);

int pea_rtl_socket(pea_interpreter* interpreter);
