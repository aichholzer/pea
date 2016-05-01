typedef union {
	pea_atom		a;
	pea_string*		s;			/* string */
	char			c;			/* char */
	int				i;			/* integer */
	pea_label		label;
} YYSTYPE;
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

