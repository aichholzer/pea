%{
#include <stdio.h>
#include <stdlib.h>

#include "pea.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_segment.h"
#include "pea_class.h"
#include "pea_function.h"
#include "pea_op.h"
#include "pea_stack.h"

// Error reporting function, called then parser find an error
#define yyerror(msg) pea_parser_error(interpreter,msg)

void pea_parser_error(pea_interpreter* interpreter,const char* err)  {
	fprintf(stdout,"%s(%d) : %s\n",interpreter->m_current_file,interpreter->m_current_line,err);
	exit(0);
}

#ifdef _DEBUG
// File to write debug output to
extern FILE* dbgout;

// Change BISON generated code to write to our output file
#undef stderr
#define stderr dbgout

#endif


#define YYPARSE_PARAM	interpreter_p
#define YYLEX_PARAM		interpreter


void pea_parser_init(pea_interpreter* interpreter) {
	pea_string*	s;

	s = pea_string_alloc(interpreter,4,"esto");

	interpreter->m_atom_this = pea_atom_add(interpreter,s);
}

void pea_parser_line(pea_interpreter* interpreter) {

	pea_segment_add(interpreter->m_curr_segment,OP_LINE);
	pea_segment_add(interpreter->m_curr_segment,(ulong)interpreter->m_current_file);
	pea_segment_add(interpreter->m_curr_segment,interpreter->m_current_line);
}

#define interpreter	((pea_interpreter*)interpreter_p)

%}

/*
 * Declare the type to be used during the parsing
 */ 
%union {
	pea_atom		a;
	pea_string*		s;			/* string */
	char			c;			/* char */
	int				i;			/* integer */
	pea_label		label;
}

%pure_parser

%token T_HTML T_INCLUDE
%token T_IF T_ELSE T_SWITCH T_CASE T_DEFAULT T_BREAK T_WHILE T_DO T_FOR T_FUNCTION T_GLOBAL T_CLASS T_FOREACH T_AS T_NEW T_ECHO T_RETURN
%token T_ATOM T_STRING T_INT
%token T_LOGICAL_OR T_LOGICAL_XOR T_LOGICAL_AND
%token T_ADD_ASSIGN T_SUB_ASSIGN T_MUL_ASSIGN T_DIV_ASSIGN T_CONCAT_ASSIGN T_MOD_ASSIGN T_AND_ASSIGN T_OR_ASSIGN T_XOR_ASSIGN
%token T_BOOLEAN_OR T_BOOLEAN_AND
%token T_SL T_SR
%token T_EQ T_NE T_LTE T_GTE T_INC T_DEC T_POINT T_DPOINT T_TRUE T_FALSE

%type <a> T_ATOM
%type <s> T_STRING T_HTML
%type <i> T_INT T_TRUE T_FALSE
%type <label> T_IF T_WHILE T_FOR T_FUNCTION T_DO T_CLASS T_FOREACH T_SWITCH T_CASE
%type <i> optional_else;
%type <i> optional_parameters;
%type <a> foreach_optional_value;
%type <i> optional_default_value optional_arguments optional_ref optional_global;

%right T_ATOM
%left T_LOGICAL_OR
%left T_LOGICAL_XOR
%left T_LOGICAL_AND
%left '=' T_ADD_ASSIGN T_SUB_ASSIGN T_MUL_ASSIGN T_DIV_ASSIGN T_CONCAT_ASSIGN T_MOD_ASSIGN T_AND_ASSIGN T_OR_ASSIGN T_XOR_ASSIGN T_SL_ASSIGN T_SR_ASSIGN
%left '?' ':'
%left T_BOOLEAN_OR
%left T_BOOLEAN_AND
%left '|'
%left '^'
%left '&'
%nonassoc T_EQ T_NE
%nonassoc '<' T_LTE '>' T_GTE
%left '+' '-' '.'
%left '*' '/' '%'
%right '!' '~' T_INC T_DEC
%right '['

%left T_ELSE

%%

main:					/* empty */
						| 
						{ 
							interpreter->m_curr_segment = interpreter->m_main_segment;
						} 
						statement_list {
							size_t offset_func;

							pea_segment_add(interpreter->m_curr_segment,OP_EXIT);

							offset_func = pea_segment_addr(interpreter->m_main_segment);

							// Append the function segment to the main segment
							pea_segment_concat(interpreter->m_main_segment,interpreter->m_func_segment);

							// Offset all function with the size of the main segment
							pea_function_offset(interpreter,offset_func);
							pea_class_offset(interpreter,offset_func);

						}


statement_list:			statement
						| statement_list statement
						;

statement:				T_HTML {
							pea_segment_add(interpreter->m_curr_segment,OP_HTML);
							pea_segment_add_string(interpreter->m_curr_segment,$1);
						}
						| T_INCLUDE '(' expression ')' ';' {
							pea_parser_line(interpreter);
							pea_segment_add(interpreter->m_curr_segment,OP_INCLUDE);	
						}
						| T_ECHO expression ';' {
							// all arguments has pushed it values onto the stack
							
							pea_segment_add(interpreter->m_curr_segment,OP_ECHO);

						}
						| compound_statement
						| expression_statement
						{
							// The expression has placed a value on the stack, pop it
							pea_segment_add(interpreter->m_curr_segment,OP_POP); 
						}
						| selection_statement
						| iteration_statement
						| function_statement
						| global_statement
						| class_statement
						| T_BREAK ';'
						| T_RETURN optional_expression ';' {
							if (interpreter->m_current_function == NULL) {
								fprintf(stdout,"PeA no permite el uso de devuelve fuera de una funcion.\n");
							}

							pea_segment_add(interpreter->m_curr_segment,OP_RETURN);
						}


compound_statement:		'{' '}'
						| '{' statement_list '}'
						;

expression_statement:	';'
						| expression ';' 
						;

optional_else:			/* empty */ {
							$$ = 0;
						}
						| T_ELSE statement {
							$$ = 1;
						}
						;

selection_statement:	
						T_IF '(' expression ')' {
							
							// the result of expression is on the top of the stack
							// Jump if expression is false

							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							$1.l_skip_if = pea_segment_add_label(interpreter->m_curr_segment);

						} statement {

							// Jump past the else statement
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							$1.l_skip_else = pea_segment_add_label(interpreter->m_curr_segment);

							// Let the false jump end up here
							pea_segment_set_label(interpreter->m_curr_segment,$1.l_skip_if);

						} optional_else	{

							//
							// Check if we got an else
							//
							if ($8) {
								pea_segment_set_label(interpreter->m_curr_segment,$1.l_skip_else);

							} else {
								// remove the jump
								pea_segment_backup(interpreter->m_curr_segment,2);

								// Reset the skip_if to end up here now
								pea_segment_set_label(interpreter->m_curr_segment,$1.l_skip_if);
							}	

						}

						| T_SWITCH '(' expression ')' '{' {
							$1.s_breaks = interpreter->m_curr_breaks;
							interpreter->m_curr_breaks = pea_stack_alloc(interpreter,sizeof(size_t));
						} case_statements '}' 
						{
							ulong	pos;

							while(pea_stack_pop(interpreter->m_curr_breaks,&pos)) {

								pea_segment_set_label(interpreter->m_curr_segment,pos);
							}

							pea_stack_free(interpreter,interpreter->m_curr_breaks);

							interpreter->m_curr_breaks = $1.s_breaks;
							
						}
						;

case_statements:		/* empty */
						| case_statement
						| case_statements case_statement

case_statement:			T_CASE expression ':' {

							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_EQ);

							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							$1.l_skip_case = pea_segment_add_label(interpreter->m_curr_segment);
						} statement_list {
							
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							$1.l_break = pea_segment_add_label(interpreter->m_curr_segment);

							// Let the false jump end up here
							pea_segment_set_label(interpreter->m_curr_segment,$1.l_skip_case);
						}
						| T_DEFAULT ':' statement_list

iteration_statement:	T_WHILE {


							// Put a label to get back here when looping
							$1.l_begin_while = pea_segment_addr(interpreter->m_curr_segment);


						} '(' expression ')' {
							
							// the result of expression is on the top of the stack
							// Skip loop code if expression is false
							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							$1.l_skip_while = pea_segment_add_label(interpreter->m_curr_segment);

						} statement {

							// Loop back to beginning of while loop
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							pea_segment_add_offset(interpreter->m_curr_segment,$1.l_begin_while);

							pea_segment_set_label(interpreter->m_curr_segment,$1.l_skip_while);
						}
						| T_DO {

							// Put a label to get back here when looping
							$1.l_begin_do = pea_segment_addr(interpreter->m_curr_segment);

						} statement T_WHILE '(' expression ')' ';' {
						
							// the result of expression is on the top of the stack
							// Loop again if expression is true
							pea_segment_add(interpreter->m_curr_segment,OP_JMP_TRUE);
							pea_segment_add_offset(interpreter->m_curr_segment,$1.l_begin_do);
							
						}
						| T_FOR '(' expression_statement {

							pea_segment_add(interpreter->m_curr_segment,OP_POP);	// expression_statement has put a value on the top of the stack, remove it

							// Put a label to get back here when looping
							$1.l_begin_for = pea_segment_addr(interpreter->m_curr_segment);

						} expression_statement { 

							// the result of expression is on the top of the stack
							// Skip loop code if not true

							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							$1.l_skip_for = pea_segment_add_label(interpreter->m_curr_segment);

							// Write post expression into temp segment
							$1.s_for = interpreter->m_curr_segment;
							interpreter->m_curr_segment = interpreter->m_temp_segment;
							pea_segment_clear(interpreter->m_curr_segment);

						} optional_expression ')' {
						
							// Pop the value of the post expression
							pea_segment_add(interpreter->m_curr_segment,OP_POP);

							// Switch back to current segment
							interpreter->m_curr_segment = $1.s_for;

						} statement {
							
							// Write out the code for the expression
							pea_segment_concat(interpreter->m_curr_segment,interpreter->m_temp_segment);

							// Loop again
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							pea_segment_add_offset(interpreter->m_curr_segment,$1.l_begin_for);
						
							// Put a label for the end of the for
							pea_segment_set_label(interpreter->m_curr_segment,$1.l_skip_for);

						} 
						| T_FOREACH '(' expression T_AS '$' T_ATOM foreach_optional_value ')' {
							
							// Create a Enum from expression
							pea_segment_add(interpreter->m_curr_segment,OP_ENUM_CREATE);

							// Put a label to get back here when looping
							$1.l_begin_for = pea_segment_addr(interpreter->m_curr_segment);
							
							// Get the next element
							pea_segment_add(interpreter->m_curr_segment,OP_ENUM_NEXT);
							
							// Skip statement if no element was found
							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							$1.l_skip_for = pea_segment_add_label(interpreter->m_curr_segment);

							pea_parser_line(interpreter);

							// Assign the key
							if ($7) {
								if (interpreter->m_current_function) {
									pea_segment_add(interpreter->m_curr_segment,OP_LOCAL_VAR);
								} else {
									pea_segment_add(interpreter->m_curr_segment,OP_GLOBAL_VAR);
								}
								pea_segment_add(interpreter->m_curr_segment,$6);

								pea_segment_add(interpreter->m_curr_segment,OP_SWAP);
								pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);

							} 

							pea_segment_add(interpreter->m_curr_segment,OP_POP);

							// Assign the value
							if (interpreter->m_current_function) {
								pea_segment_add(interpreter->m_curr_segment,OP_LOCAL_VAR);
							} else {
								pea_segment_add(interpreter->m_curr_segment,OP_GLOBAL_VAR);
							}
							if ($7) {
								pea_segment_add(interpreter->m_curr_segment,$7);
							} else {
								pea_segment_add(interpreter->m_curr_segment,$6);
							}

							pea_segment_add(interpreter->m_curr_segment,OP_SWAP);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
							
							pea_segment_add(interpreter->m_curr_segment,OP_POP);
						}
						statement
						{
							// Loop again
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							pea_segment_add_offset(interpreter->m_curr_segment,$1.l_begin_for);
						
							// Put a label for the end of the for
							pea_segment_set_label(interpreter->m_curr_segment,$1.l_skip_for);

							// Pop the last values from the stack
							pea_segment_add(interpreter->m_curr_segment,OP_POP);
							pea_segment_add(interpreter->m_curr_segment,OP_POP);
							
							// Close the enum
							pea_segment_add(interpreter->m_curr_segment,OP_ENUM_CLOSE);
						}

foreach_optional_value:	/* empty */ 
						{
							$$ = 0;
						}
						| T_DPOINT '$' T_ATOM {
							$$ = $3;
						}

optional_expression:	/* empty */
						{
							pea_parser_line(interpreter);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,0);
						}
						| expression
						;

function_statement:		T_FUNCTION T_ATOM {
							
							if (interpreter->m_current_function) {
								fprintf(stdout,"PeA no permite declarar funciones dentro de funciones.\n");
								exit(0);
							}

							// Switch to function segment
							$1.s_func = interpreter->m_curr_segment;
							interpreter->m_curr_segment = interpreter->m_func_segment;

							// We are now in a function, switch to local variables
							interpreter->m_current_function = pea_function_alloc(interpreter,interpreter->m_current_class,$2);
							if (interpreter->m_current_function == NULL) {
								yyerror("Redeclare of function");
							}

							// Save the address to this function
							interpreter->m_current_function->m_address = pea_segment_addr(interpreter->m_curr_segment);

						}
						'(' optional_arguments ')' {
							
							// Member functions has a 'this' argument as well
							if (interpreter->m_current_class) {
								
								pea_segment_add(interpreter->m_curr_segment,OP_LOCAL_VAR);
								pea_segment_add(interpreter->m_curr_segment,interpreter->m_atom_this);

								pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN_ARG);

								// Pop the arguments of the stack
								pea_segment_add(interpreter->m_curr_segment,OP_POP_EX);
								pea_segment_add(interpreter->m_curr_segment,$5 + 1);

							} else {

								// Pop the arguments of the stack
								pea_segment_add(interpreter->m_curr_segment,OP_POP_EX);
								pea_segment_add(interpreter->m_curr_segment,$5);
							}

						} compound_statement {
							
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,0);

							pea_segment_add(interpreter->m_curr_segment,OP_RETURN);
						
							// We have now left the function, switch back to global variables
							interpreter->m_current_function = NULL;
						
							// Switch back to current segment
							interpreter->m_curr_segment = $1.s_func;
						}

optional_arguments:		/* empty */
						{
							$$ = 0;
						}
						| argument
						{
							$$ = 1;
						}
						| optional_arguments ',' argument
						{
							$$ = $1 + 1;
						}
						
argument:				optional_ref '$' T_ATOM optional_default_value
						{
							// The function argument is on the stack, just write the value to a local variable
							pea_segment_add(interpreter->m_curr_segment,OP_LOCAL_VAR);
							pea_segment_add(interpreter->m_curr_segment,$3);

							if ($1) {

								if ($4) {
									fprintf(stdout,"Can't have default values for a referenced variable\n");
									exit(0);
								}

								pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN_REF_ARG);

							} else if ($4) {
								pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN_DEF_ARG);
							} else {
								pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN_ARG);
							}

							// Remember the number of arguments to the function
							interpreter->m_current_function->m_argument_count++;
						}

optional_ref:			/* empty */
						{
							$$ = 0;
						}
						| '&'
						{
							$$ = 1;
						}

optional_default_value:	/* empty */
						{
							if (interpreter->m_current_function->m_argument_first_default) {
								yyerror("Must have default value");
							}
							$$ = 0;
						}
						| '=' primary_expression {

							/* after a default valued argument, all arguments need a default value */
							if (interpreter->m_current_function->m_argument_first_default == 0) {
								interpreter->m_current_function->m_argument_first_default = interpreter->m_current_function->m_argument_count;
							}

							/* the expression has pushed in value to the stack */
							$$ = 1;
						}

global_statement:		T_GLOBAL global_vars ';'

global_vars:			global_var
						| global_vars global_var

global_var:				'$' T_ATOM
						{
							pea_function_add_global(interpreter->m_current_function,$2);
						}

class_statement:		T_CLASS T_ATOM {
							if (interpreter->m_current_class) {
								fprintf(stdout,"Can't declare a class inside a class\n");
								exit(0);
							}

							// Switch to function segment
							$1.s_func = interpreter->m_curr_segment;
							interpreter->m_curr_segment = interpreter->m_func_segment;

							// We are now in a class
							interpreter->m_current_class = pea_class_alloc(interpreter,$2);
						}
						compound_statement
						{
							interpreter->m_current_class = NULL;
						
							// Switch back to current segment
							interpreter->m_curr_segment = $1.s_func;
						}


primary_expression:		T_STRING
						{
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_STRING);
							pea_segment_add_string(interpreter->m_curr_segment,$1);
						}
						| T_INT
						{
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,$1);
						}
						| T_TRUE
						{
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
						}
						| T_FALSE
						{
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,0);
						}
						| T_ATOM
						{
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_ATOM);
							pea_segment_add(interpreter->m_curr_segment,$1);
						}
						| '$' optional_global T_ATOM 
						{
							// Check if this variable is local or global
							if ($2 || pea_function_is_global(interpreter->m_current_function,$3)) {
								pea_segment_add(interpreter->m_curr_segment,OP_GLOBAL_VAR);
								pea_segment_add(interpreter->m_curr_segment,$3);
							} else {
								pea_segment_add(interpreter->m_curr_segment,OP_LOCAL_VAR);
								pea_segment_add(interpreter->m_curr_segment,$3);
							}
						}
						| '(' expression ')'
						{
							// expression value is on top of stack, no need to do anything
						}

optional_global:		/* empty */
						{
							$$ = 0;
						} 
						| '_'
						{
							$$ = 1;
						}
postfix_expression:		primary_expression
						{
							// expression value is on top of stack, no need to do anything
						}
/*						| postfix_expression primary_expression
						{							
							// all arguments has pushed it values onto the stack
							
							pea_segment_add(interpreter->m_curr_segment,OP_CALL);
							pea_segment_add(interpreter->m_curr_segment,1); 

						} */
						| postfix_expression '[' expression ']' 
						{
							pea_segment_add(interpreter->m_curr_segment,OP_ARRAY);
						}
						| postfix_expression '(' optional_parameters ')' 
						{
							// all arguments has pushed it values onto the stack
							
							pea_segment_add(interpreter->m_curr_segment,OP_CALL);
							pea_segment_add(interpreter->m_curr_segment,$3); 
						}
						| postfix_expression T_INC 
						{
							pea_segment_add(interpreter->m_curr_segment,OP_PUSH);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
							pea_segment_add(interpreter->m_curr_segment,OP_ADD);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| postfix_expression T_DEC 
						{
							pea_segment_add(interpreter->m_curr_segment,OP_PUSH);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
							pea_segment_add(interpreter->m_curr_segment,OP_SUB);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| postfix_expression T_POINT primary_expression
						{
							pea_parser_line(interpreter);
							pea_segment_add(interpreter->m_curr_segment,OP_MEMBER_VAR);
						}

unary_expression:		postfix_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| T_INC unary_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_PUSH);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
							pea_segment_add(interpreter->m_curr_segment,OP_ADD);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| T_DEC unary_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_PUSH);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
							pea_segment_add(interpreter->m_curr_segment,OP_SUB);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| '+' unary_expression
						{
							/* noting to do */
						}
						| '-' unary_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_NEG);
						}
						| '!' unary_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_LOGICAL_NOT);
						}
						| '~' unary_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_NOT);
						}
						| T_NEW T_ATOM {
							pea_segment_add(interpreter->m_curr_segment,OP_NEW);
							pea_segment_add(interpreter->m_curr_segment,$2);
						}

multiplicative_expression:	unary_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| multiplicative_expression '*' unary_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_MUL);
						}
						| multiplicative_expression '/' unary_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_DIV);
						}
						| multiplicative_expression '%' unary_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_MOD);
						}

additive_expression:	multiplicative_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| additive_expression '+' multiplicative_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_ADD);
						}
						| additive_expression '-' multiplicative_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_SUB);
						}
						| additive_expression '.' multiplicative_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_CONCAT);
						}

shift_expression:		additive_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| shift_expression T_SL additive_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_SL);
						}
						| shift_expression T_SR additive_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_SR);
						}

relational_expression:	shift_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| relational_expression '<' shift_expression
						{
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_LT);
						}
						| relational_expression '>' shift_expression
						{
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_GT);
						}
						| relational_expression T_LTE shift_expression
						{
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_LTE);
						}
						| relational_expression T_GTE shift_expression
						{
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_GTE);
						}

equality_expression:	relational_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| equality_expression T_EQ relational_expression
						{
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_EQ);
						}
						| equality_expression T_NE relational_expression
						{
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_NE);
						}

and_expression:			equality_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| and_expression '&' equality_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_AND);
						}

exclusive_or_expression:	and_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| exclusive_or_expression '^' and_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_XOR);
						}

inclusive_or_expression:	exclusive_or_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| inclusive_or_expression '|' exclusive_or_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_OR);
						}

logical_and_expression:	inclusive_or_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| logical_and_expression T_LOGICAL_AND inclusive_or_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_LOGICAL_AND);
						}

logical_or_expression:	logical_and_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| logical_or_expression T_LOGICAL_OR logical_and_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_LOGICAL_OR);
						}

conditional_expression:	logical_or_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| logical_or_expression '?' expression ':' assignment_expression
						{
							NYI;
  						}

assignment_expression:	conditional_expression
						{
							// expression value is on top of stack, no need to do anything
						}
						| logical_or_expression '=' assignment_expression
						{
							// the value of expression is on the top of the stack
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| logical_or_expression T_ADD_ASSIGN assignment_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_ADD);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| logical_or_expression T_SUB_ASSIGN assignment_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_SUB);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| logical_or_expression T_MUL_ASSIGN assignment_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_MUL);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| logical_or_expression T_DIV_ASSIGN assignment_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_DIV);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| logical_or_expression T_CONCAT_ASSIGN assignment_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_CONCAT);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| logical_or_expression T_MOD_ASSIGN assignment_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_MOD);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| logical_or_expression T_AND_ASSIGN assignment_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_AND);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| logical_or_expression T_OR_ASSIGN assignment_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_OR);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| logical_or_expression T_XOR_ASSIGN assignment_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_XOR);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| logical_or_expression T_SL_ASSIGN assignment_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_SL);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}
						| logical_or_expression T_SR_ASSIGN assignment_expression
						{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_SR);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						}


expression:				assignment_expression
						{
							// expression value is on top of stack, no need to do anything
							pea_parser_line(interpreter);
						}


optional_parameters:	/* empty */
						{	
							$$ = 0; 
						}
						| expression {
							$$ = 1;
						}
						| optional_parameters ',' expression {
							$$ = $1 + 1;
						}


