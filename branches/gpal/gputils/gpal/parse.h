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
# define	CONSTANT_KEY	259
# define	BEGIN_KEY	260
# define	ELSE	261
# define	ELSIF	262
# define	END	263
# define	FOR	264
# define	FUNCTION_TOK	265
# define	IF	266
# define	IN	267
# define	INOUT	268
# define	IS	269
# define	LOOP	270
# define	MODULE	271
# define	NULL_TOK	272
# define	OF	273
# define	OTHERS	274
# define	PRAGMA	275
# define	PROCEDURE	276
# define	PUBLIC_STORAGE	277
# define	RETURN	278
# define	THEN	279
# define	TO	280
# define	TYPE	281
# define	OUT	282
# define	VARIABLE_KEY	283
# define	WHEN	284
# define	WHILE	285
# define	WITH	286
# define	ASM	287
# define	IDENT	288
# define	NUMBER	289
# define	STRING	290
# define	LSH	291
# define	RSH	292
# define	ARROW	293
# define	GREATER_EQUAL	294
# define	LESS_EQUAL	295
# define	EQUAL	296
# define	NOT_EQUAL	297
# define	LOGICAL_AND	298
# define	LOGICAL_OR	299


extern YYSTYPE yylval;

#endif /* not BISON_PARSE_H */
