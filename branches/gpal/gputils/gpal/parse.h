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
# define	AND	257
# define	ARRAY	258
# define	CASE	259
# define	CONSTANT_KEY	260
# define	BEGIN_KEY	261
# define	ELSE	262
# define	ELSIF	263
# define	END	264
# define	FOR	265
# define	FUNCTION_TOK	266
# define	IF	267
# define	IN	268
# define	INOUT	269
# define	IS	270
# define	LOOP	271
# define	MOD	272
# define	MODULE	273
# define	NOT	274
# define	NULL_TOK	275
# define	OF	276
# define	OR	277
# define	OTHERS	278
# define	PRAGMA	279
# define	PROCEDURE	280
# define	PUBLIC_STORAGE	281
# define	RETURN	282
# define	THEN	283
# define	TO	284
# define	TYPE	285
# define	OUT	286
# define	VARIABLE_KEY	287
# define	WHEN	288
# define	WHILE	289
# define	WITH	290
# define	XOR	291
# define	ASM	292
# define	IDENT	293
# define	NUMBER	294
# define	STRING	295
# define	LSH	296
# define	RSH	297
# define	ARROW	298
# define	GREATER_EQUAL	299
# define	LESS_EQUAL	300
# define	EQUAL	301
# define	NOT_EQUAL	302
# define	LOGICAL_AND	303
# define	LOGICAL_OR	304


extern YYSTYPE yylval;

#endif /* not BISON_PARSE_H */
