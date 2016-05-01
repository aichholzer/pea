#include <stdio.h>
#include <stdlib.h>

#include "pea.h"
#include "pea_string.h"
#include "pea_variable.h"

pea_type pea_undefined_type = {PEA_TYPE_UNDEFINED};
pea_type pea_integer_type = {PEA_TYPE_INTEGER};
pea_type pea_string_type = {PEA_TYPE_STRING};
pea_type pea_atom_type = {PEA_TYPE_ATOM};
pea_type pea_variable_type = {PEA_TYPE_VARIABLE};
pea_type pea_array_type = {PEA_TYPE_ARRAY};
pea_type pea_enum_type = {PEA_TYPE_ENUM};
