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
  enum node_dir d;
  enum node_key k;
  enum node_op o;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	ARRAY	257
# define	CASE	258
# define	CONST_KEY	259
# define	BEGIN_KEY	260
# define	ELSE	261
# define	ELSIF	262
# define	END	263
# define	EXTERN_STORAGE	264
# define	FOR	265
# define	FUNCTION_TOK	266
# define	IF	267
# define	IN	268
# define	INOUT	269
# define	IS	270
# define	LOOP	271
# define	MODULE	272
# define	NULL_TOK	273
# define	OF	274
# define	OTHERS	275
# define	PRAGMA	276
# define	PROCEDURE	277
# define	PUBLIC_STORAGE	278
# define	RETURN	279
# define	THEN	280
# define	TO	281
# define	TYPE	282
# define	OUT	283
# define	VAR_KEY	284
# define	VOLATILE_STORAGE	285
# define	WHEN	286
# define	WHILE	287
# define	WITH	288
# define	ASM	289
# define	IDENT	290
# define	NUMBER	291
# define	STRING	292
# define	LSH	293
# define	RSH	294
# define	ARROW	295
# define	GREATER_EQUAL	296
# define	LESS_EQUAL	297
# define	EQUAL	298
# define	NOT_EQUAL	299
# define	LOGICAL_AND	300
# define	LOGICAL_OR	301


extern YYSTYPE yylval;

#endif /* not BISON_PARSE_H */
