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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 59 "pea_parse.y"
typedef union YYSTYPE {
	pea_atom		a;
	pea_string*		s;			/* string */
	char			c;			/* char */
	int				i;			/* integer */
	pea_label		label;
} YYSTYPE;
/* Line 1252 of yacc.c.  */
#line 147 "pea_parse.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





