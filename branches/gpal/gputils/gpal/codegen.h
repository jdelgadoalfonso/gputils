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

struct variable {
  char *alias;
  tree *node;
  gp_boolean is_constant;		/* true if constant symbol */
  gp_boolean is_public;			/* true if public symbol */
  gp_boolean is_external;		/* true if defined elsewere */
  gp_boolean is_equ;			/* true if processor header equate */
  int value;				/* value if constant symbol */
};

void add_global(char *name, char *alias, tree *object);
struct variable *get_global(char *name);
void write_asm_line(const char *format, ...);
void write_label(char *label);
extern int temp_number;
void write_asm(void);

#endif
