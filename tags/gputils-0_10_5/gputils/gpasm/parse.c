/* A Bison parser, made from parse.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	LABEL	257
# define	IDENTIFIER	258
# define	CBLOCK	259
# define	ENDC	260
# define	FILL	261
# define	NUMBER	262
# define	STRING	263
# define	HIGH	264
# define	LOW	265
# define	LSH	266
# define	RSH	267
# define	GREATER_EQUAL	268
# define	LESS_EQUAL	269
# define	EQUAL	270
# define	NOT_EQUAL	271
# define	LOGICAL_AND	272
# define	LOGICAL_OR	273
# define	ASSIGN_PLUS	274
# define	ASSIGN_MINUS	275
# define	ASSIGN_MULTIPLY	276
# define	ASSIGN_DIVIDE	277
# define	ASSIGN_MODULUS	278
# define	ASSIGN_LSH	279
# define	ASSIGN_RSH	280
# define	ASSIGN_AND	281
# define	ASSIGN_OR	282
# define	ASSIGN_XOR	283
# define	INCREMENT	284
# define	DECREMENT	285
# define	TBL_NO_CHANGE	286
# define	TBL_POST_INC	287
# define	TBL_POST_DEC	288
# define	TBL_PRE_INC	289
# define	CONCAT	290
# define	VAR	291
# define	VARLAB_BEGIN	292
# define	VAR_BEGIN	293
# define	VAR_END	294

#line 1 "parse.y"

/* Parser for gpasm
   Copyright (C) 1998,1999,2000,2001 James Bowman, Craig Franklin

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

#include "gpasm.h"

#include "evaluate.h"
#include "gpsymbol.h"
#include "gperror.h"
#include "directive.h"
#include "lst.h"
#include "macro.h"
#include "scan.h"

void yyerror(char *message)
{
  gperror(103, message);
}

int yylex(void);
extern int _16bit_core;

/************************************************************************/

/* Some simple functions for building parse trees */

static struct pnode *mk_pnode(enum pnode_tag tag)
{
  struct pnode *new = malloc(sizeof(*new));
  new->tag = tag;
  return new;
}

struct pnode *mk_constant(int value)
{
  struct pnode *new = mk_pnode(constant);
  new->value.constant = value;
  return new;
}

static struct pnode *mk_symbol(char *value)
{
  struct pnode *new = mk_pnode(symbol);
  new->value.symbol = value;
  return new;
}

static struct pnode *mk_string(char *value)
{
  struct pnode *new = mk_pnode(string);
  new->value.string = value;
  return new;
}

struct pnode *mk_list(struct pnode *head, struct pnode *tail)
{
  struct pnode *new = mk_pnode(list);
  new->value.list.head = head;
  new->value.list.tail = tail;
  return new;
}

static struct pnode *mk_2op(int op, struct pnode *p0, struct pnode *p1)
{
  struct pnode *new = mk_pnode(binop);
  new->value.binop.op = op;
  new->value.binop.p0 = p0;
  new->value.binop.p1 = p1;
  return new;
}

static struct pnode *mk_1op(int op, struct pnode *p0)
{
  struct pnode *new = mk_pnode(unop);  new->value.unop.op = op;
  new->value.unop.p0 = p0;
  return new;
}

/************************************************************************/
/* shared functions */

gpasmVal set_label(char *label, struct pnode *parms)
{
  gpasmVal value = 0;

  if (asm_enabled()) {
    value = do_or_append_insn("set", parms);
    if (!state.mac_prev) {
      set_global(label, value, TEMPORARY, gvt_constant);
    } else {
      state.mac_body->label = label;
    }
  }

  return value;
}

int return_op(int operation) 
{
  /* returns an operator for the replacement of i+=1 with i=i+1*/
  switch(operation) {
  case ASSIGN_PLUS:     return '+';
  case ASSIGN_MINUS:    return '-';
  case ASSIGN_MULTIPLY: return '*';
  case ASSIGN_DIVIDE:   return '/';
  case ASSIGN_MODULUS:  return '%';
  case ASSIGN_LSH:      return LSH;
  case ASSIGN_RSH:      return RSH;
  case ASSIGN_AND:      return '&';
  case ASSIGN_OR:       return '|';
  case ASSIGN_XOR:      return '^'; 
  default:
    assert(0); /* Unhandled operator */ 
  }

  return 0;
}

void next_line(int value)
{
  char l[BUFSIZ];
  char *e = l;


  if (state.src->type == macro) {
    if ((state.lst.expand) && (state.lst.enabled) && (state.pass == 2)) {
      assert(state.src->lst.m->src_line != NULL);
      lst_format_line(state.src->lst.m->src_line, value);
    }
    if (state.src->lst.m->next)
      state.src->lst.m = state.src->lst.m->next;
  
  } else if (state.src->lst.f != NULL) {
    fgets(l, BUFSIZ, state.src->lst.f);
    l[strlen(l) - 1] = '\0';	/* Eat the trailing newline */

    if (state.mac_prev) {
      state.lst.line.linetype = none;
      if (state.mac_body)
	state.mac_body->src_line = strdup(l);
    }

    if (state.lst.enabled && (state.pass == 2)) {
      lst_format_line(e, value);
    }
  }

  state.src->line_number++;
  

  switch (state.next_state) {
    case _exitmacro:
      execute_exitm();
      break;

    case _macro:
      /* push the label for local directive */
      state.stTop = push_macro_symbol_table(state.stTop);
      execute_macro(state.next_buffer.macro);
      break;

    case _include:
      open_src(state.next_buffer.file, 1);
      free(state.next_buffer.file);
      break;

    default:
      break;
  }
 
}


/************************************************************************/


#line 199 "parse.y"
#ifndef YYSTYPE
typedef union {
  gpasmVal i;
  char *s;
  struct pnode *p;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 1
#endif



#define	YYFINAL		152
#define	YYFLAG		-32768
#define	YYNTBASE	60

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 294 ? yytranslate[x] : 94)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      54,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,     2,    58,    51,    20,     2,
      59,    55,    49,    47,    56,    48,     2,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    57,     2,
      18,    25,    19,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    22,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    21,     2,    53,     2,     2,     2,
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
      16,    17,    23,    24,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     2,     6,    10,    15,    20,    24,    28,
      31,    33,    35,    38,    42,    49,    57,    58,    66,    67,
      74,    79,    80,    83,    85,    88,    91,    95,    97,   101,
     103,   107,   109,   111,   113,   115,   117,   119,   121,   123,
     125,   127,   129,   132,   136,   138,   140,   142,   146,   148,
     150,   154,   156,   158,   162,   164,   166,   170,   172,   174,
     176,   178,   182,   184,   186,   188,   190,   192,   194,   196,
     200,   202,   204,   206,   210,   212,   214,   216,   220,   222,
     224,   226,   228,   231,   233,   235,   237,   239,   241,   243,
     245,   247,   249,   253,   255,   257,   259,   261,   263,   267,
     271,   273,   277
};
static const short yyrhs[] =
{
      -1,     0,    60,    61,    62,     0,    60,     1,    54,     0,
      93,    70,    72,    54,     0,    93,    25,    72,    54,     0,
      93,    37,    54,     0,    93,    36,    54,     0,    93,    63,
       0,    63,     0,    54,     0,     4,    54,     0,     4,    71,
      54,     0,     7,     4,    55,    56,    72,    54,     0,     7,
       4,    71,    55,    56,    72,    54,     0,     0,     5,    72,
      54,    64,    66,     6,    54,     0,     0,     5,    54,    65,
      66,     6,    54,     0,     5,     1,     6,    54,     0,     0,
      66,    67,     0,    54,     0,    68,    54,     0,    93,    54,
       0,    93,    72,    54,     0,    69,     0,    68,    56,    69,
       0,    92,     0,    92,    57,    72,     0,    26,     0,    27,
       0,    28,     0,    29,     0,    30,     0,    31,     0,    32,
       0,    33,     0,    34,     0,    35,     0,    72,     0,    72,
      56,     0,    72,    56,    71,     0,    73,     0,     9,     0,
      75,     0,    73,    74,    75,     0,    25,     0,    77,     0,
      75,    76,    77,     0,    24,     0,    79,     0,    77,    78,
      79,     0,    23,     0,    81,     0,    79,    80,    81,     0,
      20,     0,    21,     0,    22,     0,    83,     0,    81,    82,
      83,     0,    18,     0,    19,     0,    16,     0,    17,     0,
      14,     0,    15,     0,    85,     0,    83,    84,    85,     0,
      12,     0,    13,     0,    87,     0,    85,    86,    87,     0,
      47,     0,    48,     0,    89,     0,    87,    88,    89,     0,
      49,     0,    50,     0,    51,     0,    91,     0,    90,    91,
       0,    10,     0,    11,     0,    48,     0,    52,     0,    53,
       0,    47,     0,    92,     0,     8,     0,    58,     0,    59,
      72,    55,     0,    49,     0,    39,     0,    40,     0,    41,
       0,     4,     0,    45,    72,    55,     0,    45,    72,    46,
       0,     3,     0,    44,    72,    55,     0,    44,    72,    46,
       0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   236,   238,   238,   245,   251,   263,   272,   281,   290,
     352,   365,   374,   379,   384,   400,   416,   416,   423,   423,
     430,   437,   438,   445,   447,   449,   454,   461,   463,   467,
     472,   479,   479,   479,   479,   480,   480,   480,   480,   481,
     481,   483,   488,   494,   501,   503,   523,   525,   532,   534,
     536,   543,   545,   547,   554,   556,   558,   565,   565,   565,
     567,   569,   576,   576,   576,   576,   576,   576,   578,   580,
     587,   587,   589,   591,   598,   598,   600,   602,   609,   609,
     609,   611,   613,   620,   620,   620,   620,   620,   620,   622,
     627,   632,   637,   642,   647,   652,   657,   664,   669,   674,
     682,   687,   695
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "LABEL", "IDENTIFIER", "CBLOCK", "ENDC", 
  "FILL", "NUMBER", "STRING", "HIGH", "LOW", "LSH", "RSH", 
  "GREATER_EQUAL", "LESS_EQUAL", "EQUAL", "NOT_EQUAL", "'<'", "'>'", 
  "'&'", "'|'", "'^'", "LOGICAL_AND", "LOGICAL_OR", "'='", "ASSIGN_PLUS", 
  "ASSIGN_MINUS", "ASSIGN_MULTIPLY", "ASSIGN_DIVIDE", "ASSIGN_MODULUS", 
  "ASSIGN_LSH", "ASSIGN_RSH", "ASSIGN_AND", "ASSIGN_OR", "ASSIGN_XOR", 
  "INCREMENT", "DECREMENT", "TBL_NO_CHANGE", "TBL_POST_INC", 
  "TBL_POST_DEC", "TBL_PRE_INC", "CONCAT", "VAR", "VARLAB_BEGIN", 
  "VAR_BEGIN", "VAR_END", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'~'", 
  "'\\n'", "')'", "','", "':'", "'$'", "'('", "program", "@1", "line", 
  "statement", "@2", "@3", "const_block", "const_line", "const_def_list", 
  "const_def", "assign_equal_ops", "parameter_list", "expr", "e9", "e9op", 
  "e8", "e8op", "e7", "e7op", "e6", "e6op", "e5", "e5op", "e4", "e4op", 
  "e3", "e3op", "e2", "e2op", "e1", "e1op", "e0", "cidentifier", 
  "label_concat", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    60,    61,    60,    60,    62,    62,    62,    62,    62,
      62,    63,    63,    63,    63,    63,    64,    63,    65,    63,
      63,    66,    66,    67,    67,    67,    67,    68,    68,    69,
      69,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    71,    71,    71,    72,    72,    73,    73,    74,    75,
      75,    76,    77,    77,    78,    79,    79,    80,    80,    80,
      81,    81,    82,    82,    82,    82,    82,    82,    83,    83,
      84,    84,    85,    85,    86,    86,    87,    87,    88,    88,
      88,    89,    89,    90,    90,    90,    90,    90,    90,    91,
      91,    91,    91,    91,    91,    91,    91,    92,    92,    92,
      93,    93,    93
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     0,     3,     3,     4,     4,     3,     3,     2,
       1,     1,     2,     3,     6,     7,     0,     7,     0,     6,
       4,     0,     2,     1,     2,     2,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     1,     1,     1,     3,     1,     1,
       3,     1,     1,     3,     1,     1,     3,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     3,     3,
       1,     3,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     0,     0,     4,   100,     0,     0,     0,     0,
      11,     3,    10,     0,    97,    90,    45,    83,    84,    94,
      95,    96,     0,    88,    85,    93,    86,    87,    12,    91,
       0,     0,    41,    44,    46,    49,    52,    55,    60,    68,
      72,    76,     0,    81,    89,     0,    18,     0,     0,     0,
       0,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,     0,     0,     9,     0,     0,     0,    13,    42,    48,
       0,    51,     0,    54,     0,    57,    58,    59,     0,    66,
      67,    64,    65,    62,    63,     0,    70,    71,     0,    74,
      75,     0,    78,    79,    80,     0,    82,     0,    21,    16,
       0,     0,   102,   101,     0,     8,     7,     0,    99,    98,
      92,    43,    47,    50,    53,    56,    61,    69,    73,    77,
      20,     0,    21,     0,     0,     6,     5,     0,    23,    22,
       0,    27,    29,     0,     0,     0,     0,    19,    24,     0,
       0,    25,     0,     0,    14,     0,    28,    30,    26,    17,
      15,     0,     0
};

static const short yydefgoto[] =
{
       1,     3,    11,    12,   122,    98,   121,   129,   130,   131,
      64,    31,    32,    33,    70,    34,    72,    35,    74,    36,
      78,    37,    85,    38,    88,    39,    91,    40,    95,    41,
      42,    43,    44,   133
};

static const short yypact[] =
{
  -32768,    96,   -21,   184,-32768,-32768,    21,     0,    30,   156,
  -32768,-32768,-32768,   229,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,   156,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
     156,    -8,    -6,    26,    31,    44,    43,     3,    15,   -35,
      33,-32768,   186,-32768,-32768,    50,-32768,    17,    83,   -41,
     156,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,    18,    24,-32768,   156,   -39,    40,-32768,   156,-32768,
     171,-32768,   171,-32768,   171,-32768,-32768,-32768,   171,-32768,
  -32768,-32768,-32768,-32768,-32768,   171,-32768,-32768,   171,-32768,
  -32768,   171,-32768,-32768,-32768,   171,-32768,    27,-32768,-32768,
      29,    47,-32768,-32768,    35,-32768,-32768,    51,-32768,-32768,
  -32768,-32768,    31,    44,    43,     3,    15,   -35,    33,-32768,
  -32768,    32,-32768,   156,    42,-32768,-32768,    52,-32768,-32768,
      34,-32768,    53,   104,   196,    55,   156,-32768,-32768,    -1,
     156,-32768,    57,    63,-32768,    64,-32768,-32768,-32768,-32768,
  -32768,   107,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,    91,-32768,-32768,    -3,-32768,-32768,   -19,
  -32768,   -42,    -7,-32768,-32768,    67,-32768,    49,-32768,    60,
  -32768,    61,-32768,    62,-32768,    37,-32768,    36,-32768,    59,
  -32768,   106,   -97,   143
};


#define	YYLAST		283


static const short yytable[] =
{
      47,    45,    49,    14,    14,   102,   101,   108,    15,    16,
      17,    18,    89,    90,   103,    65,   109,    79,    80,    81,
      82,    83,    84,    66,   132,    14,   111,    86,    87,    15,
      16,    17,    18,     4,    48,     5,    14,   132,   127,    19,
      20,    21,   132,   104,    22,    22,    67,    23,    24,    25,
      68,    69,    26,    27,    46,    71,    97,   107,    29,    30,
      19,    20,    21,    75,    76,    77,    22,    73,    23,    24,
      25,    99,   105,    26,    27,    28,     9,    22,   106,    29,
      30,   120,    92,    93,    94,   123,   128,    14,   138,   125,
     139,    15,    16,    17,    18,   110,   151,     2,   136,    -2,
      -2,    -2,   124,    -2,    63,   126,   137,   152,    14,   144,
     140,   148,    15,    16,    17,    18,   135,   149,   150,   134,
     146,   113,    19,    20,    21,   117,   142,   118,    22,   145,
      23,    24,    25,   147,   114,    26,    27,   112,   100,   115,
      -2,    29,    30,    19,    20,    21,    13,   116,    96,    22,
      -2,    23,    24,    25,   119,     0,    26,    27,   141,     0,
      14,     0,    29,    30,    15,    16,    17,    18,     0,     0,
       0,     0,     0,     0,     0,    14,     0,     0,     0,    15,
       0,    17,    18,     0,     0,     0,     0,     5,     6,     7,
      14,     8,     0,     0,    15,    19,    20,    21,     0,     5,
      14,    22,   143,    23,    24,    25,     0,     0,    26,    27,
      19,    20,    21,     0,    29,    30,    22,     0,    23,    24,
      25,     0,     0,    26,    27,    19,    20,    21,     9,    29,
      30,    22,     0,     6,     7,    25,     8,     0,    10,     0,
       9,    22,     0,     0,    29,    30,     0,     0,     0,     0,
     128,     0,     0,     0,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    10
};

static const short yycheck[] =
{
       7,     1,     9,     4,     4,    46,    48,    46,     8,     9,
      10,    11,    47,    48,    55,    22,    55,    14,    15,    16,
      17,    18,    19,    30,   121,     4,    68,    12,    13,     8,
       9,    10,    11,    54,     4,     3,     4,   134,     6,    39,
      40,    41,   139,    50,    45,    45,    54,    47,    48,    49,
      56,    25,    52,    53,    54,    24,     6,    64,    58,    59,
      39,    40,    41,    20,    21,    22,    45,    23,    47,    48,
      49,    54,    54,    52,    53,    54,    44,    45,    54,    58,
      59,    54,    49,    50,    51,    56,    54,     4,    54,    54,
      56,     8,     9,    10,    11,    55,     0,     1,    56,     3,
       4,     5,    55,     7,    13,    54,    54,     0,     4,    54,
      57,    54,     8,     9,    10,    11,   123,    54,    54,   122,
     139,    72,    39,    40,    41,    88,   133,    91,    45,   136,
      47,    48,    49,   140,    74,    52,    53,    70,    55,    78,
      44,    58,    59,    39,    40,    41,     3,    85,    42,    45,
      54,    47,    48,    49,    95,    -1,    52,    53,    54,    -1,
       4,    -1,    58,    59,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     4,    -1,    -1,    -1,     8,
      -1,    10,    11,    -1,    -1,    -1,    -1,     3,     4,     5,
       4,     7,    -1,    -1,     8,    39,    40,    41,    -1,     3,
       4,    45,     6,    47,    48,    49,    -1,    -1,    52,    53,
      39,    40,    41,    -1,    58,    59,    45,    -1,    47,    48,
      49,    -1,    -1,    52,    53,    39,    40,    41,    44,    58,
      59,    45,    -1,     4,     5,    49,     7,    -1,    54,    -1,
      44,    45,    -1,    -1,    58,    59,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54
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

case 2:
#line 240 "parse.y"
{ 
          state.lst.line.was_org = state.org; 
          state.lst.line.linetype = none; 
          state.next_state = _nochange;
        }
    break;
case 4:
#line 246 "parse.y"
{ 
	  next_line(0);
	}
    break;
case 5:
#line 253 "parse.y"
{
	  struct pnode *parms;
	  int exp_result;

          exp_result = do_insn("set", mk_list(yyvsp[-1].p, NULL));          
          parms = mk_list(mk_2op(return_op(yyvsp[-2].i), 
                                 mk_symbol(yyvsp[-3].s), 
                                 mk_constant(exp_result)), NULL);
	  next_line(set_label(yyvsp[-3].s, parms));
	}
    break;
case 6:
#line 265 "parse.y"
{
	  struct pnode *parms;

	  /* implements i = 6 + 1 */           
	  parms = mk_list(yyvsp[-1].p, NULL);
	  next_line(set_label(yyvsp[-3].s, parms));
	}
    break;
case 7:
#line 274 "parse.y"
{
	  struct pnode *parms;

	  /* implements i-- */           
	  parms = mk_list(mk_1op(DECREMENT, mk_symbol(yyvsp[-2].s)), NULL);
	  next_line(set_label(yyvsp[-2].s, parms));
	}
    break;
case 8:
#line 283 "parse.y"
{
          struct pnode *parms;

	  /* implements i++ */          
	  parms = mk_list(mk_1op(INCREMENT, mk_symbol(yyvsp[-2].s)), NULL);
	  next_line(set_label(yyvsp[-2].s, parms));
	}
    break;
case 9:
#line 292 "parse.y"
{
	  if (state.lst.line.linetype == none)
	    state.lst.line.linetype = insn;
	  
	  if (asm_enabled()) {
	    if (state.mac_head) {
	      /* This is a macro definition.  Set it up */
	      struct symbol *mac;
	      struct macro_head *h = NULL;

	      mac = get_symbol(state.stMacros, yyvsp[-1].s);
	      if (mac)
		h = get_symbol_annotation(mac);

	      /* It's not an error if macro was defined on pass 1 and
		 we're in pass 2. */
	      if (h &&
		  !((h->pass == 1) && (state.pass == 2))) {
		gperror(GPE_DUPLICATE_MACRO, NULL);
	      } else {
		if (!mac)
		  mac = add_symbol(state.stMacros, yyvsp[-1].s);
		annotate_symbol(mac, state.mac_head);
		h = state.mac_head;
		h->line_number = state.src->line_number;
	      }
	      h->pass = state.pass;
 	      
	      /* The macro is defined so allow calls. */
	      if (state.pass == 2)
	        h->defined = 1;

	      state.mac_head = NULL;
	    } else if (!state.mac_prev) {
	      /* Outside a macro, just define the label. */
	      switch (state.lst.line.linetype) {
	      case set:
		set_global(yyvsp[-1].s, yyvsp[0].i, TEMPORARY, gvt_constant);
		break;
              case org:
	      case equ:
		set_global(yyvsp[-1].s, yyvsp[0].i, PERMANENT, gvt_constant);
		break;
	      case insn:
		set_global(yyvsp[-1].s, yyvsp[0].i << _16bit_core, PERMANENT, gvt_address);
		break;
	      case dir:
                gperror(GPE_ILLEGAL_LABEL, NULL);
                break;
              default:
		break;
	      }
	    } else {
	      /* Inside a macro; add the label to the current line */
	      if (state.mac_body)
		state.mac_body->label = yyvsp[-1].s;
	    }
	  }
	  next_line(yyvsp[0].i);
	}
    break;
case 10:
#line 354 "parse.y"
{
	  if (state.mac_head) {
	    /* This is a macro definition, but the label was missing */
	    state.mac_head = NULL;
	    gperror(GPE_NO_MACRO_NAME, NULL);
	  } else {
	    next_line(0);
	  }
	}
    break;
case 11:
#line 367 "parse.y"
{
	  if (!state.mac_prev) {
	    yyval.i = state.org;
	  } else {
	    macro_append();
	  }
	}
    break;
case 12:
#line 376 "parse.y"
{
	  yyval.i = do_or_append_insn(yyvsp[-1].s, NULL);
	}
    break;
case 13:
#line 381 "parse.y"
{
	  yyval.i = do_or_append_insn(yyvsp[-2].s, yyvsp[-1].p);
	}
    break;
case 14:
#line 386 "parse.y"
{
	  int number;
	  int i;

          if (!state.mac_prev) {
            number = eval_fill_number(yyvsp[-1].p);

            for (i = 0; i < number; i++) {
              yyval.i = do_insn(yyvsp[-4].s, NULL);
            }
          } else {
	    macro_append();
	  }
	}
    break;
case 15:
#line 402 "parse.y"
{
	  int number;
	  int i;

          if (!state.mac_prev) {
            number = eval_fill_number(yyvsp[-1].p);

            for (i = 0; i < number; i++) {
              yyval.i = do_insn(yyvsp[-5].s, yyvsp[-4].p);
            }
          } else {
	    macro_append();
	  }
	}
    break;
case 16:
#line 417 "parse.y"
{ begin_cblock(yyvsp[-1].p); next_line(0); }
    break;
case 17:
#line 420 "parse.y"
{
	  yyval.i = 0;
	}
    break;
case 18:
#line 424 "parse.y"
{ next_line(0); }
    break;
case 19:
#line 427 "parse.y"
{
           yyval.i = 0;
        }
    break;
case 20:
#line 432 "parse.y"
{
	  yyval.i = 0;
  	}
    break;
case 22:
#line 440 "parse.y"
{
	  next_line(0);
	}
    break;
case 25:
#line 451 "parse.y"
{
	  cblock_expr(mk_symbol(yyvsp[-1].s));
	}
    break;
case 26:
#line 456 "parse.y"
{
	  cblock_expr_incr(mk_symbol(yyvsp[-2].s), yyvsp[-1].p);
	}
    break;
case 29:
#line 469 "parse.y"
{
	  cblock_expr(yyvsp[0].p);
	}
    break;
case 30:
#line 474 "parse.y"
{
	  cblock_expr_incr(yyvsp[-2].p, yyvsp[0].p);
	}
    break;
case 41:
#line 485 "parse.y"
{
	  yyval.p = mk_list(yyvsp[0].p, NULL);
	}
    break;
case 42:
#line 490 "parse.y"
{
	  gperror(GPE_BADCHAR, "Illegal Character (,)");
          yyval.p = mk_list(yyvsp[-1].p, NULL);
	}
    break;
case 43:
#line 496 "parse.y"
{
	  yyval.p = mk_list(yyvsp[-2].p, yyvsp[0].p);
	}
    break;
case 45:
#line 505 "parse.y"
{
	  /* Cook up the string, replacing \X with its code. */
	  char *ps, *pd;

	  ps = pd = yyvsp[0].s;
	  while (*ps) {
	    if (*ps != '\\') {
	      *pd++ = *ps++;
	    } else {
	      *pd++ = gpasm_magic(ps);
	      ps += 2;
	    }
	  }
	  *pd = 0;
	  yyval.p = mk_string(yyvsp[0].s);
        }
    break;
case 47:
#line 527 "parse.y"
{
	  yyval.p = mk_2op(yyvsp[-1].i, yyvsp[-2].p, yyvsp[0].p);
	}
    break;
case 50:
#line 538 "parse.y"
{
	  yyval.p = mk_2op(yyvsp[-1].i, yyvsp[-2].p, yyvsp[0].p);
	}
    break;
case 53:
#line 549 "parse.y"
{
	  yyval.p = mk_2op(yyvsp[-1].i, yyvsp[-2].p, yyvsp[0].p);
	}
    break;
case 56:
#line 560 "parse.y"
{
	  yyval.p = mk_2op(yyvsp[-1].i, yyvsp[-2].p, yyvsp[0].p);
	}
    break;
case 61:
#line 571 "parse.y"
{
	  yyval.p = mk_2op(yyvsp[-1].i, yyvsp[-2].p, yyvsp[0].p);
	}
    break;
case 69:
#line 582 "parse.y"
{
	  yyval.p = mk_2op(yyvsp[-1].i, yyvsp[-2].p, yyvsp[0].p);
	}
    break;
case 73:
#line 593 "parse.y"
{
	  yyval.p = mk_2op(yyvsp[-1].i, yyvsp[-2].p, yyvsp[0].p);
	}
    break;
case 77:
#line 604 "parse.y"
{
	  yyval.p = mk_2op(yyvsp[-1].i, yyvsp[-2].p, yyvsp[0].p);
	}
    break;
case 82:
#line 615 "parse.y"
{
	  yyval.p = mk_1op(yyvsp[-1].i, yyvsp[0].p);
	}
    break;
case 89:
#line 624 "parse.y"
{
	  yyval.p = yyvsp[0].p;
        }
    break;
case 90:
#line 629 "parse.y"
{
	  yyval.p = mk_constant(yyvsp[0].i);
	}
    break;
case 91:
#line 634 "parse.y"
{
	  yyval.p = mk_symbol("$");
	}
    break;
case 92:
#line 639 "parse.y"
{
	  yyval.p = yyvsp[-1].p;
	}
    break;
case 93:
#line 644 "parse.y"
{
	  yyval.p = mk_constant(TBL_NO_CHANGE);
	}
    break;
case 94:
#line 649 "parse.y"
{
	  yyval.p = mk_constant(yyvsp[0].i);
	}
    break;
case 95:
#line 654 "parse.y"
{
	  yyval.p = mk_constant(yyvsp[0].i);
	}
    break;
case 96:
#line 659 "parse.y"
{
	  yyval.p = mk_constant(yyvsp[0].i);
	}
    break;
case 97:
#line 666 "parse.y"
{ 
          yyval.p = mk_symbol(yyvsp[0].s);
        }
    break;
case 98:
#line 671 "parse.y"
{
          yyval.p = mk_2op(CONCAT, mk_symbol(yyvsp[-2].s), mk_1op(VAR, yyvsp[-1].p));
        }
    break;
case 99:
#line 676 "parse.y"
{
          yyval.p = mk_2op(CONCAT, mk_symbol(yyvsp[-2].s), 
                        mk_2op(CONCAT, mk_1op(VAR, yyvsp[-1].p), mk_symbol(yyvsp[0].s)));
        }
    break;
case 100:
#line 684 "parse.y"
{ 
          yyval.s = yyvsp[0].s;
        }
    break;
case 101:
#line 689 "parse.y"
{
          if (!state.mac_prev) {
	    yyval.s = evaluate_concatenation(mk_2op(CONCAT,  mk_symbol(yyvsp[-2].s), 
                           mk_1op(VAR, yyvsp[-1].p)));
	  }
        }
    break;
case 102:
#line 697 "parse.y"
{
          if (!state.mac_prev) {
            yyval.s = evaluate_concatenation(mk_2op(CONCAT,  mk_symbol(yyvsp[-2].s), 
                      mk_2op(CONCAT, mk_1op(VAR, yyvsp[-1].p), mk_symbol(yyvsp[0].s))));
	  }
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
#line 705 "parse.y"

