#ifndef BISON_PARSE_H
# define BISON_PARSE_H

#ifndef YYSTYPE
typedef union {
  int i;
  char *s;
  tree *t;
  enum node_type y;
  enum node_size z;
  enum node_op o;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	BEGIN_KEY	257
# define	END	258
# define	FUNCTION_TOK	259
# define	IS	260
# define	PRAGMA	261
# define	PROCEDURE	262
# define	WITH	263
# define	IF	264
# define	THEN	265
# define	WHILE	266
# define	ELSIF	267
# define	ELSE	268
# define	LOOP	269
# define	RETURN	270
# define	VAR_TYPE	271
# define	CONST_TYPE	272
# define	BIT_SIZE	273
# define	BYTE_SIZE	274
# define	EXTERN_STORAGE	275
# define	PUBLIC_STORAGE	276
# define	PRIVATE_STORAGE	277
# define	VOLATILE_STORAGE	278
# define	MODULE	279
# define	ASM	280
# define	IDENT	281
# define	NUMBER	282
# define	STRING	283
# define	LSH	284
# define	RSH	285
# define	GREATER_EQUAL	286
# define	LESS_EQUAL	287
# define	EQUAL	288
# define	NOT_EQUAL	289
# define	LOGICAL_AND	290
# define	LOGICAL_OR	291


extern YYSTYPE yylval;

#endif /* not BISON_PARSE_H */
