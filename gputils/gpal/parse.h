#ifndef BISON_PARSE_H
# define BISON_PARSE_H

#ifndef YYSTYPE
typedef union {
  int i;
  char *s;
  tree *t;
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
# define	IDENT	279
# define	NUMBER	280
# define	STRING	281
# define	LSH	282
# define	RSH	283
# define	GREATER_EQUAL	284
# define	LESS_EQUAL	285
# define	EQUAL	286
# define	NOT_EQUAL	287
# define	LOGICAL_AND	288
# define	LOGICAL_OR	289


extern YYSTYPE yylval;

#endif /* not BISON_PARSE_H */
