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
# define	ASM	279
# define	IDENT	280
# define	NUMBER	281
# define	STRING	282
# define	LSH	283
# define	RSH	284
# define	GREATER_EQUAL	285
# define	LESS_EQUAL	286
# define	EQUAL	287
# define	NOT_EQUAL	288
# define	LOGICAL_AND	289
# define	LOGICAL_OR	290

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

static void
process_pragma(tree *expr)
{
  tree *lhs;
  tree *rhs;

  switch (expr->tag) {
  case node_binop:
    lhs = expr->value.binop.p0;
    rhs = expr->value.binop.p1;
    if ((expr->value.binop.op != op_eq) ||
        (lhs->tag != node_symbol)) {
      gp_error("unknown pragma");
    } else {
      if (strcasecmp(lhs->value.symbol, "processor") == 0) {
        if (rhs->tag != node_symbol) {
          gp_error("invalid processor name");        
        } else {
          if (state.processor_chosen == false) {
            select_processor(rhs->value.symbol);
          }        
        }
      } else if (strcasecmp(lhs->value.symbol, "code_section") == 0) {
        if (rhs->tag != node_symbol) {
          gp_error("invalid code section name");
        } else {
          if (state.src->type == with) {            
            if ((state.section.code) && 
                (strcmp(rhs->value.symbol, state.section.code) == 0)) {
              state.section.code_default = storage_local;
            } else {
              state.section.code_default = storage_extern;
            }
          } else {
            if (state.src->type == source) {
              gp_warning("section pragma's should be in .pub files");
            }
            if (state.section.code) {
              gp_error("duplicate code section name");
            } else {
              state.section.code = rhs->value.symbol;
            }
          }        
        }
      } else if (strcasecmp(lhs->value.symbol, "udata_section") == 0) {
        if (rhs->tag != node_symbol) {
          gp_error("invalid udata section name");
        } else {
          if (state.src->type == with) {            
            if ((state.section.udata) &&
                (strcmp(rhs->value.symbol, state.section.udata) == 0)) {
              state.section.udata_default = storage_local;
            } else {
              state.section.udata_default = storage_extern;
            }
          } else {
            if (state.src->type == source) {
              gp_warning("section pragma's should be in .pub files");
            }
            if (state.section.code) {
              gp_error("duplicate udata section name");
            } else {
              state.section.udata = rhs->value.symbol;
            }
          }        
        }
      } else {
        gp_error("unknown pragma \"%s\"", lhs->value.symbol);
      }
    }
    break;
  default:
    gp_error("unknown pragma");
  }
  
  return;
}


#line 133 "parse.y"
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



#define	YYFINAL		151
#define	YYFLAG		-32768
#define	YYNTBASE	55

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 290 ? yytranslate[x] : 88)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      51,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,     2,     2,    48,    38,     2,
      52,    53,    46,    44,    54,    45,     2,    47,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    29,
      36,    43,    37,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    39,     2,    50,     2,     2,     2,
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
      26,    27,    28,    30,    31,    32,    33,    34,    35,    41,
      42
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     8,    12,    16,    18,    24,    28,
      36,    42,    44,    49,    51,    55,    58,    64,    69,    71,
      74,    79,    86,    88,    90,    92,    94,    96,    99,   102,
     110,   119,   123,   125,   128,   133,   139,   142,   148,   150,
     154,   156,   158,   160,   164,   166,   168,   172,   174,   176,
     178,   182,   184,   186,   188,   190,   194,   196,   198,   200,
     202,   204,   206,   208,   212,   214,   216,   218,   222,   224,
     226,   228,   232,   234,   236,   238,   240,   243,   245,   247,
     249,   251,   253,   257,   262,   264
};
static const short yyrhs[] =
{
      -1,    55,    56,     0,    55,     1,    51,     0,     7,    70,
      29,     0,     9,    26,    29,     0,    62,     0,     8,    57,
      60,     8,    29,     0,     8,    57,    29,     0,     5,    57,
      16,    64,    60,     5,    29,     0,     5,    57,    16,    64,
      29,     0,    26,     0,    26,    52,    58,    53,     0,    59,
       0,    59,    54,    58,     0,    64,    26,     0,     6,    61,
       3,    65,     4,     0,     6,     3,    65,     4,     0,    62,
       0,    62,    61,     0,    63,    64,    26,    29,     0,    63,
      64,    26,    43,    70,    29,     0,    18,     0,    17,     0,
      19,     0,    20,     0,    66,     0,    66,    65,     0,    25,
      29,     0,    10,    70,    11,    65,     4,    10,    29,     0,
      10,    70,    11,    65,    67,     4,    10,    29,     0,    12,
      70,    68,     0,    68,     0,    70,    29,     0,    13,    70,
      11,    65,     0,    13,    70,    11,    65,    67,     0,    14,
      65,     0,    15,    65,     4,    15,    29,     0,    70,     0,
      70,    54,    69,     0,    71,     0,    28,     0,    73,     0,
      71,    72,    73,     0,    43,     0,    75,     0,    73,    74,
      75,     0,    41,     0,    42,     0,    77,     0,    75,    76,
      77,     0,    38,     0,    39,     0,    40,     0,    79,     0,
      77,    78,    79,     0,    36,     0,    37,     0,    34,     0,
      35,     0,    32,     0,    33,     0,    81,     0,    79,    80,
      81,     0,    30,     0,    31,     0,    83,     0,    81,    82,
      83,     0,    44,     0,    45,     0,    85,     0,    83,    84,
      85,     0,    46,     0,    47,     0,    48,     0,    87,     0,
      86,    87,     0,    45,     0,    49,     0,    50,     0,    44,
       0,    26,     0,    26,    52,    53,     0,    26,    52,    69,
      53,     0,    27,     0,    52,    70,    53,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   187,   189,   191,   195,   200,   205,   210,   219,   230,
     239,   252,   257,   264,   269,   276,   290,   295,   302,   307,
     314,   326,   341,   346,   353,   358,   365,   370,   377,   382,
     387,   392,   397,   402,   409,   415,   420,   428,   435,   440,
     447,   449,   456,   458,   465,   467,   469,   476,   477,   479,
     481,   488,   489,   490,   492,   494,   501,   502,   503,   504,
     505,   506,   508,   510,   517,   518,   520,   522,   529,   530,
     532,   534,   541,   542,   543,   545,   547,   554,   555,   556,
     557,   559,   564,   570,   576,   581
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
  "VOLATILE_STORAGE", "ASM", "IDENT", "NUMBER", "STRING", "';'", "LSH", 
  "RSH", "GREATER_EQUAL", "LESS_EQUAL", "EQUAL", "NOT_EQUAL", "'<'", 
  "'>'", "'&'", "'|'", "'^'", "LOGICAL_AND", "LOGICAL_OR", "'='", "'+'", 
  "'-'", "'*'", "'/'", "'%'", "'!'", "'~'", "'\\n'", "'('", "')'", "','", 
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
       0,    55,    55,    55,    56,    56,    56,    56,    56,    56,
      56,    57,    57,    58,    58,    59,    60,    60,    61,    61,
      62,    62,    63,    63,    64,    64,    65,    65,    66,    66,
      66,    66,    66,    66,    67,    67,    67,    68,    69,    69,
      70,    70,    71,    71,    72,    73,    73,    74,    74,    75,
      75,    76,    76,    76,    77,    77,    78,    78,    78,    78,
      78,    78,    79,    79,    80,    80,    81,    81,    82,    82,
      83,    83,    84,    84,    84,    85,    85,    86,    86,    86,
      86,    87,    87,    87,    87,    87
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     3,     3,     3,     1,     5,     3,     7,
       5,     1,     4,     1,     3,     2,     5,     4,     1,     2,
       4,     6,     1,     1,     1,     1,     1,     2,     2,     7,
       8,     3,     1,     2,     4,     5,     2,     5,     1,     3,
       1,     1,     1,     3,     1,     1,     3,     1,     1,     1,
       3,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     3,     4,     1,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     0,     0,     0,     0,     0,    23,    22,     2,
       6,     0,     3,    11,     0,    81,    84,    41,    80,    77,
      78,    79,     0,     0,    40,    42,    45,    49,    54,    62,
      66,    70,     0,    75,     0,     0,    24,    25,     0,     0,
       0,     0,     0,     4,    44,     0,    47,    48,     0,    51,
      52,    53,     0,    60,    61,    58,    59,    56,    57,     0,
      64,    65,     0,    68,    69,     0,    72,    73,    74,     0,
      76,     0,     8,     0,     5,     0,     0,    13,     0,     0,
      82,     0,    38,    85,    43,    46,    50,    55,    63,    67,
      71,     0,     0,    18,     0,    20,     0,    12,     0,    15,
      10,     0,    83,     0,     0,     0,     0,     0,     0,    26,
      32,     0,     0,    19,     7,     0,    14,     0,    39,     0,
       0,     0,    28,    17,    27,    33,     0,    21,     9,     0,
      31,     0,    16,     0,     0,     0,     0,     0,     0,    37,
       0,     0,    36,     0,    29,     0,     0,    34,    30,    35,
       0,     0
};

static const short yydefgoto[] =
{
       1,     9,    14,    76,    77,    73,    92,    93,    11,    78,
     108,   109,   138,   110,    81,   111,    24,    45,    25,    48,
      26,    52,    27,    59,    28,    62,    29,    65,    30,    69,
      31,    32,    33
};

static const short yypact[] =
{
  -32768,    89,   -44,     1,    21,     1,     3,-32768,-32768,-32768,
  -32768,    48,-32768,   -36,     7,    -2,-32768,-32768,-32768,-32768,
  -32768,-32768,    21,    13,    16,    67,   -27,    42,    52,    66,
      56,-32768,   -12,-32768,    -3,    27,-32768,-32768,    38,    48,
      48,     8,    19,-32768,-32768,    36,-32768,-32768,    36,-32768,
  -32768,-32768,    36,-32768,-32768,-32768,-32768,-32768,-32768,    36,
  -32768,-32768,    36,-32768,-32768,    36,-32768,-32768,-32768,    36,
  -32768,    14,-32768,    61,-32768,   -19,    31,    33,    65,    22,
  -32768,    40,    51,-32768,    67,   -27,    42,    52,    66,    56,
  -32768,    -6,    92,    95,    87,-32768,    21,-32768,    48,-32768,
  -32768,   112,-32768,    21,    21,    21,    -6,    90,   114,    -6,
  -32768,    91,    -6,-32768,-32768,    93,-32768,    94,-32768,   110,
     109,   121,-32768,-32768,-32768,-32768,   122,-32768,-32768,    -6,
  -32768,   113,-32768,    41,    98,   119,    21,    -6,   126,-32768,
     102,   123,-32768,   125,-32768,    -6,   104,   101,-32768,-32768,
     136,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,   132,    43,-32768,    59,    46,   139,-32768,   -10,
    -104,-32768,    -5,    23,    44,    -4,-32768,-32768,    99,-32768,
      97,-32768,    96,-32768,   100,-32768,    84,-32768,    85,-32768,
      80,-32768,   120
};


#define	YYLAST		159


static const short yytable[] =
{
      23,    38,   121,    71,   104,   124,   105,    12,   126,   106,
      95,    49,    50,    51,    15,    16,    39,    91,    42,   107,
      15,    16,    17,    40,    96,   133,    72,    13,    71,    35,
      79,     7,     8,   142,    15,    16,    17,    82,    18,    19,
      22,   147,    43,    20,    21,   135,    22,    15,    16,    17,
      41,   100,    18,    19,   136,   137,    74,    20,    21,    44,
      22,    80,    15,    16,    75,    18,    19,    36,    37,    94,
      20,    21,    83,    22,    53,    54,    55,    56,    57,    58,
      18,    19,    60,    61,    97,    20,    21,    98,    22,   150,
       2,    99,   115,   102,     3,   112,     4,     5,     6,    82,
     119,   120,    66,    67,    68,   103,     7,     8,    46,    47,
      63,    64,     7,     8,   136,   137,   114,   117,   123,   122,
     125,   129,   127,   128,   106,   131,   132,   139,   134,   140,
     143,   144,   141,   148,   145,   146,   151,    34,   101,   113,
      10,   116,   149,   130,    84,    85,    88,   118,    86,    90,
      89,     0,    70,     0,     0,     0,     0,     0,     0,    87
};

static const short yycheck[] =
{
       4,    11,   106,     6,    10,   109,    12,    51,   112,    15,
      29,    38,    39,    40,    26,    27,    52,     3,    22,    25,
      26,    27,    28,    16,    43,   129,    29,    26,     6,    26,
      40,    17,    18,   137,    26,    27,    28,    41,    44,    45,
      52,   145,    29,    49,    50,     4,    52,    26,    27,    28,
      52,    29,    44,    45,    13,    14,    29,    49,    50,    43,
      52,    53,    26,    27,    26,    44,    45,    19,    20,     8,
      49,    50,    53,    52,    32,    33,    34,    35,    36,    37,
      44,    45,    30,    31,    53,    49,    50,    54,    52,     0,
       1,    26,    96,    53,     5,     3,     7,     8,     9,   103,
     104,   105,    46,    47,    48,    54,    17,    18,    41,    42,
      44,    45,    17,    18,    13,    14,    29,     5,     4,    29,
      29,    11,    29,    29,    15,     4,     4,    29,    15,    10,
       4,    29,   136,    29,    11,    10,     0,     5,    79,    93,
       1,    98,   147,   120,    45,    48,    62,   103,    52,    69,
      65,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    59
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
#line 197 "parse.y"
{
	  process_pragma(yyvsp[-1].t);
	}
    break;
case 5:
#line 202 "parse.y"
{
	  open_src(yyvsp[-1].s, with);
	}
    break;
case 6:
#line 207 "parse.y"
{
	  add_entity(yyvsp[0].t);
        }
    break;
case 7:
#line 212 "parse.y"
{ 
          if (state.src->type == source) {
            add_entity(mk_proc(yyvsp[-3].t, storage_private, yyvsp[-2].t));
          } else {
            yyerror("procedures can only be defined in .pal files");
          }
     	}
    break;
case 8:
#line 221 "parse.y"
{ 
	  if (state.src->type == source_with) {
            add_entity(mk_proc_prot(yyvsp[-1].t, storage_public));
	  } else if (state.src->type == with) {
            add_entity(mk_proc_prot(yyvsp[-1].t, state.section.code_default));
          } else {
            yyerror("procedure declarations can only be in .pub files");
          }
     	}
    break;
case 9:
#line 232 "parse.y"
{ 
	  if (state.src->type == source) {
            add_entity(mk_func(yyvsp[-5].t, storage_private, yyvsp[-3].z, yyvsp[-2].t));
          } else {
            yyerror("functions can only be defined in .pal files");
          }
     	}
    break;
case 10:
#line 241 "parse.y"
{ 
	  if (state.src->type == source_with) {
            add_entity(mk_func_prot(yyvsp[-3].t, storage_public, yyvsp[-1].z));
	  } else if (state.src->type == with) {
            add_entity(mk_func_prot(yyvsp[-3].t, state.section.code_default, yyvsp[-1].z));
          } else {
            yyerror("function declarations can only be in .pub files");
          }
     	}
    break;
case 11:
#line 254 "parse.y"
{
 	  yyval.t = mk_head(yyvsp[0].s, NULL);
     	}
    break;
case 12:
#line 259 "parse.y"
{
 	  yyval.t = mk_head(yyvsp[-3].s, yyvsp[-1].t);
     	}
    break;
case 13:
#line 266 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 14:
#line 271 "parse.y"
{
	  yyval.t = node_list(yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 15:
#line 278 "parse.y"
{	  
	  if (state.src->type == source_with) {
	    yyval.t = mk_decl(type_var, yyvsp[-1].z, storage_public, yyvsp[0].s, NULL);
	  } else if (state.src->type == with) {
	    yyval.t = mk_decl(type_var, yyvsp[-1].z, state.section.udata_default, yyvsp[0].s, NULL);
	  } else {
	    /* should only get here from inside a function or procedure */
	    yyval.t = mk_decl(type_var, yyvsp[-1].z, storage_private, yyvsp[0].s, NULL);
	  }
        }
    break;
case 16:
#line 292 "parse.y"
{
 	  yyval.t = mk_body(yyvsp[-3].t, yyvsp[-1].t);
     	}
    break;
case 17:
#line 297 "parse.y"
{
 	  yyval.t = mk_body(NULL, yyvsp[-1].t);
     	}
    break;
case 18:
#line 304 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 19:
#line 309 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 20:
#line 316 "parse.y"
{ 
	  if (state.src->type == source_with) {
	    yyval.t = mk_decl_prot(yyvsp[-3].y, yyvsp[-2].z, storage_public, yyvsp[-1].s);
	  } else if (state.src->type == with) {
	    yyval.t = mk_decl_prot(yyvsp[-3].y, yyvsp[-2].z, state.section.udata_default, yyvsp[-1].s);
	  } else {
	    /* should only get here from inside a function or procedure */
	    yyval.t = mk_decl(yyvsp[-3].y, yyvsp[-2].z, storage_private, yyvsp[-1].s, NULL);
	  }
        }
    break;
case 21:
#line 328 "parse.y"
{ 
	  if (state.src->type == source_with) {
	    yyerror("initialized data can only appear in pal files");
	    yyval.t = mk_decl_prot(yyvsp[-5].y, yyvsp[-4].z, storage_public, yyvsp[-3].s);
	  } else if (state.src->type == with) {
	    yyerror("initialized data can only appear in pal files");
            yyval.t = mk_decl_prot(yyvsp[-5].y, yyvsp[-4].z, state.section.udata_default, yyvsp[-3].s);
	  } else {
	    yyval.t = mk_decl(yyvsp[-5].y, yyvsp[-4].z, storage_private, yyvsp[-3].s, yyvsp[-1].t);
	  }
        }
    break;
case 22:
#line 343 "parse.y"
{
	  yyval.y = type_const;
	}
    break;
case 23:
#line 348 "parse.y"
{
	  yyval.y = type_var;
	}
    break;
case 24:
#line 355 "parse.y"
{
	  yyval.z = size_bit;
	}
    break;
case 25:
#line 360 "parse.y"
{
	  yyval.z = size_byte;
	}
    break;
case 26:
#line 367 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 27:
#line 372 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 28:
#line 379 "parse.y"
{
	  yyval.t = mk_assembly(yyvsp[-1].s);
	}
    break;
case 29:
#line 384 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-5].t, yyvsp[-3].t, NULL);
	}
    break;
case 30:
#line 389 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-6].t, yyvsp[-4].t, yyvsp[-3].t);
	}
    break;
case 31:
#line 394 "parse.y"
{
	  yyval.t= mk_loop(NULL, yyvsp[-1].t, NULL, yyvsp[0].t);	
	}
    break;
case 32:
#line 399 "parse.y"
{
	  yyval.t= mk_loop(NULL, NULL, NULL, yyvsp[0].t);
	}
    break;
case 33:
#line 404 "parse.y"
{
	  yyval.t = yyvsp[-1].t;
	}
    break;
case 34:
#line 411 "parse.y"
{
	  /* last statement is elsif */
	  yyval.t = mk_cond(yyvsp[-2].t, yyvsp[0].t, NULL);
	}
    break;
case 35:
#line 417 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-3].t, yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 36:
#line 422 "parse.y"
{
	  /* last statement is else */
	  yyval.t = mk_cond(NULL, yyvsp[0].t, NULL);
	}
    break;
case 37:
#line 430 "parse.y"
{
	  yyval.t = yyvsp[-3].t;
	}
    break;
case 38:
#line 437 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 39:
#line 442 "parse.y"
{
	  yyval.t = node_list(yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 41:
#line 451 "parse.y"
{
	  yyval.t = mk_string(yyvsp[0].s);
        }
    break;
case 43:
#line 460 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 44:
#line 465 "parse.y"
{ yyval.o = op_eq; }
    break;
case 46:
#line 471 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 47:
#line 476 "parse.y"
{ yyval.o = op_land; }
    break;
case 48:
#line 477 "parse.y"
{ yyval.o = op_lor; }
    break;
case 50:
#line 483 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 51:
#line 488 "parse.y"
{ yyval.o = op_and; }
    break;
case 52:
#line 489 "parse.y"
{ yyval.o = op_or; }
    break;
case 53:
#line 490 "parse.y"
{ yyval.o = op_xor; }
    break;
case 55:
#line 496 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 56:
#line 501 "parse.y"
{ yyval.o = op_lt; }
    break;
case 57:
#line 502 "parse.y"
{ yyval.o = op_gt; }
    break;
case 58:
#line 503 "parse.y"
{ yyval.o = op_eq; }
    break;
case 59:
#line 504 "parse.y"
{ yyval.o = op_ne; }
    break;
case 60:
#line 505 "parse.y"
{ yyval.o = op_gte; }
    break;
case 61:
#line 506 "parse.y"
{ yyval.o = op_lte; }
    break;
case 63:
#line 512 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 64:
#line 517 "parse.y"
{ yyval.o = op_lsh; }
    break;
case 65:
#line 518 "parse.y"
{ yyval.o = op_rsh; }
    break;
case 67:
#line 524 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 68:
#line 529 "parse.y"
{ yyval.o = op_add; }
    break;
case 69:
#line 530 "parse.y"
{ yyval.o = op_sub; }
    break;
case 71:
#line 536 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 72:
#line 541 "parse.y"
{ yyval.o = op_mult; }
    break;
case 73:
#line 542 "parse.y"
{ yyval.o = op_div; }
    break;
case 74:
#line 543 "parse.y"
{ yyval.o = op_mod; }
    break;
case 76:
#line 549 "parse.y"
{
	  yyval.t = mk_unop(yyvsp[-1].o, yyvsp[0].t);
	}
    break;
case 77:
#line 554 "parse.y"
{ yyval.o = op_neg; }
    break;
case 78:
#line 555 "parse.y"
{ yyval.o = op_not; }
    break;
case 79:
#line 556 "parse.y"
{ yyval.o = op_com; }
    break;
case 80:
#line 557 "parse.y"
{ yyval.o = op_add; }
    break;
case 81:
#line 561 "parse.y"
{
	  yyval.t = mk_symbol(yyvsp[0].s);
        }
    break;
case 82:
#line 566 "parse.y"
{
	  /* function or procedure call */
	  yyval.t = mk_call(yyvsp[-2].s, NULL);
	}
    break;
case 83:
#line 572 "parse.y"
{
	  /* function or procedure call with arguments */
	  yyval.t = mk_call(yyvsp[-3].s, yyvsp[-1].t);
	}
    break;
case 84:
#line 578 "parse.y"
{
	  yyval.t = mk_constant(yyvsp[0].i);
	}
    break;
case 85:
#line 583 "parse.y"
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
#line 588 "parse.y"

