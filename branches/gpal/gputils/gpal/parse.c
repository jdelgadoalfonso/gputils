/* A Bison parser, made from parse.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

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


#line 55 "parse.y"
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
#ifndef YYDEBUG
# define YYDEBUG 1
#endif



#define	YYFINAL		171
#define	YYFLAG		-32768
#define	YYNTBASE	56

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 291 ? yytranslate[x] : 91)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,     2,     2,    49,    39,     2,
      53,    54,    47,    45,    55,    46,     2,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
      37,    44,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    41,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    40,     2,    51,     2,     2,     2,
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
      26,    27,    28,    29,    31,    32,    33,    34,    35,    36,
      42,    43
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     8,    12,    18,    25,    31,    38,
      40,    43,    47,    49,    55,    59,    67,    73,    75,    80,
      82,    86,    89,    95,   100,   102,   105,   110,   117,   119,
     121,   123,   125,   127,   130,   133,   141,   150,   154,   156,
     159,   164,   170,   173,   179,   181,   185,   187,   189,   191,
     195,   197,   199,   203,   205,   207,   209,   213,   215,   217,
     219,   221,   225,   227,   229,   231,   233,   235,   237,   239,
     243,   245,   247,   249,   253,   255,   257,   259,   263,   265,
     267,   269,   271,   274,   276,   278,   280,   282,   284,   288,
     293,   295
};
static const short yyrhs[] =
{
      -1,    56,    57,     0,    56,     1,    52,     0,     9,    27,
      30,     0,    25,     6,     4,    25,    30,     0,    25,     6,
      58,     4,    25,    30,     0,    22,     6,     4,    22,    30,
       0,    22,     6,    58,     4,    22,    30,     0,    59,     0,
      59,    58,     0,     7,    73,    30,     0,    65,     0,     8,
      60,    63,     8,    30,     0,     8,    60,    30,     0,     5,
      60,    16,    67,    63,     5,    30,     0,     5,    60,    16,
      67,    30,     0,    27,     0,    27,    53,    61,    54,     0,
      62,     0,    62,    55,    61,     0,    67,    27,     0,     6,
      64,     3,    68,     4,     0,     6,     3,    68,     4,     0,
      65,     0,    65,    64,     0,    66,    67,    27,    30,     0,
      66,    67,    27,    44,    73,    30,     0,    18,     0,    17,
       0,    19,     0,    20,     0,    69,     0,    69,    68,     0,
      26,    30,     0,    10,    73,    11,    68,     4,    10,    30,
       0,    10,    73,    11,    68,    70,     4,    10,    30,     0,
      12,    73,    71,     0,    71,     0,    73,    30,     0,    13,
      73,    11,    68,     0,    13,    73,    11,    68,    70,     0,
      14,    68,     0,    15,    68,     4,    15,    30,     0,    73,
       0,    73,    55,    72,     0,    74,     0,    29,     0,    76,
       0,    74,    75,    76,     0,    44,     0,    78,     0,    76,
      77,    78,     0,    42,     0,    43,     0,    80,     0,    78,
      79,    80,     0,    39,     0,    40,     0,    41,     0,    82,
       0,    80,    81,    82,     0,    37,     0,    38,     0,    35,
       0,    36,     0,    33,     0,    34,     0,    84,     0,    82,
      83,    84,     0,    31,     0,    32,     0,    86,     0,    84,
      85,    86,     0,    45,     0,    46,     0,    88,     0,    86,
      87,    88,     0,    47,     0,    48,     0,    49,     0,    90,
       0,    89,    90,     0,    46,     0,    50,     0,    51,     0,
      45,     0,    27,     0,    27,    53,    54,     0,    27,    53,
      72,    54,     0,    28,     0,    53,    73,    54,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   112,   114,   116,   120,   125,   130,   135,   140,   147,
     152,   159,   164,   169,   174,   179,   184,   191,   196,   203,
     208,   215,   222,   227,   234,   239,   246,   251,   258,   263,
     270,   275,   282,   287,   294,   299,   304,   309,   314,   319,
     326,   332,   337,   345,   352,   357,   364,   366,   373,   375,
     382,   384,   386,   393,   394,   396,   398,   405,   406,   407,
     409,   411,   418,   419,   420,   421,   422,   423,   425,   427,
     434,   435,   437,   439,   446,   447,   449,   451,   458,   459,
     460,   462,   464,   471,   472,   473,   474,   476,   481,   487,
     493,   498
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "BEGIN_KEY", "END", "FUNCTION_TOK", "IS", 
  "PRAGMA", "PROCEDURE", "WITH", "IF", "THEN", "WHILE", "ELSIF", "ELSE", 
  "LOOP", "RETURN", "VAR_TYPE", "CONST_TYPE", "BIT_SIZE", "BYTE_SIZE", 
  "EXTERN_STORAGE", "PUBLIC_STORAGE", "PRIVATE_STORAGE", 
  "VOLATILE_STORAGE", "MODULE", "ASM", "IDENT", "NUMBER", "STRING", "';'", 
  "LSH", "RSH", "GREATER_EQUAL", "LESS_EQUAL", "EQUAL", "NOT_EQUAL", 
  "'<'", "'>'", "'&'", "'|'", "'^'", "LOGICAL_AND", "LOGICAL_OR", "'='", 
  "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'~'", "'\\n'", "'('", "')'", 
  "','", "program", "entity", "element_list", "element", "head", 
  "arg_list", "arg", "body", "decl_block", "decl", "decl_type", 
  "decl_size", "statement_block", "statement", "if_body", 
  "loop_statement", "parameter_list", "expr", "e8", "e8op", "e7", "e7op", 
  "e6", "e6op", "e5", "e5op", "e4", "e4op", "e3", "e3op", "e2", "e2op", 
  "e1", "e1op", "e0", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    56,    56,    56,    57,    57,    57,    57,    57,    58,
      58,    59,    59,    59,    59,    59,    59,    60,    60,    61,
      61,    62,    63,    63,    64,    64,    65,    65,    66,    66,
      67,    67,    68,    68,    69,    69,    69,    69,    69,    69,
      70,    70,    70,    71,    72,    72,    73,    73,    74,    74,
      75,    76,    76,    77,    77,    78,    78,    79,    79,    79,
      80,    80,    81,    81,    81,    81,    81,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
      87,    88,    88,    89,    89,    89,    89,    90,    90,    90,
      90,    90
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     3,     3,     5,     6,     5,     6,     1,
       2,     3,     1,     5,     3,     7,     5,     1,     4,     1,
       3,     2,     5,     4,     1,     2,     4,     6,     1,     1,
       1,     1,     1,     2,     2,     7,     8,     3,     1,     2,
       4,     5,     2,     5,     1,     3,     1,     1,     1,     3,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     3,     4,
       1,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       0,     4,     0,     0,     0,     0,    29,    28,     0,     9,
      12,     0,     0,     0,     0,    17,     0,    87,    90,    47,
      86,    83,    84,    85,     0,     0,    46,    48,    51,    55,
      60,    68,    72,    76,     0,    81,     0,     0,    10,    30,
      31,     0,     0,     0,     7,     0,     0,     0,     0,    11,
      50,     0,    53,    54,     0,    57,    58,    59,     0,    66,
      67,    64,    65,    62,    63,     0,    70,    71,     0,    74,
      75,     0,    78,    79,    80,     0,    82,     0,    14,     0,
       0,     0,     5,     0,     0,    19,     0,     0,    88,     0,
      44,    91,    49,    52,    56,    61,    69,    73,    77,     0,
       0,    24,     0,     8,    26,     0,     6,    18,     0,    21,
      16,     0,    89,     0,     0,     0,     0,     0,     0,    32,
      38,     0,     0,    25,    13,     0,    20,     0,    45,     0,
       0,     0,    34,    23,    33,    39,     0,    27,    15,     0,
      37,     0,    22,     0,     0,     0,     0,     0,     0,    43,
       0,     0,    42,     0,    35,     0,     0,    40,    36,    41,
       0,     0
};

static const short yydefgoto[] =
{
       1,     6,    18,    19,    26,    94,    95,    89,   110,    20,
      21,    96,   128,   129,   158,   130,    99,   131,    36,    61,
      37,    64,    38,    68,    39,    75,    40,    78,    41,    81,
      42,    85,    43,    44,    45
};

static const short yypact[] =
{
  -32768,    63,   -44,    20,    19,    53,-32768,-32768,    32,    85,
      90,-32768,    49,    46,    24,    46,-32768,-32768,    72,   107,
  -32768,    10,    62,    87,    66,    60,   112,    76,-32768,-32768,
  -32768,-32768,-32768,-32768,    24,   100,    88,   -24,    41,    83,
      36,    54,    57,-32768,   -16,-32768,    -2,   109,-32768,-32768,
  -32768,   106,   104,   110,-32768,    10,    10,     4,    82,-32768,
  -32768,    33,-32768,-32768,    33,-32768,-32768,-32768,    33,-32768,
  -32768,-32768,-32768,-32768,-32768,    33,-32768,-32768,    33,-32768,
  -32768,    33,-32768,-32768,-32768,    33,-32768,    -1,-32768,   129,
     108,   -17,-32768,   111,    86,    84,   116,     8,-32768,    91,
      89,-32768,   -24,    41,    83,    36,    54,    57,-32768,    -5,
     143,   105,   117,-32768,-32768,    24,-32768,-32768,    10,-32768,
  -32768,   144,-32768,    24,    24,    24,    -5,   118,   146,    -5,
  -32768,   121,    -5,-32768,-32768,   122,-32768,   123,-32768,   145,
     139,   151,-32768,-32768,-32768,-32768,   153,-32768,-32768,    -5,
  -32768,   147,-32768,    52,   128,   149,    24,    -5,   156,-32768,
     131,   152,-32768,   154,-32768,    -5,   135,   113,-32768,-32768,
     166,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,    25,-32768,   155,    50,-32768,    70,    58,   -72,
  -32768,   -20,  -123,-32768,     5,    31,    51,   -14,-32768,-32768,
     114,-32768,   115,-32768,   119,-32768,    98,-32768,    99,-32768,
      95,-32768,    93,-32768,   136
};


#define	YYLAST		187


static const short yytable[] =
{
      35,    51,   109,   141,    87,   124,   144,   125,     7,   146,
     126,    27,    28,   114,    87,   111,    16,    17,    62,    63,
      58,   127,    27,    28,    29,     9,   153,   115,    88,    49,
      50,    27,    28,    29,   162,    23,    97,    34,   120,   111,
      30,    31,   167,   100,    48,    32,    33,     8,    34,    30,
      31,    27,    28,    29,    32,    33,   155,    34,    98,    10,
      27,    28,    11,   170,     2,   156,   157,    76,    77,    30,
      31,    24,     3,    25,    32,    33,    47,    34,    30,    31,
      65,    66,    67,    32,    33,     4,    34,    52,     5,    12,
      13,    53,    14,    15,    22,    13,    54,    14,    15,    79,
      80,   135,    16,    17,    82,    83,    84,    16,    17,   100,
     139,   140,    13,    55,    14,    15,    69,    70,    71,    72,
      73,    74,    16,    17,    16,    17,   156,   157,    56,    57,
      59,    90,    60,    91,    92,    93,   101,   112,   113,   118,
     117,   116,   161,   119,   123,   122,   132,   134,   142,   137,
     143,   145,   147,   148,   126,   151,   149,   152,   159,   160,
     163,   164,   154,   165,   166,   168,   171,   121,   136,   133,
      46,   150,   169,   105,   138,   102,   107,   106,   108,   103,
      86,     0,     0,     0,     0,     0,     0,   104
};

static const short yycheck[] =
{
      14,    21,     3,   126,     6,    10,   129,    12,    52,   132,
      15,    27,    28,    30,     6,    87,    17,    18,    42,    43,
      34,    26,    27,    28,    29,     6,   149,    44,    30,    19,
      20,    27,    28,    29,   157,    10,    56,    53,    30,   111,
      45,    46,   165,    57,    19,    50,    51,    27,    53,    45,
      46,    27,    28,    29,    50,    51,     4,    53,    54,     6,
      27,    28,    30,     0,     1,    13,    14,    31,    32,    45,
      46,    22,     9,    27,    50,    51,     4,    53,    45,    46,
      39,    40,    41,    50,    51,    22,    53,    25,    25,     4,
       5,     4,     7,     8,     4,     5,    30,     7,     8,    45,
      46,   115,    17,    18,    47,    48,    49,    17,    18,   123,
     124,   125,     5,    53,     7,     8,    33,    34,    35,    36,
      37,    38,    17,    18,    17,    18,    13,    14,    16,    53,
      30,    22,    44,    27,    30,    25,    54,     8,    30,    55,
      54,    30,   156,    27,    55,    54,     3,    30,    30,     5,
       4,    30,    30,    30,    15,     4,    11,     4,    30,    10,
       4,    30,    15,    11,    10,    30,     0,    97,   118,   111,
      15,   140,   167,    75,   123,    61,    81,    78,    85,    64,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    68
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
#line 122 "parse.y"
{
	  open_src(yyvsp[-1].s, source_with);
	}
    break;
case 5:
#line 127 "parse.y"
{
	  gp_warning("empty module");
	}
    break;
case 6:
#line 132 "parse.y"
{
	  add_entity(mk_file(yyvsp[-3].t, state.src->type));
	}
    break;
case 7:
#line 137 "parse.y"
{
	  gp_warning("empty public");
	}
    break;
case 8:
#line 142 "parse.y"
{
	  add_entity(mk_file(yyvsp[-3].t, state.src->type));
	}
    break;
case 9:
#line 149 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 10:
#line 154 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 11:
#line 161 "parse.y"
{
	  yyval.t = mk_pragma(yyvsp[-1].t);
	}
    break;
case 12:
#line 166 "parse.y"
{
	  yyval.t = yyvsp[0].t;
        }
    break;
case 13:
#line 171 "parse.y"
{ 
	  yyval.t = mk_proc(yyvsp[-3].t, yyvsp[-2].t);
     	}
    break;
case 14:
#line 176 "parse.y"
{ 
	  yyval.t = mk_proc(yyvsp[-1].t, NULL);
     	}
    break;
case 15:
#line 181 "parse.y"
{ 
	  yyval.t = mk_func(yyvsp[-5].t, yyvsp[-3].z, yyvsp[-2].t);
     	}
    break;
case 16:
#line 186 "parse.y"
{ 
	  yyval.t = mk_func(yyvsp[-3].t, yyvsp[-1].z, NULL);
     	}
    break;
case 17:
#line 193 "parse.y"
{
 	  yyval.t = mk_head(yyvsp[0].s, NULL);
     	}
    break;
case 18:
#line 198 "parse.y"
{
 	  yyval.t = mk_head(yyvsp[-3].s, yyvsp[-1].t);
     	}
    break;
case 19:
#line 205 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 20:
#line 210 "parse.y"
{
	  yyval.t = node_list(yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 21:
#line 217 "parse.y"
{	  
	  yyval.t = mk_decl(type_var, yyvsp[-1].z, yyvsp[0].s, NULL);
        }
    break;
case 22:
#line 224 "parse.y"
{
 	  yyval.t = mk_body(yyvsp[-3].t, yyvsp[-1].t);
     	}
    break;
case 23:
#line 229 "parse.y"
{
 	  yyval.t = mk_body(NULL, yyvsp[-1].t);
     	}
    break;
case 24:
#line 236 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 25:
#line 241 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 26:
#line 248 "parse.y"
{ 
	  yyval.t = mk_decl(yyvsp[-3].y, yyvsp[-2].z, yyvsp[-1].s, NULL);
        }
    break;
case 27:
#line 253 "parse.y"
{ 
	  yyval.t = mk_decl(yyvsp[-5].y, yyvsp[-4].z, yyvsp[-3].s, yyvsp[-1].t);
        }
    break;
case 28:
#line 260 "parse.y"
{
	  yyval.y = type_const;
	}
    break;
case 29:
#line 265 "parse.y"
{
	  yyval.y = type_var;
	}
    break;
case 30:
#line 272 "parse.y"
{
	  yyval.z = size_bit;
	}
    break;
case 31:
#line 277 "parse.y"
{
	  yyval.z = size_byte;
	}
    break;
case 32:
#line 284 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 33:
#line 289 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 34:
#line 296 "parse.y"
{
	  yyval.t = mk_assembly(yyvsp[-1].s);
	}
    break;
case 35:
#line 301 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-5].t, yyvsp[-3].t, NULL);
	}
    break;
case 36:
#line 306 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-6].t, yyvsp[-4].t, yyvsp[-3].t);
	}
    break;
case 37:
#line 311 "parse.y"
{
	  yyval.t= mk_loop(NULL, yyvsp[-1].t, NULL, yyvsp[0].t);	
	}
    break;
case 38:
#line 316 "parse.y"
{
	  yyval.t= mk_loop(NULL, NULL, NULL, yyvsp[0].t);
	}
    break;
case 39:
#line 321 "parse.y"
{
	  yyval.t = yyvsp[-1].t;
	}
    break;
case 40:
#line 328 "parse.y"
{
	  /* last statement is elsif */
	  yyval.t = mk_cond(yyvsp[-2].t, yyvsp[0].t, NULL);
	}
    break;
case 41:
#line 334 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-3].t, yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 42:
#line 339 "parse.y"
{
	  /* last statement is else */
	  yyval.t = mk_cond(NULL, yyvsp[0].t, NULL);
	}
    break;
case 43:
#line 347 "parse.y"
{
	  yyval.t = yyvsp[-3].t;
	}
    break;
case 44:
#line 354 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 45:
#line 359 "parse.y"
{
	  yyval.t = node_list(yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 47:
#line 368 "parse.y"
{
	  yyval.t = mk_string(yyvsp[0].s);
        }
    break;
case 49:
#line 377 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 50:
#line 382 "parse.y"
{ yyval.o = op_eq; }
    break;
case 52:
#line 388 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 53:
#line 393 "parse.y"
{ yyval.o = op_land; }
    break;
case 54:
#line 394 "parse.y"
{ yyval.o = op_lor; }
    break;
case 56:
#line 400 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 57:
#line 405 "parse.y"
{ yyval.o = op_and; }
    break;
case 58:
#line 406 "parse.y"
{ yyval.o = op_or; }
    break;
case 59:
#line 407 "parse.y"
{ yyval.o = op_xor; }
    break;
case 61:
#line 413 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 62:
#line 418 "parse.y"
{ yyval.o = op_lt; }
    break;
case 63:
#line 419 "parse.y"
{ yyval.o = op_gt; }
    break;
case 64:
#line 420 "parse.y"
{ yyval.o = op_eq; }
    break;
case 65:
#line 421 "parse.y"
{ yyval.o = op_ne; }
    break;
case 66:
#line 422 "parse.y"
{ yyval.o = op_gte; }
    break;
case 67:
#line 423 "parse.y"
{ yyval.o = op_lte; }
    break;
case 69:
#line 429 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 70:
#line 434 "parse.y"
{ yyval.o = op_lsh; }
    break;
case 71:
#line 435 "parse.y"
{ yyval.o = op_rsh; }
    break;
case 73:
#line 441 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 74:
#line 446 "parse.y"
{ yyval.o = op_add; }
    break;
case 75:
#line 447 "parse.y"
{ yyval.o = op_sub; }
    break;
case 77:
#line 453 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 78:
#line 458 "parse.y"
{ yyval.o = op_mult; }
    break;
case 79:
#line 459 "parse.y"
{ yyval.o = op_div; }
    break;
case 80:
#line 460 "parse.y"
{ yyval.o = op_mod; }
    break;
case 82:
#line 466 "parse.y"
{
	  yyval.t = mk_unop(yyvsp[-1].o, yyvsp[0].t);
	}
    break;
case 83:
#line 471 "parse.y"
{ yyval.o = op_neg; }
    break;
case 84:
#line 472 "parse.y"
{ yyval.o = op_not; }
    break;
case 85:
#line 473 "parse.y"
{ yyval.o = op_com; }
    break;
case 86:
#line 474 "parse.y"
{ yyval.o = op_add; }
    break;
case 87:
#line 478 "parse.y"
{
	  yyval.t = mk_symbol(yyvsp[0].s);
        }
    break;
case 88:
#line 483 "parse.y"
{
	  /* function or procedure call */
	  yyval.t = mk_call(yyvsp[-2].s, NULL);
	}
    break;
case 89:
#line 489 "parse.y"
{
	  /* function or procedure call with arguments */
	  yyval.t = mk_call(yyvsp[-3].s, yyvsp[-1].t);
	}
    break;
case 90:
#line 495 "parse.y"
{
	  yyval.t = mk_constant(yyvsp[0].i);
	}
    break;
case 91:
#line 500 "parse.y"
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
#line 505 "parse.y"

