/* gpasm preprocessor implementation
   Copyright (C) 1012 Borut Razem

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
#include "gpasm.h"
#include "evaluate.h"
#include "gperror.h"
#include "directive.h"
#include "gptypes.h"
#include "gpsymbol.h"
#include "preprocess.h"

#define DEBUG 0
#define DBG_printf !DEBUG ? (void)0 : (void)printf

#define BUF_REPLACE(buf, start, end, len, repl_buf, repl_len, buf_size) \
  do { \
    memmove(&(buf)[(start) + (repl_len)], &(buf)[(end)], (len) - (end)); \
    memcpy(&(buf)[(start)], (repl_buf), repl_len); \
  } \
  while (0)

#define BUF_REPLACE_UPDATE(buf, start, end, len, repl_buf, repl_len, buf_size) \
  do { \
    BUF_REPLACE((buf), (start), (end), (len), (repl_buf), (repl_len), (buf_size)); \
    (len) += (repl_len) - ((end) - (start)); \
    (end) = (start) + (repl_len); \
  } \
  while (0)

static struct pnode *param_list = NULL;
struct arg_list_s {
  const char *str;
  struct arg_list_s *next;
} *arg_list = NULL, *arg_list_tail = NULL;

static char *
check_defines(char *symbol, int symlen, struct pnode **param_list_p)
{
  struct symbol *sym;
  struct pnode *p;
  char *subst = NULL;

  *param_list_p = NULL;

  /* If not quoted, check for #define substitution */
  if (NULL != (sym = get_symbol_len(state.stDefines, symbol, symlen))) {
    p = get_symbol_annotation(sym);
    if (p) {
      struct pnode *p2 = HEAD(p);

      assert(list == p->tag);
      assert(p2->tag == string);
      subst = p2->value.string;

      *param_list_p = TAIL(p);
      if (subst == NULL)
        subst = "";
      else if (strlen(subst) == symlen && strncmp(symbol, subst, symlen) == 0) {
        /* check for a bad subsitution */
        subst = NULL;
      }
    } else {
      subst = "";
    }
  }

  return subst;
}

static int
is_first_iden(int c)
{
  return !isascii(c) || c == '_' || c == '.' || c == '?' || c == '@' || c == '#' || isalpha(c);
}

static int
is_iden(int c)
{
  return is_first_iden(c) || isdigit(c);
}

static inline void
skip_spaces(const char *buf, int *i)
{
  while (isspace(buf[*i]))
    ++(*i);
}

static void
add_arg(const char *str)
{
  struct arg_list_s *new = malloc(sizeof(struct arg_list_s));

  new->str = str;
  new->next = NULL;

  if (arg_list_tail)
    arg_list_tail = arg_list_tail->next = new;
  else
    arg_list_tail = arg_list = new;
}

static void
fal(struct arg_list_s *p)
{
  if (p) {
    if (p->next) {
      fal(p->next);
      free(p);
    }
  }
}

static void
free_arg_list(void)
{
  fal(arg_list);
  arg_list_tail = arg_list = NULL;
}

static int
substitute_define_param(char *buf, int start, int *i, int *n, int max_size)
{
  int mlen = *i - start;
  struct arg_list_s *argp = arg_list;
  struct pnode *parp = param_list;

  assert(mlen > 0);

  /* find argument */
  while (parp) {
    assert(HEAD(parp)->tag == symbol);
    if (0 == strncmp(&buf[start], HEAD(parp)->value.symbol, mlen)) {
      /* substitute */
      int len = strlen(argp->str);

      DBG_printf("@@@substituting parameter %*.*s with %s\n", mlen, mlen, &buf[start], argp->str);

      if (*n + len - mlen >= max_size) {
        gpverror(GPE_INTERNAL, "Flex buffer too small.");
        return 0;
      }
      else {
        BUF_REPLACE_UPDATE(buf, start, *i, *n, argp->str, len, max_size);
        return 1;
      }
    }
    parp = TAIL(parp);
    argp = argp->next;
  }

  return 0; /* no substitutuon */
}

static int preprocess(char *buf, int *n, int max_size, int (*substitute)(char *buf, int start, int *i, int *n, int max_size), int level);

static int
substitute_define(char *buf, int start, int *i, int *n, int max_size)
{
  int mlen = *i - start;
  char *sub;

  if (mlen <= 0) {
    /* nothing to substitute */
    return 0;
  }

  if (NULL != (sub = check_defines(&buf[start], mlen, &param_list))) {
    int n_params = list_length(param_list);

    DBG_printf("define %*.*s has %d parameters\n", mlen, mlen, &buf[start], n_params);
    if (0 != n_params) {
      /* has parameters: collect arguments */
      int bracket;
      int n_args = 0;

      skip_spaces(buf, i);
      if (buf[*i] == '(') {
        ++(*i);
        bracket = 1;
      }

      for (; ; ) {
        int start1;
        int end1;
        int state = 0;
        int prev_esc = 0;

        skip_spaces(buf, i);
        start1 = *i;

        while (*i < *n && (0 != state || (buf[*i] != ',' && ((bracket && buf[*i] != ')') || (!bracket && buf[*i] != '\n'))))) {
          switch (buf[*i]) {
          case '\\':
            prev_esc = (0 != state) ? !prev_esc : 0;
            break;

          case '"':
          case '\'':
            if (!prev_esc)
              state = (0 == state) ? buf[*i] : ((state == buf[*i]) ? 0 : state);
          default:
            prev_esc = 0;
            break;
          }
          ++(*i);
        }

        /* right trim */
        end1 = *i - 1;
        while (end1 >= 0 && isspace(buf[end1]))
          --end1;
        ++end1;

        add_arg(strndup(&buf[start1], end1 - start1));
        ++n_args;

        if (*i < *n) {
          if ((bracket && ')' == buf[*i]) || (!bracket && '\n' == buf[*i])) {
            /* Don't eat newline! */
            if ('\n' != buf[*i])
              ++(*i);

            if (n_args == n_params) {
              char buf1[1024];
              int len = strlen(sub);

              /* substitute define parameters */
              memcpy(buf1, sub, len);
              preprocess(buf1, &len, sizeof(buf1), &substitute_define_param, 1);
              free_arg_list();

              /* substitute defines */
              preprocess(buf1, &len, sizeof(buf1), &substitute_define, 1);

              DBG_printf("@1@substituting define parameter %*.*s with %*.*s\n", mlen, mlen, &buf[start], len, len, buf1);

              mlen = *i - start;
              if (*n + len - mlen >= max_size) {
                gpverror(GPE_INTERNAL, "Flex buffer too small.");
                return 0;
              }
              else {
                BUF_REPLACE_UPDATE(buf, start, *i, *n, buf1, len, max_size);
                return 1;
              }
            }
            else {
              /* error n_args != n_params: no substitution */
              free_arg_list();
              return 0;
            }
          }
          else if (',' != buf[*i]) {
            /* error unknown delimiter: no substitution */
            free_arg_list();
            return 0;
          }
          else
            ++(*i);
        }
        if (*i >= *n) {
          /* error no ending bracket or newline: no substitution */
          free_arg_list();
          return 0;
        }
      } /* for each argument */
    } /* if has parameters */
    else {
      char buf1[1024];
      int oldlen = strlen(sub);
      int len = oldlen;

      /* substitute define */
      memcpy(buf1, sub, len);
      preprocess(buf1, &len, sizeof(buf1), &substitute_define, 1);

      DBG_printf("@2@substituting define parameter %*.*s with %*.*s\n", mlen, mlen, &buf[start], len, len, buf1);

      if (*n + len - mlen >= max_size) {
        gpverror(GPE_INTERNAL, "Flex buffer too small.");
        return 0;
      }
      else {
        BUF_REPLACE_UPDATE(buf, start, *i, *n, buf1, len, max_size);
        return 1;
      }
    }
  }
  return 0;
}

#define NELEM(x) (sizeof(x) / sizeof(*x))

static int
no_process_iden(const char *iden, int len)
{
  static const char * const iden_tbl[] = {
    "#define",
    "#ifdef",
    "#ifndef",
    "#undefine",
    "define",
    "ifdef",
    "ifndef",
  };
  int i;

  for (i = 0; i < NELEM(iden_tbl); ++i) {
    if (strlen(iden_tbl[i]) == len && 0 == strncasecmp(iden, iden_tbl[i], len))
      return 1;
  }
  return 0;
}

static int
preprocess(char *buf, int *n, int max_size, int (*substitute)(char *buf, int start, int *i, int *n, int max_size), int level)
{
  int start = -1;
  int state = 0;        /* '"': in double quotes; '\'': in single quotes; ';': in comment */
  int prev_esc = 0;     /* 1: prev char was escape */
  int in_hv = 0;        /* in #v */
  int number_start = 0; /* 1: possible start of a x'nnn' formatted number */
  int substituted = 0;  /* if there was a substitution in the preprocess run */
  int i;

  DBG_printf("---%*.*s\n", *n, *n, buf);

  for (i = 0; i < *n; ++i) {
    int c = buf[i];

    if (0 == state) {
      if ('#' == c)
        in_hv = '#';
      else if ('#' == in_hv && ('v' == c || 'V' == c))
        in_hv = 'v';
      else if ('v' == in_hv && '(' == c) {
        if (-1 != start) {
          if (start < i - 2) {
            /* preprocess the identifier before #v */
            int end = i - 2;

            DBG_printf("@1@Preprocessing identifier: %*.*s\n", end - start, end - start, &buf[start]);
            substituted |= (*substitute)(buf, start, &end, n, max_size);
            i = end + 2;
          }
          start = -1;
        }
        in_hv = '(';
      }
      else
        in_hv = 0;

      if (-1 == start && is_first_iden(c)) {
        switch (c) {
        case 'a': case 'A':
        case 'b': case 'B':
        case 'd': case 'D':
        case 'h': case 'H':
        case 'o': case 'O':
          number_start = 1;
          break;

        default:
          number_start = 0;
          break;
        }
        start = i;
      }
      else {
        if (-1 != start && !is_iden(c)) {
          if (0 == level && no_process_iden(&buf[start], i - start)) {
            start = -1;
            break;
          }

          if (c != '\'' || !number_start) {
            DBG_printf("@2@Preprocessing identifier: %*.*s\n", i - start, i - start, &buf[start]);
            substituted |= (*substitute)(buf, start, &i, n, max_size);
          }
          start = -1;
        }
        number_start = 0;
      }
    }

    switch (c) {
    case '\\':
      prev_esc =  ('"' == state || '\'' == state) ? !prev_esc : 0;
      break;

    case ';':
      if (0 == state)
        state = c;
      prev_esc = 0;
      break;

    case '"':
    case '\'':
      if (!prev_esc && state != ';')
        state = (0 == state) ? c : ((state == c) ? 0 : state);
    default:
      prev_esc = 0;
      break;
    }
  }

  if (-1 != start) {
    DBG_printf("@3@Preprocessing identifier: %*.*s\n", i - start, i - start, &buf[start]);
    substituted |= (*substitute)(buf, start, &i, n, max_size);
  }

  DBG_printf("+++%*.*s; substituted = %d\n", *n, *n, buf, substituted);

  return substituted;
}

static int
preprocess_defines(char *buf, int *n, int max_size)
{
  return preprocess(buf, n, max_size, substitute_define, 0);
}

void
preprocess_hv_params(char *buf, int *n, int max_size)
{
  int start = -1;
  int state = 0;        /* '"': in double quotes; '\'': in single quotes; ';': in comment; '(' in #v argument */
  int prev_esc = 0;     /* 1: prev char was escape */
  int in_hv = 0;        /* in #v */
  int hv_parenth = 0;   /* #v parenthesis nesting depth */
  int i;

  DBG_printf("---preprocess_hv_params: %*.*s\n", *n, *n, buf);

  for (i = 0; i < *n; ++i) {
    int c = buf[i];

    if ('(' == state) {
      if ('(' == in_hv) {
        start = i;
        in_hv = 0;
      }
      if ('(' == c)
        ++hv_parenth;
      else if (')' == c) {
        if (0 <= --hv_parenth) {
          char buf1[1024];
          int n1 = i - start;

          memcpy(buf1, &buf[start], n1);
          if (preprocess(buf1, &n1, sizeof (buf1), substitute_define, 0)) {
            BUF_REPLACE_UPDATE(buf, start, i, *n, buf1, n1, max_size);
          }
          start = -1;
          state = 0;
        }
      }
    }
    else if (0 == state) {
      if ('#' == c)
        in_hv = '#';
      else if ('#' == in_hv && ('v' == c || 'V' == c))
        in_hv = 'v';
      else if ('v' == in_hv && '(' == c) {
        in_hv = '(';
        ++hv_parenth;
        state = '(';
      }
      else
        in_hv = 0;
    }

    if (0 == state) {
      if (-1 == start && is_first_iden(c)) {
        start = i;
      }
    }

    switch (c) {
    case '\\':
      prev_esc =  ('"' == state || '\'' == state) ? !prev_esc : 0;
      break;

    case ';':
      if (0 == state)
        state = c;
      prev_esc = 0;
      break;

    case '"':
    case '\'':
      if (!prev_esc && state != ';')
        state = (0 == state) ? c : ((state == c) ? 0 : state);
    default:
      prev_esc = 0;
      break;
    }
  }

  DBG_printf("+++preprocess_hv_params: %*.*s\n", *n, *n, buf);
}

static int
preprocess_hv(char *buf, int *n, int max_size)
{
  char res_buf[11];
  char *p = buf;
  int substituted;
  int rest;

  rest = *n;

  for (; ; ) {
    int res_len;

    DBG_printf ("chunk = %*.*s\n", rest, rest, p);
    if (ppparse_chunk (p, rest)) {
      substituted = 1;
      DBG_printf ("col_begin = %d; col_end = %d; result = %d\n", col_begin, col_end, result);
      snprintf (res_buf, sizeof res_buf, "%d", result);
      res_len = strlen (res_buf);
      if (rest + (col_begin + res_len) - col_end >= max_size) {
        gpverror(GPE_INTERNAL, "Flex buffer too small.");
        --(*n);
        return 0;
      }
      else {
        BUF_REPLACE(p, col_begin, col_end, rest, res_buf, res_len, max_size);
        p += col_begin + res_len;
        *n += res_len - (col_end - col_begin);
        DBG_printf("buf = %*.*s\n", *n, *n, buf);
        rest -= col_end;
        max_size -= col_end;
      }
    }
    else
      break;
  }

  return substituted;
}

void
preprocess_line(char *buf, int *n, int max_size)
{
  int res;

  do {
    /* res = preprocess(buf, n, max_size, substitute_macro, 0); */
    res = preprocess_defines(buf, n, max_size);
    res |= preprocess_hv(buf, n, max_size);
  }
  while (res);
}

static char *
check_macro_params(char *symbol, int symlen)
{
  struct symbol *sym;
  struct pnode *p;
  char *subst = NULL;

  if (NULL != (sym = get_symbol_len(state.stMacroParams, symbol, symlen))) {
    p = get_symbol_annotation(sym);
    if (p) {
      struct pnode *p2 = HEAD(p);

      assert(list == p->tag);
      assert(p2->tag == string);
      subst = p2->value.string;

      assert(NULL == TAIL(p));
      if (subst == NULL)
        subst = "";
      else if (strlen(subst) == symlen && strncmp(symbol, subst, symlen) == 0) {
        /* check for a bad subsitution */
        subst = NULL;
      }
    } else {
      subst = "";
    }
  }

  return subst;
}

static int
substitute_macro_param(char *buf, int start, int *i, int *n, int max_size)
{
  int mlen = *i - start;
  char *sub;

  if (mlen <= 0) {
    /* nothing to substitute */
    return 0;
  }

  if (NULL != (sub = check_macro_params(&buf[start], mlen))) {
    char buf1[1024];
    int len = strlen(sub);

    /* substitute define */
    memcpy(buf1, sub, len);

    DBG_printf("@@@substituting macro parameter %*.*s with %*.*s\n", mlen, mlen, &buf[start], len, len, buf1);

    if (*n + len - mlen >= max_size) {
      gpverror(GPE_INTERNAL, "Flex buffer too small.");
      return 0;
    }
    else {
      BUF_REPLACE_UPDATE(buf, start, *i, *n, buf1, len, max_size);
      return 1;
    }
  }
  return 0;
}

void
preprocess_macro_params(char *buf, int *n, int max_size) {
  preprocess(buf, n, max_size, &substitute_macro_param, 1);
}
