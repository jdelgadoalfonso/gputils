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
#include "analyze.h"
#include "codegen.h"
#include "codegen14.h"

/* data movement */

void
gen_get_mem(char *name)
{
  codegen_write_asm("movf %s, w", name);
}

void
gen_put_mem(char *name)
{
  codegen_write_asm("movwf %s", name);
}

void
gen_put_reg(int reg)
{
  codegen_write_asm("movwf %#x", reg);
}

void
gen_immed(int value)
{
  codegen_write_asm("movlw %#x", value);
}

/* branches */

void
gen_call(char *name)
{
  codegen_write_asm("pagesel %s", name);
  codegen_write_asm("call %s", name);
}

void
gen_goto(char *name)
{
  codegen_write_asm("pagesel %s", name);
  codegen_write_asm("goto %s", name);
}

void
gen_return(void)
{
  codegen_write_asm("return");
}

void
gen_boolean(void)
{
  codegen_write_asm("btfss STATUS, Z");
  codegen_write_asm("movlw 1");
}

void
write_test(tree *test, char *end_label)
{
  gen_expr(test);
  codegen_write_asm("addlw 0             ; FIXME update CCR is not always needed");
  codegen_write_asm("btfsc STATUS, Z");
  codegen_write_asm("goto %s", end_label);
}

static void
gen_unop_expr(tree *expr)
{

  gen_expr(expr->value.unop.p0);
  switch (expr->value.unop.op) {
  case op_not:
    codegen_write_asm("xorlw 1"); 
    break;
  case op_add:
    break;
  case op_neg:
    codegen_write_asm("sublw 0"); 
    break;
  case op_com:
    codegen_write_asm("xorlw 0xff"); 
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
    codegen_write_asm("addlw %#x", value);
    break;
  case op_sub:
    codegen_write_asm("sublw %#x", value); 
    break;
  case op_mult:
  case op_div:
  case op_mod:
    gp_error("unsupported operator");
    break;
  case op_and:
    codegen_write_asm("andlw %#x", value); 
    break;
  case op_or:
    codegen_write_asm("iorlw %#x", value); 
    break;
  case op_xor:
    codegen_write_asm("xorlw %#x", value); 
    break;
  case op_lsh:
  case op_rsh:
    gp_error("unsupported operator");
    break;
  case op_eq:
    codegen_write_asm("xorlw %#x", value); 
    gen_boolean();
    codegen_write_asm("xorlw 1"); 
    break;
  case op_ne:
    codegen_write_asm("xorlw %#x", value); 
    gen_boolean();
    break;
  case op_lt:
    codegen_write_asm("sublw %#x", value);
    codegen_write_asm("movf STATUS, w");
    codegen_write_asm("andlw 1");
    codegen_write_asm("xorlw 1");
    break;
  case op_gt:
    codegen_write_asm("sublw %#x", value); 
    codegen_write_asm("movf STATUS, w");
    codegen_write_asm("andlw 1");
    break;
  case op_gte:
  case op_lte: 
    gp_error("unsupported operator");
    break;
  case op_land:
    codegen_write_asm("andlw %#x", value); 
    break;
  case op_lor:
    codegen_write_asm("iorlw %#x", value); 
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
    codegen_write_asm("addwf %s, w", name); 
    break;
  case op_sub:
    codegen_write_asm("subwf %s, w", name); 
    break;
  case op_mult:
  case op_div:
  case op_mod:
    gp_error("unsupported operator");
    break;
  case op_and:
    codegen_write_asm("andwf %s, w", name); 
    break;
  case op_or:
    codegen_write_asm("iorwf %s, w", name); 
    break;
  case op_xor:
    codegen_write_asm("xorwf %s, w", name); 
    break;
  case op_lsh:
  case op_rsh:
    gp_error("unsupported operator");
    break;
  case op_eq:
    codegen_write_asm("xorwf %s, w", name); 
    gen_boolean();
    codegen_write_asm("xorlw 1"); 
    break;
  case op_ne:
    codegen_write_asm("xorwf %s, w", name); 
    gen_boolean();
    break;
  case op_lt:
    codegen_write_asm("subwf %s, w", name); 
    codegen_write_asm("movf STATUS, w");
    codegen_write_asm("andlw 1");
    codegen_write_asm("xorlw 1");
    break;
  case op_gt:
    codegen_write_asm("subwf %s, w", name); 
    codegen_write_asm("movf STATUS, w");
    codegen_write_asm("andlw 1");
    break;
  case op_gte:
  case op_lte: 
    gp_error("unsupported operator");
    break;
  case op_land:
    codegen_write_asm("andwf %s, w", name); 
    break;
  case op_lor:
    codegen_write_asm("iorwf %s, w", name); 
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
    sprintf(temp_name, "%s_temp_%d", state.basefilename, temp_number++);
    codegen_write_asm("movwf %s", temp_name); 
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
      codegen_write_asm("movlw %i", var->value);
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
