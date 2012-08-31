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

/* #define DEBUG */

#ifdef DEBUG
#include <stdarg.h>

int
DBG_printf(char *fmt, ...)
{
  va_list ap;
  int ret;

  va_start(ap, fmt);
  ret = vfprintf(stderr, fmt, ap);
  va_end(ap);

  return ret;
}
#else
#define DBG_printf  1 ? (void)0 : (void)printf
#endif

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
  if (NULL != (sym = get_symbol_len(state.stTopDefines, symbol, symlen))) {
    p = get_symbol_annotation(sym);
    if (p) {
      struct pnode *p2 = HEAD(p);

      assert(list == p->tag);
      assert(p2->tag == string);
      subst = p2->value.string;

      *param_list_p = TAIL(p);
      if (subst == NULL)
        subst = "";
      if (strlen(subst) == symlen && strncmp(symbol, subst, symlen) == 0) {
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
substitute_param(char *buf, int start, int *i, int *n, int max_size)
{
  int mlen = *i - start;
  struct arg_list_s *argp = arg_list;
  struct pnode *parp = param_list;

  /* find argument */
  while (parp) {
    assert(HEAD(parp)->tag == symbol);
    if (0 == strncmp(&buf[start], HEAD(parp)->value.symbol, mlen)) {
      /* substitute */
      int len = strlen(argp->str);

      DBG_printf("@@@substituting %*.*s with %s\n", mlen, mlen, &buf[start], argp->str);

      if (*n + len - mlen >= max_size) {
        gperror(103, "internal error: flex buffer too small");
        return 0;
      }
      else {
        memmove(&buf[start + len], &buf[*i], *n - *i);
        memcpy(&buf[start], argp->str, len);
        *i = start + len;
        *n = *n + len - mlen;
        return 1;
      }
    }
    parp = TAIL(parp);
    argp = argp->next;
  }

  return 0; /* no substitutuon */
}

static int preprocess(char *buf, int n, int max_size, int (*substitute)(char *buf, int start, int *i, int *n, int max_size), int level);

static int
substitute_macro(char *buf, int start, int *i, int *n, int max_size)
{
  int mlen = *i - start;
  char *sub;

  if (mlen <= 0) {
    /* nothing to substitute */
    return 0;
  }

  if (NULL != (sub = check_defines(&buf[start], mlen, &param_list))) {
    int n_params = list_length(param_list);

    if (0 != n_params) {
      /* has arguments */
      skip_spaces(buf, i);
      if (buf[(*i)++] == '(') {
        int n_args = 0;

        for (; ; ) {
          int start1;
          int end1;
          int state = 0;
          int prev_esc = 0;

          skip_spaces(buf, i);
          start1 = *i;

          while (*i < *n && (0 != state || (buf[*i] != ',' && buf[*i] != ')'))) {
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
            switch (buf[(*i)++]) {
            case ')':
              if (n_args == n_params) {
                char buf1[1024];
                int n1 = strlen(sub);
                int len;

                memcpy(buf1, sub, n1);
                len = preprocess(buf1, n1, sizeof(buf1), substitute_param, 1);
                free_arg_list();

                DBG_printf("@@@substituting %*.*s with %*.*s\n", mlen, mlen, &buf[start], len, len, buf1);

                mlen = *i - start;
                if (*n + len - mlen >= max_size) {
                  gperror(103, "internal error: flex buffer too small");
                  return 0;
                }
                else {
                  memmove(&buf[start + len], &buf[*i], *n - *i);
                  memcpy(&buf[start], buf1, len);
                  *i = start + len;
                  *n = *n + len - mlen;
                  return 1;
                }
              }
              else {
                /* error n_args != n_params: no substitution */
                free_arg_list();
                return 0;
              }
              break;

            case ',':
              break;

            default:
              /* error unknown delimiter: no substitution */
              free_arg_list();
              return 0;
            }
          }
          else {
            /* error no ending bracket: no substitution */
            free_arg_list();
            return 0;
          }
        }
      }
      else {
        /* error no params: no substitution */
        return 0;
      }
    }
    else {
      int len = strlen(sub);

      DBG_printf("@@@substituting %*.*s with %s\n", mlen, mlen, &buf[start], sub);

      if (*n + len - mlen >= max_size) {
        gperror(103, "internal error: flex buffer too small");
        return 0;
      }
      else {
        memmove(&buf[start + len], &buf[*i], *n - *i);
        memcpy(&buf[start], sub, len);
        *i = start + len;
        *n = *n + len - mlen;
        return 1;
      }
    }
  }
  return 0;
}

#define NELEM(x) (sizeof(x) / sizeof(*x))

enum no_process_type {
  np_none = 0,
  np_eol,
  np_next_iden
};

static enum no_process_type
no_process_iden(const char *iden, int len)
{
  static struct iden_tbl_s {
    const char *iden;
    enum no_process_type type;
  } iden_tbl[] = {
    { "#define", np_next_iden },
    { "#ifdef", np_eol },
    { "#ifndef", np_eol },
    { "#undefine", np_eol },
    { "define", np_eol },
    { "ifdef", np_next_iden },
    { "ifndef", np_eol },
  };
  int i;

  for (i = 0; i < NELEM(iden_tbl); ++i) {
    if (strlen(iden_tbl[i].iden) == len && 0 == strncasecmp(iden, iden_tbl[i].iden, len))
      return iden_tbl[i].type;
  }
  return 0;
}

static int
preprocess(char *buf, int n, int max_size, int (*substitute)(char *buf, int start, int *i, int *n, int max_size), int level)
{
  int start = -1;
  int state = 0;    /* '"': in double quotes; '\'': in single quotes; ';': in comment */
  int prev_esc = 0; /* 1: prev char was escape */
  int number_start = 0; /* 1: possible start of a x'nnn' formatted number */
  int preproc_iden = 1; /* don't preprocess (next) identifier */
  int i;

  DBG_printf("---%*.*s\n", n, n, buf);

  for (i = 0; i < n; ++i) {
    int c = buf[i];

    if (0 == state) {
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
          enum no_process_type npi = no_process_iden(&buf[start], i - start);

          if (0 == level && np_eol == npi) {
            start = -1;
            break;
          }

          if (0 == level && np_next_iden == npi)
            preproc_iden = 0;
          else {
            if (preproc_iden && (c != '\'' || !number_start)) {
              DBG_printf("@@@Preprocessing identifier: %*.*s\n", i - start, i - start, &buf[start]);
              (*substitute)(buf, start, &i, &n, max_size);
            }
            else
              preproc_iden = 1;
            start = -1;
          }
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
    DBG_printf("@@@Preprocessing identifier: %*.*s\n", i - start, i - start, &buf[start]);
   (*substitute)(buf, start, &i, &n, max_size);
  }

  DBG_printf("+++%*.*s\n", n, n, buf);

  return n;
}

int
preprocess_line(char *buf, int n, int max_size)
{
  return preprocess(buf, n, max_size, substitute_macro, 0);
}
