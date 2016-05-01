#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pea.h"
#include "pea_mem.h"

void* pea_malloc(pea_interpreter* interpreter,size_t size) {
	return malloc(size);
}

void* pea_calloc(pea_interpreter* interpreter,size_t size,size_t count) {
	return calloc(size,count);
}

void pea_free(pea_interpreter* interpreter,void* mem) {
	free(mem);
}
