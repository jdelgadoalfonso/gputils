/* A Bison parser, made from parse.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

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

#line 1 "parse.y"

/* Parser
   Copyright (C) 2003 
   Craig Franklin

This file is part of gputils.

gputils is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

gputils is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with gputils; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include "stdhdr.h"

#include "libgputils.h"
#include "gpal.h"
#include "scan.h"

void
yyerror(char *message)
{

  gp_num_errors++;

  if (gp_quiet != 0)
    return;

  assert(message != NULL);
  
  if (state.src) {
    printf("%s:%d:%s\n", state.src->name, state.src->line_number, message);
  } else {
    printf("error: %s\n", message);
  }

  return;
}

int yylex(void);

static tree *case_ident;


#line 57 "parse.y"
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
#ifndef YYDEBUG
# define YYDEBUG 1
#endif



#define	YYFINAL		222
#define	YYFLAG		-32768
#define	YYNTBASE	69

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 301 ? yytranslate[x] : 108)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      63,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    61,     2,     2,     2,    60,    50,     2,
      64,    65,    58,    56,    66,    57,     2,    59,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    40,    39,
      48,    55,    49,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    67,     2,    68,    52,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    51,     2,    62,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    41,    42,    43,    44,    45,    46,    47,
      53,    54
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     8,    12,    18,    25,    31,    38,
      40,    43,    47,    49,    51,    57,    61,    69,    75,    81,
      90,    98,   100,   105,   107,   111,   116,   118,   120,   122,
     128,   133,   135,   138,   144,   152,   154,   156,   158,   161,
     164,   168,   171,   179,   188,   189,   198,   204,   208,   210,
     213,   218,   224,   227,   232,   238,   243,   249,   253,   255,
     259,   261,   263,   267,   269,   271,   275,   277,   279,   281,
     285,   287,   289,   291,   293,   297,   299,   301,   303,   305,
     307,   309,   311,   315,   317,   319,   321,   325,   327,   329,
     331,   335,   337,   339,   341,   343,   346,   348,   350,   352,
     354,   356,   358,   363,   367,   372,   374
};
static const short yyrhs[] =
{
      -1,    69,    70,     0,    69,     1,    63,     0,    34,    36,
      39,     0,    18,    16,     9,    18,    39,     0,    18,    16,
      71,     9,    18,    39,     0,    24,    16,     9,    24,    39,
       0,    24,    16,    71,     9,    24,    39,     0,    72,     0,
      72,    71,     0,    22,    90,    39,     0,    73,     0,    80,
       0,    23,    74,    78,    23,    39,     0,    23,    74,    39,
       0,    12,    74,    25,    36,    78,    12,    39,     0,    12,
      74,    25,    36,    39,     0,    28,    36,    16,    36,    39,
       0,    28,    36,    16,     3,    88,    20,    36,    39,     0,
      28,    36,    16,    64,    89,    65,    39,     0,    36,     0,
      36,    64,    75,    65,     0,    76,     0,    76,    66,    75,
       0,    36,    40,    77,    36,     0,    14,     0,    15,     0,
      29,     0,    16,    79,     6,    82,     9,     0,    16,     6,
      82,     9,     0,    80,     0,    80,    79,     0,    81,    36,
      40,    36,    39,     0,    81,    36,    40,    36,    55,    90,
      39,     0,     5,     0,    30,     0,    83,     0,    83,    82,
       0,    19,    39,     0,    25,    90,    39,     0,    35,    39,
       0,    13,    90,    26,    82,     9,    13,    39,     0,    13,
      90,    26,    82,    85,     9,    13,    39,     0,     0,     4,
      36,    84,    16,    86,     9,     4,    39,     0,    11,    36,
      14,    88,    87,     0,    33,    90,    87,     0,    87,     0,
      90,    39,     0,     8,    90,    26,    82,     0,     8,    90,
      26,    82,    85,     0,     7,    82,     0,    32,   107,    43,
      82,     0,    32,   107,    43,    82,    86,     0,    32,    21,
      43,    82,     0,    17,    82,     9,    17,    39,     0,    90,
      27,    90,     0,    90,     0,    90,    66,    89,     0,    91,
       0,    93,     0,    91,    92,    93,     0,    55,     0,    95,
       0,    93,    94,    95,     0,    53,     0,    54,     0,    97,
       0,    95,    96,    97,     0,    50,     0,    51,     0,    52,
       0,    99,     0,    97,    98,    99,     0,    48,     0,    49,
       0,    46,     0,    47,     0,    44,     0,    45,     0,   101,
       0,    99,   100,   101,     0,    41,     0,    42,     0,   103,
       0,   101,   102,   103,     0,    56,     0,    57,     0,   105,
       0,   103,   104,   105,     0,    58,     0,    59,     0,    60,
       0,   107,     0,   106,   107,     0,    57,     0,    61,     0,
      62,     0,    56,     0,    38,     0,    36,     0,    36,    67,
      90,    68,     0,    36,    64,    65,     0,    36,    64,    89,
      65,     0,    37,     0,    64,    90,    65,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   120,   122,   124,   128,   133,   138,   143,   148,   155,
     160,   167,   172,   177,   182,   187,   192,   197,   204,   210,
     216,   224,   229,   236,   241,   248,   255,   257,   258,   261,
     266,   273,   278,   285,   291,   298,   303,   310,   315,   322,
     327,   332,   337,   342,   347,   347,   352,   371,   376,   381,
     388,   394,   399,   407,   413,   418,   426,   433,   441,   446,
     453,   455,   457,   464,   466,   468,   475,   476,   478,   480,
     487,   488,   489,   491,   493,   500,   501,   502,   503,   504,
     505,   507,   509,   516,   517,   519,   521,   528,   529,   531,
     533,   540,   541,   542,   544,   546,   553,   554,   555,   556,
     558,   563,   568,   573,   579,   585,   590
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "ARRAY", "CASE", "CONST_KEY", "BEGIN_KEY", 
  "ELSE", "ELSIF", "END", "EXTERN_STORAGE", "FOR", "FUNCTION_TOK", "IF", 
  "IN", "INOUT", "IS", "LOOP", "MODULE", "NULL_TOK", "OF", "OTHERS", 
  "PRAGMA", "PROCEDURE", "PUBLIC_STORAGE", "RETURN", "THEN", "TO", "TYPE", 
  "OUT", "VAR_KEY", "VOLATILE_STORAGE", "WHEN", "WHILE", "WITH", "ASM", 
  "IDENT", "NUMBER", "STRING", "';'", "':'", "LSH", "RSH", "ARROW", 
  "GREATER_EQUAL", "LESS_EQUAL", "EQUAL", "NOT_EQUAL", "'<'", "'>'", 
  "'&'", "'|'", "'^'", "LOGICAL_AND", "LOGICAL_OR", "'='", "'+'", "'-'", 
  "'*'", "'/'", "'%'", "'!'", "'~'", "'\\n'", "'('", "')'", "','", "'['", 
  "']'", "program", "entity", "element_list", "element", "type", "head", 
  "arg_list", "arg", "arg_direction", "body", "decl_block", "decl", 
  "decl_key", "statement_block", "statement", "@1", "if_body", 
  "case_body", "loop_statement", "range", "parameter_list", "expr", "e8", 
  "e8op", "e7", "e7op", "e6", "e6op", "e5", "e5op", "e4", "e4op", "e3", 
  "e3op", "e2", "e2op", "e1", "e1op", "e0", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    69,    69,    69,    70,    70,    70,    70,    70,    71,
      71,    72,    72,    72,    72,    72,    72,    72,    73,    73,
      73,    74,    74,    75,    75,    76,    77,    77,    77,    78,
      78,    79,    79,    80,    80,    81,    81,    82,    82,    83,
      83,    83,    83,    83,    84,    83,    83,    83,    83,    83,
      85,    85,    85,    86,    86,    86,    87,    88,    89,    89,
      90,    91,    91,    92,    93,    93,    94,    94,    95,    95,
      96,    96,    96,    97,    97,    98,    98,    98,    98,    98,
      98,    99,    99,   100,   100,   101,   101,   102,   102,   103,
     103,   104,   104,   104,   105,   105,   106,   106,   106,   106,
     107,   107,   107,   107,   107,   107,   107
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     3,     3,     5,     6,     5,     6,     1,
       2,     3,     1,     1,     5,     3,     7,     5,     5,     8,
       7,     1,     4,     1,     3,     4,     1,     1,     1,     5,
       4,     1,     2,     5,     7,     1,     1,     1,     2,     2,
       3,     2,     7,     8,     0,     8,     5,     3,     1,     2,
       4,     5,     2,     4,     5,     4,     5,     3,     1,     3,
       1,     1,     3,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     4,     3,     4,     1,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       0,    35,     0,     0,     0,     0,     0,    36,     0,     9,
      12,    13,     0,     0,     0,     4,     0,    21,     0,   101,
     105,   100,    99,    96,    97,    98,     0,     0,    60,    61,
      64,    68,    73,    81,    85,    89,     0,    94,     0,     0,
       0,    10,     0,     0,     0,     5,     0,     0,     0,     0,
       0,    11,    63,     0,    66,    67,     0,    70,    71,    72,
       0,    79,    80,    77,    78,    75,    76,     0,    83,    84,
       0,    87,    88,     0,    91,    92,    93,     0,    95,     0,
      15,     0,     0,     0,     0,     7,     0,     0,     0,    23,
       0,   103,     0,    58,     0,   106,    62,    65,    69,    74,
      82,    86,    90,     0,     0,    31,     0,     0,     0,     0,
       6,     0,     8,     0,    22,     0,    17,     0,   104,     0,
     102,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,    48,     0,     0,    32,    14,     0,     0,    18,     0,
      33,     0,    26,    27,    28,     0,    24,     0,    59,    44,
       0,     0,     0,    39,     0,     0,    41,    30,    38,    49,
       0,     0,     0,     0,     0,    25,    16,     0,     0,     0,
       0,    40,    47,    29,     0,    57,    20,    34,     0,     0,
       0,     0,    19,     0,     0,    46,     0,     0,     0,     0,
      56,     0,     0,     0,    52,     0,     0,     0,     0,     0,
       0,     0,    42,     0,    55,    53,    45,    50,    43,    54,
      51,     0,     0
};

static const short yydefgoto[] =
{
       1,     6,    18,    19,    20,    28,    98,    99,   155,    91,
     114,    21,    22,   139,   140,   177,   199,   194,   141,   146,
     102,   142,    38,    63,    39,    66,    40,    70,    41,    77,
      42,    80,    43,    83,    44,    87,    45,    46,    47
};

static const short yypact[] =
{
  -32768,     6,   -43,     7,    15,    -1,-32768,-32768,   122,   131,
      30,-32768,    60,    44,    64,    44,    49,-32768,    34,   144,
  -32768,-32768,    52,    80,   115,-32768,    90,    66,   107,   -48,
  -32768,-32768,-32768,-32768,-32768,-32768,    64,    94,    83,    -3,
      43,    62,    33,    10,    54,-32768,   -23,-32768,    16,   119,
     121,-32768,   101,   103,   123,-32768,   110,   124,    25,    64,
      86,-32768,-32768,    64,-32768,-32768,    64,-32768,-32768,-32768,
      64,-32768,-32768,-32768,-32768,-32768,-32768,    64,-32768,-32768,
      64,-32768,-32768,    64,-32768,-32768,-32768,    64,-32768,    12,
  -32768,   132,     1,   118,   126,-32768,   129,   125,    98,   104,
      17,-32768,   106,   111,   105,-32768,    -3,    43,    62,    33,
      10,    54,-32768,    35,   163,     4,   136,    64,   137,    64,
  -32768,   -34,-32768,    69,-32768,   110,-32768,   166,-32768,    64,
  -32768,   143,   145,    64,    35,   141,    64,    64,   146,   173,
      35,-32768,   147,    35,-32768,-32768,   164,   160,-32768,   127,
  -32768,    64,-32768,-32768,-32768,   152,-32768,   150,-32768,-32768,
     176,   165,   184,-32768,   155,   178,-32768,-32768,-32768,-32768,
     187,   161,    64,   159,   162,-32768,-32768,   183,    64,    35,
     185,-32768,-32768,-32768,   167,-32768,-32768,-32768,   168,   178,
     109,   169,-32768,   -11,   194,-32768,    35,    64,   191,   196,
  -32768,   170,   171,   203,-32768,   186,   172,   197,    35,    35,
     177,    35,-32768,   179,-32768,   168,-32768,    50,-32768,-32768,
  -32768,   209,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,    19,-32768,-32768,   200,    92,-32768,-32768,   120,
     108,   -86,-32768,  -132,-32768,-32768,     2,     9,  -153,    47,
     -70,   -14,-32768,-32768,   158,-32768,   156,-32768,   157,-32768,
     149,-32768,   148,-32768,   151,-32768,   142,-32768,   -45
};


#define	YYLAST		234


static const short yytable[] =
{
      37,    88,   162,   115,   117,   150,   221,     2,   168,    11,
     201,   170,   182,    29,    30,    31,    58,    11,   113,    59,
       7,   151,    60,     8,     3,    29,    30,    31,    24,   115,
       4,     9,    89,    89,    17,    10,   195,   118,    51,   131,
       5,    36,    17,    50,   103,   104,   132,   190,   133,   149,
      64,    65,   134,    36,   135,    90,   126,   196,   197,   158,
     136,    29,    30,    31,   204,   119,    81,    82,   137,    25,
     138,    29,    30,    31,    78,    79,   214,   215,    26,   217,
      27,    32,    33,   152,   153,    49,    34,    35,    52,    36,
     101,    32,    33,    67,    68,    69,    34,    35,   154,    36,
      29,    30,    31,   147,    53,   103,    71,    72,    73,    74,
      75,    76,    84,    85,    86,   103,   196,   197,   198,   161,
      32,    33,   164,   165,    54,    34,    35,    11,    36,    55,
      56,    12,    57,    61,    13,    92,    11,   174,    62,    93,
      23,    94,    95,    13,    14,    15,    97,    96,   202,    11,
      16,   105,    17,    14,    15,   116,    13,   120,   185,    16,
     100,    17,   121,   124,   147,   123,    14,    15,   122,   143,
     125,   128,    16,   130,    17,   145,   148,   129,   157,   159,
     163,   160,   167,   205,   171,   166,   169,   172,   175,   176,
     178,   179,   173,   180,   181,   134,   183,   184,   186,   188,
     193,   187,   191,   203,   206,   207,   192,   210,   200,   222,
     213,   212,   211,   208,   209,    48,   216,   156,   218,   220,
     127,   106,   107,   144,   219,   189,   109,   108,   110,   112,
       0,     0,     0,     0,   111
};

static const short yycheck[] =
{
      14,    46,   134,    89,     3,    39,     0,     1,   140,     5,
      21,   143,   165,    36,    37,    38,    64,     5,     6,    67,
      63,    55,    36,    16,    18,    36,    37,    38,     9,   115,
      24,    16,    16,    16,    30,    36,   189,    36,    19,     4,
      34,    64,    30,     9,    58,    59,    11,   179,    13,   119,
      53,    54,    17,    64,    19,    39,    39,     7,     8,   129,
      25,    36,    37,    38,   196,    64,    56,    57,    33,    39,
      35,    36,    37,    38,    41,    42,   208,   209,    18,   211,
      36,    56,    57,    14,    15,    36,    61,    62,    36,    64,
      65,    56,    57,    50,    51,    52,    61,    62,    29,    64,
      36,    37,    38,   117,    24,   119,    44,    45,    46,    47,
      48,    49,    58,    59,    60,   129,     7,     8,     9,   133,
      56,    57,   136,   137,     9,    61,    62,     5,    64,    39,
      64,     9,    25,    39,    12,    16,     5,   151,    55,    18,
       9,    40,    39,    12,    22,    23,    36,    24,   193,     5,
      28,    65,    30,    22,    23,    23,    12,    39,   172,    28,
      36,    30,    36,    65,   178,    40,    22,    23,    39,     6,
      66,    65,    28,    68,    30,    39,    39,    66,    12,    36,
      39,    36,     9,   197,    20,    39,    39,    27,    36,    39,
      14,    26,    65,     9,    39,    17,     9,    36,    39,    16,
      32,    39,    17,     9,    13,     9,    39,     4,    39,     0,
      13,    39,    26,    43,    43,    15,    39,   125,    39,   217,
     100,    63,    66,   115,   215,   178,    77,    70,    80,    87,
      -1,    -1,    -1,    -1,    83
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

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

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

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
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


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
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
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
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


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
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
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

#ifdef YYERROR_VERBOSE

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
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
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
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
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

  if (yyssp >= yyss + yystacksize - 1)
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
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
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
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
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
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 4:
#line 130 "parse.y"
{
	  open_src(yyvsp[-1].s, source_with);
	}
    break;
case 5:
#line 135 "parse.y"
{
	  gp_warning("empty module");
	}
    break;
case 6:
#line 140 "parse.y"
{
	  add_entity(mk_file(yyvsp[-3].t, state.src->type));
	}
    break;
case 7:
#line 145 "parse.y"
{
	  gp_warning("empty public");
	}
    break;
case 8:
#line 150 "parse.y"
{
	  add_entity(mk_file(yyvsp[-3].t, state.src->type));
	}
    break;
case 9:
#line 157 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 10:
#line 162 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 11:
#line 169 "parse.y"
{
	  yyval.t = mk_pragma(yyvsp[-1].t);
	}
    break;
case 12:
#line 174 "parse.y"
{
	  yyval.t = yyvsp[0].t;
        }
    break;
case 13:
#line 179 "parse.y"
{
	  yyval.t = yyvsp[0].t;
        }
    break;
case 14:
#line 184 "parse.y"
{ 
	  yyval.t = mk_proc(yyvsp[-3].t, yyvsp[-2].t);
     	}
    break;
case 15:
#line 189 "parse.y"
{ 
	  yyval.t = mk_proc(yyvsp[-1].t, NULL);
     	}
    break;
case 16:
#line 194 "parse.y"
{ 
	  yyval.t = mk_func(yyvsp[-5].t, yyvsp[-3].s, yyvsp[-2].t);
     	}
    break;
case 17:
#line 199 "parse.y"
{ 
	  yyval.t = mk_func(yyvsp[-3].t, yyvsp[-1].s, NULL);
     	}
    break;
case 18:
#line 206 "parse.y"
{
	  /* alias */
	  yyval.t = mk_type(yyvsp[-3].s, NULL, NULL, NULL, yyvsp[-1].s);
        }
    break;
case 19:
#line 212 "parse.y"
{
	  /* array */
	  yyval.t = mk_type(yyvsp[-6].s, yyvsp[-3].r.start, yyvsp[-3].r.end, NULL, yyvsp[-1].s);
        }
    break;
case 20:
#line 218 "parse.y"
{
	  /* enumerated type */
	  yyval.t = mk_type(yyvsp[-5].s, NULL, NULL, yyvsp[-2].t, NULL);
        }
    break;
case 21:
#line 226 "parse.y"
{
 	  yyval.t = mk_head(yyvsp[0].s, NULL);
     	}
    break;
case 22:
#line 231 "parse.y"
{
 	  yyval.t = mk_head(yyvsp[-3].s, yyvsp[-1].t);
     	}
    break;
case 23:
#line 238 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 24:
#line 243 "parse.y"
{
	  yyval.t = node_list(yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 25:
#line 250 "parse.y"
{	  
	  yyval.t = mk_arg(yyvsp[-3].s, yyvsp[-1].d, yyvsp[0].s);
        }
    break;
case 26:
#line 256 "parse.y"
{ yyval.d = dir_in; }
    break;
case 27:
#line 257 "parse.y"
{ yyval.d = dir_inout; }
    break;
case 28:
#line 258 "parse.y"
{ yyval.d = dir_out; }
    break;
case 29:
#line 263 "parse.y"
{
 	  yyval.t = mk_body(yyvsp[-3].t, yyvsp[-1].t);
     	}
    break;
case 30:
#line 268 "parse.y"
{
 	  yyval.t = mk_body(NULL, yyvsp[-1].t);
     	}
    break;
case 31:
#line 275 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 32:
#line 280 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 33:
#line 288 "parse.y"
{ 
	  yyval.t = mk_decl(yyvsp[-4].k, yyvsp[-1].s, yyvsp[-3].s, NULL);
        }
    break;
case 34:
#line 293 "parse.y"
{ 
	  yyval.t = mk_decl(yyvsp[-6].k, yyvsp[-3].s, yyvsp[-5].s, yyvsp[-1].t);
        }
    break;
case 35:
#line 300 "parse.y"
{
	  yyval.k = key_const;
	}
    break;
case 36:
#line 305 "parse.y"
{
	  yyval.k = key_var;
	}
    break;
case 37:
#line 312 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 38:
#line 317 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 39:
#line 324 "parse.y"
{
	  yyval.t = mk_assembly(strdup("  nop"));
	}
    break;
case 40:
#line 329 "parse.y"
{
	  yyval.t = mk_return(yyvsp[-1].t);
	}
    break;
case 41:
#line 334 "parse.y"
{
	  yyval.t = mk_assembly(yyvsp[-1].s);
	}
    break;
case 42:
#line 339 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-5].t, yyvsp[-3].t, NULL);
	}
    break;
case 43:
#line 344 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-6].t, yyvsp[-4].t, yyvsp[-3].t);
	}
    break;
case 44:
#line 348 "parse.y"
{ case_ident = mk_symbol(yyvsp[0].s, NULL); }
    break;
case 45:
#line 349 "parse.y"
{
	  yyval.t = yyvsp[-3].t;
	}
    break;
case 46:
#line 354 "parse.y"
{
	  tree *init;
          tree *exit;
          tree *increment;
          
          /* IDENT = range.start; */
          init = mk_binop(op_eq, mk_symbol(yyvsp[-3].s, NULL), yyvsp[-1].r.start);
          
          /* IDENT = IDENT + 1; */
          increment = mk_binop(op_eq, mk_symbol(yyvsp[-3].s, NULL), 
                               mk_binop(op_add, mk_symbol(yyvsp[-3].s, NULL), mk_constant(1)));
          
          /* while (IDENT <= range.end) then loop */
          exit = mk_binop(op_lte, mk_symbol(yyvsp[-3].s, NULL), yyvsp[-1].r.end);

	  yyval.t = mk_loop(init, exit, increment, yyvsp[0].t);
	}
    break;
case 47:
#line 373 "parse.y"
{
	  yyval.t= mk_loop(NULL, yyvsp[-1].t, NULL, yyvsp[0].t);	
	}
    break;
case 48:
#line 378 "parse.y"
{
	  yyval.t= mk_loop(NULL, NULL, NULL, yyvsp[0].t);
	}
    break;
case 49:
#line 383 "parse.y"
{
	  yyval.t = yyvsp[-1].t;
	}
    break;
case 50:
#line 390 "parse.y"
{
	  /* last statement is elsif */
	  yyval.t = mk_cond(yyvsp[-2].t, yyvsp[0].t, NULL);
	}
    break;
case 51:
#line 396 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-3].t, yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 52:
#line 401 "parse.y"
{
	  /* last statement is else */
	  yyval.t = mk_cond(NULL, yyvsp[0].t, NULL);
	}
    break;
case 53:
#line 409 "parse.y"
{
	  /* last statement is elsif equivalent */
	  yyval.t = mk_cond(mk_binop(op_eq, case_ident, yyvsp[-2].t), yyvsp[0].t, NULL);
	}
    break;
case 54:
#line 415 "parse.y"
{
	  yyval.t = mk_cond(mk_binop(op_eq, case_ident, yyvsp[-3].t), yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 55:
#line 420 "parse.y"
{
	  /* last statement is else equivalent */
	  yyval.t = mk_cond(NULL, yyvsp[0].t, NULL);
	}
    break;
case 56:
#line 428 "parse.y"
{
	  yyval.t = yyvsp[-3].t;
	}
    break;
case 57:
#line 435 "parse.y"
{
	  yyval.r.start = yyvsp[-2].t;
	  yyval.r.end = yyvsp[0].t;
        }
    break;
case 58:
#line 443 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 59:
#line 448 "parse.y"
{
	  yyval.t = node_list(yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 62:
#line 459 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 63:
#line 464 "parse.y"
{ yyval.o = op_eq; }
    break;
case 65:
#line 470 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 66:
#line 475 "parse.y"
{ yyval.o = op_land; }
    break;
case 67:
#line 476 "parse.y"
{ yyval.o = op_lor; }
    break;
case 69:
#line 482 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 70:
#line 487 "parse.y"
{ yyval.o = op_and; }
    break;
case 71:
#line 488 "parse.y"
{ yyval.o = op_or; }
    break;
case 72:
#line 489 "parse.y"
{ yyval.o = op_xor; }
    break;
case 74:
#line 495 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 75:
#line 500 "parse.y"
{ yyval.o = op_lt; }
    break;
case 76:
#line 501 "parse.y"
{ yyval.o = op_gt; }
    break;
case 77:
#line 502 "parse.y"
{ yyval.o = op_eq; }
    break;
case 78:
#line 503 "parse.y"
{ yyval.o = op_ne; }
    break;
case 79:
#line 504 "parse.y"
{ yyval.o = op_gte; }
    break;
case 80:
#line 505 "parse.y"
{ yyval.o = op_lte; }
    break;
case 82:
#line 511 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 83:
#line 516 "parse.y"
{ yyval.o = op_lsh; }
    break;
case 84:
#line 517 "parse.y"
{ yyval.o = op_rsh; }
    break;
case 86:
#line 523 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 87:
#line 528 "parse.y"
{ yyval.o = op_add; }
    break;
case 88:
#line 529 "parse.y"
{ yyval.o = op_sub; }
    break;
case 90:
#line 535 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 91:
#line 540 "parse.y"
{ yyval.o = op_mult; }
    break;
case 92:
#line 541 "parse.y"
{ yyval.o = op_div; }
    break;
case 93:
#line 542 "parse.y"
{ yyval.o = op_mod; }
    break;
case 95:
#line 548 "parse.y"
{
	  yyval.t = mk_unop(yyvsp[-1].o, yyvsp[0].t);
	}
    break;
case 96:
#line 553 "parse.y"
{ yyval.o = op_neg; }
    break;
case 97:
#line 554 "parse.y"
{ yyval.o = op_not; }
    break;
case 98:
#line 555 "parse.y"
{ yyval.o = op_com; }
    break;
case 99:
#line 556 "parse.y"
{ yyval.o = op_add; }
    break;
case 100:
#line 560 "parse.y"
{
	  yyval.t = mk_string(yyvsp[0].s);
        }
    break;
case 101:
#line 565 "parse.y"
{
	  yyval.t = mk_symbol(yyvsp[0].s, NULL);
        }
    break;
case 102:
#line 570 "parse.y"
{
	  yyval.t = mk_symbol(yyvsp[-3].s, yyvsp[-1].t);
        }
    break;
case 103:
#line 575 "parse.y"
{
	  /* function or procedure call */
	  yyval.t = mk_call(yyvsp[-2].s, NULL);
	}
    break;
case 104:
#line 581 "parse.y"
{
	  /* function or procedure call with arguments */
	  yyval.t = mk_call(yyvsp[-3].s, yyvsp[-1].t);
	}
    break;
case 105:
#line 587 "parse.y"
{
	  yyval.t = mk_constant(yyvsp[0].i);
	}
    break;
case 106:
#line 592 "parse.y"
{
	  yyval.t = yyvsp[-1].t;
	}
    break;
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
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

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 597 "parse.y"

