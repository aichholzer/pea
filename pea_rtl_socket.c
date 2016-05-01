#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef WIN32
#include <winsock.h>
#else
#include <sys/socket.h>
#endif

#include "pea.h"
#include "pea_op.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_segment.h"
#include "pea_class.h"
#include "pea_function.h"
#include "pea_object.h"
#include "pea_map.h"
#include "pea_stack.h"
#include "pea_variable.h"

int pea_socket(pea_interpreter* interpreter,int af,int type,int protocol) {
  return socket(af,type,protocol);
}

int pea_socketclose(pea_interpreter* interpreter,int s) {
  return 0;
}


int pea_rtl_socket(pea_interpreter* interpreter) {
  pea_function_alloc_native(interpreter,NULL,"zocalo","iiii",pea_socket);
  pea_function_alloc_native(interpreter,NULL,"zocalo_cerrar","ii",pea_socketclose);
  return 0;
}
