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
    var->class = storage_unknown;
    var->size = 0;
    var->bitsize = 0;
    var->nelts = 0;
    var->is_init = false;
    var->is_equ = false;
    var->is_constant = false;
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
add_constant(char *name, int value, tree *node)
{
  struct variable *var;

  var = add_global(name, name, node);
  var->is_constant = true;
  var->value = value;

  return var;
}

void
add_equ(char *name, int value)
{
  struct symbol *sym;
  struct variable *var;

  sym = get_symbol(state.top, name);
  if (sym == NULL) {
    sym = add_symbol(state.global, name);
    var = malloc(sizeof(*var));
    annotate_symbol(sym, var);
    var->alias = strdup(name);
    var->class = storage_unknown;
    var->size = 0;
    var->bitsize = 0;
    var->nelts = 0;
    var->is_init = true;
    var->is_equ = true;
    var->is_constant = true;
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
                  enum node_storage class)
{
  char buffer[BUFSIZ];
  struct variable *var;

  if (prefix)
    sprintf(buffer, "%s_%s", prefix, name);
  else
    sprintf(buffer, "%s", name);

  var = add_global(name, buffer, symbol);
  if (var)
    var->class = class;

  return var;
}
