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

void yyerror(char *message)
{
  gp_error("%s:%d:%s",
           state.src->name,
	   state.src->line_number,
	   message);
}

int yylex(void);


#line 43 "parse.y"
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



#define	YYFINAL		146
#define	YYFLAG		-32768
#define	YYNTBASE	54

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 289 ? yytranslate[x] : 87)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      50,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,     2,     2,    47,    37,     2,
      51,    52,    45,    43,    53,    44,     2,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    28,
      35,    42,    36,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    39,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    38,     2,    49,     2,     2,     2,
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
      26,    27,    29,    30,    31,    32,    33,    34,    40,    41
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     8,    12,    16,    18,    24,    28,
      36,    42,    44,    49,    51,    55,    58,    64,    69,    71,
      74,    79,    81,    83,    85,    87,    89,    92,   100,   109,
     113,   115,   118,   123,   129,   132,   138,   140,   144,   146,
     148,   150,   154,   156,   158,   162,   164,   166,   168,   172,
     174,   176,   178,   180,   184,   186,   188,   190,   192,   194,
     196,   198,   202,   204,   206,   208,   212,   214,   216,   218,
     222,   224,   226,   228,   230,   233,   235,   237,   239,   241,
     243,   247,   252,   254
};
static const short yyrhs[] =
{
      -1,    54,    55,     0,    54,     1,    50,     0,     7,    69,
      28,     0,     9,    25,    28,     0,    61,     0,     8,    56,
      59,     8,    28,     0,     8,    56,    28,     0,     5,    56,
      16,    63,    59,     5,    28,     0,     5,    56,    16,    63,
      28,     0,    25,     0,    25,    51,    57,    52,     0,    58,
       0,    58,    53,    57,     0,    63,    25,     0,     6,    60,
       3,    64,     4,     0,     6,     3,    64,     4,     0,    61,
       0,    61,    60,     0,    62,    63,    68,    28,     0,    18,
       0,    17,     0,    19,     0,    20,     0,    65,     0,    65,
      64,     0,    10,    69,    11,    64,     4,    10,    28,     0,
      10,    69,    11,    64,    66,     4,    10,    28,     0,    12,
      69,    67,     0,    67,     0,    69,    28,     0,    13,    69,
      11,    64,     0,    13,    69,    11,    64,    66,     0,    14,
      64,     0,    15,    64,     4,    15,    28,     0,    69,     0,
      69,    53,    68,     0,    70,     0,    27,     0,    72,     0,
      70,    71,    72,     0,    42,     0,    74,     0,    72,    73,
      74,     0,    40,     0,    41,     0,    76,     0,    74,    75,
      76,     0,    37,     0,    38,     0,    39,     0,    78,     0,
      76,    77,    78,     0,    35,     0,    36,     0,    33,     0,
      34,     0,    31,     0,    32,     0,    80,     0,    78,    79,
      80,     0,    29,     0,    30,     0,    82,     0,    80,    81,
      82,     0,    43,     0,    44,     0,    84,     0,    82,    83,
      84,     0,    45,     0,    46,     0,    47,     0,    86,     0,
      85,    86,     0,    44,     0,    48,     0,    49,     0,    43,
       0,    25,     0,    25,    51,    52,     0,    25,    51,    68,
      52,     0,    26,     0,    51,    69,    52,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    96,    98,   100,   104,   109,   114,   119,   128,   139,
     148,   161,   166,   173,   178,   185,   192,   197,   204,   209,
     216,   230,   235,   242,   247,   254,   259,   266,   271,   276,
     281,   286,   293,   299,   304,   312,   319,   324,   331,   333,
     340,   342,   349,   351,   353,   360,   361,   363,   365,   372,
     373,   374,   376,   378,   385,   386,   387,   388,   389,   390,
     392,   394,   401,   402,   404,   406,   413,   414,   416,   418,
     425,   426,   427,   429,   431,   438,   439,   440,   441,   443,
     448,   454,   460,   465
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
  "VOLATILE_STORAGE", "IDENT", "NUMBER", "STRING", "';'", "LSH", "RSH", 
  "GREATER_EQUAL", "LESS_EQUAL", "EQUAL", "NOT_EQUAL", "'<'", "'>'", 
  "'&'", "'|'", "'^'", "LOGICAL_AND", "LOGICAL_OR", "'='", "'+'", "'-'", 
  "'*'", "'/'", "'%'", "'!'", "'~'", "'\\n'", "'('", "')'", "','", 
  "program", "line", "head", "arg_list", "arg", "body", "decl_block", 
  "decl", "decl_type", "decl_size", "statement_block", "statement", 
  "if_body", "loop_statement", "parameter_list", "expr", "e8", "e8op", 
  "e7", "e7op", "e6", "e6op", "e5", "e5op", "e4", "e4op", "e3", "e3op", 
  "e2", "e2op", "e1", "e1op", "e0", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    54,    54,    54,    55,    55,    55,    55,    55,    55,
      55,    56,    56,    57,    57,    58,    59,    59,    60,    60,
      61,    62,    62,    63,    63,    64,    64,    65,    65,    65,
      65,    65,    66,    66,    66,    67,    68,    68,    69,    69,
      70,    70,    71,    72,    72,    73,    73,    74,    74,    75,
      75,    75,    76,    76,    77,    77,    77,    77,    77,    77,
      78,    78,    79,    79,    80,    80,    81,    81,    82,    82,
      83,    83,    83,    84,    84,    85,    85,    85,    85,    86,
      86,    86,    86,    86
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     3,     3,     3,     1,     5,     3,     7,
       5,     1,     4,     1,     3,     2,     5,     4,     1,     2,
       4,     1,     1,     1,     1,     1,     2,     7,     8,     3,
       1,     2,     4,     5,     2,     5,     1,     3,     1,     1,
       1,     3,     1,     1,     3,     1,     1,     1,     3,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       3,     4,     1,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     0,     0,     0,     0,     0,    22,    21,     2,
       6,     0,     3,    11,     0,    79,    82,    39,    78,    75,
      76,    77,     0,     0,    38,    40,    43,    47,    52,    60,
      64,    68,     0,    73,     0,     0,    23,    24,     0,     0,
       0,     0,     0,     4,    42,     0,    45,    46,     0,    49,
      50,    51,     0,    58,    59,    56,    57,    54,    55,     0,
      62,    63,     0,    66,    67,     0,    70,    71,    72,     0,
      74,     0,     8,     0,     5,     0,    36,     0,    13,     0,
       0,    80,     0,    83,    41,    44,    48,    53,    61,    65,
      69,     0,     0,    18,     0,    20,     0,    12,     0,    15,
      10,     0,    81,     0,     0,     0,     0,    25,    30,     0,
       0,    19,     7,    37,    14,     0,     0,     0,     0,    17,
      26,    31,     0,     9,     0,    29,     0,    16,     0,     0,
       0,     0,     0,     0,    35,     0,     0,    34,     0,    27,
       0,     0,    32,    28,    33,     0,     0
};

static const short yydefgoto[] =
{
       1,     9,    14,    77,    78,    73,    92,    93,    11,    79,
     106,   107,   133,   108,    75,   109,    24,    45,    25,    48,
      26,    52,    27,    59,    28,    62,    29,    65,    30,    69,
      31,    32,    33
};

static const short yypact[] =
{
  -32768,    96,   -38,    -6,    32,    -6,     3,-32768,-32768,-32768,
  -32768,    44,-32768,   -21,    16,   -11,-32768,-32768,-32768,-32768,
  -32768,-32768,    32,    14,    27,   -25,    23,    19,    48,    45,
      61,-32768,   -22,-32768,     7,    17,-32768,-32768,    32,    44,
      44,    22,    20,-32768,-32768,    42,-32768,-32768,    42,-32768,
  -32768,-32768,    42,-32768,-32768,-32768,-32768,-32768,-32768,    42,
  -32768,-32768,    42,-32768,-32768,    42,-32768,-32768,-32768,    42,
  -32768,     6,-32768,    71,-32768,    54,    31,    35,    49,    73,
       8,-32768,    57,-32768,   -25,    23,    19,    48,    45,    61,
  -32768,    -5,   109,    77,    87,-32768,    32,-32768,    44,-32768,
  -32768,   111,-32768,    32,    32,    -5,   113,    -5,-32768,    90,
      -5,-32768,-32768,-32768,-32768,    91,   110,   105,   118,-32768,
  -32768,-32768,   119,-32768,    -5,-32768,   114,-32768,    13,    98,
     115,    32,    -5,   120,-32768,   100,   121,-32768,   123,-32768,
      -5,   102,    97,-32768,-32768,   131,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,   129,    37,-32768,    56,    46,   136,-32768,    -9,
     -99,-32768,    -2,    21,   -40,    -4,-32768,-32768,    99,-32768,
      93,-32768,    94,-32768,    83,-32768,    81,-32768,    80,-32768,
      78,-32768,   116
};


#define	YYLAST		148


static const short yytable[] =
{
      23,    82,    38,    15,    16,   103,   118,   104,   120,    91,
     105,   122,    12,    71,    71,    46,    47,   130,    42,    13,
      15,    16,    17,     7,     8,   128,   131,   132,    35,    22,
      39,    80,    40,   137,    76,    72,   100,    76,    18,    19,
      41,   142,    43,    20,    21,    74,    22,    15,    16,    17,
      53,    54,    55,    56,    57,    58,   113,    15,    16,    17,
      49,    50,    51,    36,    37,    18,    19,    15,    16,    44,
      20,    21,    83,    22,    81,    18,    19,    60,    61,    94,
      20,    21,    95,    22,    96,    18,    19,    97,    63,    64,
      20,    21,    76,    22,     7,     8,   145,     2,    99,   116,
     117,     3,    98,     4,     5,     6,    66,    67,    68,   102,
     131,   132,   110,     7,     8,   112,   115,   119,   121,   123,
     105,   124,   126,   127,   138,   135,   134,   136,   139,   129,
     143,   146,   140,   141,    34,   114,   101,    10,   125,   111,
     144,    85,    87,    88,    84,    89,    86,    90,    70
};

static const short yycheck[] =
{
       4,    41,    11,    25,    26,    10,   105,    12,   107,     3,
      15,   110,    50,     6,     6,    40,    41,     4,    22,    25,
      25,    26,    27,    17,    18,   124,    13,    14,    25,    51,
      51,    40,    16,   132,    38,    28,    28,    41,    43,    44,
      51,   140,    28,    48,    49,    28,    51,    25,    26,    27,
      31,    32,    33,    34,    35,    36,    96,    25,    26,    27,
      37,    38,    39,    19,    20,    43,    44,    25,    26,    42,
      48,    49,    52,    51,    52,    43,    44,    29,    30,     8,
      48,    49,    28,    51,    53,    43,    44,    52,    43,    44,
      48,    49,    96,    51,    17,    18,     0,     1,    25,   103,
     104,     5,    53,     7,     8,     9,    45,    46,    47,    52,
      13,    14,     3,    17,    18,    28,     5,     4,    28,    28,
      15,    11,     4,     4,     4,    10,    28,   131,    28,    15,
      28,     0,    11,    10,     5,    98,    80,     1,   117,    93,
     142,    48,    59,    62,    45,    65,    52,    69,    32
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
#line 106 "parse.y"
{
	  process_pragma(yyvsp[-1].t);
	}
    break;
case 5:
#line 111 "parse.y"
{
	  open_src(yyvsp[-1].s, with);
	}
    break;
case 6:
#line 116 "parse.y"
{
	  add_entity(yyvsp[0].t);
        }
    break;
case 7:
#line 121 "parse.y"
{ 
          if (state.src->type == source) {
            add_entity(mk_proc(yyvsp[-3].t, storage_private, yyvsp[-2].t));
          } else {
            gp_error("procedures can only be defined in .pal files");
          }
     	}
    break;
case 8:
#line 130 "parse.y"
{ 
	  if (state.src->type == source_with) {
            add_entity(mk_proc_prot(yyvsp[-1].t, storage_public));
	  } else if (state.src->type == with) {
            add_entity(mk_proc_prot(yyvsp[-1].t, storage_extern));
          } else {
            gp_error("procedure declarations can only be in .pub files");
          }
     	}
    break;
case 9:
#line 141 "parse.y"
{ 
	  if (state.src->type == source) {
            add_entity(mk_func(yyvsp[-5].t, storage_private, yyvsp[-3].z, yyvsp[-2].t));
          } else {
            gp_error("functions can only be defined in .pal files");
          }
     	}
    break;
case 10:
#line 150 "parse.y"
{ 
	  if (state.src->type == source_with) {
            add_entity(mk_func_prot(yyvsp[-3].t, storage_public, yyvsp[-1].z));
	  } else if (state.src->type == with) {
            add_entity(mk_func_prot(yyvsp[-3].t, storage_extern, yyvsp[-1].z));
          } else {
            gp_error("function declarations can only be in .pub files");
          }
     	}
    break;
case 11:
#line 163 "parse.y"
{
 	  yyval.t = mk_head(yyvsp[0].s, NULL);
     	}
    break;
case 12:
#line 168 "parse.y"
{
 	  yyval.t = mk_head(yyvsp[-3].s, yyvsp[-1].t);
     	}
    break;
case 13:
#line 175 "parse.y"
{
	  yyval.t = mk_list(yyvsp[0].t, NULL);
	}
    break;
case 14:
#line 180 "parse.y"
{
	  yyval.t = mk_list(yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 15:
#line 187 "parse.y"
{	  
	  yyval.t = mk_decl(0, yyvsp[-1].z, 0, mk_symbol(yyvsp[0].s));
        }
    break;
case 16:
#line 194 "parse.y"
{
 	  yyval.t = mk_body(yyvsp[-3].t, yyvsp[-1].t);
     	}
    break;
case 17:
#line 199 "parse.y"
{
 	  yyval.t = mk_body(NULL, yyvsp[-1].t);
     	}
    break;
case 18:
#line 206 "parse.y"
{
	  yyval.t = mk_list(yyvsp[0].t, NULL);
	}
    break;
case 19:
#line 211 "parse.y"
{
	  yyval.t = mk_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 20:
#line 218 "parse.y"
{ 
	  if (state.src->type == source_with) {
	    yyval.t = mk_decl_prot(yyvsp[-3].y, yyvsp[-2].z, storage_public, yyvsp[-1].t);
	  } else if (state.src->type == with) {
	    yyval.t = mk_decl_prot(yyvsp[-3].y, yyvsp[-2].z, storage_extern, yyvsp[-1].t);
	  } else {
	    /* should only get here from inside a function or procedure */
	    yyval.t = mk_decl(yyvsp[-3].y, yyvsp[-2].z, storage_private, yyvsp[-1].t);
	  }
        }
    break;
case 21:
#line 232 "parse.y"
{
	  yyval.y = type_const;
	}
    break;
case 22:
#line 237 "parse.y"
{
	  yyval.y = type_var;
	}
    break;
case 23:
#line 244 "parse.y"
{
	  yyval.z = size_bit;
	}
    break;
case 24:
#line 249 "parse.y"
{
	  yyval.z = size_byte;
	}
    break;
case 25:
#line 256 "parse.y"
{
	  yyval.t = mk_list(yyvsp[0].t, NULL);
	}
    break;
case 26:
#line 261 "parse.y"
{
	  yyval.t = mk_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 27:
#line 268 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-5].t, yyvsp[-3].t, NULL);
	}
    break;
case 28:
#line 273 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-6].t, yyvsp[-4].t, yyvsp[-3].t);
	}
    break;
case 29:
#line 278 "parse.y"
{
	  yyval.t= mk_loop(NULL, yyvsp[-1].t, NULL, yyvsp[0].t);	
	}
    break;
case 30:
#line 283 "parse.y"
{
	  yyval.t= mk_loop(NULL, NULL, NULL, yyvsp[0].t);
	}
    break;
case 31:
#line 288 "parse.y"
{
	  yyval.t = yyvsp[-1].t;
	}
    break;
case 32:
#line 295 "parse.y"
{
	  /* last statement is elsif */
	  yyval.t = mk_cond(yyvsp[-2].t, yyvsp[0].t, NULL);
	}
    break;
case 33:
#line 301 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-3].t, yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 34:
#line 306 "parse.y"
{
	  /* last statement is else */
	  yyval.t = mk_cond(NULL, yyvsp[0].t, NULL);
	}
    break;
case 35:
#line 314 "parse.y"
{
	  yyval.t = yyvsp[-3].t;
	}
    break;
case 36:
#line 321 "parse.y"
{
	  yyval.t = mk_list(yyvsp[0].t, NULL);
	}
    break;
case 37:
#line 326 "parse.y"
{
	  yyval.t = mk_list(yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 39:
#line 335 "parse.y"
{
	  yyval.t = mk_string(yyvsp[0].s);
        }
    break;
case 41:
#line 344 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 42:
#line 349 "parse.y"
{ yyval.o = op_eq; }
    break;
case 44:
#line 355 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 45:
#line 360 "parse.y"
{ yyval.o = op_land; }
    break;
case 46:
#line 361 "parse.y"
{ yyval.o = op_lor; }
    break;
case 48:
#line 367 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 49:
#line 372 "parse.y"
{ yyval.o = op_and; }
    break;
case 50:
#line 373 "parse.y"
{ yyval.o = op_or; }
    break;
case 51:
#line 374 "parse.y"
{ yyval.o = op_xor; }
    break;
case 53:
#line 380 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 54:
#line 385 "parse.y"
{ yyval.o = op_lt; }
    break;
case 55:
#line 386 "parse.y"
{ yyval.o = op_gt; }
    break;
case 56:
#line 387 "parse.y"
{ yyval.o = op_eq; }
    break;
case 57:
#line 388 "parse.y"
{ yyval.o = op_ne; }
    break;
case 58:
#line 389 "parse.y"
{ yyval.o = op_gte; }
    break;
case 59:
#line 390 "parse.y"
{ yyval.o = op_lte; }
    break;
case 61:
#line 396 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 62:
#line 401 "parse.y"
{ yyval.o = op_lsh; }
    break;
case 63:
#line 402 "parse.y"
{ yyval.o = op_rsh; }
    break;
case 65:
#line 408 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 66:
#line 413 "parse.y"
{ yyval.o = op_add; }
    break;
case 67:
#line 414 "parse.y"
{ yyval.o = op_sub; }
    break;
case 69:
#line 420 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 70:
#line 425 "parse.y"
{ yyval.o = op_mult; }
    break;
case 71:
#line 426 "parse.y"
{ yyval.o = op_div; }
    break;
case 72:
#line 427 "parse.y"
{ yyval.o = op_mod; }
    break;
case 74:
#line 433 "parse.y"
{
	  yyval.t = mk_unop(yyvsp[-1].o, yyvsp[0].t);
	}
    break;
case 75:
#line 438 "parse.y"
{ yyval.o = op_neg; }
    break;
case 76:
#line 439 "parse.y"
{ yyval.o = op_not; }
    break;
case 77:
#line 440 "parse.y"
{ yyval.o = op_com; }
    break;
case 78:
#line 441 "parse.y"
{ yyval.o = op_add; }
    break;
case 79:
#line 445 "parse.y"
{
	  yyval.t = mk_symbol(yyvsp[0].s);
        }
    break;
case 80:
#line 450 "parse.y"
{
	  /* function or procedure call */
	  yyval.t = mk_call(yyvsp[-2].s, NULL);
	}
    break;
case 81:
#line 456 "parse.y"
{
	  /* function or procedure call with arguments */
	  yyval.t = mk_call(yyvsp[-3].s, yyvsp[-1].t);
	}
    break;
case 82:
#line 462 "parse.y"
{
	  yyval.t = mk_constant(yyvsp[0].i);
	}
    break;
case 83:
#line 467 "parse.y"
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
#line 472 "parse.y"

