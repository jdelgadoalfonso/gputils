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

#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#define LOCAL_DATA_LABEL "_local_data"

void codegen_write_asm(const char *format, ...);
char *codegen_next_label(void);
void codegen_write_label(char *label);
void codegen_jump(char *label);

void codegen_call(char *label, enum node_storage storage);
void codegen_banksel(char *label);
void codegen_test(tree *node, char *label);
void codegen_expr(tree *statement);
void codegen_assembly(tree *assembly);
void codegen_put_mem(struct variable *var, gp_boolean add_banksel);
void codegen_init_proc(char *name, 
                       enum node_storage storage,
                       gp_boolean is_func);
void codegen_finish_proc(void);
void codegen_init_data(void);
void codegen_write_data(char *label, enum node_storage storage);
void codegen_finish_data(void);
char *codegen_get_temp(void);
void codegen_init_asm(void);
void codegen_close_asm(void);

#endif
