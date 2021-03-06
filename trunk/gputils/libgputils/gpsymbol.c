
/* GP Symbol table support.

   Copyright (C) 2014-2016 Molnar Karoly

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

/*------------------------------------------------------------------------------------------------*/

static int
_hash_sort_cmp(const void *P0, const void *P1)
{
  const gp_hash_type *h0 = (const gp_hash_type *)P0;
  const gp_hash_type *h1 = (const gp_hash_type *)P1;
  const char         *s0;
  const char         *s1;

  if (h0->hash.high.u64 < h1->hash.high.u64) {
    return -1;
  }
  else if (h0->hash.high.u64 > h1->hash.high.u64) {
    return 1;
  }
  else {
    if (h0->hash.low.u64 < h1->hash.low.u64) {
      return -1;
    }
    else if (h0->hash.low.u64 > h1->hash.low.u64) {
      return 1;
    }
    else {
      s0 = (h0->symbol != NULL) ? h0->symbol->name : NULL;
      s1 = (h1->symbol != NULL) ? h1->symbol->name : NULL;

      if ((s0 == NULL) && (s1 == NULL)) {
        return 0;
      }
      else if ((s0 != NULL) && (s1 != NULL)) {
        return strcmp(s0, s1);
      }
      else if (s0 != NULL) {
        return 1;
      }
      else {
        return -1;
      }
    }
  }
}

/*------------------------------------------------------------------------------------------------*/

static int
_hash_find_cmp(const void *P0, const void *P1)
{
  const gp_hash_type *h0 = (const gp_hash_type *)P0;
  const gp_hash_type *h1 = (const gp_hash_type *)P1;

  if (h0->hash.high.u64 < h1->hash.high.u64) {
    return -1;
  }
  else if (h0->hash.high.u64 > h1->hash.high.u64) {
    return 1;
  }
  else {
    if (h0->hash.low.u64 < h1->hash.low.u64) {
      return -1;
    }
    else if (h0->hash.low.u64 > h1->hash.low.u64) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

/*------------------------------------------------------------------------------------------------*/

gp_hash_type *
gp_symbol_make_hash_table(gp_object_type *Object)
{
  gp_symbol_type *current;
  gp_hash_type   *table;
  gp_hash_type   *tp;
  unsigned int    num_symbols;
  hash128_t      *h;

  if (Object == NULL) {
    return NULL;
  }

  current = Object->symbols;
  num_symbols = 0;
  while (current != NULL) {
    if ((current->class != C_FILE)    && (current->class != C_EOF) &&
        (current->class != C_SECTION) && (current->section_name != NULL)) {
      ++num_symbols;
    }
    current = current->next;
  }

  table = (gp_hash_type *)GP_Calloc(num_symbols, sizeof(gp_hash_type));

  Object->symbol_hashtable      = table;
  Object->symbol_hashtable_size = num_symbols;

  tp      = table;
  current = Object->symbols;
  while (current != NULL) {
    if ((current->class != C_FILE)    && (current->class != C_EOF) &&
        (current->class != C_SECTION) && (current->section_name != NULL)) {
      h = &tp->hash;
      gp_hash_init(h);
      gp_hash_str(h, current->section_name, false);
      gp_hash_mem(h, &current->value, sizeof(current->value));
      tp->symbol = current;
      ++tp;
    }
    current = current->next;
  }

  qsort(table, num_symbols, sizeof(gp_hash_type), _hash_sort_cmp);
  return table;
}

/*------------------------------------------------------------------------------------------------*/

const gp_symbol_type *
gp_symbol_find_hash_table(const gp_object_type *Object, const char *Section_name, gp_symvalue_t Symbol_value)
{
  gp_hash_type  gp_hash;
  gp_hash_type *ret;

  if ((Object == NULL) || (Section_name == NULL)) {
    return NULL;
  }

  if ((Object->symbol_hashtable == NULL) || (Object->symbol_hashtable_size == 0)) {
    return NULL;
  }

  gp_hash_init(&gp_hash.hash);
  gp_hash_str(&gp_hash.hash, Section_name, false);
  gp_hash_mem(&gp_hash.hash, &Symbol_value, sizeof(Symbol_value));

  ret = (gp_hash_type *)bsearch(&gp_hash, Object->symbol_hashtable, Object->symbol_hashtable_size,
                                sizeof(gp_hash_type), _hash_find_cmp);

  return ((ret != NULL) ? ret->symbol : NULL);
}
