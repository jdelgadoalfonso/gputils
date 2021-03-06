/* code generation
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

#ifndef __CODEGEN14_H__
#define __CODEGEN14_H__

void gen_get_mem(char *name);
void gen_get_mem_offset(char *name, int offset);

void gen_put_mem(char *name);
void gen_put_mem_offset(char *name, int offset);
void gen_put_reg(int reg);

void gen_binop_constant(enum node_op op, int value);

void write_test(tree *test, char *end_label);
void gen_expr(tree *expr);

#endif
