/* code generation for 14 bit pics
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

#include "libgputils.h"
#include "gpal.h"
#include "codegen.h"
#include "codegen14.h"

/* data movement */

void
gen_get_mem(char *name)
{
  write_asm_line("movf %s, w", name);
}

void
gen_put_mem(char *name)
{
  write_asm_line("movwf %s", name);
}

void
gen_put_reg(int reg)
{
  write_asm_line("movwf %#x", reg);
}

void
gen_immed(int value)
{
  write_asm_line("movlw %#x", value);
}

/* branches */

void
gen_call(char *name)
{
  write_asm_line("pagesel %s", name);
  write_asm_line("call %s", name);
}

void
gen_goto(char *name)
{
  write_asm_line("pagesel %s", name);
  write_asm_line("goto %s", name);
}

void
gen_return(void)
{
  write_asm_line("return");
}

void
gen_boolean(void)
{
  write_asm_line("btfss STATUS, Z");
  write_asm_line("movlw 1");
}

void
write_test(tree *test, char *end_label)
{
  gen_expr(test);
  write_asm_line("addlw 0             ; FIXME update CCR is not always needed");
  write_asm_line("btfsc STATUS, Z");
  write_asm_line("goto %s", end_label);
}

static void
gen_unop_expr(tree *expr)
{

  gen_expr(expr->value.unop.p0);
  switch (expr->value.unop.op) {
  case op_not:
    write_asm_line("xorlw 1"); 
    break;
  case op_add:
    break;
  case op_neg:
    write_asm_line("sublw 0"); 
    break;
  case op_com:
    write_asm_line("xorlw 0xff"); 
    break;
  default:
    assert(0);
  }

}

static void
gen_binop_constant(enum node_op op, int value)
{

  switch (op) {
  case op_add:
    write_asm_line("addlw %#x", value);
    break;
  case op_sub:
    write_asm_line("sublw %#x", value); 
    break;
  case op_mult:
  case op_div:
  case op_mod:
    gp_error("unsupported operator");
    break;
  case op_and:
    write_asm_line("andlw %#x", value); 
    break;
  case op_or:
    write_asm_line("iorlw %#x", value); 
    break;
  case op_xor:
    write_asm_line("xorlw %#x", value); 
    break;
  case op_lsh:
  case op_rsh:
    gp_error("unsupported operator");
    break;
  case op_eq:
    write_asm_line("xorlw %#x", value); 
    gen_boolean();
    write_asm_line("xorlw 1"); 
    break;
  case op_ne:
    write_asm_line("xorlw %#x", value); 
    gen_boolean();
    break;
  case op_lt:
    write_asm_line("sublw %#x", value);
    write_asm_line("movf STATUS, w");
    write_asm_line("andlw 1");
    write_asm_line("xorlw 1");
    break;
  case op_gt:
    write_asm_line("sublw %#x", value); 
    write_asm_line("movf STATUS, w");
    write_asm_line("andlw 1");
    break;
  case op_gte:
  case op_lte: 
    gp_error("unsupported operator");
    break;
  case op_land:
    write_asm_line("andlw %#x", value); 
    break;
  case op_lor:
    write_asm_line("iorlw %#x", value); 
    break;
  default:
    assert(0); /* Unhandled binary operator */
  }

}

static void
gen_binop_symbol(enum node_op op, char *name)
{

  switch (op) {
  case op_add:
    write_asm_line("addwf %s, w", name); 
    break;
  case op_sub:
    write_asm_line("subwf %s, w", name); 
    break;
  case op_mult:
  case op_div:
  case op_mod:
    gp_error("unsupported operator");
    break;
  case op_and:
    write_asm_line("andwf %s, w", name); 
    break;
  case op_or:
    write_asm_line("iorwf %s, w", name); 
    break;
  case op_xor:
    write_asm_line("xorwf %s, w", name); 
    break;
  case op_lsh:
  case op_rsh:
    gp_error("unsupported operator");
    break;
  case op_eq:
    write_asm_line("xorwf %s, w", name); 
    gen_boolean();
    write_asm_line("xorlw 1"); 
    break;
  case op_ne:
    write_asm_line("xorwf %s, w", name); 
    gen_boolean();
    break;
  case op_lt:
    write_asm_line("subwf %s, w", name); 
    write_asm_line("movf STATUS, w");
    write_asm_line("andlw 1");
    write_asm_line("xorlw 1");
    break;
  case op_gt:
    write_asm_line("subwf %s, w", name); 
    write_asm_line("movf STATUS, w");
    write_asm_line("andlw 1");
    break;
  case op_gte:
  case op_lte: 
    gp_error("unsupported operator");
    break;
  case op_land:
    write_asm_line("andwf %s, w", name); 
    break;
  case op_lor:
    write_asm_line("iorwf %s, w", name); 
    break;
  default:
    assert(0); /* Unhandled binary operator */
  }

}

static void
gen_binop_expr(tree *expr)
{
  tree *lhs = expr->value.binop.p0;
  tree *rhs = expr->value.binop.p1;

  /* calculate right hand side */
  gen_expr(rhs);

  if (lhs->tag == node_constant) {
    gen_binop_constant(expr->value.binop.op, lhs->value.constant);
  } else if (lhs->tag == node_symbol) { 
    struct variable *var;

    var = get_global(lhs->value.symbol);
    if (var->is_constant) {
      gen_binop_constant(expr->value.binop.op, var->value);
    } else {
      gen_binop_symbol(expr->value.binop.op, var->alias);
    }
  } else {
    char temp_name[BUFSIZ];
 
    /* it is a complex expression so save temp data */
    sprintf(temp_name, "_temp_%d", temp_number++);
    write_asm_line("movwf %s", temp_name); 
    gen_expr(lhs);
    gen_binop_symbol(expr->value.binop.op, temp_name);
  }

}

void
gen_expr(tree *expr)
{
  struct variable *var;

  switch(expr->tag) {
  case node_constant:
    gen_immed(expr->value.constant);    
    break;
  case node_symbol:
    var = get_global(expr->value.symbol);
    if (var->is_constant) {
      write_asm_line("movlw %i", var->value);
    } else {
      gen_get_mem(var->alias);
    }
    break;
  case node_unop:
    gen_unop_expr(expr);
    break;
  case node_binop:
    gen_binop_expr(expr);
    break;
  default:
    print_node(expr, 0);
    assert(0);
  }

}
