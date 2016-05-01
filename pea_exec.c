#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "pea.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_segment.h"
#include "pea_class.h"
#include "pea_function.h"
#include "pea_object.h"
#include "pea_variable.h"
#include "pea_op.h"
#include "pea_array.h"
#include "pea_rtl.h"

#ifdef _DEBUG

// Debug trace file
FILE* dbgout;
#endif

//
// pea_interpreter_exec - executes a byte-coded program
//
void pea_interpreter_exec(pea_interpreter* interpreter,pea_segment* p) {
  unsigned          opcode;
  pea_atom          var;
  unsigned          pos;
  unsigned          l;
  pea_variable      v1;
  pea_variable      v2;
  pea_variable      v3;
  pea_variable      v4;
  pea_function*     func;
  pea_class*        cls;
  char              buff[1024];

  // Loop until exit or end of input
  while(!pea_segment_end(p)) {
    
    opcode = pea_segment_get(p);
    
    pea_print(interpreter,dbgout,"%d(%d) Ejecuta: %s ",pea_segment_pos(p) - 1,pea_variable_stack_size(interpreter),opInfo[opcode].name);
    pea_flush(interpreter,dbgout);

    switch(opcode) {
    case OP_INCLUDE:
      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);

      pea_variable_tostring(interpreter,&v1);

      //
      // FIX: save parsed scripts with starting offset in map in interpreter object
      // If we have read and parsed this script before, reuse the same code
      //

      // Save the current pos
      pos = pea_segment_pos(p);

      // Jump to the new script
      pea_segment_jump(p,pea_segment_addr(p));

      // Locate the file
      v2.m_value.s = pea_searchenv(interpreter,v1.m_value.s,NULL);

      if (v2.m_value.s) {
        pea_string_get(v2.m_value.s,buff,sizeof(buff));

        // Parse the included script
        if (pea_parser_include(interpreter,buff) >= 0) {

          // Execute the new script
          pea_interpreter_exec(interpreter,p);
        }
      } else {
    		pea_print(interpreter,stdout,"%E No puedo incluir el archivo: \"%S\"\n",v1.m_value.s);
      }

      // return back to current pos
      pea_segment_jump(p,pos);

      break;

    case OP_CONST_STRING:

      v1.m_type = &pea_string_type;
      pea_segment_get_string(p,&v1.m_value.s);

      pea_print(interpreter,dbgout,"<%S>",v1.m_value.s);

      pea_variable_stack_push(interpreter,&v1);

      break;
    case OP_CONST_INT:

      v1.m_type = &pea_integer_type;
      v1.m_value.i = pea_segment_get(p);

      pea_print(interpreter,dbgout,"<%d>",v1.m_value.i);

      pea_variable_stack_push(interpreter,&v1);

      break;
    case OP_CONST_ATOM:

      v1.m_type = &pea_atom_type;
      v1.m_value.a = pea_segment_get(p);

      pea_print(interpreter,dbgout,"<%a>",v1.m_value.a);

      pea_variable_stack_push(interpreter,&v1);

      break;

    case OP_COMPARE_GT:
      
      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v2);
      pea_variable_stack_pop(interpreter,&v1);

      v1.m_value.i = pea_variable_compare(interpreter,&v1,&v2) > 0;
      v1.m_type = &pea_integer_type;

      pea_variable_stack_push(interpreter,&v1);
      break;
    case OP_COMPARE_LT:
      
      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v2);
      pea_variable_stack_pop(interpreter,&v1);

      v1.m_value.i = pea_variable_compare(interpreter,&v1,&v2) < 0;
      v1.m_type = &pea_integer_type;

      pea_variable_stack_push(interpreter,&v1);
      break;
    case OP_COMPARE_GTE:
      
      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v2);
      pea_variable_stack_pop(interpreter,&v1);

      v1.m_value.i = pea_variable_compare(interpreter,&v1,&v2) >= 0;
      v1.m_type = &pea_integer_type;

      pea_variable_stack_push(interpreter,&v1);
      break;
    case OP_COMPARE_LTE:
      
      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v2);
      pea_variable_stack_pop(interpreter,&v1);

      v1.m_value.i = pea_variable_compare(interpreter,&v1,&v2) <= 0;
      v1.m_type = &pea_integer_type;

      pea_variable_stack_push(interpreter,&v1);
      break;
    case OP_COMPARE_EQ:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      v1.m_value.i = pea_variable_compare(interpreter,&v1,&v2) == 0;
      v1.m_type = &pea_integer_type;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_COMPARE_NE:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      v1.m_value.i = pea_variable_compare(interpreter,&v1,&v2) != 0;
      v1.m_type = &pea_integer_type;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_JMP_TRUE:

      pos = pea_segment_get(p);
      
      pea_print(interpreter,dbgout,"%d",pos);

      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);
      
      pea_variable_toint(interpreter,&v1);

      if (v1.m_value.i) {
        pea_segment_jump_rel(p,pos);
      }
      break;

    case OP_JMP_FALSE:

      pos = pea_segment_get(p);

      pea_print(interpreter,dbgout,"%d",pos);

      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);
      
      pea_variable_toint(interpreter,&v1);

      if (!v1.m_value.i) {
        pea_segment_jump_rel(p,pos);
      }
      break;

    case OP_JMP:

      pos = pea_segment_get(p);

      pea_print(interpreter,dbgout,"%d",pos);

      pea_segment_jump_rel(p,pos);

      break;

    case OP_READ:

      pea_variable_stack_pop(interpreter,&v1);

      if (v1.m_type->m_type_id != PEA_TYPE_VARIABLE) {
        pea_print(interpreter,dbgout,"No es una variable\n");
        pea_print(interpreter,stdout,"%E No es un tipo de variable");
        v2.m_type = &pea_undefined_type;
      } else {
        pea_variable_copy(interpreter,&v2,v1.m_value.v);
      }

      pea_variable_stack_push(interpreter,&v2);
      break;

    case OP_ASSIGN:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      if (v2.m_type->m_type_id != PEA_TYPE_VARIABLE) {
        pea_print(interpreter,dbgout,"No es una variable\n");
        pea_print(interpreter,stdout,"%E No es un tipo de variable");
      } else {
        pea_variable_assign(interpreter,v2.m_value.v,&v1);
      }

      pea_variable_stack_push(interpreter,&v1);

      break;

    case OP_SWAP:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v2);
      pea_variable_stack_pop(interpreter,&v1);

      pea_variable_stack_push(interpreter,&v2);
      pea_variable_stack_push(interpreter,&v1);

      break;

    case OP_DUP_2:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v2);
      pea_variable_stack_pop(interpreter,&v1);

      pea_variable_stack_push(interpreter,&v1);
      pea_variable_stack_push(interpreter,&v1);
      pea_variable_stack_push(interpreter,&v2);

      break;

    case OP_GLOBAL_VAR:

      var = pea_segment_get(p);

      pea_print(interpreter,dbgout,"<%a>",var);

      pea_globalvar_get(interpreter,var,&v1);

      pea_variable_stack_push(interpreter,&v1);

      break;

    case OP_LOCAL_VAR:

      var = pea_segment_get(p);

      pea_print(interpreter,dbgout,"<%a>",var);

      pea_localvar_get(interpreter,var,&v1);

      pea_variable_stack_push(interpreter,&v1);

      break;

    case OP_MEMBER_VAR:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v2);
      pea_variable_stack_pop(interpreter,&v1);
      
      pea_variable_toobject(interpreter,&v1);
      pea_variable_toatom(interpreter,&v2);

      if (v2.m_type->m_type_id != PEA_TYPE_ATOM) {
        pea_print(interpreter,dbgout,"No es un miembro\n");
        v2.m_type = &pea_undefined_type;
        pea_print(interpreter,stdout,"%E No es un miembro");

      } else if (v1.m_type->m_type_id == PEA_TYPE_CLASS) {

        pea_print(interpreter,dbgout,"<%a>",v2.m_value.a);

        pea_object_var_get(interpreter,v1.m_value.o,&v2,&v1);

      } else if (v1.m_type->m_type_id == PEA_TYPE_ARRAY) {

        pea_print(interpreter,dbgout,"<%a>",v2.m_value.a);

		if (v1.m_value.r == NULL) {
			v2.m_type = &pea_undefined_type;
		} else if (pea_array_get_attr(interpreter,v1.m_value.r,v2.m_value.a,&v1) < 0) {
          pea_print(interpreter,dbgout,"Indice invalido\n");
         pea_print(interpreter,stdout,"%E Indice invalido");
          v2.m_type = &pea_undefined_type;
        }

      } else if (v1.m_type->m_type_id == PEA_TYPE_STRING) {

        pea_print(interpreter,dbgout,"<%a>",v2.m_value.a);

        if (pea_string_get_attr(interpreter,v1.m_value.s,v2.m_value.a,&v1) < 0) {
          pea_print(interpreter,dbgout,"Indice invalido\n");
          pea_print(interpreter,stdout,"%E Indice invalido");
          v2.m_type = &pea_undefined_type;
        }

      } else {
        pea_print(interpreter,dbgout,"No es un objeto\n");
        pea_print(interpreter,stdout,"%E No es un tipo de objeto");
        v2.m_type = &pea_undefined_type;
      } 

      pea_variable_stack_push(interpreter,&v1);

      break;

    case OP_BINARY_OR:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toint(interpreter,&v1);
      pea_variable_toint(interpreter,&v2);

      v1.m_value.i = v2.m_value.i | v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_BINARY_AND:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toint(interpreter,&v1);
      pea_variable_toint(interpreter,&v2);

      v1.m_value.i = v2.m_value.i & v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_BINARY_XOR:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toint(interpreter,&v1);
      pea_variable_toint(interpreter,&v2);

      v1.m_value.i = v2.m_value.i ^ v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_BINARY_SL:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toint(interpreter,&v1);
      pea_variable_toint(interpreter,&v2);

      v1.m_value.i = v2.m_value.i << v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_BINARY_SR:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toint(interpreter,&v1);
      pea_variable_toint(interpreter,&v2);

      v1.m_value.i = v2.m_value.i >> v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_BINARY_NOT:
      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);

      pea_variable_toint(interpreter,&v1);

      v1.m_value.i = ~v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_LOGICAL_AND:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toint(interpreter,&v1);
      pea_variable_toint(interpreter,&v2);

      v1.m_value.i = v2.m_value.i && v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_LOGICAL_OR:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toint(interpreter,&v1);
      pea_variable_toint(interpreter,&v2);

      v1.m_value.i = v2.m_value.i || v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_LOGICAL_NOT:
      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);

      pea_variable_toint(interpreter,&v1);

      v1.m_value.i = !v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_SUB:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toint(interpreter,&v1);
      pea_variable_toint(interpreter,&v2);

      v1.m_value.i = v2.m_value.i - v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_ADD:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toint(interpreter,&v1);
      pea_variable_toint(interpreter,&v2);

      v1.m_value.i = v2.m_value.i + v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_DIV:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toint(interpreter,&v1);
      pea_variable_toint(interpreter,&v2);

      v1.m_value.i = v2.m_value.i / v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_MUL:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toint(interpreter,&v1);
      pea_variable_toint(interpreter,&v2);

      v1.m_value.i = v2.m_value.i * v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_MOD:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toint(interpreter,&v1);
      pea_variable_toint(interpreter,&v2);

      v1.m_value.i = v2.m_value.i % v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);
      break;

    case OP_NEG:
      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);

      pea_variable_toint(interpreter,&v1);

      v1.m_value.i = -v1.m_value.i;

      pea_variable_stack_push(interpreter,&v1);

      break;

    case OP_CONCAT:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_tostring(interpreter,&v1);
      pea_variable_tostring(interpreter,&v2);

      v1.m_value.s = pea_string_concat(interpreter,v2.m_value.s,v1.m_value.s);

      pea_variable_stack_push(interpreter,&v1);
      break;


    case OP_POP:

      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,NULL);
      break;

    case OP_POP_EX:

      // Get the number of arguments to pop
      var = pea_segment_get(p);

      pea_print(interpreter,dbgout,"<%d>",var);

      assert(pea_variable_stack_size(interpreter) >= (ulong)var);

      while(var--) {
        pea_variable_stack_pop(interpreter,NULL);
      }
      break;

    case OP_PUSH:

      pea_variable_stack_pop(interpreter,&v1);

      pea_variable_stack_push(interpreter,&v1);
      pea_variable_stack_push (interpreter,&v1);
      break;

    case OP_EXIT:
      return;

    case OP_HTML:

      v1.m_type = &pea_string_type;
      pea_segment_get_string(p,&v1.m_value.s);

      pea_print(interpreter,stdout,"%S",v1.m_value.s);

      break;

    case OP_CALL:
      
      // Get the number of arguments
      var = pea_segment_get(p);

      assert(pea_variable_stack_size(interpreter) > (ulong)var);

      pea_variable_stack_pop_ex(interpreter,&v1,var);

call_deref:
      switch(v1.m_type->m_type_id) {
      case PEA_TYPE_FUNCTION:
        func = (pea_function*)v1.m_type;

        if (v1.m_value.o) {
          pea_print(interpreter,dbgout,"<obj->%a>",func->m_name);
        } else {
          pea_print(interpreter,dbgout,"<%a>",func->m_name);
        }

        break;
      case PEA_TYPE_ATOM:
        pea_print(interpreter,dbgout,"<%a>",v1.m_value.a);
        func = pea_function_find(interpreter,NULL,v1.m_value.a);
        if (func == NULL) {
			pea_print(interpreter,stdout,"Llamada a funcion no definida: \'%a\'\n",v1.m_value.a);
        }
        break;
      case PEA_TYPE_VARIABLE:
        pea_variable_copy(interpreter,&v1,v1.m_value.v);
        goto call_deref;
      default:
        pea_print(interpreter,stdout,"Llamada a funcion no definida\n");
        func = NULL;
        break;
      } 

      if (func == NULL) {
        v1.m_type = &pea_undefined_type;
        pea_variable_stack_push(interpreter,&v1);
        break;
      } 


      // Call native function
      if (func->m_func) {
        ulong arg_count;
        ulong return_val;
        ulong arg1;
        ulong arg2;
        ulong arg3;
        ulong arg4;

        if (func->m_args[1] == 'v') {

          // Push this if an member function
          if (v1.m_type->m_type_id == PEA_TYPE_FUNCTION && v1.m_value.o) {
            v2.m_type = (pea_type*)v1.m_value.o->m_class;
            v2.m_value.o = v1.m_value.o;

            // push this
            pea_variable_stack_push(interpreter,&v2);

            var++;
          }

          // Variable number of arguments
          return_val = ((PFN_NATIVE_V)func->m_func)(interpreter,var);
  
        } else {

          arg_count = strlen(&func->m_args[1]);
        
          if (v1.m_type->m_type_id == PEA_TYPE_FUNCTION && v1.m_value.o) {
            var++;
          }

          if (arg_count != (ulong)var) {

            if (arg_count < (ulong)var) {
			        pea_print(interpreter,stdout,"%E Demasiados parametros para la funcion: %a()",func->m_name);

              while (func->m_argument_count < (ulong)var) {
    
                pea_variable_stack_pop(interpreter,NULL);
          
                var--;
              }

            } else {
              while (arg_count > (ulong)var) {
    
                v2.m_type = &pea_undefined_type;
                pea_variable_stack_push(interpreter,&v2);
          
                var++;
              }
            }
          }

          // Push this if an member function
          if (v1.m_type->m_type_id == PEA_TYPE_FUNCTION && v1.m_value.o) {
            v2.m_type = (pea_type*)v1.m_value.o->m_class;
            v2.m_value.o = v1.m_value.o;

            // push this
            pea_variable_stack_push(interpreter,&v2);
          }

          switch(arg_count) {
          case 0:
            return_val = ((PFN_NATIVE_0)func->m_func)(interpreter);
            break;
          case 1:

            pea_variable_stack_pop_native(interpreter,func->m_args[1],&arg1);
          
            return_val = ((PFN_NATIVE_1)func->m_func)(interpreter,arg1);
            break;
          case 2:

            pea_variable_stack_pop_native(interpreter,func->m_args[2],&arg2);
            pea_variable_stack_pop_native(interpreter,func->m_args[1],&arg1);
          
            return_val = ((PFN_NATIVE_2)func->m_func)(interpreter,arg1,arg2);
            break;
          case 3:

            pea_variable_stack_pop_native(interpreter,func->m_args[3],&arg3);
            pea_variable_stack_pop_native(interpreter,func->m_args[2],&arg2);
            pea_variable_stack_pop_native(interpreter,func->m_args[1],&arg1);
          
            return_val = ((PFN_NATIVE_3)func->m_func)(interpreter,arg1,arg2,arg3);
            break;
          case 4:

            pea_variable_stack_pop_native(interpreter,func->m_args[4],&arg4);
            pea_variable_stack_pop_native(interpreter,func->m_args[3],&arg3);
            pea_variable_stack_pop_native(interpreter,func->m_args[2],&arg2);
            pea_variable_stack_pop_native(interpreter,func->m_args[1],&arg1);
          
            return_val = ((PFN_NATIVE_4)func->m_func)(interpreter,arg1,arg2,arg3,arg4);
            break;
          default:
            NYI;
          }
        }

        pea_variable_stack_push_native(interpreter,func->m_args[0],return_val);
        
      } else {

        if (func->m_argument_count < (ulong)var) {
			pea_print(interpreter,stdout,"%E Demasiados parametros para la funcion: %a()",func->m_name);

          while (func->m_argument_count < (ulong)var) {
    
            pea_variable_stack_pop(interpreter,NULL);
          
            var--;
          }

        } else {

          if (var < func->m_argument_first_default) {
			  pea_print(interpreter,stdout,"%E Faltan parametros para la funcion: %a()",func->m_name);
          }

          while (func->m_argument_count > (ulong)var) {
    
            v2.m_type = &pea_undefined_type;
            pea_variable_stack_push(interpreter,&v2);
          
            var++;
          }
        }

        // Push this if an member function
        if (v1.m_type->m_type_id == PEA_TYPE_FUNCTION && v1.m_value.o) {
          v2.m_type = (pea_type*)v1.m_value.o->m_class;
          v2.m_value.o = v1.m_value.o;

          // push this
          pea_variable_stack_push(interpreter,&v2);

          var++;
        }

        // Mark the start of the arguments on the value stack
        pea_variable_stack_arg_start(interpreter,var);

        // Create a new frame of local variables
        pea_localvar_push(interpreter);

        // Push current position
        pea_call_stack_push(interpreter,pea_segment_pos(p));

        // goto the function
        pea_segment_jump(p,func->m_address);
      }
      
      break;

    case OP_RETURN:

      l = pea_call_stack_pop(interpreter);

      // goto the position we had before the call
      pea_segment_jump(p,l);

      // Drop all local variables
      pea_localvar_clear(interpreter);
      break;

    case OP_ENUM_CREATE:

      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);

      pea_variable_toarray(interpreter,&v1);

      if (v1.m_type->m_type_id != PEA_TYPE_ARRAY) {
        pea_print(interpreter,dbgout,"No es un arreglo\n");
        pea_print(interpreter,stdout,"%E No es un tipo de arreglo");
        v2.m_type = &pea_undefined_type;
      } else {
        v2.m_value.e = pea_array_enum_create(interpreter,v1.m_value.r);
        if (v2.m_value.e) {
          v2.m_type = &pea_enum_type;
        } else {
          v2.m_type = &pea_undefined_type;
        }
      }

      pea_variable_stack_push(interpreter,&v2);

      break;
    case OP_ENUM_NEXT:

      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);

      if (v1.m_type->m_type_id != PEA_TYPE_ENUM) {
		  pea_print(interpreter,dbgout,"No es una enumeracion\n");
        v2.m_type = &pea_undefined_type;
        v3.m_type = &pea_undefined_type;
        v4.m_type = &pea_integer_type;
        v4.m_value.i = 0;
      } else {

        v4.m_type = &pea_integer_type;
        v4.m_value.i = pea_array_enum_next(interpreter,v1.m_value.e,&v3,&v2);
  
      }

      pea_variable_stack_push(interpreter,&v1);
      pea_variable_stack_push(interpreter,&v2);
      pea_variable_stack_push(interpreter,&v3);
      pea_variable_stack_push(interpreter,&v4);

      break;
    case OP_ENUM_CLOSE:
      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);
      if (v1.m_type->m_type_id != PEA_TYPE_ENUM) {
        pea_print(interpreter,dbgout,"No es una enumeracion\n");
      } else {
        
        pea_array_enum_close(interpreter,v1.m_value.e);

      }

      break;
    case OP_ARRAY:
      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_toarray(interpreter,&v2);
      if (v2.m_type->m_type_id != PEA_TYPE_ARRAY) {
        pea_print(interpreter,dbgout,"No es un arreglo\n");
        pea_print(interpreter,stdout,"%E No es un tipo de arreglo");
        v2.m_type = &pea_undefined_type;
      } else {

        if (v2.m_value.r != NULL) {
          pea_array_get(interpreter,v2.m_value.r,&v1,&v2);
        } else {
          v2.m_type = &pea_undefined_type;
        }
      }

      pea_variable_stack_push(interpreter,&v2);

      break;
    case OP_LINE:
      interpreter->m_current_file = (char*)pea_segment_get(p);
      interpreter->m_current_line = pea_segment_get(p);
      pea_print(interpreter,dbgout," %d",interpreter->m_current_line);
      break;
    case OP_NEW:

      var = pea_segment_get(p);

      cls = pea_class_find(interpreter,var);
      if (cls == NULL) {
		  pea_print(interpreter,stdout,"%E Clase desconocida: %a\n",var);
        v2.m_type = &pea_undefined_type;
      } else {

        v2.m_type = (pea_type*)cls;
        v2.m_value.o = pea_object_alloc(interpreter,cls);
      }

      pea_variable_stack_push(interpreter,&v2);

      break;
    case OP_ECHO:
      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);

      pea_variable_tostring(interpreter,&v1);

      if (v1.m_type->m_type_id != PEA_TYPE_STRING) {
        pea_print(interpreter,dbgout,"No es una cadena\n");
      } else {
        pea_string_write(v1.m_value.s,stdout);
      }

      break;
    case OP_ASSIGN_ARG:
      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);

      pea_variable_stack_arg_next(interpreter,&v2);

      if (v1.m_type->m_type_id != PEA_TYPE_VARIABLE) {
        pea_print(interpreter,dbgout,"No es una variable\n");
        pea_print(interpreter,stdout,"%E No es un tipo de variable");
      } else {
        pea_variable_copy(interpreter,v1.m_value.v,&v2);
      }

      break;
    case OP_ASSIGN_REF_ARG:
      assert(pea_variable_stack_size(interpreter) > 0);

      pea_variable_stack_pop(interpreter,&v1);

      pea_variable_stack_arg_next(interpreter,&v2);

      if (v1.m_type->m_type_id != PEA_TYPE_VARIABLE) {
        pea_print(interpreter,dbgout,"No es una variable\n");
        pea_print(interpreter,stdout,"%E No es un tipo de variable");
      } else if (v1.m_type->m_type_id != PEA_TYPE_VARIABLE) {        
        pea_print(interpreter,dbgout,"No es una variable\n");
        pea_print(interpreter,stdout,"%E No es un tipo de variable");
      } else {
        v1.m_value.v->m_type = &pea_variable_type;
        v1.m_value.v->m_value.v = v2.m_value.v;
      }

      break;
    case OP_ASSIGN_DEF_ARG:

      assert(pea_variable_stack_size(interpreter) > 1);

      pea_variable_stack_pop(interpreter,&v1);
      pea_variable_stack_pop(interpreter,&v2);

      pea_variable_stack_arg_next(interpreter,&v3);

      if (v1.m_type->m_type_id != PEA_TYPE_VARIABLE) {
        pea_print(interpreter,dbgout,"No es una variable\n");
        pea_print(interpreter,stdout,"%E No es un tipo de variable");
      } else {
        if (v3.m_type->m_type_id == PEA_TYPE_UNDEFINED) {
          pea_variable_copy(interpreter,v1.m_value.v,&v2);
        } else {
          pea_variable_copy(interpreter,v1.m_value.v,&v3);
        }
      }

      break;
    default:
		pea_print(interpreter,stdout,"Codigo-byte no soportado: %x\n",opcode);
      exit(1);
    }

    pea_print(interpreter,dbgout,"\n");
  }
}

