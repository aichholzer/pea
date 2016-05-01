%{

%}
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pea.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_segment.h"
#include "pea_parse.h"

#define YY_SKIP_YYWRAP 1
#define YY_ALWAYS_INTERACTIVE	1

int yywrap()  {
	return 1;
}

void unescape(char* s) {
	char*	d = s;

	while(*s) {
		if (*s == '\\') {
			switch(s[1]) {
			case 'n':
				*d++='\n';
				s+=2;
				break;
			case '\"':
				*d++='\"';
				s+=2;
				break;
			case '\'':
				*d++='\'';
				s+=2;
				break;
			case 'r':
				*d++='\r';
				s+=2;
				break;
			case '\\':
				*d++=*s++;
				s+=2;
				break;
			case '0':
				*d++=0;
				s+=2;
				break;				
			default:
				*d++=*s++;
				break;
			}
		} else {
			*d++ = *s++;
		}
	}
	*d=0;
}

int count_newlines(char* s) {
	int r = 0;

	while(*s) {
		if (*s == '\n') {
			r++;
		}
		s++;
	}

	return r;
}

#define YY_DECL int yylex(YYSTYPE* yylval,pea_interpreter* interpreter)

%}

WS		[ \t\v\n\f\r]
NAME	[a-zA-Z\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*
D		[0-9]

%x	ST_HTML
%x	ST_SCRIPT

%%

<INITIAL>([^<]|"<"[^?]){1,400} {
	interpreter->m_current_line += count_newlines(yytext);
	yylval->s = pea_string_alloc(interpreter,yyleng,yytext);
	return T_HTML;
}

<INITIAL>"<?"	{
	BEGIN(ST_SCRIPT);
}

<ST_SCRIPT>"?>" {
	BEGIN(INITIAL);
}

<ST_SCRIPT>"/*"([^\*]|\*[^/])*"*/" { 	
	interpreter->m_current_line += count_newlines(yytext); 
}

<ST_SCRIPT>(\/\/)+[^\n]* {}

<ST_SCRIPT>"escribe"		{ return T_ECHO; }
<ST_SCRIPT>"nuevo"		{ return T_NEW; }
<ST_SCRIPT>"si"			{ return T_IF; }
<ST_SCRIPT>"o"			{ return T_ELSE; }
<ST_SCRIPT>"mientras"		{ return T_WHILE; }
<ST_SCRIPT>"para"		{ return T_FOR; }
<ST_SCRIPT>"cadauno"		{ return T_FOREACH; }
<ST_SCRIPT>"como"		{ return T_AS; }
<ST_SCRIPT>"hacer"		{ return T_DO; }
<ST_SCRIPT>"cambio"		{ return T_SWITCH; }
<ST_SCRIPT>"caso"		{ return T_CASE; }
<ST_SCRIPT>"predet"		{ return T_DEFAULT; }
<ST_SCRIPT>"rompe"		{ return T_BREAK; }
<ST_SCRIPT>"funcion"		{ return T_FUNCTION; }
<ST_SCRIPT>"global"		{ return T_GLOBAL; }
<ST_SCRIPT>"clase"		{ return T_CLASS; }
<ST_SCRIPT>"incluir"		{ return T_INCLUDE; }
<ST_SCRIPT>"devuelve"		{ return T_RETURN; }
<ST_SCRIPT>"verdad"		{ return T_TRUE; }
<ST_SCRIPT>"falso"		{ return T_FALSE; }

<ST_SCRIPT>"=="			{ return T_EQ; }
<ST_SCRIPT>"!="			{ return T_NE; }
 
<ST_SCRIPT>"<="			{ return T_LTE; }
<ST_SCRIPT>">="			{ return T_GTE; }

<ST_SCRIPT>"+="			{ return T_ADD_ASSIGN; }
<ST_SCRIPT>"-="			{ return T_SUB_ASSIGN; }
<ST_SCRIPT>"*="			{ return T_MUL_ASSIGN; }
<ST_SCRIPT>"/="			{ return T_DIV_ASSIGN; }
<ST_SCRIPT>".="			{ return T_CONCAT_ASSIGN; }
<ST_SCRIPT>"%="			{ return T_MOD_ASSIGN; }
<ST_SCRIPT>"&="			{ return T_AND_ASSIGN; }
<ST_SCRIPT>"|="			{ return T_OR_ASSIGN; }
<ST_SCRIPT>"^="			{ return T_XOR_ASSIGN; }
<ST_SCRIPT>"<<="		{ return T_SL_ASSIGN; }
<ST_SCRIPT>">>="		{ return T_SR_ASSIGN; }

<ST_SCRIPT>"<<"			{ return T_SL; }
<ST_SCRIPT>">>"			{ return T_SR; }

<ST_SCRIPT>"&&"			{ return T_LOGICAL_AND; }
<ST_SCRIPT>"||"			{ return T_LOGICAL_OR; }

<ST_SCRIPT>"--"			{ return T_DEC; }
<ST_SCRIPT>"++"			{ return T_INC; }

<ST_SCRIPT>"->"			{ return T_POINT; }
<ST_SCRIPT>"=>"			{ return T_DPOINT; }

<ST_SCRIPT>{D}+	{ 
	yylval->i = atoi(yytext);
	return T_INT; 
}

<ST_SCRIPT>\"(\\.|[^\\"])*\" {
	yytext[yyleng-1] = 0;
	unescape(yytext);
	yylval->s = pea_string_alloc(interpreter,0,yytext+1);
	return T_STRING;
}

<ST_SCRIPT>\'(\\.|[^\\'])*\' {
	yytext[yyleng-1] = 0;
	unescape(yytext);
	yylval->s = pea_string_alloc(interpreter,0,yytext+1);
	return T_STRING;
}

<ST_SCRIPT>{NAME}	{
	yylval->s = pea_string_alloc(interpreter,yyleng,yytext);
	yylval->a = pea_atom_add(interpreter,yylval->s);
	return T_ATOM;
}

<ST_SCRIPT>{WS}	{ /* eat white space */ interpreter->m_current_line += count_newlines(yytext);  }

<ST_SCRIPT>.	{	/* return the special char to the parser */
	return yytext[0];
}


%%

int pea_parser_include(pea_interpreter* interpreter,const char* file) {

	yyin = fopen(file,"r");
	if (yyin == NULL) {
		pea_print(interpreter,stdout,"%E No puedo incluir el archivo: \"%s\"\n",file);
		return -1;
	}

	yyrestart(yyin);

	interpreter->m_current_file = (char*)file;
	interpreter->m_current_line = 1;
	
	BEGIN(INITIAL);

	yyparse(interpreter);

	fclose(yyin);

	return 0;
}

int pea_eval(pea_interpreter* interpreter,char* buff) {
	YY_BUFFER_STATE buffer;
	ulong			pos;

	buffer = yy_scan_string(buff);

	interpreter->m_current_file = "(eval)";
	interpreter->m_current_line = 1;
	
	BEGIN(ST_SCRIPT);

	// Save the current pos
	pos = pea_segment_pos(interpreter->m_main_segment);

	// Jump to the new script
	pea_segment_jump(interpreter->m_main_segment,pea_segment_addr(interpreter->m_main_segment));

	yyparse(interpreter);

	// Execute the new script
	pea_interpreter_exec(interpreter,interpreter->m_main_segment);

	// return back to current pos
	pea_segment_jump(interpreter->m_main_segment,pos);

	return 0;
}
