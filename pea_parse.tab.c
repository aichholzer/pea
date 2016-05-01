/* A Bison parser, made by GNU Bison 1.875b.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_HTML = 258,
     T_INCLUDE = 259,
     T_IF = 260,
     T_ELSE = 261,
     T_SWITCH = 262,
     T_CASE = 263,
     T_DEFAULT = 264,
     T_BREAK = 265,
     T_WHILE = 266,
     T_DO = 267,
     T_FOR = 268,
     T_FUNCTION = 269,
     T_GLOBAL = 270,
     T_CLASS = 271,
     T_FOREACH = 272,
     T_AS = 273,
     T_NEW = 274,
     T_ECHO = 275,
     T_ATOM = 276,
     T_STRING = 277,
     T_INT = 278,
     T_LOGICAL_OR = 279,
     T_LOGICAL_XOR = 280,
     T_LOGICAL_AND = 281,
     T_ADD_ASSIGN = 282,
     T_SUB_ASSIGN = 283,
     T_MUL_ASSIGN = 284,
     T_DIV_ASSIGN = 285,
     T_CONCAT_ASSIGN = 286,
     T_MOD_ASSIGN = 287,
     T_AND_ASSIGN = 288,
     T_OR_ASSIGN = 289,
     T_XOR_ASSIGN = 290,
     T_BOOLEAN_OR = 291,
     T_BOOLEAN_AND = 292,
     T_SL = 293,
     T_SR = 294,
     T_EQ = 295,
     T_NE = 296,
     T_LTE = 297,
     T_GTE = 298,
     T_INC = 299,
     T_DEC = 300,
     T_POINT = 301,
     T_DPOINT = 302,
     T_TRUE = 303,
     T_FALSE = 304,
     T_SR_ASSIGN = 305,
     T_SL_ASSIGN = 306
   };
#endif
#define T_HTML 258
#define T_INCLUDE 259
#define T_IF 260
#define T_ELSE 261
#define T_SWITCH 262
#define T_CASE 263
#define T_DEFAULT 264
#define T_BREAK 265
#define T_WHILE 266
#define T_DO 267
#define T_FOR 268
#define T_FUNCTION 269
#define T_GLOBAL 270
#define T_CLASS 271
#define T_FOREACH 272
#define T_AS 273
#define T_NEW 274
#define T_ECHO 275
#define T_ATOM 276
#define T_STRING 277
#define T_INT 278
#define T_LOGICAL_OR 279
#define T_LOGICAL_XOR 280
#define T_LOGICAL_AND 281
#define T_ADD_ASSIGN 282
#define T_SUB_ASSIGN 283
#define T_MUL_ASSIGN 284
#define T_DIV_ASSIGN 285
#define T_CONCAT_ASSIGN 286
#define T_MOD_ASSIGN 287
#define T_AND_ASSIGN 288
#define T_OR_ASSIGN 289
#define T_XOR_ASSIGN 290
#define T_BOOLEAN_OR 291
#define T_BOOLEAN_AND 292
#define T_SL 293
#define T_SR 294
#define T_EQ 295
#define T_NE 296
#define T_LTE 297
#define T_GTE 298
#define T_INC 299
#define T_DEC 300
#define T_POINT 301
#define T_DPOINT 302
#define T_TRUE 303
#define T_FALSE 304
#define T_SR_ASSIGN 305
#define T_SL_ASSIGN 306




/* Copy the first part of user declarations.  */
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
	fprintf(stderr,"%s(%d) : %s\n",interpreter->m_current_file,interpreter->m_current_line,err);
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

	s = pea_string_alloc(interpreter,4,"this");

	interpreter->m_atom_this = pea_atom_add(interpreter,s);
}

void pea_parser_line(pea_interpreter* interpreter) {

	pea_segment_add(interpreter->m_curr_segment,OP_LINE);
	pea_segment_add(interpreter->m_curr_segment,(ulong)interpreter->m_current_file);
	pea_segment_add(interpreter->m_curr_segment,interpreter->m_current_line);
}

#define interpreter	((pea_interpreter*)interpreter_p)



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 59 "pea_parse.y"
typedef union YYSTYPE {
	pea_atom		a;
	pea_string*		s;			/* string */
	char			c;			/* char */
	int				i;			/* integer */
	pea_label		label;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 241 "pea_parse.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 253 "pea_parse.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   386

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  53
/* YYNRULES -- Number of rules. */
#define YYNRULES  133
/* YYNRULES -- Number of states. */
#define YYNSTATES  244

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,     2,     2,    74,    65,    57,     2,
      69,    70,    63,    60,    75,    61,    62,    64,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    54,    71,
      58,    50,    59,    53,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    68,     2,    76,    56,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,    55,    73,    67,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    51,    52
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     5,     8,    10,    13,    15,    21,
      25,    27,    29,    31,    33,    35,    37,    39,    42,    45,
      49,    51,    54,    55,    58,    59,    60,    69,    70,    79,
      80,    82,    85,    86,    92,    96,    97,    98,   106,   107,
     116,   117,   118,   119,   130,   131,   142,   143,   147,   148,
     150,   151,   152,   161,   162,   164,   168,   172,   173,   176,
     180,   182,   185,   188,   189,   194,   196,   198,   200,   202,
     204,   207,   211,   213,   218,   223,   226,   229,   233,   235,
     238,   241,   244,   247,   250,   253,   256,   258,   262,   266,
     270,   272,   276,   280,   284,   286,   290,   294,   296,   300,
     304,   308,   312,   314,   318,   322,   324,   328,   330,   334,
     336,   340,   342,   346,   348,   352,   354,   360,   362,   366,
     370,   374,   378,   382,   386,   390,   394,   398,   402,   406,
     410,   412,   413,   415
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
      78,     0,    -1,    -1,    -1,    79,    80,    -1,    81,    -1,
      80,    81,    -1,     3,    -1,     4,    69,   128,    70,    71,
      -1,    20,   128,    71,    -1,    82,    -1,    83,    -1,    85,
      -1,    92,    -1,   102,    -1,   108,    -1,   111,    -1,    10,
      71,    -1,    72,    73,    -1,    72,    80,    73,    -1,    71,
      -1,   128,    71,    -1,    -1,     6,    81,    -1,    -1,    -1,
       5,    69,   128,    70,    86,    81,    87,    84,    -1,    -1,
       7,    69,   128,    70,    72,    88,    89,    73,    -1,    -1,
      90,    -1,    89,    90,    -1,    -1,     8,   128,    54,    91,
      80,    -1,     9,    54,    80,    -1,    -1,    -1,    11,    93,
      69,   128,    70,    94,    81,    -1,    -1,    12,    95,    81,
      11,    69,   128,    70,    71,    -1,    -1,    -1,    -1,    13,
      69,    83,    96,    83,    97,   101,    70,    98,    81,    -1,
      -1,    17,    69,   128,    18,    74,    21,   100,    70,    99,
      81,    -1,    -1,    47,    74,    21,    -1,    -1,   128,    -1,
      -1,    -1,    14,    21,   103,    69,   105,    70,   104,    82,
      -1,    -1,   106,    -1,   105,    75,   106,    -1,    74,    21,
     107,    -1,    -1,    50,   113,    -1,    15,   109,    71,    -1,
     110,    -1,   109,   110,    -1,    74,    21,    -1,    -1,    16,
      21,   112,    82,    -1,    22,    -1,    23,    -1,    48,    -1,
      49,    -1,    21,    -1,    74,    21,    -1,    69,   128,    70,
      -1,   113,    -1,   114,    68,   128,    76,    -1,   114,    69,
     129,    70,    -1,   114,    44,    -1,   114,    45,    -1,   114,
      46,   113,    -1,   114,    -1,    44,   115,    -1,    45,   115,
      -1,    60,   115,    -1,    61,   115,    -1,    66,   115,    -1,
      67,   115,    -1,    19,    21,    -1,   115,    -1,   116,    63,
     115,    -1,   116,    64,   115,    -1,   116,    65,   115,    -1,
     116,    -1,   117,    60,   116,    -1,   117,    61,   116,    -1,
     117,    62,   116,    -1,   117,    -1,   118,    38,   117,    -1,
     118,    39,   117,    -1,   118,    -1,   119,    58,   118,    -1,
     119,    59,   118,    -1,   119,    42,   118,    -1,   119,    43,
     118,    -1,   119,    -1,   120,    40,   119,    -1,   120,    41,
     119,    -1,   120,    -1,   121,    57,   120,    -1,   121,    -1,
     122,    56,   121,    -1,   122,    -1,   123,    55,   122,    -1,
     123,    -1,   124,    26,   123,    -1,   124,    -1,   125,    24,
     124,    -1,   125,    -1,   125,    53,   128,    54,   127,    -1,
     126,    -1,   125,    50,   127,    -1,   125,    27,   127,    -1,
     125,    28,   127,    -1,   125,    29,   127,    -1,   125,    30,
     127,    -1,   125,    31,   127,    -1,   125,    32,   127,    -1,
     125,    33,   127,    -1,   125,    34,   127,    -1,   125,    35,
     127,    -1,   125,    52,   127,    -1,   125,    51,   127,    -1,
     127,    -1,    -1,   128,    -1,   129,    75,   128,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   109,   109,   111,   111,   131,   132,   135,   139,   143,
     149,   150,   155,   156,   157,   158,   159,   160,   163,   164,
     167,   168,   171,   174,   180,   188,   180,   215,   215,   234,
     235,   236,   238,   238,   253,   255,   262,   255,   277,   277,
     290,   297,   310,   290,   331,   331,   399,   402,   407,   412,
     415,   436,   415,   472,   475,   479,   484,   501,   507,   518,
     520,   521,   523,   528,   528,   550,   555,   560,   565,   570,
     575,   586,   591,   603,   607,   614,   622,   630,   636,   640,
     648,   656,   660,   664,   668,   672,   677,   681,   685,   689,
     694,   698,   702,   706,   711,   715,   719,   724,   728,   733,
     738,   743,   749,   753,   758,   764,   768,   773,   777,   782,
     786,   791,   795,   800,   804,   809,   813,   818,   822,   827,
     833,   839,   845,   851,   857,   863,   869,   875,   881,   887,
     895,   903,   906,   909
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_HTML", "T_INCLUDE", "T_IF", "T_ELSE", 
  "T_SWITCH", "T_CASE", "T_DEFAULT", "T_BREAK", "T_WHILE", "T_DO", 
  "T_FOR", "T_FUNCTION", "T_GLOBAL", "T_CLASS", "T_FOREACH", "T_AS", 
  "T_NEW", "T_ECHO", "T_ATOM", "T_STRING", "T_INT", "T_LOGICAL_OR", 
  "T_LOGICAL_XOR", "T_LOGICAL_AND", "T_ADD_ASSIGN", "T_SUB_ASSIGN", 
  "T_MUL_ASSIGN", "T_DIV_ASSIGN", "T_CONCAT_ASSIGN", "T_MOD_ASSIGN", 
  "T_AND_ASSIGN", "T_OR_ASSIGN", "T_XOR_ASSIGN", "T_BOOLEAN_OR", 
  "T_BOOLEAN_AND", "T_SL", "T_SR", "T_EQ", "T_NE", "T_LTE", "T_GTE", 
  "T_INC", "T_DEC", "T_POINT", "T_DPOINT", "T_TRUE", "T_FALSE", "'='", 
  "T_SR_ASSIGN", "T_SL_ASSIGN", "'?'", "':'", "'|'", "'^'", "'&'", "'<'", 
  "'>'", "'+'", "'-'", "'.'", "'*'", "'/'", "'%'", "'!'", "'~'", "'['", 
  "'('", "')'", "';'", "'{'", "'}'", "'$'", "','", "']'", "$accept", 
  "main", "@1", "statement_list", "statement", "compound_statement", 
  "expression_statement", "optional_else", "selection_statement", "@2", 
  "@3", "@4", "case_statements", "case_statement", "@5", 
  "iteration_statement", "@6", "@7", "@8", "@9", "@10", "@11", "@12", 
  "foreach_optional_value", "optional_expression", "function_statement", 
  "@13", "@14", "optional_arguments", "argument", 
  "optional_default_value", "global_statement", "global_vars", 
  "global_var", "class_statement", "@15", "primary_expression", 
  "postfix_expression", "unary_expression", "multiplicative_expression", 
  "additive_expression", "shift_expression", "relational_expression", 
  "equality_expression", "and_expression", "exclusive_or_expression", 
  "inclusive_or_expression", "logical_and_expression", 
  "logical_or_expression", "conditional_expression", 
  "assignment_expression", "expression", "optional_parameters", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
      61,   305,   306,    63,    58,   124,    94,    38,    60,    62,
      43,    45,    46,    42,    47,    37,    33,   126,    91,    40,
      41,    59,   123,   125,    36,    44,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    77,    78,    79,    78,    80,    80,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    82,    82,
      83,    83,    84,    84,    86,    87,    85,    88,    85,    89,
      89,    89,    91,    90,    90,    93,    94,    92,    95,    92,
      96,    97,    98,    92,    99,    92,   100,   100,   101,   101,
     103,   104,   102,   105,   105,   105,   106,   107,   107,   108,
     109,   109,   110,   112,   111,   113,   113,   113,   113,   113,
     113,   113,   114,   114,   114,   114,   114,   114,   115,   115,
     115,   115,   115,   115,   115,   115,   116,   116,   116,   116,
     117,   117,   117,   117,   118,   118,   118,   119,   119,   119,
     119,   119,   120,   120,   120,   121,   121,   122,   122,   123,
     123,   124,   124,   125,   125,   126,   126,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     128,   129,   129,   129
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     0,     2,     1,     2,     1,     5,     3,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     3,
       1,     2,     0,     2,     0,     0,     8,     0,     8,     0,
       1,     2,     0,     5,     3,     0,     0,     7,     0,     8,
       0,     0,     0,    10,     0,    10,     0,     3,     0,     1,
       0,     0,     8,     0,     1,     3,     3,     0,     2,     3,
       1,     2,     2,     0,     4,     1,     1,     1,     1,     1,
       2,     3,     1,     4,     4,     2,     2,     3,     1,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     3,     3,
       1,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     5,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     0,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       3,     0,     0,     1,     7,     0,     0,     0,     0,    35,
      38,     0,     0,     0,     0,     0,     0,     0,    69,    65,
      66,     0,     0,    67,    68,     0,     0,     0,     0,     0,
      20,     0,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    72,    78,    86,    90,    94,    97,   102,   105,
     107,   109,   111,   113,   115,   117,   130,     0,     0,     0,
       0,    17,     0,     0,     0,    50,     0,     0,    60,    63,
       0,    85,     0,    79,    80,    81,    82,    83,    84,     0,
      18,     0,    70,     6,    75,    76,     0,     0,   131,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,     0,     0,    40,     0,    62,
      59,    61,     0,     0,     9,    71,    19,    77,     0,   132,
       0,    87,    88,    89,    91,    92,    93,    95,    96,   100,
     101,    98,    99,   103,   104,   106,   108,   110,   112,   114,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   118,
     129,   128,     0,     0,    24,     0,     0,     0,     0,    53,
      64,     0,    73,    74,     0,     0,     8,     0,    27,    36,
       0,    41,     0,     0,    54,     0,   133,   116,    25,    29,
       0,     0,    48,    57,    51,     0,    46,    22,     0,     0,
       0,    30,    37,     0,     0,    49,     0,    56,     0,    55,
       0,     0,     0,    26,     0,     0,    28,    31,    39,    42,
      58,    52,     0,    44,    23,    32,    34,     0,    47,     0,
       0,    43,    45,    33
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,     2,    33,    34,    35,    36,   223,    37,   187,
     207,   199,   210,   211,   240,    38,    62,   200,    63,   178,
     202,   237,   239,   221,   214,    39,   128,   218,   193,   194,
     217,    40,    67,    68,    41,   132,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,   140
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -128
static const short yypact[] =
{
      29,    41,   281,  -128,  -128,   -18,   -12,     0,    10,  -128,
    -128,    18,    32,    36,    95,    48,    98,   121,  -128,  -128,
    -128,   121,   121,  -128,  -128,   121,   121,   121,   121,   121,
    -128,    63,    99,   281,  -128,  -128,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,    57,  -128,   -57,    28,     8,    -3,    24,
      64,    66,    72,   102,   210,  -128,  -128,    60,   121,   121,
     121,  -128,    69,   281,   312,  -128,   118,   -22,  -128,  -128,
     121,  -128,    70,  -128,  -128,  -128,  -128,  -128,  -128,    75,
    -128,   209,  -128,  -128,  -128,  -128,   -11,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,  -128,    76,    77,    78,   121,   138,  -128,    81,  -128,
    -128,  -128,    79,   134,  -128,  -128,  -128,  -128,    80,  -128,
     -61,  -128,  -128,  -128,   -57,   -57,   -57,    28,    28,     8,
       8,     8,     8,    -3,    -3,    24,    64,    66,    72,   102,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,
    -128,  -128,   101,    82,  -128,    86,    87,    90,   312,    88,
    -128,    89,  -128,  -128,   121,   121,  -128,   281,  -128,  -128,
     121,  -128,   139,   -25,  -128,   140,  -128,  -128,  -128,    85,
     281,    94,   121,   122,  -128,    88,   124,   167,   121,   123,
      27,  -128,  -128,   104,   106,  -128,   -11,  -128,    79,  -128,
     105,   108,   281,  -128,   126,   281,  -128,  -128,  -128,  -128,
    -128,  -128,   162,  -128,  -128,  -128,   281,   281,  -128,   281,
     281,  -128,  -128,   281
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
    -128,  -128,  -128,   -29,   -33,  -127,   -60,  -128,  -128,  -128,
    -128,  -128,  -128,   -26,  -128,  -128,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,   -20,
    -128,  -128,  -128,   127,  -128,  -128,   -83,  -128,     6,    21,
       3,   -38,     4,    96,    93,    97,    92,    84,  -128,  -128,
     -93,   -16,  -128
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const short yytable[] =
{
      83,    72,    81,   137,   127,   180,    89,    90,    91,   183,
      18,    19,    20,    79,   184,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,    73,    74,    -2,
     126,    75,    76,    77,    78,   208,   209,    23,    24,    97,
      98,     3,   122,   123,   124,   204,    95,    96,    83,   130,
     205,    58,    66,    65,   133,    99,   100,    59,    29,   149,
     150,   151,   152,    32,   101,   102,     4,     5,     6,    60,
       7,   138,   139,     8,     9,    10,    11,    12,    13,    14,
      15,    61,    16,    17,    18,    19,    20,    64,    92,    93,
      94,   231,   197,   208,   209,   141,   142,   143,   147,   148,
     226,    84,    85,    86,   172,   153,   154,    21,    22,   176,
      66,    23,    24,   144,   145,   146,    69,    70,   191,    71,
      82,   103,   104,    25,    26,    87,    88,   105,   106,    27,
      28,   121,    29,   230,    30,    31,    80,    32,   125,   129,
      16,   134,    18,    19,    20,   135,   173,   174,   175,   177,
     179,    31,   181,   186,   198,   185,   182,   189,   188,   190,
     203,   206,   192,   195,   213,    21,    22,   212,   196,    23,
      24,   220,   216,   222,   201,   228,   229,   225,   233,   232,
     235,    25,    26,   238,   227,   219,   215,    27,    28,   234,
      29,   159,   224,     0,   131,    32,   236,   156,   158,   155,
       0,     0,   157,    83,   241,     0,   242,     0,     0,     0,
      83,   243,     4,     5,     6,     0,     7,     0,     0,     8,
       9,    10,    11,    12,    13,    14,    15,     0,    16,    17,
      18,    19,    20,     0,   107,     0,     0,   108,   109,   110,
     111,   112,   113,   114,   115,   116,     0,     0,     0,     0,
       0,     0,     0,    21,    22,     0,     0,    23,    24,     0,
     117,   118,   119,   120,     0,     0,     0,     0,     0,    25,
      26,     0,     0,     0,     0,    27,    28,     0,    29,     0,
      30,    31,   136,    32,     4,     5,     6,     0,     7,     0,
       0,     8,     9,    10,    11,    12,    13,    14,    15,     0,
      16,    17,    18,    19,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    22,     0,     0,    23,
      24,    16,     0,    18,    19,    20,     0,     0,     0,     0,
       0,    25,    26,     0,     0,     0,     0,    27,    28,     0,
      29,     0,    30,    31,     0,    32,    21,    22,     0,     0,
      23,    24,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    25,    26,     0,     0,     0,     0,    27,    28,
       0,    29,     0,    30,     0,     0,    32
};

static const short yycheck[] =
{
      33,    17,    31,    86,    64,   132,    63,    64,    65,    70,
      21,    22,    23,    29,    75,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,    21,    22,     0,
      63,    25,    26,    27,    28,     8,     9,    48,    49,    42,
      43,     0,    58,    59,    60,    70,    38,    39,    81,    71,
      75,    69,    74,    21,    70,    58,    59,    69,    69,    97,
      98,    99,   100,    74,    40,    41,     3,     4,     5,    69,
       7,    87,    88,    10,    11,    12,    13,    14,    15,    16,
      17,    71,    19,    20,    21,    22,    23,    69,    60,    61,
      62,   218,   185,     8,     9,    89,    90,    91,    95,    96,
      73,    44,    45,    46,   120,   101,   102,    44,    45,   125,
      74,    48,    49,    92,    93,    94,    21,    69,   178,    21,
      21,    57,    56,    60,    61,    68,    69,    55,    26,    66,
      67,    71,    69,   216,    71,    72,    73,    74,    69,    21,
      19,    71,    21,    22,    23,    70,    70,    70,    70,    11,
      69,    72,    18,    71,   187,    54,    76,    70,    72,    69,
      21,    21,    74,    74,    70,    44,    45,   200,   184,    48,
      49,    47,    50,     6,   190,    71,    70,    54,    70,    74,
      54,    60,    61,    21,   210,   205,   202,    66,    67,   222,
      69,   107,   208,    -1,    67,    74,   225,   104,   106,   103,
      -1,    -1,   105,   236,   237,    -1,   239,    -1,    -1,    -1,
     243,   240,     3,     4,     5,    -1,     7,    -1,    -1,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    19,    20,
      21,    22,    23,    -1,    24,    -1,    -1,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    -1,    -1,    48,    49,    -1,
      50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    66,    67,    -1,    69,    -1,
      71,    72,    73,    74,     3,     4,     5,    -1,     7,    -1,
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    48,
      49,    19,    -1,    21,    22,    23,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,    -1,
      69,    -1,    71,    72,    -1,    74,    44,    45,    -1,    -1,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,
      -1,    69,    -1,    71,    -1,    -1,    74
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    78,    79,     0,     3,     4,     5,     7,    10,    11,
      12,    13,    14,    15,    16,    17,    19,    20,    21,    22,
      23,    44,    45,    48,    49,    60,    61,    66,    67,    69,
      71,    72,    74,    80,    81,    82,    83,    85,    92,   102,
     108,   111,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,    69,    69,
      69,    71,    93,    95,    69,    21,    74,   109,   110,    21,
      69,    21,   128,   115,   115,   115,   115,   115,   115,   128,
      73,    80,    21,    81,    44,    45,    46,    68,    69,    63,
      64,    65,    60,    61,    62,    38,    39,    42,    43,    58,
      59,    40,    41,    57,    56,    55,    26,    24,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    50,    51,    52,
      53,    71,   128,   128,   128,    69,    81,    83,   103,    21,
      71,   110,   112,   128,    71,    70,    73,   113,   128,   128,
     129,   115,   115,   115,   116,   116,   116,   117,   117,   118,
     118,   118,   118,   119,   119,   120,   121,   122,   123,   124,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   128,    70,    70,    70,   128,    11,    96,    69,
      82,    18,    76,    70,    75,    54,    71,    86,    72,    70,
      69,    83,    74,   105,   106,    74,   128,   127,    81,    88,
      94,   128,    97,    21,    70,    75,    21,    87,     8,     9,
      89,    90,    81,    70,   101,   128,    50,   107,   104,   106,
      47,   100,     6,    84,   128,    54,    73,    90,    71,    70,
     113,    82,    74,    70,    81,    54,    80,    98,    21,    99,
      91,    81,    81,    80
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 111 "pea_parse.y"
    { 
							interpreter->m_curr_segment = interpreter->m_main_segment;
						;}
    break;

  case 4:
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

						;}
    break;

  case 7:
#line 135 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_HTML);
							pea_segment_add_string(interpreter->m_curr_segment,yyvsp[0].s);
						;}
    break;

  case 8:
#line 139 "pea_parse.y"
    {
							pea_parser_line(interpreter);
							pea_segment_add(interpreter->m_curr_segment,OP_INCLUDE);	
						;}
    break;

  case 9:
#line 143 "pea_parse.y"
    {
							// all arguments has pushed it values onto the stack
							
							pea_segment_add(interpreter->m_curr_segment,OP_ECHO);

						;}
    break;

  case 11:
#line 151 "pea_parse.y"
    {
							// The expression has placed a value on the stack, pop it
							pea_segment_add(interpreter->m_curr_segment,OP_POP); 
						;}
    break;

  case 22:
#line 171 "pea_parse.y"
    {
							yyval.i = 0;
						;}
    break;

  case 23:
#line 174 "pea_parse.y"
    {
							yyval.i = 1;
						;}
    break;

  case 24:
#line 180 "pea_parse.y"
    {
							
							// the result of expression is on the top of the stack
							// Jump if expression is false

							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							yyvsp[-3].label.l_skip_if = pea_segment_add_label(interpreter->m_curr_segment);

						;}
    break;

  case 25:
#line 188 "pea_parse.y"
    {

							// Jump past the else statement
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							yyvsp[-5].label.l_skip_else = pea_segment_add_label(interpreter->m_curr_segment);

							// Let the false jump end up here
							pea_segment_set_label(interpreter->m_curr_segment,yyvsp[-5].label.l_skip_if);

						;}
    break;

  case 26:
#line 197 "pea_parse.y"
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

						;}
    break;

  case 27:
#line 215 "pea_parse.y"
    {
							yyvsp[-4].label.s_breaks = interpreter->m_curr_breaks;
							interpreter->m_curr_breaks = pea_stack_alloc(interpreter,sizeof(size_t));
						;}
    break;

  case 28:
#line 219 "pea_parse.y"
    {
							ulong	pos;

							while(pea_stack_pop(interpreter->m_curr_breaks,&pos)) {

								pea_segment_set_label(interpreter->m_curr_segment,pos);
							}

							pea_stack_free(interpreter,interpreter->m_curr_breaks);

							interpreter->m_curr_breaks = yyvsp[-7].label.s_breaks;
							
						;}
    break;

  case 32:
#line 238 "pea_parse.y"
    {

							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_EQ);

							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							yyvsp[-2].label.l_skip_case = pea_segment_add_label(interpreter->m_curr_segment);
						;}
    break;

  case 33:
#line 245 "pea_parse.y"
    {
							
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							yyvsp[-4].label.l_break = pea_segment_add_label(interpreter->m_curr_segment);

							// Let the false jump end up here
							pea_segment_set_label(interpreter->m_curr_segment,yyvsp[-4].label.l_skip_case);
						;}
    break;

  case 35:
#line 255 "pea_parse.y"
    {


							// Put a label to get back here when looping
							yyvsp[0].label.l_begin_while = pea_segment_addr(interpreter->m_curr_segment);


						;}
    break;

  case 36:
#line 262 "pea_parse.y"
    {
							
							// the result of expression is on the top of the stack
							// Skip loop code if expression is false
							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							yyvsp[-4].label.l_skip_while = pea_segment_add_label(interpreter->m_curr_segment);

						;}
    break;

  case 37:
#line 269 "pea_parse.y"
    {

							// Loop back to beginning of while loop
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							pea_segment_add_offset(interpreter->m_curr_segment,yyvsp[-6].label.l_begin_while);

							pea_segment_set_label(interpreter->m_curr_segment,yyvsp[-6].label.l_skip_while);
						;}
    break;

  case 38:
#line 277 "pea_parse.y"
    {

							// Put a label to get back here when looping
							yyvsp[0].label.l_begin_do = pea_segment_addr(interpreter->m_curr_segment);

						;}
    break;

  case 39:
#line 282 "pea_parse.y"
    {
						
							// the result of expression is on the top of the stack
							// Loop again if expression is true
							pea_segment_add(interpreter->m_curr_segment,OP_JMP_TRUE);
							pea_segment_add_offset(interpreter->m_curr_segment,yyvsp[-7].label.l_begin_do);
							
						;}
    break;

  case 40:
#line 290 "pea_parse.y"
    {

							pea_segment_add(interpreter->m_curr_segment,OP_POP);	// expression_statement has put a value on the top of the stack, remove it

							// Put a label to get back here when looping
							yyvsp[-2].label.l_begin_for = pea_segment_addr(interpreter->m_curr_segment);

						;}
    break;

  case 41:
#line 297 "pea_parse.y"
    { 

							// the result of expression is on the top of the stack
							// Skip loop code if not true

							pea_segment_add(interpreter->m_curr_segment,OP_JMP_FALSE);
							yyvsp[-4].label.l_skip_for = pea_segment_add_label(interpreter->m_curr_segment);

							// Write post expression into temp segment
							yyvsp[-4].label.s_for = interpreter->m_curr_segment;
							interpreter->m_curr_segment = interpreter->m_temp_segment;
							pea_segment_clear(interpreter->m_curr_segment);

						;}
    break;

  case 42:
#line 310 "pea_parse.y"
    {
						
							// Pop the value of the post expression
							pea_segment_add(interpreter->m_curr_segment,OP_POP);

							// Switch back to current segment
							interpreter->m_curr_segment = yyvsp[-7].label.s_for;

						;}
    break;

  case 43:
#line 318 "pea_parse.y"
    {
							
							// Write out the code for the expression
							pea_segment_concat(interpreter->m_curr_segment,interpreter->m_temp_segment);

							// Loop again
							pea_segment_add(interpreter->m_curr_segment,OP_JMP);
							pea_segment_add_offset(interpreter->m_curr_segment,yyvsp[-9].label.l_begin_for);
						
							// Put a label for the end of the for
							pea_segment_set_label(interpreter->m_curr_segment,yyvsp[-9].label.l_skip_for);

						;}
    break;

  case 44:
#line 331 "pea_parse.y"
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
						;}
    break;

  case 45:
#line 382 "pea_parse.y"
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
						;}
    break;

  case 46:
#line 399 "pea_parse.y"
    {
							yyval.a = 0;
						;}
    break;

  case 47:
#line 402 "pea_parse.y"
    {
							yyval.a = yyvsp[0].a;
						;}
    break;

  case 48:
#line 407 "pea_parse.y"
    {
							pea_parser_line(interpreter);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,0);
						;}
    break;

  case 50:
#line 415 "pea_parse.y"
    {
							
							if (interpreter->m_current_function) {
								fprintf(stderr,"Can't declare functions inside functions\n");
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

						;}
    break;

  case 51:
#line 436 "pea_parse.y"
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

						;}
    break;

  case 52:
#line 457 "pea_parse.y"
    {
							
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,0);

							pea_segment_add(interpreter->m_curr_segment,OP_RETURN);
						
							// We have now left the function, switch back to global variables
							interpreter->m_current_function = NULL;
						
							// Switch back to current segment
							interpreter->m_curr_segment = yyvsp[-7].label.s_func;
						;}
    break;

  case 53:
#line 472 "pea_parse.y"
    {
							yyval.i = 0;
						;}
    break;

  case 54:
#line 476 "pea_parse.y"
    {
							yyval.i = 1;
						;}
    break;

  case 55:
#line 480 "pea_parse.y"
    {
							yyval.i = yyvsp[-2].i + 1;
						;}
    break;

  case 56:
#line 485 "pea_parse.y"
    {
							// The function argument is on the stack, just write the value to a local variable
							pea_segment_add(interpreter->m_curr_segment,OP_LOCAL_VAR);
							pea_segment_add(interpreter->m_curr_segment,yyvsp[-1].a);

							if (yyvsp[0].i) {
								pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN_DEF_ARG);
							} else {
								pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN_ARG);
							}

							// Remember the number of arguments to the function
							interpreter->m_current_function->m_argument_count++;
						;}
    break;

  case 57:
#line 501 "pea_parse.y"
    {
							if (interpreter->m_current_function->m_argument_first_default) {
								yyerror("Must have default value");
							}
							yyval.i = 0;
						;}
    break;

  case 58:
#line 507 "pea_parse.y"
    {

							/* after a default valued argument, all arguments need a default value */
							if (interpreter->m_current_function->m_argument_first_default == 0) {
								interpreter->m_current_function->m_argument_first_default = interpreter->m_current_function->m_argument_count;
							}

							/* the expression has pushed in value to the stack */
							yyval.i = 1;
						;}
    break;

  case 62:
#line 524 "pea_parse.y"
    {
							pea_function_add_global(interpreter->m_current_function,yyvsp[0].a);
						;}
    break;

  case 63:
#line 528 "pea_parse.y"
    {
							if (interpreter->m_current_class) {
								fprintf(stderr,"Can't declare a class inside a class\n");
								exit(0);
							}

							// Switch to function segment
							yyvsp[-1].label.s_func = interpreter->m_curr_segment;
							interpreter->m_curr_segment = interpreter->m_func_segment;

							// We are now in a class
							interpreter->m_current_class = pea_class_alloc(interpreter,yyvsp[0].a);
						;}
    break;

  case 64:
#line 542 "pea_parse.y"
    {
							interpreter->m_current_class = NULL;
						
							// Switch back to current segment
							interpreter->m_curr_segment = yyvsp[-3].label.s_func;
						;}
    break;

  case 65:
#line 551 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_STRING);
							pea_segment_add_string(interpreter->m_curr_segment,yyvsp[0].s);
						;}
    break;

  case 66:
#line 556 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,yyvsp[0].i);
						;}
    break;

  case 67:
#line 561 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
						;}
    break;

  case 68:
#line 566 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,0);
						;}
    break;

  case 69:
#line 571 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_ATOM);
							pea_segment_add(interpreter->m_curr_segment,yyvsp[0].a);
						;}
    break;

  case 70:
#line 576 "pea_parse.y"
    {
							// Check if this variable is local or global
							if (pea_function_is_global(interpreter->m_current_function,yyvsp[0].a)) {
								pea_segment_add(interpreter->m_curr_segment,OP_GLOBAL_VAR);
								pea_segment_add(interpreter->m_curr_segment,yyvsp[0].a);
							} else {
								pea_segment_add(interpreter->m_curr_segment,OP_LOCAL_VAR);
								pea_segment_add(interpreter->m_curr_segment,yyvsp[0].a);
							}
						;}
    break;

  case 71:
#line 587 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 72:
#line 592 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 73:
#line 604 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_ARRAY);
						;}
    break;

  case 74:
#line 608 "pea_parse.y"
    {
							// all arguments has pushed it values onto the stack
							
							pea_segment_add(interpreter->m_curr_segment,OP_CALL);
							pea_segment_add(interpreter->m_curr_segment,yyvsp[-1].i); 
						;}
    break;

  case 75:
#line 615 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_PUSH);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
							pea_segment_add(interpreter->m_curr_segment,OP_ADD);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 76:
#line 623 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_PUSH);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
							pea_segment_add(interpreter->m_curr_segment,OP_SUB);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 77:
#line 631 "pea_parse.y"
    {
							pea_parser_line(interpreter);
							pea_segment_add(interpreter->m_curr_segment,OP_MEMBER_VAR);
						;}
    break;

  case 78:
#line 637 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 79:
#line 641 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_PUSH);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
							pea_segment_add(interpreter->m_curr_segment,OP_ADD);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 80:
#line 649 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_PUSH);
							pea_segment_add(interpreter->m_curr_segment,OP_CONST_INT);
							pea_segment_add(interpreter->m_curr_segment,1);
							pea_segment_add(interpreter->m_curr_segment,OP_SUB);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 81:
#line 657 "pea_parse.y"
    {
							/* noting to do */
						;}
    break;

  case 82:
#line 661 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_NEG);
						;}
    break;

  case 83:
#line 665 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_LOGICAL_NOT);
						;}
    break;

  case 84:
#line 669 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_NOT);
						;}
    break;

  case 85:
#line 672 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_NEW);
							pea_segment_add(interpreter->m_curr_segment,yyvsp[0].a);
						;}
    break;

  case 86:
#line 678 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 87:
#line 682 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_MUL);
						;}
    break;

  case 88:
#line 686 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_DIV);
						;}
    break;

  case 89:
#line 690 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_MOD);
						;}
    break;

  case 90:
#line 695 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 91:
#line 699 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_ADD);
						;}
    break;

  case 92:
#line 703 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_SUB);
						;}
    break;

  case 93:
#line 707 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_CONCAT);
						;}
    break;

  case 94:
#line 712 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 95:
#line 716 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_SL);
						;}
    break;

  case 96:
#line 720 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_SR);
						;}
    break;

  case 97:
#line 725 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 98:
#line 729 "pea_parse.y"
    {
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_LT);
						;}
    break;

  case 99:
#line 734 "pea_parse.y"
    {
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_GT);
						;}
    break;

  case 100:
#line 739 "pea_parse.y"
    {
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_LTE);
						;}
    break;

  case 101:
#line 744 "pea_parse.y"
    {
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_GTE);
						;}
    break;

  case 102:
#line 750 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 103:
#line 754 "pea_parse.y"
    {
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_EQ);
						;}
    break;

  case 104:
#line 759 "pea_parse.y"
    {
							// expression 1 and 2 is on the stack, call compare
							pea_segment_add(interpreter->m_curr_segment,OP_COMPARE_NE);
						;}
    break;

  case 105:
#line 765 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 106:
#line 769 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_AND);
						;}
    break;

  case 107:
#line 774 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 108:
#line 778 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_XOR);
						;}
    break;

  case 109:
#line 783 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 110:
#line 787 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_OR);
						;}
    break;

  case 111:
#line 792 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 112:
#line 796 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_LOGICAL_AND);
						;}
    break;

  case 113:
#line 801 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 114:
#line 805 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_LOGICAL_OR);
						;}
    break;

  case 115:
#line 810 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 116:
#line 814 "pea_parse.y"
    {
							NYI;
  						;}
    break;

  case 117:
#line 819 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
						;}
    break;

  case 118:
#line 823 "pea_parse.y"
    {
							// the value of expression is on the top of the stack
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 119:
#line 828 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_ADD);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 120:
#line 834 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_SUB);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 121:
#line 840 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_MUL);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 122:
#line 846 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_DIV);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 123:
#line 852 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_CONCAT);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 124:
#line 858 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_MOD);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 125:
#line 864 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_AND);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 126:
#line 870 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_OR);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 127:
#line 876 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_XOR);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 128:
#line 882 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_SL);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 129:
#line 888 "pea_parse.y"
    {
							pea_segment_add(interpreter->m_curr_segment,OP_DUP_2);
							pea_segment_add(interpreter->m_curr_segment,OP_BINARY_SR);
							pea_segment_add(interpreter->m_curr_segment,OP_ASSIGN);
						;}
    break;

  case 130:
#line 896 "pea_parse.y"
    {
							// expression value is on top of stack, no need to do anything
							pea_parser_line(interpreter);
						;}
    break;

  case 131:
#line 903 "pea_parse.y"
    {	
							yyval.i = 0; 
						;}
    break;

  case 132:
#line 906 "pea_parse.y"
    {
							yyval.i = 1;
						;}
    break;

  case 133:
#line 909 "pea_parse.y"
    {
							yyval.i = yyvsp[-2].i + 1;
						;}
    break;


    }

/* Line 999 of yacc.c.  */
#line 2497 "pea_parse.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}



