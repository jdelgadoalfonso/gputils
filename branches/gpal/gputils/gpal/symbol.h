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

#ifndef __SYMBOL_H__
#define __SYMBOL_H__

struct variable *add_global(char *name, char *alias, tree *node);
struct variable *get_global(char *name);
struct variable *add_constant(char *name, int value, tree *node, char *type);
void add_equ(char *name, int value);
struct variable * add_global_symbol(char *name,
                                    char *prefix,
                                    tree *symbol,
                                    enum sym_tag tag,
                                    enum node_storage class,
                                    char *type);
void add_type_prim(char *name, int size, int bitsize);
void add_type_array(char *name, int start, int end, char *type);
void add_type_enum(char *name);
void add_type_alias(char *name, char *type);
struct type *get_type(char *name);
int type_size(struct type *type);
void add_type_prims(void);

#define SYM_TYPE(x) (x->type->tag)

#endif
