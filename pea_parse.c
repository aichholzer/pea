
/*  A Bison parser, made from pea_parse.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	T_HTML	257
#define	T_INCLUDE	258
#define	T_IF	259
#define	T_ELSE	260
#define	T_SWITCH	261
#define	T_CASE	262
#define	T_DEFAULT	263
#define	T_BREAK	264
#define	T_WHILE	265
#define	T_DO	266
#define	T_FOR	267
#define	T_FUNCTION	268
#define	T_GLOBAL	269
#define	T_CLASS	270
#define	T_FOREACH	271
#define	T_AS	272
#define	T_NEW	273
#define	T_ECHO	274
#define	T_RETURN	275
#define	T_ATOM	276
#define	T_STRING	277
#define	T_INT	278
#define	T_LOGICAL_OR	279
#define	T_LOGICAL_XOR	280
#define	T_LOGICAL_AND	281
#define	T_ADD_ASSIGN	282
#define	T_SUB_ASSIGN	283
#define	T_MUL_ASSIGN	284
#define	T_DIV_ASSIGN	285
#define	T_CONCAT_ASSIGN	286
#define	T_MOD_ASSIGN	287
#define	T_AND_ASSIGN	288
#define	T_OR_ASSIGN	289
#define	T_XOR_ASSIGN	290
#define	T_BOOLEAN_OR	291
#define	T_BOOLEAN_AND	292
#define	T_SL	293
#define	T_SR	294
#define	T_EQ	295
#define	T_NE	296
#define	T_LTE	297
#define	T_GTE	298
#define	T_INC	299
#define	T_DEC	300
#define	T_POINT	301
#define	T_DPOINT	302
#define	T_TRUE	303
#define	T_FALSE	304
#define	T_SL_ASSIGN	305
#define	T_SR_ASSIGN	306

#line 1 "pea_parse.y"

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


#line 59 "pea_parse.y"
typedef union {
	pea_atom		a;
	pea_string*		s;			/* string */
	char			c;			/* char */
	int				i;			/* integer */
	pea_label		label;
} YYSTYPE;
#ifndef YYDEBUG
#define YYDEBUG 1
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		251
#define	YYFLAG		-32768
#define	YYNTBASE	79

#define YYTRANSLATE(x) ((unsigned)(x) <= 306 ? yytranslate[x] : 133)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    67,     2,     2,    75,    66,    58,     2,    70,
    71,    64,    61,    76,    62,    63,    65,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    55,    72,    59,
    51,    60,    54,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    69,     2,    78,    57,    77,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    73,    56,    74,    68,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    52,    53
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     2,     5,     7,    10,    12,    18,    22,    24,
    26,    28,    30,    32,    34,    36,    39,    43,    46,    50,
    52,    55,    56,    59,    60,    61,    70,    71,    80,    81,
    83,    86,    87,    93,    97,    98,    99,   107,   108,   117,
   118,   119,   120,   131,   132,   143,   144,   148,   149,   151,
   152,   153,   162,   163,   165,   169,   174,   175,   177,   178,
   181,   185,   187,   190,   193,   194,   199,   201,   203,   205,
   207,   209,   213,   217,   218,   220,   222,   227,   232,   235,
   238,   242,   244,   247,   250,   253,   256,   259,   262,   265,
   267,   271,   275,   279,   281,   285,   289,   293,   295,   299,
   303,   305,   309,   313,   317,   321,   323,   327,   331,   333,
   337,   339,   343,   345,   349,   351,   355,   357,   361,   363,
   369,   371,   375,   379,   383,   387,   391,   395,   399,   403,
   407,   411,   415,   419,   421,   422,   424
};

static const short yyrhs[] = {    -1,
     0,    80,    81,     0,    82,     0,    81,    82,     0,     3,
     0,     4,    70,   131,    71,    72,     0,    20,   131,    72,
     0,    83,     0,    84,     0,    86,     0,    93,     0,   103,
     0,   110,     0,   113,     0,    10,    72,     0,    21,   102,
    72,     0,    73,    74,     0,    73,    81,    74,     0,    72,
     0,   131,    72,     0,     0,     6,    82,     0,     0,     0,
     5,    70,   131,    71,    87,    82,    88,    85,     0,     0,
     7,    70,   131,    71,    73,    89,    90,    74,     0,     0,
    91,     0,    90,    91,     0,     0,     8,   131,    55,    92,
    81,     0,     9,    55,    81,     0,     0,     0,    11,    94,
    70,   131,    71,    95,    82,     0,     0,    12,    96,    82,
    11,    70,   131,    71,    72,     0,     0,     0,     0,    13,
    70,    84,    97,    84,    98,   102,    71,    99,    82,     0,
     0,    17,    70,   131,    18,    75,    22,   101,    71,   100,
    82,     0,     0,    48,    75,    22,     0,     0,   131,     0,
     0,     0,    14,    22,   104,    70,   106,    71,   105,    83,
     0,     0,   107,     0,   106,    76,   107,     0,   108,    75,
    22,   109,     0,     0,    58,     0,     0,    51,   115,     0,
    15,   111,    72,     0,   112,     0,   111,   112,     0,    75,
    22,     0,     0,    16,    22,   114,    83,     0,    23,     0,
    24,     0,    49,     0,    50,     0,    22,     0,    75,   116,
    22,     0,    70,   131,    71,     0,     0,    77,     0,   115,
     0,   117,    69,   131,    78,     0,   117,    70,   132,    71,
     0,   117,    45,     0,   117,    46,     0,   117,    47,   115,
     0,   117,     0,    45,   118,     0,    46,   118,     0,    61,
   118,     0,    62,   118,     0,    67,   118,     0,    68,   118,
     0,    19,    22,     0,   118,     0,   119,    64,   118,     0,
   119,    65,   118,     0,   119,    66,   118,     0,   119,     0,
   120,    61,   119,     0,   120,    62,   119,     0,   120,    63,
   119,     0,   120,     0,   121,    39,   120,     0,   121,    40,
   120,     0,   121,     0,   122,    59,   121,     0,   122,    60,
   121,     0,   122,    43,   121,     0,   122,    44,   121,     0,
   122,     0,   123,    41,   122,     0,   123,    42,   122,     0,
   123,     0,   124,    58,   123,     0,   124,     0,   125,    57,
   124,     0,   125,     0,   126,    56,   125,     0,   126,     0,
   127,    27,   126,     0,   127,     0,   128,    25,   127,     0,
   128,     0,   128,    54,   131,    55,   130,     0,   129,     0,
   128,    51,   130,     0,   128,    28,   130,     0,   128,    29,
   130,     0,   128,    30,   130,     0,   128,    31,   130,     0,
   128,    32,   130,     0,   128,    33,   130,     0,   128,    34,
   130,     0,   128,    35,   130,     0,   128,    36,   130,     0,
   128,    52,   130,     0,   128,    53,   130,     0,   130,     0,
     0,   131,     0,   132,    76,   131,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   109,   110,   114,   131,   132,   135,   139,   143,   149,   150,
   155,   156,   157,   158,   159,   160,   161,   170,   171,   174,
   175,   178,   181,   186,   195,   204,   222,   225,   241,   242,
   243,   245,   252,   260,   262,   269,   276,   284,   289,   297,
   304,   317,   325,   338,   389,   405,   409,   413,   419,   422,
   443,   464,   478,   482,   486,   491,   516,   520,   525,   532,
   543,   545,   546,   548,   553,   567,   575,   580,   585,   590,
   595,   600,   611,   616,   620,   624,   636,   640,   647,   655,
   663,   669,   673,   681,   689,   693,   697,   701,   705,   710,
   714,   718,   722,   727,   731,   735,   739,   744,   748,   752,
   757,   761,   766,   771,   776,   782,   786,   791,   797,   801,
   806,   810,   815,   819,   824,   828,   833,   837,   842,   846,
   851,   855,   860,   866,   872,   878,   884,   890,   896,   902,
   908,   914,   920,   928,   935,   939,   942
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","T_HTML",
"T_INCLUDE","T_IF","T_ELSE","T_SWITCH","T_CASE","T_DEFAULT","T_BREAK","T_WHILE",
"T_DO","T_FOR","T_FUNCTION","T_GLOBAL","T_CLASS","T_FOREACH","T_AS","T_NEW",
"T_ECHO","T_RETURN","T_ATOM","T_STRING","T_INT","T_LOGICAL_OR","T_LOGICAL_XOR",
"T_LOGICAL_AND","T_ADD_ASSIGN","T_SUB_ASSIGN","T_MUL_ASSIGN","T_DIV_ASSIGN",
"T_CONCAT_ASSIGN","T_MOD_ASSIGN","T_AND_ASSIGN","T_OR_ASSIGN","T_XOR_ASSIGN",
"T_BOOLEAN_OR","T_BOOLEAN_AND","T_SL","T_SR","T_EQ","T_NE","T_LTE","T_GTE","T_INC",
"T_DEC","T_POINT","T_DPOINT","T_TRUE","T_FALSE","'='","T_SL_ASSIGN","T_SR_ASSIGN",
"'?'","':'","'|'","'^'","'&'","'<'","'>'","'+'","'-'","'.'","'*'","'/'","'%'",
"'!'","'~'","'['","'('","')'","';'","'{'","'}'","'$'","','","'_'","']'","main",
"@1","statement_list","statement","compound_statement","expression_statement",
"optional_else","selection_statement","@2","@3","@4","case_statements","case_statement",
"@5","iteration_statement","@6","@7","@8","@9","@10","@11","@12","foreach_optional_value",
"optional_expression","function_statement","@13","@14","optional_arguments",
"argument","optional_ref","optional_default_value","global_statement","global_vars",
"global_var","class_statement","@15","primary_expression","optional_global",
"postfix_expression","unary_expression","multiplicative_expression","additive_expression",
"shift_expression","relational_expression","equality_expression","and_expression",
"exclusive_or_expression","inclusive_or_expression","logical_and_expression",
"logical_or_expression","conditional_expression","assignment_expression","expression",
"optional_parameters", NULL
};
#endif

static const short yyr1[] = {     0,
    79,    80,    79,    81,    81,    82,    82,    82,    82,    82,
    82,    82,    82,    82,    82,    82,    82,    83,    83,    84,
    84,    85,    85,    87,    88,    86,    89,    86,    90,    90,
    90,    92,    91,    91,    94,    95,    93,    96,    93,    97,
    98,    99,    93,   100,    93,   101,   101,   102,   102,   104,
   105,   103,   106,   106,   106,   107,   108,   108,   109,   109,
   110,   111,   111,   112,   114,   113,   115,   115,   115,   115,
   115,   115,   115,   116,   116,   117,   117,   117,   117,   117,
   117,   118,   118,   118,   118,   118,   118,   118,   118,   119,
   119,   119,   119,   120,   120,   120,   120,   121,   121,   121,
   122,   122,   122,   122,   122,   123,   123,   123,   124,   124,
   125,   125,   126,   126,   127,   127,   128,   128,   129,   129,
   130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
   130,   130,   130,   131,   132,   132,   132
};

static const short yyr2[] = {     0,
     0,     0,     2,     1,     2,     1,     5,     3,     1,     1,
     1,     1,     1,     1,     1,     2,     3,     2,     3,     1,
     2,     0,     2,     0,     0,     8,     0,     8,     0,     1,
     2,     0,     5,     3,     0,     0,     7,     0,     8,     0,
     0,     0,    10,     0,    10,     0,     3,     0,     1,     0,
     0,     8,     0,     1,     3,     4,     0,     1,     0,     2,
     3,     1,     2,     2,     0,     4,     1,     1,     1,     1,
     1,     3,     3,     0,     1,     1,     4,     4,     2,     2,
     3,     1,     2,     2,     2,     2,     2,     2,     2,     1,
     3,     3,     3,     1,     3,     3,     3,     1,     3,     3,
     1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
     1,     3,     1,     3,     1,     3,     1,     3,     1,     5,
     1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     1,     0,     1,     3
};

static const short yydefact[] = {     2,
     0,     6,     0,     0,     0,     0,    35,    38,     0,     0,
     0,     0,     0,     0,     0,    48,    71,    67,    68,     0,
     0,    69,    70,     0,     0,     0,     0,     0,    20,     0,
    74,     3,     4,     9,    10,    11,    12,    13,    14,    15,
    76,    82,    90,    94,    98,   101,   106,   109,   111,   113,
   115,   117,   119,   121,   134,     0,     0,     0,     0,    16,
     0,     0,     0,    50,     0,     0,    62,    65,     0,    89,
     0,     0,    49,    83,    84,    85,    86,    87,    88,     0,
    18,     0,    75,     0,     5,    79,    80,     0,     0,   135,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    21,     0,     0,     0,     0,     0,    40,     0,
    64,    61,    63,     0,     0,     8,    17,    73,    19,    72,
    81,     0,   136,     0,    91,    92,    93,    95,    96,    97,
    99,   100,   104,   105,   102,   103,   107,   108,   110,   112,
   114,   116,   118,   123,   124,   125,   126,   127,   128,   129,
   130,   131,   122,   132,   133,     0,     0,    24,     0,     0,
     0,     0,    53,    66,     0,    77,    78,     0,     0,     7,
     0,    27,    36,     0,    41,    58,     0,    54,     0,     0,
   137,   120,    25,    29,     0,     0,    48,    51,    57,     0,
    46,    22,     0,     0,     0,    30,    37,     0,     0,     0,
    55,    59,     0,     0,     0,    26,     0,     0,    28,    31,
    39,    42,    52,     0,    56,     0,    44,    23,    32,    34,
     0,    60,    47,     0,     0,    43,    45,    33,     0,     0,
     0
};

static const short yydefgoto[] = {   249,
     1,    32,    33,    34,    35,   226,    36,   191,   212,   204,
   215,   216,   245,    37,    61,   205,    62,   182,   207,   241,
   244,   224,    72,    38,   130,   220,   197,   198,   199,   235,
    39,    66,    67,    40,   134,    41,    84,    42,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
    55,    56,   144
};

static const short yypact[] = {    15,
   288,-32768,   -41,   -29,    -6,    23,-32768,-32768,    13,    21,
    -9,    83,    38,    94,   320,   320,-32768,-32768,-32768,   320,
   320,-32768,-32768,   320,   320,   320,   320,   320,-32768,   116,
    40,   288,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   -36,-32768,    16,    -7,    35,     8,    45,    60,    65,
    69,   107,   216,-32768,-32768,    70,   320,   320,   320,-32768,
    71,   288,    39,-32768,   121,     4,-32768,-32768,   320,-32768,
    72,    73,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    75,
-32768,   215,-32768,   126,-32768,-32768,-32768,   -10,   320,   320,
   320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
   320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
   320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
   320,   320,-32768,    78,    79,    80,   320,   141,-32768,    84,
-32768,-32768,-32768,    85,   135,-32768,-32768,-32768,-32768,-32768,
-32768,    77,-32768,   -27,-32768,-32768,-32768,    16,    16,    16,
    -7,    -7,    35,    35,    35,    35,     8,     8,    45,    60,
    65,    69,   107,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   101,    88,-32768,    90,    86,
    97,    39,   -16,-32768,    89,-32768,-32768,   320,   320,-32768,
   288,-32768,-32768,   320,-32768,-32768,   -23,-32768,    93,   147,
-32768,-32768,-32768,    82,   288,    99,   320,-32768,   113,   150,
   127,   168,   320,   124,    -1,-32768,-32768,   108,   110,    85,
-32768,   134,   112,   123,   288,-32768,   137,   288,-32768,-32768,
-32768,-32768,-32768,   -10,-32768,   174,-32768,-32768,-32768,   288,
   288,-32768,-32768,   288,   288,-32768,-32768,   288,   197,   198,
-32768
};

static const short yypgoto[] = {-32768,
-32768,   -28,   -32,  -128,   -58,-32768,-32768,-32768,-32768,-32768,
-32768,   -13,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    -8,-32768,-32768,-32768,-32768,    -5,-32768,-32768,
-32768,-32768,   139,-32768,-32768,   -87,-32768,-32768,    11,     3,
    -4,   -30,     9,    98,   100,   103,   105,   102,-32768,-32768,
   -93,   -12,-32768
};


#define	YYLAST		395


static const short yytable[] = {    85,
   141,    82,    71,    73,   129,   184,   213,   214,    86,    87,
    88,    17,    18,    19,    -1,    80,   164,   165,   166,   167,
   168,   169,   170,   171,   172,   173,   174,   175,    57,   128,
    74,    75,    89,    90,    76,    77,    78,    79,    22,    23,
    58,   196,    64,   187,   124,   125,   126,   208,   188,    85,
    99,   100,   209,    94,    95,    96,   135,    14,   -57,    28,
    17,    18,    19,    59,    31,    65,   101,   102,   153,   154,
   155,   156,   229,    97,    98,   132,   142,   143,    65,    91,
    92,    93,    63,    20,    21,   103,   104,    22,    23,   213,
   214,   233,   151,   152,    60,   202,   148,   149,   150,    24,
    25,   145,   146,   147,    68,    26,    27,    69,    28,   176,
    29,   157,   158,    31,   180,    70,    83,   105,     2,     3,
     4,   106,     5,   195,   107,     6,     7,     8,     9,    10,
    11,    12,    13,   108,    14,    15,    16,    17,    18,    19,
   127,   123,   131,   136,   137,   138,   242,   140,   177,   178,
   179,   181,   185,   183,   186,   189,   193,    30,   203,   190,
    20,    21,   192,   200,    22,    23,   194,   210,   211,   218,
   196,   222,   217,   225,   223,   201,    24,    25,   228,   231,
   232,   206,    26,    27,   234,    28,   236,    29,    30,    81,
    31,   239,   238,   237,    73,   243,   250,   251,   219,   240,
   227,   230,   159,   221,   133,   160,     0,    85,   246,   161,
   163,   247,   162,     0,     0,    85,   248,     2,     3,     4,
     0,     5,     0,     0,     6,     7,     8,     9,    10,    11,
    12,    13,     0,    14,    15,    16,    17,    18,    19,     0,
   109,     0,     0,   110,   111,   112,   113,   114,   115,   116,
   117,   118,     0,     0,     0,     0,     0,     0,     0,    20,
    21,     0,     0,    22,    23,     0,   119,   120,   121,   122,
     0,     0,     0,     0,     0,    24,    25,     0,     0,     0,
     0,    26,    27,     0,    28,     0,    29,    30,   139,    31,
     2,     3,     4,     0,     5,     0,     0,     6,     7,     8,
     9,    10,    11,    12,    13,     0,    14,    15,    16,    17,
    18,    19,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    20,    21,     0,     0,    22,    23,    14,     0,
     0,    17,    18,    19,     0,     0,     0,     0,    24,    25,
     0,     0,     0,     0,    26,    27,     0,    28,     0,    29,
    30,     0,    31,     0,    20,    21,     0,     0,    22,    23,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    24,    25,     0,     0,     0,     0,    26,    27,     0,    28,
     0,     0,     0,     0,    31
};

static const short yycheck[] = {    32,
    88,    30,    15,    16,    63,   134,     8,     9,    45,    46,
    47,    22,    23,    24,     0,    28,   110,   111,   112,   113,
   114,   115,   116,   117,   118,   119,   120,   121,    70,    62,
    20,    21,    69,    70,    24,    25,    26,    27,    49,    50,
    70,    58,    22,    71,    57,    58,    59,    71,    76,    82,
    43,    44,    76,    61,    62,    63,    69,    19,    75,    70,
    22,    23,    24,    70,    75,    75,    59,    60,    99,   100,
   101,   102,    74,    39,    40,    72,    89,    90,    75,    64,
    65,    66,    70,    45,    46,    41,    42,    49,    50,     8,
     9,   220,    97,    98,    72,   189,    94,    95,    96,    61,
    62,    91,    92,    93,    22,    67,    68,    70,    70,   122,
    72,   103,   104,    75,   127,    22,    77,    58,     3,     4,
     5,    57,     7,   182,    56,    10,    11,    12,    13,    14,
    15,    16,    17,    27,    19,    20,    21,    22,    23,    24,
    70,    72,    22,    72,    72,    71,   234,    22,    71,    71,
    71,    11,    18,    70,    78,    55,    71,    73,   191,    72,
    45,    46,    73,    75,    49,    50,    70,    75,    22,    71,
    58,    22,   205,     6,    48,   188,    61,    62,    55,    72,
    71,   194,    67,    68,    51,    70,    75,    72,    73,    74,
    75,    55,   225,    71,   207,    22,     0,     0,   207,   228,
   213,   215,   105,   209,    66,   106,    -1,   240,   241,   107,
   109,   244,   108,    -1,    -1,   248,   245,     3,     4,     5,
    -1,     7,    -1,    -1,    10,    11,    12,    13,    14,    15,
    16,    17,    -1,    19,    20,    21,    22,    23,    24,    -1,
    25,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
    46,    -1,    -1,    49,    50,    -1,    51,    52,    53,    54,
    -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
    -1,    67,    68,    -1,    70,    -1,    72,    73,    74,    75,
     3,     4,     5,    -1,     7,    -1,    -1,    10,    11,    12,
    13,    14,    15,    16,    17,    -1,    19,    20,    21,    22,
    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    45,    46,    -1,    -1,    49,    50,    19,    -1,
    -1,    22,    23,    24,    -1,    -1,    -1,    -1,    61,    62,
    -1,    -1,    -1,    -1,    67,    68,    -1,    70,    -1,    72,
    73,    -1,    75,    -1,    45,    46,    -1,    -1,    49,    50,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    61,    62,    -1,    -1,    -1,    -1,    67,    68,    -1,    70,
    -1,    -1,    -1,    -1,    75
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/local/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 2:
#line 111 "pea_parse.y"
{ 
							interpreter->m_curr_segment = interpreter->m_main_segment;
						;
    break;}
case 3:
#line 114 "pea_parse.y"
{
							size_t offset_func;

							pea_segment_add(interpreter->m_curr_segment,OP_EXIT);

							offset_func = pea_segment_addr(interpreter->m_main_segment);

							// Append the function segment to the main segment
							pea_segment_concat(interpreter->m_main_segment,interpreter->m_func_segment);

							// Offset all function with the size of the main segment
							pea_function_offset(interpreter,offset_func);
							pea_class_offset(interpreter,offset_func);

						;
    break;}
case 6:
#line 135 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_HTML);
							pea_segment_add_string(interpreter->m_curr_segment,yyvsp[0].s);
						;
    break;}
case 7:
#line 139 "pea_parse.y"
{
							pea_parser_line(interpreter);
							pea_segment_add(interpreter->m_curr_segment,OP_INCLUDE);	
						;
    break;}
case 8:
#line 143 "pea_parse.y"
{
							// all arguments has pushed it values onto the stack
							
							pea_segment_add(interpreter->m_curr_segment,OP_ECHO);

						;
    break;}
case 10:
#line 151 "pea_parse.y"
{
							// The expression has placed a value on the stack, pop it
							pea_segment_add(interpreter->m_curr_segment,OP_POP); 
						;
    break;}
case 17:
#line 161 "pea_parse.y"
{
							if (interpreter->m_current_function == NULL) {
								fprintf(stdout,"PeA no permite el uso de devuelve fuera de una funcion.\n");
							}

							pea_segment_add(interpreter->m_curr_segment,OP_RETURN);
						;
    break;}
case 22:
#line 178 "pea_parse.y"
{
							yyval.i = 0;
						;
    break;}
case 23:
#line 181 "pea_parse.y"
{
							yyval.i = 1;
						;
    break;}
case 24:
#line 187 "pea_parse.y"
{
							
							// the result of expression is on the top of the stack
							// Jump if expression is false

							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							yyvsp[-3].label.l_skip_if = pea_segment_add_label(interpreter->m_curr_segment);

						;
    break;}
case 25:
#line 195 "pea_parse.y"
{

							// Jump past the else statement
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							yyvsp[-5].label.l_skip_else = pea_segment_add_label(interpreter->m_curr_segment);

							// Let the false jump end up here
							pea_segment_set_label(interpreter->m_curr_segment,yyvsp[-5].label.l_skip_if);

						;
    break;}
case 26:
#line 204 "pea_parse.y"
{

							//
							// Check if we got an else
							//
							if (yyvsp[0].i) {
								pea_segment_set_label(interpreter->m_curr_segment,yyvsp[-7].label.l_skip_else);

							} else {
								// remove the jump
								pea_segment_backup(interpreter->m_curr_segment,2);

								// Reset the skip_if to end up here now
								pea_segment_set_label(interpreter->m_curr_segment,yyvsp[-7].label.l_skip_if);
							}	

						;
    break;}
case 27:
#line 222 "pea_parse.y"
{
							yyvsp[-4].label.s_breaks = interpreter->m_curr_breaks;
							interpreter->m_curr_breaks = pea_stack_alloc(interpreter,sizeof(size_t));
						;
    break;}
case 28:
#line 226 "pea_parse.y"
{
							ulong	pos;

							while(pea_stack_pop(interpreter->m_curr_breaks,&pos)) {

								pea_segment_set_label(interpreter->m_curr_segment,pos);
							}

							pea_stack_free(interpreter,interpreter->m_curr_breaks);

							interpreter->m_curr_breaks = yyvsp[-7].label.s_breaks;
							
						;
    break;}
case 32:
#line 245 "pea_parse.y"
{

							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_EQ);

							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							yyvsp[-2].label.l_skip_case = pea_segment_add_label(interpreter->m_curr_segment);
						;
    break;}
case 33:
#line 252 "pea_parse.y"
{
							
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							yyvsp[-4].label.l_break = pea_segment_add_label(interpreter->m_curr_segment);

							// Let the false jump end up here
							pea_segment_set_label(interpreter->m_curr_segment,yyvsp[-4].label.l_skip_case);
						;
    break;}
case 35:
#line 262 "pea_parse.y"
{


							// Put a label to get back here when looping
							yyvsp[0].label.l_begin_while = pea_segment_addr(interpreter->m_curr_segment);


						;
    break;}
case 36:
#line 269 "pea_parse.y"
{
							
							// the result of expression is on the top of the stack
							// Skip loop code if expression is false
							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							yyvsp[-4].label.l_skip_while = pea_segment_add_label(interpreter->m_curr_segment);

						;
    break;}
case 37:
#line 276 "pea_parse.y"
{

							// Loop back to beginning of while loop
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							pea_segment_add_offset(interpreter->m_curr_segment,yyvsp[-6].label.l_begin_while);

							pea_segment_set_label(interpreter->m_curr_segment,yyvsp[-6].label.l_skip_while);
						;
    break;}
case 38:
#line 284 "pea_parse.y"
{

							// Put a label to get back here when looping
							yyvsp[0].label.l_begin_do = pea_segment_addr(interpreter->m_curr_segment);

						;
    break;}
case 39:
#line 289 "pea_parse.y"
{
						
							// the result of expression is on the top of the stack
							// Loop again if expression is true
							pea_segment_add(interpreter->m_curr_segment,OP_JMP_TRUE);
							pea_segment_add_offset(interpreter->m_curr_segment,yyvsp[-7].label.l_begin_do);
							
						;
    break;}
case 40:
#line 297 "pea_parse.y"
{

							pea_segment_add(interpreter->m_curr_segment,OP_POP);	// expression_statement has put a value on the top of the stack, remove it

							// Put a label to get back here when looping
							yyvsp[-2].label.l_begin_for = pea_segment_addr(interpreter->m_curr_segment);

						;
    break;}
case 41:
#line 304 "pea_parse.y"
{ 

							// the result of expression is on the top of the stack
							// Skip loop code if not true

							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							yyvsp[-4].label.l_skip_for = pea_segment_add_label(interpreter->m_curr_segment);

							// Write post expression into temp segment
							yyvsp[-4].label.s_for = interpreter->m_curr_segment;
							interpreter->m_curr_segment = interpreter->m_temp_segment;
							pea_segment_clear(interpreter->m_curr_segment);

						;
    break;}
case 42:
#line 317 "pea_parse.y"
{
						
							// Pop the value of the post expression
							pea_segment_add(interpreter->m_curr_segment,OP_POP);

							// Switch back to current segment
							interpreter->m_curr_segment = yyvsp[-7].label.s_for;

						;
    break;}
case 43:
#line 325 "pea_parse.y"
{
							
							// Write out the code for the expression
							pea_segment_concat(interpreter->m_curr_segment,interpreter->m_temp_segment);

							// Loop again
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							pea_segment_add_offset(interpreter->m_curr_segment,yyvsp[-9].label.l_begin_for);
						
							// Put a label for the end of the for
							pea_segment_set_label(interpreter->m_curr_segment,yyvsp[-9].label.l_skip_for);

						;
    break;}
case 44:
#line 338 "pea_parse.y"
{
							
							// Create a Enum from expression
							pea_segment_add(interpreter->m_curr_segment,OP_ENUM_CREATE);

							// Put a label to get back here when looping
							yyvsp[-7].label.l_begin_for = pea_segment_addr(interpreter->m_curr_segment);
							
							// Get the next element
							pea_segment_add(interpreter->m_curr_segment,OP_ENUM_NEXT);
							
							// Skip statement if no element was found
							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							yyvsp[-7].label.l_skip_for = pea_segment_add_label(interpreter->m_curr_segment);

							pea_parser_line(interpreter);

							// Assign the key
							if (yyvsp[-1].a) {
								if (interpreter->m_current_function) {
									pea_segment_add(interpreter->m_curr_segment,OP_LOCAL_VAR);
								} else {
									pea_segment_add(interpreter->m_curr_segment,OP_GLOBAL_VAR);
								}
								pea_segment_add(interpreter->m_curr_segment,yyvsp[-2].a);

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
							if (yyvsp[-1].a) {
								pea_segment_add(interpreter->m_curr_segment,yyvsp[-1].a);
							} else {
								pea_segment_add(interpreter->m_curr_segment,yyvsp[-2].a);
							}

							pea_segment_add(interpreter->m_curr_segment,OP_SWAP);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
							
							pea_segment_add(interpreter->m_curr_segment,OP_POP);
						;
    break;}
case 45:
#line 389 "pea_parse.y"
{
							// Loop again
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							pea_segment_add_offset(interpreter->m_curr_segment,yyvsp[-9].label.l_begin_for);
						
							// Put a label for the end of the for
							pea_segment_set_label(interpreter->m_curr_segment,yyvsp[-9].label.l_skip_for);

							// Pop the last values from the stack
							pea_segment_add(interpreter->m_curr_segment,OP_POP);
							pea_segment_add(interpreter->m_curr_segment,OP_POP);
							
							// Close the enum
							pea_segment_add(interpreter->m_curr_segment,OP_ENUM_CLOSE);
						;
    break;}
case 46:
#line 406 "pea_parse.y"
{
							yyval.a = 0;
						;
    break;}
case 47:
#line 409 "pea_parse.y"
{
							yyval.a = yyvsp[0].a;
						;
    break;}
case 48:
#line 414 "pea_parse.y"
{
							pea_parser_line(interpreter);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,0);
						;
    break;}
case 50:
#line 422 "pea_parse.y"
{
							
							if (interpreter->m_current_function) {
								fprintf(stdout,"PeA no permite declarar funciones dentro de funciones.\n");
								exit(0);
							}

							// Switch to function segment
							yyvsp[-1].label.s_func = interpreter->m_curr_segment;
							interpreter->m_curr_segment = interpreter->m_func_segment;

							// We are now in a function, switch to local variables
							interpreter->m_current_function = pea_function_alloc(interpreter,interpreter->m_current_class,yyvsp[0].a);
							if (interpreter->m_current_function == NULL) {
								yyerror("Redeclare of function");
							}

							// Save the address to this function
							interpreter->m_current_function->m_address = pea_segment_addr(interpreter->m_curr_segment);

						;
    break;}
case 51:
#line 443 "pea_parse.y"
{
							
							// Member functions has a 'this' argument as well
							if (interpreter->m_current_class) {
								
								pea_segment_add(interpreter->m_curr_segment,OP_LOCAL_VAR);
								pea_segment_add(interpreter->m_curr_segment,interpreter->m_atom_this);

								pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN_ARG);

								// Pop the arguments of the stack
								pea_segment_add(interpreter->m_curr_segment,OP_POP_EX);
								pea_segment_add(interpreter->m_curr_segment,yyvsp[-1].i + 1);

							} else {

								// Pop the arguments of the stack
								pea_segment_add(interpreter->m_curr_segment,OP_POP_EX);
								pea_segment_add(interpreter->m_curr_segment,yyvsp[-1].i);
							}

						;
    break;}
case 52:
#line 464 "pea_parse.y"
{
							
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,0);

							pea_segment_add(interpreter->m_curr_segment,OP_RETURN);
						
							// We have now left the function, switch back to global variables
							interpreter->m_current_function = NULL;
						
							// Switch back to current segment
							interpreter->m_curr_segment = yyvsp[-7].label.s_func;
						;
    break;}
case 53:
#line 479 "pea_parse.y"
{
							yyval.i = 0;
						;
    break;}
case 54:
#line 483 "pea_parse.y"
{
							yyval.i = 1;
						;
    break;}
case 55:
#line 487 "pea_parse.y"
{
							yyval.i = yyvsp[-2].i + 1;
						;
    break;}
case 56:
#line 492 "pea_parse.y"
{
							// The function argument is on the stack, just write the value to a local variable
							pea_segment_add(interpreter->m_curr_segment,OP_LOCAL_VAR);
							pea_segment_add(interpreter->m_curr_segment,yyvsp[-1].a);

							if (yyvsp[-3].i) {

								if (yyvsp[0].i) {
									fprintf(stdout,"Can't have default values for a referenced variable\n");
									exit(0);
								}

								pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN_REF_ARG);

							} else if (yyvsp[0].i) {
								pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN_DEF_ARG);
							} else {
								pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN_ARG);
							}

							// Remember the number of arguments to the function
							interpreter->m_current_function->m_argument_count++;
						;
    break;}
case 57:
#line 517 "pea_parse.y"
{
							yyval.i = 0;
						;
    break;}
case 58:
#line 521 "pea_parse.y"
{
							yyval.i = 1;
						;
    break;}
case 59:
#line 526 "pea_parse.y"
{
							if (interpreter->m_current_function->m_argument_first_default) {
								yyerror("Must have default value");
							}
							yyval.i = 0;
						;
    break;}
case 60:
#line 532 "pea_parse.y"
{

							/* after a default valued argument, all arguments need a default value */
							if (interpreter->m_current_function->m_argument_first_default == 0) {
								interpreter->m_current_function->m_argument_first_default = interpreter->m_current_function->m_argument_count;
							}

							/* the expression has pushed in value to the stack */
							yyval.i = 1;
						;
    break;}
case 64:
#line 549 "pea_parse.y"
{
							pea_function_add_global(interpreter->m_current_function,yyvsp[0].a);
						;
    break;}
case 65:
#line 553 "pea_parse.y"
{
							if (interpreter->m_current_class) {
								fprintf(stdout,"Can't declare a class inside a class\n");
								exit(0);
							}

							// Switch to function segment
							yyvsp[-1].label.s_func = interpreter->m_curr_segment;
							interpreter->m_curr_segment = interpreter->m_func_segment;

							// We are now in a class
							interpreter->m_current_class = pea_class_alloc(interpreter,yyvsp[0].a);
						;
    break;}
case 66:
#line 567 "pea_parse.y"
{
							interpreter->m_current_class = NULL;
						
							// Switch back to current segment
							interpreter->m_curr_segment = yyvsp[-3].label.s_func;
						;
    break;}
case 67:
#line 576 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_STRING);
							pea_segment_add_string(interpreter->m_curr_segment,yyvsp[0].s);
						;
    break;}
case 68:
#line 581 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,yyvsp[0].i);
						;
    break;}
case 69:
#line 586 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
						;
    break;}
case 70:
#line 591 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,0);
						;
    break;}
case 71:
#line 596 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_ATOM);
							pea_segment_add(interpreter->m_curr_segment,yyvsp[0].a);
						;
    break;}
case 72:
#line 601 "pea_parse.y"
{
							// Check if this variable is local or global
							if (yyvsp[-1].i || pea_function_is_global(interpreter->m_current_function,yyvsp[0].a)) {
								pea_segment_add(interpreter->m_curr_segment,OP_GLOBAL_VAR);
								pea_segment_add(interpreter->m_curr_segment,yyvsp[0].a);
							} else {
								pea_segment_add(interpreter->m_curr_segment,OP_LOCAL_VAR);
								pea_segment_add(interpreter->m_curr_segment,yyvsp[0].a);
							}
						;
    break;}
case 73:
#line 612 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 74:
#line 617 "pea_parse.y"
{
							yyval.i = 0;
						;
    break;}
case 75:
#line 621 "pea_parse.y"
{
							yyval.i = 1;
						;
    break;}
case 76:
#line 625 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 77:
#line 637 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_ARRAY);
						;
    break;}
case 78:
#line 641 "pea_parse.y"
{
							// all arguments has pushed it values onto the stack
							
							pea_segment_add(interpreter->m_curr_segment,OP_CALL);
							pea_segment_add(interpreter->m_curr_segment,yyvsp[-1].i); 
						;
    break;}
case 79:
#line 648 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_PUSH);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
							pea_segment_add(interpreter->m_curr_segment,OP_ADD);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 80:
#line 656 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_PUSH);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
							pea_segment_add(interpreter->m_curr_segment,OP_SUB);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 81:
#line 664 "pea_parse.y"
{
							pea_parser_line(interpreter);
							pea_segment_add(interpreter->m_curr_segment,OP_MEMBER_VAR);
						;
    break;}
case 82:
#line 670 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 83:
#line 674 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_PUSH);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
							pea_segment_add(interpreter->m_curr_segment,OP_ADD);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 84:
#line 682 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_PUSH);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
							pea_segment_add(interpreter->m_curr_segment,OP_SUB);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 85:
#line 690 "pea_parse.y"
{
							/* noting to do */
						;
    break;}
case 86:
#line 694 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_NEG);
						;
    break;}
case 87:
#line 698 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_LOGICAL_NOT);
						;
    break;}
case 88:
#line 702 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_NOT);
						;
    break;}
case 89:
#line 705 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_NEW);
							pea_segment_add(interpreter->m_curr_segment,yyvsp[0].a);
						;
    break;}
case 90:
#line 711 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 91:
#line 715 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_MUL);
						;
    break;}
case 92:
#line 719 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_DIV);
						;
    break;}
case 93:
#line 723 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_MOD);
						;
    break;}
case 94:
#line 728 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 95:
#line 732 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_ADD);
						;
    break;}
case 96:
#line 736 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_SUB);
						;
    break;}
case 97:
#line 740 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_CONCAT);
						;
    break;}
case 98:
#line 745 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 99:
#line 749 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_SL);
						;
    break;}
case 100:
#line 753 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_SR);
						;
    break;}
case 101:
#line 758 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 102:
#line 762 "pea_parse.y"
{
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_LT);
						;
    break;}
case 103:
#line 767 "pea_parse.y"
{
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_GT);
						;
    break;}
case 104:
#line 772 "pea_parse.y"
{
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_LTE);
						;
    break;}
case 105:
#line 777 "pea_parse.y"
{
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_GTE);
						;
    break;}
case 106:
#line 783 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 107:
#line 787 "pea_parse.y"
{
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_EQ);
						;
    break;}
case 108:
#line 792 "pea_parse.y"
{
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_NE);
						;
    break;}
case 109:
#line 798 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 110:
#line 802 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_AND);
						;
    break;}
case 111:
#line 807 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 112:
#line 811 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_XOR);
						;
    break;}
case 113:
#line 816 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 114:
#line 820 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_OR);
						;
    break;}
case 115:
#line 825 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 116:
#line 829 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_LOGICAL_AND);
						;
    break;}
case 117:
#line 834 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 118:
#line 838 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_LOGICAL_OR);
						;
    break;}
case 119:
#line 843 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 120:
#line 847 "pea_parse.y"
{
							NYI;
  						;
    break;}
case 121:
#line 852 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
						;
    break;}
case 122:
#line 856 "pea_parse.y"
{
							// the value of expression is on the top of the stack
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 123:
#line 861 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_ADD);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 124:
#line 867 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_SUB);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 125:
#line 873 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_MUL);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 126:
#line 879 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_DIV);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 127:
#line 885 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_CONCAT);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 128:
#line 891 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_MOD);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 129:
#line 897 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_AND);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 130:
#line 903 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_OR);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 131:
#line 909 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_XOR);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 132:
#line 915 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_SL);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 133:
#line 921 "pea_parse.y"
{
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_SR);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;
    break;}
case 134:
#line 929 "pea_parse.y"
{
							// expression value is on top of stack, no need to do anything
							pea_parser_line(interpreter);
						;
    break;}
case 135:
#line 936 "pea_parse.y"
{	
							yyval.i = 0; 
						;
    break;}
case 136:
#line 939 "pea_parse.y"
{
							yyval.i = 1;
						;
    break;}
case 137:
#line 942 "pea_parse.y"
{
							yyval.i = yyvsp[-2].i + 1;
						;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/local/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 947 "pea_parse.y"
