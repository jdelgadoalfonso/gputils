/* symbol table
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

#ifdef STDC_HEADERS
#include <stdarg.h>
#endif

#include "libgputils.h"
#include "gpal.h"
#include "symbol.h"
#include "analyze.h"

struct variable *
add_global(char *name, char *alias, tree *node)
{
  struct symbol *sym;
  struct variable *var;

  sym = get_symbol(state.top, name);
  if (sym == NULL) {
    sym = add_symbol(state.top, name);
    var = malloc(sizeof(*var));
    annotate_symbol(sym, var);
    var->alias = gp_lower_case(alias);
    var->tag = sym_unknown;
    var->class = storage_unknown;
    var->type = NULL;
    var->is_init = false;
    var->value = 0;
    var->file_id = node->file_id;
    var->line_number = node->line_number;
    var->node = node;
  } else {
    var = get_symbol_annotation(sym);
    analyze_error(node,
                  "redefinition of \"%s\",\n\talso defined in %s:%i:",
                  name,
                  get_compile(var->file_id),
                  var->line_number);
  }
  
  return var;
}

struct variable *
get_global(char *name)
{
  struct symbol *sym;
  struct variable *var = NULL;

  sym = get_symbol(state.top, name);
  if (sym != NULL) {
    var = get_symbol_annotation(sym);
  }

  return var;
}

struct variable *
add_constant(char *name, int value, tree *node, char *type)
{
  struct variable *var;

  var = add_global(name, name, node);
  if (var) {
    if (type) {
      var->type = get_type(type);   
      if (var->type == NULL) {
        analyze_error(node, "unknown symbol type \"%s\"", type);
      }
    }
    var->tag = sym_const;
    var->value = value;
  }

  return var;
}

void
add_equ(char *name, int value)
{
  struct symbol *sym;
  struct variable *var;
  struct symbol *prim;
  struct type *prim_type = NULL;

  prim = get_symbol(state.type, "uint8");
  if (prim == NULL) {
    assert(0);
  } else {
    prim_type = get_symbol_annotation(prim);
    assert(prim_type != NULL);
  }

  sym = get_symbol(state.top, name);
  if (sym == NULL) {
    sym = add_symbol(state.global, name);
    var = malloc(sizeof(*var));
    annotate_symbol(sym, var);
    var->alias = strdup(name);
    var->tag = sym_equ;
    var->class = storage_unknown;
    var->type = prim_type;
    var->is_init = true;
    var->value = value;
    var->file_id = state.src->file_id;
    var->line_number = state.src->line_number;
    var->node = NULL;
  } else {
    gp_num_errors++;
    if (gp_quiet == 0) {
      printf("%s:%d:error duplicate symbol \"%s\"\n",
             state.src->name,
             state.src->line_number,
             name);
    }
  }

  return;
}

/* add one symbol to the global table */

struct variable *
add_global_symbol(char *name,
                  char *prefix,
                  tree *symbol,
                  enum sym_tag tag,
                  enum node_storage class,
                  char *type)
{
  char buffer[BUFSIZ];
  struct variable *var;

  if (prefix)
    sprintf(buffer, "_%s_%s", prefix, name);
  else
    sprintf(buffer, "%s", name);

  var = add_global(name, buffer, symbol);
  if (var) {
    if (type) {
      var->type = get_type(type);   
      if (var->type == NULL) {
        analyze_error(symbol, "unknown symbol type \"%s\"", type);
      }
    }
    var->tag = tag;
    var->class = class;
  }

  return var;
}

static void
add_type_prim(char *name, enum size_tag size)
{
  struct symbol *sym;
  struct type *new;

  sym = get_symbol(state.type, name);
  if (sym == NULL) {
    sym = add_symbol(state.type, name);
    new = malloc(sizeof(*new));
    annotate_symbol(sym, new);
    new->tag = type_prim;
    new->size = size;
    new->nelts = 0;
    new->start = 0;
    new->end = 0;
    new->prim = NULL;
  } else {
    analyze_error(NULL, "redefinition of type \"%s\"", name);
  }
  
  return;
}

void
add_type_array(char *name, int start, int end, char *type)
{
  struct symbol *sym;
  struct type *new;
  struct symbol *prim;
  struct type *prim_type = NULL;

  prim = get_symbol(state.type, type);
  if (prim == NULL) {
    analyze_error(NULL, "unknown type \"%s\"", type);
    return;
  } else {
    prim_type = get_symbol_annotation(prim);
    assert(prim_type != NULL);
    if (prim_type->tag != type_prim) {
      analyze_error(NULL, "arrays can't be of derived type \"%s\"", type);
      return;
    }
  }

  sym = get_symbol(state.type, name);
  if (sym == NULL) {
    sym = add_symbol(state.type, name);
    new = malloc(sizeof(*new));
    annotate_symbol(sym, new);
    new->tag = type_array;
    new->size = size_unknown;
    new->nelts = end - start + 1;
    new->start = start;
    new->end = end;
    new->prim = prim_type;
  } else {
    analyze_error(NULL, "redefinition of type \"%s\"", name);
  }
  
  return;
}

void
add_type_enum(char *name)
{
  struct symbol *sym;
  struct type *new;
  struct symbol *prim;
  struct type *prim_type = NULL;

  prim = get_symbol(state.type, "uint8");
  if (prim == NULL) {
    assert(0);
  } else {
    prim_type = get_symbol_annotation(prim);
    assert(prim_type != NULL);
  }

  sym = get_symbol(state.type, name);
  if (sym == NULL) {
    sym = add_symbol(state.type, name);
    new = malloc(sizeof(*new));
    annotate_symbol(sym, new);
    new->tag = type_enum;
    new->size = size_unknown;
    new->nelts = 0;
    new->start = 0;
    new->end = 0;
    new->prim = prim_type;
  } else {
    analyze_error(NULL, "redefinition of type \"%s\"", name);
  }
  
  return ;
}

void
add_type_alias(char *name, char *type)
{
  struct symbol *sym;
  struct type *new;
  struct symbol *prim;
  struct type *prim_type;

  prim = get_symbol(state.type, type);
  if (prim == NULL) {
    analyze_error(NULL, "unknown type \"%s\"", type);
    return;
  } else {
    prim_type = get_symbol_annotation(prim);
    assert(prim_type != NULL);
  }

  sym = get_symbol(state.type, name);
  if (sym == NULL) {
    sym = add_symbol(state.type, name);
    new = malloc(sizeof(*new));
    annotate_symbol(sym, new);
    new->tag = type_alias;
    new->size = size_unknown;
    new->nelts = 0;
    new->start = 0;
    new->end = 0;
    new->prim = prim_type;
  } else {
    analyze_error(NULL, "redefinition of type \"%s\"", name);
  }
  
  return;
}

struct type *
get_type(char *name)
{
  struct symbol *sym;
  struct type *type = NULL;

  sym = get_symbol(state.type, name);
  if (sym != NULL) {
    type = get_symbol_annotation(sym);
  }

  return type;
}

/* determine the size of a primative in bytes */

int
prim_size(enum size_tag size)
{
  int byte_size = 0;

  switch (size) {
  case size_bit:
    byte_size = 1;
    break;
  case size_uint8:
    byte_size = 1;
    break;
  case size_int8:
    byte_size = 1;
    break;
  case size_uint16:
    byte_size = 2;
    break;
  case size_int16:
    byte_size = 2;
    break;
  case size_uint24:
    byte_size = 3;
    break;
  case size_int24:
    byte_size = 3;
    break;
  case size_uint32:
    byte_size = 4;
    break;
  case size_int32:
    byte_size = 4;
    break;
  case size_float:
    byte_size = 4;
    break;
  default:
    assert(0);
  }

  return byte_size;
}

/* determine the primative size */

enum size_tag
prim_type(struct type *type)
{
  enum size_tag size = size_unknown;

  switch (type->tag) {
  case type_prim:
    size = type->size;
    break;
  case type_array:
  case type_enum:
  case type_alias:
    size = type->prim->size;
    break;
  default:
    assert(0);
  }

  return size;
}

/* determine the size of a type in bytes */

int
type_size(struct type *type)
{
  int size = 0;

  switch (type->tag) {
  case type_prim:
    size = prim_size(type->size);
    break;
  case type_array:
    size = type->nelts * prim_size(type->size);
    break;
  case type_enum:
    size = type_size(type->prim);
    break;
  case type_alias:
    size = type_size(type->prim);
    break;
  default:
    assert(0);
  }

  return size;
}

void
add_type_prims(void)
{
  add_type_prim("bit",    size_bit);
  add_type_prim("uint8",  size_uint8);
  add_type_prim("int8",   size_int8);
  add_type_prim("uint16", size_uint16);
  add_type_prim("int16",  size_int16);
  add_type_prim("uint24", size_uint24);
  add_type_prim("int24",  size_int24);
  add_type_prim("uint32", size_uint32);
  add_type_prim("int32",  size_int32);
  add_type_prim("float",  size_float);

  return;
}
