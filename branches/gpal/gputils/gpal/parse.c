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

/* FIXME: Clean this up.  We need to read the pragmas then modify the data
   so the mod doesn't start after the pragma statement. Maybe use the
   parse tree to implement the pragmas. */

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
          /* FIXME: change from symbol to string */
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
      } else if (strcasecmp(lhs->value.symbol, "code_address") == 0) {
        if (rhs->tag != node_constant) {
          gp_error("invalid code address");
        } else if (state.src->type == source) {            
          state.section.code_addr = rhs->value.constant;
          state.section.code_addr_valid = true;
        } else {
          gp_error("udata section addresses can only be in .pal files");
        }
      } else if (strcasecmp(lhs->value.symbol, "udata_address") == 0) {
        if (rhs->tag != node_constant) {
          gp_error("invalid udata address");
        } else if (state.src->type == source) {            
          state.section.udata_addr = rhs->value.constant;
          state.section.udata_addr_valid = true;
        } else {
          gp_error("udata section addresses can only be in .pal files");
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


#line 156 "parse.y"
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
       0,     0,     1,     4,     8,    12,    16,    22,    29,    35,
      42,    44,    47,    49,    55,    59,    67,    73,    75,    80,
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
      -1,    56,    57,     0,    56,     1,    52,     0,     7,    73,
      30,     0,     9,    27,    30,     0,    25,     6,     4,    25,
      30,     0,    25,     6,    58,     4,    25,    30,     0,    22,
       6,     4,    22,    30,     0,    22,     6,    58,     4,    22,
      30,     0,    59,     0,    59,    58,     0,    65,     0,     8,
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
       0,   213,   215,   217,   221,   226,   231,   233,   238,   240,
     247,   252,   259,   264,   273,   284,   293,   306,   311,   318,
     323,   330,   344,   349,   356,   361,   368,   380,   395,   400,
     407,   412,   419,   424,   431,   436,   441,   446,   451,   456,
     463,   469,   474,   482,   489,   494,   501,   503,   510,   512,
     519,   521,   523,   530,   531,   533,   535,   542,   543,   544,
     546,   548,   555,   556,   557,   558,   559,   560,   562,   564,
     571,   572,   574,   576,   583,   584,   586,   588,   595,   596,
     597,   599,   601,   608,   609,   610,   611,   613,   618,   624,
     630,   635
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
       0,    56,    56,    56,    57,    57,    57,    57,    57,    57,
      58,    58,    59,    59,    59,    59,    59,    60,    60,    61,
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
       0,     0,     2,     3,     3,     3,     5,     6,     5,     6,
       1,     2,     1,     5,     3,     7,     5,     1,     4,     1,
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
       1,     0,     0,     0,     0,     0,     0,     2,     3,    87,
      90,    47,    86,    83,    84,    85,     0,     0,    46,    48,
      51,    55,    60,    68,    72,    76,     0,    81,     0,     0,
       0,     0,     0,     4,    50,     0,    53,    54,     0,    57,
      58,    59,     0,    66,    67,    64,    65,    62,    63,     0,
      70,    71,     0,    74,    75,     0,    78,    79,    80,     0,
      82,     5,     0,     0,     0,    29,    28,     0,    10,    12,
       0,     0,     0,    88,     0,    44,    91,    49,    52,    56,
      61,    69,    73,    77,     0,    17,     0,     0,     0,    11,
      30,    31,     0,     0,     0,    89,     0,     8,     0,     0,
       0,    14,     0,     0,     0,     6,     0,    45,     0,    19,
       0,     0,     0,     0,    24,     0,     9,    26,     0,     7,
      18,     0,    21,    16,     0,     0,     0,     0,     0,     0,
      32,    38,     0,     0,    25,    13,     0,    20,     0,     0,
       0,     0,    34,    23,    33,    39,     0,    27,    15,     0,
      37,     0,    22,     0,     0,     0,     0,     0,     0,    43,
       0,     0,    42,     0,    35,     0,     0,    40,    36,    41,
       0,     0
};

static const short yydefgoto[] =
{
       1,     7,    67,    68,    86,   108,   109,   102,   113,    69,
      70,   110,   129,   130,   158,   131,    74,   132,    18,    35,
      19,    38,    20,    42,    21,    49,    22,    52,    23,    55,
      24,    59,    25,    26,    27
};

static const short yypact[] =
{
  -32768,    78,   -36,    22,     0,    28,    37,-32768,-32768,     4,
  -32768,-32768,-32768,-32768,-32768,-32768,    22,    32,    36,    23,
      30,    91,    59,    51,   -26,-32768,   -18,-32768,    44,    84,
      90,     2,    29,-32768,-32768,    31,-32768,-32768,    31,-32768,
  -32768,-32768,    31,-32768,-32768,-32768,-32768,-32768,-32768,    31,
  -32768,-32768,    31,-32768,-32768,    31,-32768,-32768,-32768,    31,
  -32768,-32768,    64,    72,    72,-32768,-32768,   110,   101,-32768,
      85,    92,   112,-32768,    66,    75,-32768,    23,    30,    91,
      59,    51,   -26,-32768,   102,    68,   115,     8,   111,-32768,
  -32768,-32768,   107,   105,   113,-32768,    22,-32768,    85,    85,
      43,-32768,   128,   109,   -19,-32768,   114,-32768,    83,    86,
     116,     9,    -9,   137,    93,   117,-32768,-32768,    22,-32768,
  -32768,    85,-32768,-32768,   140,    22,    22,    -9,   118,   138,
      -9,-32768,   119,    -9,-32768,-32768,   120,-32768,   121,   135,
     139,   148,-32768,-32768,-32768,-32768,   151,-32768,-32768,    -9,
  -32768,   141,-32768,    50,   127,   149,    22,    -9,   154,-32768,
     130,   150,-32768,   152,-32768,    -9,   133,    99,-32768,-32768,
     164,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,   -23,-32768,   103,    45,-32768,    54,    55,   -88,
  -32768,   -66,  -125,-32768,     1,    33,    74,    -3,-32768,-32768,
     136,-32768,   134,-32768,   132,-32768,   126,-32768,   124,-32768,
     122,-32768,   123,-32768,   153
};


#define	YYLAST		182


static const short yytable[] =
{
      17,   125,   141,   126,    92,   144,   127,    72,   146,     9,
      10,   117,   114,    32,   100,   100,     8,   128,     9,    10,
      11,    56,    57,    58,   153,   118,   114,    28,    75,     9,
      10,    11,   162,   111,    29,    16,    12,    13,   101,   123,
     167,    14,    15,    30,    16,    89,   112,    12,    13,     9,
      10,    11,    14,    15,   155,    16,    73,    31,     9,    10,
      65,    66,    33,   156,   157,    36,    37,    12,    13,    39,
      40,    41,    14,    15,    61,    16,    12,    13,   170,     2,
      34,    14,    15,    76,    16,     3,    84,     4,    62,    63,
      50,    51,    64,    75,    71,    63,    53,    54,    64,    85,
       5,    65,    66,     6,    90,    91,    63,    65,    66,    64,
      65,    66,   156,   157,    88,   136,    94,    93,    65,    66,
      95,    98,   139,   140,    43,    44,    45,    46,    47,    48,
      96,    99,    97,   103,   104,   105,   115,   120,   106,   116,
     133,   121,   143,   122,   119,   138,   149,   135,   142,   145,
     147,   148,   151,   161,   127,   152,   154,   159,   163,   160,
     164,   165,   166,   168,   171,   124,   137,    87,   169,   134,
     107,    77,    78,   150,    79,    80,    81,    82,     0,    60,
       0,     0,    83
};

static const short yycheck[] =
{
       3,    10,   127,    12,    70,   130,    15,    30,   133,    27,
      28,    30,   100,    16,     6,     6,    52,    26,    27,    28,
      29,    47,    48,    49,   149,    44,   114,    27,    31,    27,
      28,    29,   157,    99,     6,    53,    45,    46,    30,    30,
     165,    50,    51,     6,    53,    68,     3,    45,    46,    27,
      28,    29,    50,    51,     4,    53,    54,    53,    27,    28,
      17,    18,    30,    13,    14,    42,    43,    45,    46,    39,
      40,    41,    50,    51,    30,    53,    45,    46,     0,     1,
      44,    50,    51,    54,    53,     7,    22,     9,     4,     5,
      31,    32,     8,    96,     4,     5,    45,    46,     8,    27,
      22,    17,    18,    25,    19,    20,     5,    17,    18,     8,
      17,    18,    13,    14,     4,   118,     4,    25,    17,    18,
      54,    53,   125,   126,    33,    34,    35,    36,    37,    38,
      55,    16,    30,    22,    27,    30,     8,    54,    25,    30,
       3,    55,     4,    27,    30,     5,    11,    30,    30,    30,
      30,    30,     4,   156,    15,     4,    15,    30,     4,    10,
      30,    11,    10,    30,     0,   111,   121,    64,   167,   114,
      96,    35,    38,   140,    42,    49,    52,    55,    -1,    26,
      -1,    -1,    59
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
#line 223 "parse.y"
{
	  process_pragma(yyvsp[-1].t);
	}
    break;
case 5:
#line 228 "parse.y"
{
	  open_src(yyvsp[-1].s, with);
	}
    break;
case 6:
#line 232 "parse.y"
{ }
    break;
case 7:
#line 235 "parse.y"
{
	  add_entity(mk_module(yyvsp[-3].t));
	}
    break;
case 8:
#line 239 "parse.y"
{ }
    break;
case 9:
#line 242 "parse.y"
{
	  add_entity(mk_public(yyvsp[-3].t));
	}
    break;
case 10:
#line 249 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 11:
#line 254 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 12:
#line 261 "parse.y"
{
	  yyval.t = yyvsp[0].t;
        }
    break;
case 13:
#line 266 "parse.y"
{ 
          if (state.src->type == source) {
            yyval.t = mk_proc(yyvsp[-3].t, storage_private, yyvsp[-2].t);
          } else {
            yyerror("procedures can only be defined in modules");
          }
     	}
    break;
case 14:
#line 275 "parse.y"
{ 
	  if (state.src->type == source_with) {
            yyval.t = mk_proc_prot(yyvsp[-1].t, storage_public);
	  } else if (state.src->type == with) {
            yyval.t = mk_proc_prot(yyvsp[-1].t, state.section.code_default);
          } else {
            yyerror("procedure declarations can only be in a public");
          }
     	}
    break;
case 15:
#line 286 "parse.y"
{ 
	  if (state.src->type == source) {
            yyval.t = mk_func(yyvsp[-5].t, storage_private, yyvsp[-3].z, yyvsp[-2].t);
          } else {
            yyerror("functions can only be defined in modules");
          }
     	}
    break;
case 16:
#line 295 "parse.y"
{ 
	  if (state.src->type == source_with) {
            yyval.t = mk_func_prot(yyvsp[-3].t, storage_public, yyvsp[-1].z);
	  } else if (state.src->type == with) {
            yyval.t = mk_func_prot(yyvsp[-3].t, state.section.code_default, yyvsp[-1].z);
          } else {
            yyerror("function declarations can only be in a public");
          }
     	}
    break;
case 17:
#line 308 "parse.y"
{
 	  yyval.t = mk_head(yyvsp[0].s, NULL);
     	}
    break;
case 18:
#line 313 "parse.y"
{
 	  yyval.t = mk_head(yyvsp[-3].s, yyvsp[-1].t);
     	}
    break;
case 19:
#line 320 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 20:
#line 325 "parse.y"
{
	  yyval.t = node_list(yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 21:
#line 332 "parse.y"
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
case 22:
#line 346 "parse.y"
{
 	  yyval.t = mk_body(yyvsp[-3].t, yyvsp[-1].t);
     	}
    break;
case 23:
#line 351 "parse.y"
{
 	  yyval.t = mk_body(NULL, yyvsp[-1].t);
     	}
    break;
case 24:
#line 358 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 25:
#line 363 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 26:
#line 370 "parse.y"
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
case 27:
#line 382 "parse.y"
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
case 28:
#line 397 "parse.y"
{
	  yyval.y = type_const;
	}
    break;
case 29:
#line 402 "parse.y"
{
	  yyval.y = type_var;
	}
    break;
case 30:
#line 409 "parse.y"
{
	  yyval.z = size_bit;
	}
    break;
case 31:
#line 414 "parse.y"
{
	  yyval.z = size_byte;
	}
    break;
case 32:
#line 421 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 33:
#line 426 "parse.y"
{
	  yyval.t = node_list(yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 34:
#line 433 "parse.y"
{
	  yyval.t = mk_assembly(yyvsp[-1].s);
	}
    break;
case 35:
#line 438 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-5].t, yyvsp[-3].t, NULL);
	}
    break;
case 36:
#line 443 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-6].t, yyvsp[-4].t, yyvsp[-3].t);
	}
    break;
case 37:
#line 448 "parse.y"
{
	  yyval.t= mk_loop(NULL, yyvsp[-1].t, NULL, yyvsp[0].t);	
	}
    break;
case 38:
#line 453 "parse.y"
{
	  yyval.t= mk_loop(NULL, NULL, NULL, yyvsp[0].t);
	}
    break;
case 39:
#line 458 "parse.y"
{
	  yyval.t = yyvsp[-1].t;
	}
    break;
case 40:
#line 465 "parse.y"
{
	  /* last statement is elsif */
	  yyval.t = mk_cond(yyvsp[-2].t, yyvsp[0].t, NULL);
	}
    break;
case 41:
#line 471 "parse.y"
{
	  yyval.t = mk_cond(yyvsp[-3].t, yyvsp[-1].t, yyvsp[0].t);
	}
    break;
case 42:
#line 476 "parse.y"
{
	  /* last statement is else */
	  yyval.t = mk_cond(NULL, yyvsp[0].t, NULL);
	}
    break;
case 43:
#line 484 "parse.y"
{
	  yyval.t = yyvsp[-3].t;
	}
    break;
case 44:
#line 491 "parse.y"
{
	  yyval.t = node_list(yyvsp[0].t, NULL);
	}
    break;
case 45:
#line 496 "parse.y"
{
	  yyval.t = node_list(yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 47:
#line 505 "parse.y"
{
	  yyval.t = mk_string(yyvsp[0].s);
        }
    break;
case 49:
#line 514 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 50:
#line 519 "parse.y"
{ yyval.o = op_eq; }
    break;
case 52:
#line 525 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 53:
#line 530 "parse.y"
{ yyval.o = op_land; }
    break;
case 54:
#line 531 "parse.y"
{ yyval.o = op_lor; }
    break;
case 56:
#line 537 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 57:
#line 542 "parse.y"
{ yyval.o = op_and; }
    break;
case 58:
#line 543 "parse.y"
{ yyval.o = op_or; }
    break;
case 59:
#line 544 "parse.y"
{ yyval.o = op_xor; }
    break;
case 61:
#line 550 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 62:
#line 555 "parse.y"
{ yyval.o = op_lt; }
    break;
case 63:
#line 556 "parse.y"
{ yyval.o = op_gt; }
    break;
case 64:
#line 557 "parse.y"
{ yyval.o = op_eq; }
    break;
case 65:
#line 558 "parse.y"
{ yyval.o = op_ne; }
    break;
case 66:
#line 559 "parse.y"
{ yyval.o = op_gte; }
    break;
case 67:
#line 560 "parse.y"
{ yyval.o = op_lte; }
    break;
case 69:
#line 566 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 70:
#line 571 "parse.y"
{ yyval.o = op_lsh; }
    break;
case 71:
#line 572 "parse.y"
{ yyval.o = op_rsh; }
    break;
case 73:
#line 578 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 74:
#line 583 "parse.y"
{ yyval.o = op_add; }
    break;
case 75:
#line 584 "parse.y"
{ yyval.o = op_sub; }
    break;
case 77:
#line 590 "parse.y"
{
	  yyval.t = mk_binop(yyvsp[-1].o, yyvsp[-2].t, yyvsp[0].t);
	}
    break;
case 78:
#line 595 "parse.y"
{ yyval.o = op_mult; }
    break;
case 79:
#line 596 "parse.y"
{ yyval.o = op_div; }
    break;
case 80:
#line 597 "parse.y"
{ yyval.o = op_mod; }
    break;
case 82:
#line 603 "parse.y"
{
	  yyval.t = mk_unop(yyvsp[-1].o, yyvsp[0].t);
	}
    break;
case 83:
#line 608 "parse.y"
{ yyval.o = op_neg; }
    break;
case 84:
#line 609 "parse.y"
{ yyval.o = op_not; }
    break;
case 85:
#line 610 "parse.y"
{ yyval.o = op_com; }
    break;
case 86:
#line 611 "parse.y"
{ yyval.o = op_add; }
    break;
case 87:
#line 615 "parse.y"
{
	  yyval.t = mk_symbol(yyvsp[0].s);
        }
    break;
case 88:
#line 620 "parse.y"
{
	  /* function or procedure call */
	  yyval.t = mk_call(yyvsp[-2].s, NULL);
	}
    break;
case 89:
#line 626 "parse.y"
{
	  /* function or procedure call with arguments */
	  yyval.t = mk_call(yyvsp[-3].s, yyvsp[-1].t);
	}
    break;
case 90:
#line 632 "parse.y"
{
	  yyval.t = mk_constant(yyvsp[0].i);
	}
    break;
case 91:
#line 637 "parse.y"
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
#line 642 "parse.y"

