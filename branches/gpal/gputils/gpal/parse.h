#ifndef BISON_PARSE_H
# define BISON_PARSE_H

#ifndef YYSTYPE
typedef union {
  int i;
  struct {
    tree *start;
    tree *end;
  } r;
  char *s;
  tree *t;
  enum node_type y;
  enum node_size z;
  enum node_op o;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	CASE	257
# define	CONST_TYPE	258
# define	BEGIN_KEY	259
# define	BIT_SIZE	260
# define	BYTE_SIZE	261
# define	ELSE	262
# define	ELSIF	263
# define	END	264
# define	EXTERN_STORAGE	265
# define	FOR	266
# define	FUNCTION_TOK	267
# define	IF	268
# define	IN	269
# define	IS	270
# define	LOOP	271
# define	MODULE	272
# define	NULL_TOK	273
# define	OTHERS	274
# define	PRAGMA	275
# define	PROCEDURE	276
# define	PUBLIC_STORAGE	277
# define	RETURN	278
# define	THEN	279
# define	TO	280
# define	VAR_TYPE	281
# define	VOLATILE_STORAGE	282
# define	WHEN	283
# define	WHILE	284
# define	WITH	285
# define	ASM	286
# define	IDENT	287
# define	NUMBER	288
# define	STRING	289
# define	LSH	290
# define	RSH	291
# define	ARROW	292
# define	GREATER_EQUAL	293
# define	LESS_EQUAL	294
# define	EQUAL	295
# define	NOT_EQUAL	296
# define	LOGICAL_AND	297
# define	LOGICAL_OR	298


extern YYSTYPE yylval;

#endif /* not BISON_PARSE_H */
