/* A Bison parser, made from parse.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

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
  enum node_type y;
  enum node_size z;
  enum node_op o;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 1
#endif



#define	YYFINAL		197
#define	YYFLAG		-32768
#define	YYNTBASE	63

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 298 ? yytranslate[x] : 101)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      59,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,     2,     2,     2,    56,    46,     2,
      60,    61,    54,    52,    62,    53,     2,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
      44,    51,    45,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    47,     2,    58,     2,     2,     2,
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
      37,    38,    39,    40,    41,    42,    43,    49,    50
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     8,    12,    18,    25,    31,    38,
      40,    43,    47,    49,    55,    59,    67,    73,    75,    80,
      82,    86,    89,    95,   100,   102,   105,   110,   117,   119,
     121,   123,   125,   127,   130,   133,   136,   144,   153,   154,
     163,   169,   173,   175,   178,   183,   189,   192,   197,   203,
     208,   214,   218,   220,   224,   226,   228,   232,   234,   236,
     240,   242,   244,   246,   250,   252,   254,   256,   258,   262,
     264,   266,   268,   270,   272,   274,   276,   280,   282,   284,
     286,   290,   292,   294,   296,   300,   302,   304,   306,   308,
     311,   313,   315,   317,   319,   321,   323,   327,   332,   334
};
static const short yyrhs[] =
{
      -1,    63,    64,     0,    63,     1,    59,     0,    31,    33,
      36,     0,    18,    16,    10,    18,    36,     0,    18,    16,
      65,    10,    18,    36,     0,    23,    16,    10,    23,    36,
       0,    23,    16,    65,    10,    23,    36,     0,    66,     0,
      66,    65,     0,    21,    83,    36,     0,    72,     0,    22,
      67,    70,    22,    36,     0,    22,    67,    36,     0,    13,
      67,    24,    74,    70,    13,    36,     0,    13,    67,    24,
      74,    36,     0,    33,     0,    33,    60,    68,    61,     0,
      69,     0,    69,    62,    68,     0,    74,    33,     0,    16,
      71,     5,    75,    10,     0,    16,     5,    75,    10,     0,
      72,     0,    72,    71,     0,    73,    74,    33,    36,     0,
      73,    74,    33,    51,    83,    36,     0,     4,     0,    27,
       0,     6,     0,     7,     0,    76,     0,    76,    75,     0,
      19,    36,     0,    32,    36,     0,    14,    83,    25,    75,
      10,    14,    36,     0,    14,    83,    25,    75,    78,    10,
      14,    36,     0,     0,     3,    33,    77,    16,    79,    10,
       3,    36,     0,    12,    33,    15,    81,    80,     0,    30,
      83,    80,     0,    80,     0,    83,    36,     0,     9,    83,
      25,    75,     0,     9,    83,    25,    75,    78,     0,     8,
      75,     0,    29,   100,    39,    75,     0,    29,   100,    39,
      75,    79,     0,    29,    20,    39,    75,     0,    17,    75,
      10,    17,    36,     0,    83,    26,    83,     0,    83,     0,
      83,    62,    82,     0,    84,     0,    86,     0,    84,    85,
      86,     0,    51,     0,    88,     0,    86,    87,    88,     0,
      49,     0,    50,     0,    90,     0,    88,    89,    90,     0,
      46,     0,    47,     0,    48,     0,    92,     0,    90,    91,
      92,     0,    44,     0,    45,     0,    42,     0,    43,     0,
      40,     0,    41,     0,    94,     0,    92,    93,    94,     0,
      37,     0,    38,     0,    96,     0,    94,    95,    96,     0,
      52,     0,    53,     0,    98,     0,    96,    97,    98,     0,
      54,     0,    55,     0,    56,     0,   100,     0,    99,   100,
       0,    53,     0,    57,     0,    58,     0,    52,     0,    35,
       0,    33,     0,    33,    60,    61,     0,    33,    60,    82,
      61,     0,    34,     0,    60,    83,    61,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   119,   121,   123,   127,   132,   137,   142,   147,   154,
     159,   166,   171,   176,   181,   186,   191,   198,   203,   210,
     215,   222,   229,   234,   241,   246,   253,   258,   265,   270,
     277,   282,   289,   294,   301,   306,   311,   316,   321,   321,
     326,   345,   350,   355,   362,   368,   373,   381,   387,   392,
     400,   407,   415,   420,   427,   429,   431,   438,   440,   442,
     449,   450,   452,   454,   461,   462,   463,   465,   467,   474,
     475,   476,   477,   478,   479,   481,   483,   490,   491,   493,
     495,   502,   503,   505,   507,   514,   515,   516,   518,   520,
     527,   528,   529,   530,   532,   537,   542,   548,   554,   559
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "CASE", "CONST_TYPE", "BEGIN_KEY", 
  "BIT_SIZE", "BYTE_SIZE", "ELSE", "ELSIF", "END", "EXTERN_STORAGE", 
  "FOR", "FUNCTION_TOK", "IF", "IN", "IS", "LOOP", "MODULE", "NULL_TOK", 
  "OTHERS", "PRAGMA", "PROCEDURE", "PUBLIC_STORAGE", "RETURN", "THEN", 
  "TO", "VAR_TYPE", "VOLATILE_STORAGE", "WHEN", "WHILE", "WITH", "ASM", 
  "IDENT", "NUMBER", "STRING", "';'", "LSH", "RSH", "ARROW", 
  "GREATER_EQUAL", "LESS_EQUAL", "EQUAL", "NOT_EQUAL", "'<'", "'>'", 
  "'&'", "'|'", "'^'", "LOGICAL_AND", "LOGICAL_OR", "'='", "'+'", "'-'", 
  "'*'", "'/'", "'%'", "'!'", "'~'", "'\\n'", "'('", "')'", "','", 
  "program", "entity", "element_list", "element", "head", "arg_list", 
  "arg", "body", "decl_block", "decl", "decl_type", "decl_size", 
  "statement_block", "statement", "@1", "if_body", "case_body", 
  "loop_statement", "range", "parameter_list", "expr", "e8", "e8op", "e7", 
  "e7op", "e6", "e6op", "e5", "e5op", "e4", "e4op", "e3", "e3op", "e2", 
  "e2op", "e1", "e1op", "e0", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    63,    63,    63,    64,    64,    64,    64,    64,    65,
      65,    66,    66,    66,    66,    66,    66,    67,    67,    68,
      68,    69,    70,    70,    71,    71,    72,    72,    73,    73,
      74,    74,    75,    75,    76,    76,    76,    76,    77,    76,
      76,    76,    76,    76,    78,    78,    78,    79,    79,    79,
      80,    81,    82,    82,    83,    84,    84,    85,    86,    86,
      87,    87,    88,    88,    89,    89,    89,    90,    90,    91,
      91,    91,    91,    91,    91,    92,    92,    93,    93,    94,
      94,    95,    95,    96,    96,    97,    97,    97,    98,    98,
      99,    99,    99,    99,   100,   100,   100,   100,   100,   100
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     3,     3,     5,     6,     5,     6,     1,
       2,     3,     1,     5,     3,     7,     5,     1,     4,     1,
       3,     2,     5,     4,     1,     2,     4,     6,     1,     1,
       1,     1,     1,     2,     2,     2,     7,     8,     0,     8,
       5,     3,     1,     2,     4,     5,     2,     4,     5,     4,
       5,     3,     1,     3,     1,     1,     3,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     3,     4,     1,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       0,    28,     0,     0,     0,     0,    29,     0,     9,    12,
       0,     0,     0,     4,     0,    17,     0,    95,    98,    94,
      93,    90,    91,    92,     0,     0,    54,    55,    58,    62,
      67,    75,    79,    83,     0,    88,     0,     0,    10,    30,
      31,     0,     0,     0,     5,     0,     0,     0,     0,    11,
      57,     0,    60,    61,     0,    64,    65,    66,     0,    73,
      74,    71,    72,    69,    70,     0,    77,    78,     0,    81,
      82,     0,    85,    86,    87,     0,    89,     0,    14,     0,
       0,     0,     7,     0,     0,    19,     0,     0,    96,     0,
      52,    99,    56,    59,    63,    68,    76,    80,    84,     0,
       0,    24,     0,     6,    26,     0,     8,    18,     0,    21,
      16,     0,    97,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    32,    42,     0,     0,    25,    13,     0,    20,
       0,    53,    38,     0,     0,     0,    34,     0,    35,    23,
      33,    43,     0,    27,    15,     0,     0,     0,     0,    41,
      22,     0,     0,     0,     0,     0,     0,     0,    40,     0,
       0,     0,     0,     0,    50,     0,     0,     0,    51,    46,
       0,     0,     0,     0,     0,     0,     0,    36,     0,    49,
      47,    39,    44,    37,    48,    45,     0,     0
};

static const short yydefgoto[] =
{
       1,     6,    17,    18,    26,    94,    95,    89,   110,    19,
      20,    96,   131,   132,   155,   173,   167,   133,   162,    99,
     134,    36,    61,    37,    64,    38,    68,    39,    75,    40,
      78,    41,    81,    42,    85,    43,    44,    45
};

static const short yypact[] =
{
  -32768,    11,   -21,    35,    44,    48,-32768,-32768,    76,   100,
      60,-32768,    66,    73,    42,    73,-32768,    98,   103,-32768,
      72,    88,   104,-32768,    84,    77,   102,    78,-32768,-32768,
  -32768,-32768,-32768,-32768,    42,   105,    85,   -31,    22,    12,
      55,    82,    63,-32768,   -20,-32768,     5,   121,-32768,-32768,
  -32768,   107,   108,   122,-32768,    72,    72,    30,    86,-32768,
  -32768,    42,-32768,-32768,    42,-32768,-32768,-32768,    42,-32768,
  -32768,-32768,-32768,-32768,-32768,    42,-32768,-32768,    42,-32768,
  -32768,    42,-32768,-32768,-32768,    42,-32768,     0,-32768,   124,
     112,   -28,-32768,   113,    89,    81,   118,    69,-32768,    91,
      92,-32768,   -31,    22,    12,    55,    82,    63,-32768,    14,
     148,    46,   125,-32768,-32768,    42,-32768,-32768,    72,-32768,
  -32768,   143,-32768,    42,   126,   127,    42,    14,   128,    42,
     129,   152,    14,-32768,   130,    14,-32768,-32768,   131,-32768,
     132,-32768,-32768,   154,   133,   153,-32768,   155,-32768,-32768,
  -32768,-32768,   160,-32768,-32768,   157,    42,    14,   158,-32768,
  -32768,   142,   155,   150,   123,   138,     2,   167,-32768,    42,
      14,    42,   164,   169,-32768,   141,   144,   178,-32768,-32768,
     159,   146,   171,    14,    14,   151,    14,-32768,   156,-32768,
     142,-32768,   120,-32768,-32768,-32768,   186,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,     7,-32768,   173,    71,-32768,    93,    80,   -81,
  -32768,   -17,  -125,-32768,-32768,     1,     4,  -138,-32768,    74,
     -14,-32768,-32768,   134,-32768,   135,-32768,   136,-32768,   137,
  -32768,   139,-32768,   115,-32768,   116,-32768,   -43
};


#define	YYLAST		217


static const short yytable[] =
{
      35,    86,   145,    51,    11,   109,   111,   150,   114,   159,
     152,   196,     2,    27,    28,    29,    22,   124,    62,    63,
      58,    87,   175,   115,   168,    48,   125,    16,   126,     3,
     111,   127,   164,   128,     4,    27,    28,    29,     7,    97,
      34,    88,     5,   100,   129,   179,   130,    27,    28,    29,
      11,     8,    69,    70,    71,    72,    73,    74,   189,   190,
       9,   192,    34,    27,    28,    29,    30,    31,    65,    66,
      67,    32,    33,    16,    34,    27,    28,    29,    49,    50,
      11,    10,    30,    31,    24,    87,    12,    32,    33,    13,
      34,    98,    76,    77,    30,    31,    23,    14,    15,    32,
      33,   138,    34,    16,    11,   120,    25,    11,    47,   100,
      21,    52,   144,    13,    53,   147,    13,    82,    83,    84,
      54,    14,    15,   176,    14,    15,    56,    16,   170,   171,
      16,   170,   171,   172,    79,    80,    60,    55,    57,    90,
      91,    59,   163,   118,    92,    93,   112,   101,   113,   116,
     117,   119,   122,   135,   123,   178,   140,   180,   157,   142,
     143,   137,   149,   158,   146,   148,   151,   153,   154,   156,
     160,   166,   127,   161,   174,   165,   169,   177,   181,   182,
     183,   185,   187,   184,   186,   188,   197,   191,    46,   139,
     121,   136,   193,   195,   194,   102,   107,   141,     0,   103,
       0,   108,     0,     0,   104,     0,     0,     0,     0,     0,
       0,     0,   105,     0,     0,     0,     0,   106
};

static const short yycheck[] =
{
      14,    44,   127,    20,     4,     5,    87,   132,    36,   147,
     135,     0,     1,    33,    34,    35,     9,     3,    49,    50,
      34,    16,    20,    51,   162,    18,    12,    27,    14,    18,
     111,    17,   157,    19,    23,    33,    34,    35,    59,    56,
      60,    36,    31,    57,    30,   170,    32,    33,    34,    35,
       4,    16,    40,    41,    42,    43,    44,    45,   183,   184,
      16,   186,    60,    33,    34,    35,    52,    53,    46,    47,
      48,    57,    58,    27,    60,    33,    34,    35,     6,     7,
       4,    33,    52,    53,    18,    16,    10,    57,    58,    13,
      60,    61,    37,    38,    52,    53,    36,    21,    22,    57,
      58,   115,    60,    27,     4,    36,    33,     4,    10,   123,
      10,    23,   126,    13,    10,   129,    13,    54,    55,    56,
      36,    21,    22,   166,    21,    22,    24,    27,     8,     9,
      27,     8,     9,    10,    52,    53,    51,    60,    60,    18,
      33,    36,   156,    62,    36,    23,    22,    61,    36,    36,
      61,    33,    61,     5,    62,   169,    13,   171,    25,    33,
      33,    36,    10,    10,    36,    36,    36,    36,    36,    15,
      10,    29,    17,    16,    36,    17,    26,    10,    14,    10,
      39,     3,    36,    39,    25,    14,     0,    36,    15,   118,
      97,   111,    36,   192,   190,    61,    81,   123,    -1,    64,
      -1,    85,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    78
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
#line 129 "parse.y"
{
	  open_src(yyvsp[-1].s, source_with);
	}
    break;
case 5:
#line 134 "parse.y"
{
	  gp_warning("empty module");
	}
    break;
case 6:
#line 139 "parse.y"
{
	  add_entity(mk_file(yyvsp[-3].t, state.src->type));
	}
    break;
case 7:
#line 144 "parse.y"
{
	  gp_warning("empty public");
	}
    break;
case 8:
#line 149 "parse.y"
{
	  add_entity(mk_file(yyvsp[-3].t, state.src->type));
	}
    break;
case 9:
#line 156 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 10:
#line 161 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 11:
#line 168 "parse.y"
{
	  yyval.t = mk_pragma(yyvsp[-1].t);
	}
    break;
case 12:
#line 173 "parse.y"
{
	  yyval.t = yyvsp[0].t;
        }
    break;
case 13:
#line 178 "parse.y"
{ 
	  yyval.t = mk_proc(yyvsp[-3].t, yyvsp[-2].t);
     	}
    break;
case 14:
#line 183 "parse.y"
{ 
	  yyval.t = mk_proc(yyvsp[-1].t, NULL);
     	}
    break;
case 15:
#line 188 "parse.y"
{ 
	  yyval.t = mk_func(yyvsp[-5].t, yyvsp[-3].z, yyvsp[-2].t);
     	}
    break;
case 16:
#line 193 "parse.y"
{ 
	  yyval.t = mk_func(yyvsp[-3].t, yyvsp[-1].z, NULL);
     	}
    break;
case 17:
#line 200 "parse.y"
{
 	  yyval.t = mk_head(yyvsp[0].s, NULL);
     	}
    break;
case 18:
#line 205 "parse.y"
{
 	  yyval.t = mk_head(yyvsp[-3].s, yyvsp[-1].t);
     	}
    break;
case 19:
#line 212 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 20:
#line 217 "parse.y"
{
	  yyval.t = node_list(yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 21:
#line 224 "parse.y"
{	  
	  yyval.t = mk_decl(type_var, yyvsp[-1].z, yyvsp[0].s, NULL);
        }
    break;
case 22:
#line 231 "parse.y"
{
 	  yyval.t = mk_body(yyvsp[-3].t, yyvsp[-1].t);
     	}
    break;
case 23:
#line 236 "parse.y"
{
 	  yyval.t = mk_body(NULL, yyvsp[-1].t);
     	}
    break;
case 24:
#line 243 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 25:
#line 248 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 26:
#line 255 "parse.y"
{ 
	  yyval.t = mk_decl(yyvsp[-3].y, yyvsp[-2].z, yyvsp[-1].s, NULL);
        }
    break;
case 27:
#line 260 "parse.y"
{ 
	  yyval.t = mk_decl(yyvsp[-5].y, yyvsp[-4].z, yyvsp[-3].s, yyvsp[-1].t);
        }
    break;
case 28:
#line 267 "parse.y"
{
	  yyval.y = type_const;
	}
    break;
case 29:
#line 272 "parse.y"
{
	  yyval.y = type_var;
	}
    break;
case 30:
#line 279 "parse.y"
{
	  yyval.z = size_bit;
	}
    break;
case 31:
#line 284 "parse.y"
{
	  yyval.z = size_byte;
	}
    break;
case 32:
#line 291 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 33:
#line 296 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 34:
#line 303 "parse.y"
{
	  yyval.t = mk_assembly(strdup("  nop"));
	}
    break;
case 35:
#line 308 "parse.y"
{
	  yyval.t = mk_assembly(yyvsp[-1].s);
	}
    break;
case 36:
#line 313 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-5].t, yyvsp[-3].t, NULL);
	}
    break;
case 37:
#line 318 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-6].t, yyvsp[-4].t, yyvsp[-3].t);
	}
    break;
case 38:
#line 322 "parse.y"
{ case_ident = mk_symbol(yyvsp[0].s); }
    break;
case 39:
#line 323 "parse.y"
{
	  yyval.t = yyvsp[-3].t;
	}
    break;
case 40:
#line 328 "parse.y"
{
	  tree *init;
          tree *exit;
          tree *increment;
          
          /* IDENT = range.start; */
          init = mk_binop(op_eq, mk_symbol(yyvsp[-3].s), yyvsp[-1].r.start);
          
          /* IDENT = IDENT + 1; */
          increment = mk_binop(op_eq, mk_symbol(yyvsp[-3].s), 
                               mk_binop(op_add, mk_symbol(yyvsp[-3].s), mk_constant(1)));
          
          /* while (IDENT <= range.end) then loop */
          exit = mk_binop(op_lte, mk_symbol(yyvsp[-3].s), yyvsp[-1].r.end);

	  yyval.t = mk_loop(init, exit, increment, yyvsp[0].t);
	}
    break;
case 41:
#line 347 "parse.y"
{
	  yyval.t= mk_loop(NULL, yyvsp[-1].t, NULL, yyvsp[0].t);	
	}
    break;
case 42:
#line 352 "parse.y"
{
	  yyval.t= mk_loop(NULL, NULL, NULL, yyvsp[0].t);
	}
    break;
case 43:
#line 357 "parse.y"
{
	  yyval.t = yyvsp[-1].t;
	}
    break;
case 44:
#line 364 "parse.y"
{
	  /* last statement is elsif */
	  yyval.t = mk_cond(yyvsp[-2].t, yyvsp[0].t, NULL);
	}
    break;
case 45:
#line 370 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-3].t, yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 46:
#line 375 "parse.y"
{
	  /* last statement is else */
	  yyval.t = mk_cond(NULL, yyvsp[0].t, NULL);
	}
    break;
case 47:
#line 383 "parse.y"
{
	  /* last statement is elsif equivalent */
	  yyval.t = mk_cond(mk_binop(op_eq, case_ident, yyvsp[-2].t), yyvsp[0].t, NULL);
	}
    break;
case 48:
#line 389 "parse.y"
{
	  yyval.t = mk_cond(mk_binop(op_eq, case_ident, yyvsp[-3].t), yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 49:
#line 394 "parse.y"
{
	  /* last statement is else equivalent */
	  yyval.t = mk_cond(NULL, yyvsp[0].t, NULL);
	}
    break;
case 50:
#line 402 "parse.y"
{
	  yyval.t = yyvsp[-3].t;
	}
    break;
case 51:
#line 409 "parse.y"
{
	  yyval.r.start = yyvsp[-2].t;
	  yyval.r.end = yyvsp[0].t;
        }
    break;
case 52:
#line 417 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 53:
#line 422 "parse.y"
{
	  yyval.t = node_list(yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 56:
#line 433 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 57:
#line 438 "parse.y"
{ yyval.o = op_eq; }
    break;
case 59:
#line 444 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 60:
#line 449 "parse.y"
{ yyval.o = op_land; }
    break;
case 61:
#line 450 "parse.y"
{ yyval.o = op_lor; }
    break;
case 63:
#line 456 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 64:
#line 461 "parse.y"
{ yyval.o = op_and; }
    break;
case 65:
#line 462 "parse.y"
{ yyval.o = op_or; }
    break;
case 66:
#line 463 "parse.y"
{ yyval.o = op_xor; }
    break;
case 68:
#line 469 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 69:
#line 474 "parse.y"
{ yyval.o = op_lt; }
    break;
case 70:
#line 475 "parse.y"
{ yyval.o = op_gt; }
    break;
case 71:
#line 476 "parse.y"
{ yyval.o = op_eq; }
    break;
case 72:
#line 477 "parse.y"
{ yyval.o = op_ne; }
    break;
case 73:
#line 478 "parse.y"
{ yyval.o = op_gte; }
    break;
case 74:
#line 479 "parse.y"
{ yyval.o = op_lte; }
    break;
case 76:
#line 485 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 77:
#line 490 "parse.y"
{ yyval.o = op_lsh; }
    break;
case 78:
#line 491 "parse.y"
{ yyval.o = op_rsh; }
    break;
case 80:
#line 497 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 81:
#line 502 "parse.y"
{ yyval.o = op_add; }
    break;
case 82:
#line 503 "parse.y"
{ yyval.o = op_sub; }
    break;
case 84:
#line 509 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 85:
#line 514 "parse.y"
{ yyval.o = op_mult; }
    break;
case 86:
#line 515 "parse.y"
{ yyval.o = op_div; }
    break;
case 87:
#line 516 "parse.y"
{ yyval.o = op_mod; }
    break;
case 89:
#line 522 "parse.y"
{
	  yyval.t = mk_unop(yyvsp[-1].o, yyvsp[0].t);
	}
    break;
case 90:
#line 527 "parse.y"
{ yyval.o = op_neg; }
    break;
case 91:
#line 528 "parse.y"
{ yyval.o = op_not; }
    break;
case 92:
#line 529 "parse.y"
{ yyval.o = op_com; }
    break;
case 93:
#line 530 "parse.y"
{ yyval.o = op_add; }
    break;
case 94:
#line 534 "parse.y"
{
	  yyval.t = mk_string(yyvsp[0].s);
        }
    break;
case 95:
#line 539 "parse.y"
{
	  yyval.t = mk_symbol(yyvsp[0].s);
        }
    break;
case 96:
#line 544 "parse.y"
{
	  /* function or procedure call */
	  yyval.t = mk_call(yyvsp[-2].s, NULL);
	}
    break;
case 97:
#line 550 "parse.y"
{
	  /* function or procedure call with arguments */
	  yyval.t = mk_call(yyvsp[-3].s, yyvsp[-1].t);
	}
    break;
case 98:
#line 556 "parse.y"
{
	  yyval.t = mk_constant(yyvsp[0].i);
	}
    break;
case 99:
#line 561 "parse.y"
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
#line 566 "parse.y"

