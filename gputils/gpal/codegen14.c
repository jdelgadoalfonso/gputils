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
#include "symbol.h"
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
  char *reg1 = NULL;
  char *reg2 = NULL;
  char *label1 = NULL;
  char *label2 = NULL;

  switch (op) {
  case op_add:
    codegen_write_asm("addlw %#x", value);
    break;
  case op_sub:
    codegen_write_asm("sublw %#x", value); 
    break;
  case op_mult:
    reg1 = codegen_get_temp();
    label1 = codegen_next_label();
    codegen_write_asm("movwf %s", reg1); 
    codegen_write_asm("movlw 0");
    codegen_write_label(label1);
    codegen_write_asm("addlw %#x", value);
    codegen_write_asm("decfsz %s, f", reg1);
    codegen_write_asm("goto %s", label1);
    break;
  case op_div:
    reg1 = codegen_get_temp();
    reg2 = codegen_get_temp();
    label1 = codegen_next_label();
    label2 = codegen_next_label();
    codegen_write_asm("movwf %s", reg1);    /* store the divisor in temp*/
    codegen_write_asm("movlw %#x", value);
    codegen_write_asm("movwf %s", reg2);    /* store the dividend */
    codegen_write_asm("movf %s, w", reg1);  /* move the divisor into w */
    codegen_write_asm("clrf %s", reg1);     /* clear the result */
    codegen_write_label(label1);
    codegen_write_asm("subwf %s, f", reg2); /* sub the divisor from the dividend */
    codegen_write_asm("btfsc STATUS, C");
    codegen_write_asm("goto %s", label2);
    codegen_write_asm("incf %s, f", reg1);  /* increment the result */
    codegen_write_asm("goto %s", label1);
    codegen_write_label(label2);
    codegen_write_asm("movf %s, w", reg1);  /* move the result into w */
    break;
  case op_mod:
    reg1 = codegen_get_temp();
    reg2 = codegen_get_temp();
    label1 = codegen_next_label();
    codegen_write_asm("movwf %s", reg1);    /* store the divisor in temp*/
    codegen_write_asm("movlw %#x", value);
    codegen_write_asm("movwf %s", reg2);    /* store the dividend */
    codegen_write_asm("movf %s, w", reg1);  /* move the divisor into w */
    codegen_write_label(label1);
    codegen_write_asm("subwf %s, f", reg2); /* sub the divisor from the dividend */
    codegen_write_asm("btfss STATUS, C");
    codegen_write_asm("goto %s", label1);
    codegen_write_asm("addwf %s, w", reg2); /* move the modulus into w */
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
    reg1 = codegen_get_temp();
    reg2 = codegen_get_temp();
    label1 = codegen_next_label();
    label2 = codegen_next_label();
    codegen_write_asm("movwf %s", reg2);    /* store the number of shifts in temp*/
    codegen_write_asm("movlw %#x", value);
    codegen_write_asm("movwf %s", reg1);    /* store the number to be shifted */
    codegen_write_asm("movf %s", reg2);     /* test number of shifts */
    codegen_write_asm("btfsc STATUS, Z");
    codegen_write_asm("goto %s", label2);
    codegen_write_label(label1);
    codegen_write_asm("bcf STATUS, C");
    codegen_write_asm("rlf %s, f", reg1); 
    codegen_write_asm("decfsz %s", reg2);
    codegen_write_asm("goto %s", label1);
    codegen_write_label(label2);
    codegen_write_asm("movf %s, w", reg1);  /* move the result into w */
    break;
  case op_rsh:
    reg1 = codegen_get_temp();
    reg2 = codegen_get_temp();
    label1 = codegen_next_label();
    label2 = codegen_next_label();
    codegen_write_asm("movwf %s", reg2);    /* store the number of shifts in temp*/
    codegen_write_asm("movlw %#x", value);
    codegen_write_asm("movwf %s", reg1);    /* store the number to be shifted */
    codegen_write_asm("movf %s", reg2);     /* test number of shifts */
    codegen_write_asm("btfsc STATUS, Z");
    codegen_write_asm("goto %s", label2);
    codegen_write_label(label1);
    codegen_write_asm("bcf STATUS, C");
    codegen_write_asm("rrf %s, f", reg1); 
    codegen_write_asm("decfsz %s", reg2);
    codegen_write_asm("goto %s", label1);
    codegen_write_label(label2);
    codegen_write_asm("movf %s, w", reg1);  /* move the result into w */
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
    reg1 = codegen_get_temp();
    codegen_write_asm("movwf %s", reg1);
    codegen_write_asm("movlw %#x", value);
    codegen_write_asm("subwf %s, w", reg1);
    codegen_write_asm("movf STATUS, w");
    codegen_write_asm("andlw 1");
    codegen_write_asm("xorlw 1");
    break;
  case op_lte: 
    reg1 = codegen_get_temp();
    codegen_write_asm("movwf %s", reg1);
    codegen_write_asm("movlw %#x", value);
    codegen_write_asm("subwf %s, w", reg1);
    codegen_write_asm("movf STATUS, w");
    codegen_write_asm("andlw 1");
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

  if (reg1)
    free(reg1);

  if (reg2)
    free(reg2);

  if (label1)
    free(label1);

  if (label2)
    free(label2);

  return;
}

static void
gen_binop_symbol(enum node_op op, char *name)
{
  char *reg1 = NULL;
  char *reg2 = NULL;
  char *label1 = NULL;
  char *label2 = NULL;

  switch (op) {
  case op_add:
    codegen_write_asm("addwf %s, w", name); 
    break;
  case op_sub:
    codegen_write_asm("subwf %s, w", name); 
    break;
  case op_mult:
    reg1 = codegen_get_temp();
    label1 = codegen_next_label();
    codegen_write_asm("movwf %s", reg1); 
    codegen_write_asm("movlw 0");
    codegen_write_label(label1);
    codegen_write_asm("addwf %s, w", name);
    codegen_write_asm("decfsz %s, f", reg1);
    codegen_write_asm("goto %s", label1);
    break;
  case op_div:
    reg1 = codegen_get_temp();
    reg2 = codegen_get_temp();
    label1 = codegen_next_label();
    label2 = codegen_next_label();
    codegen_write_asm("movwf %s", reg1);    /* store the divisor in temp*/
    codegen_write_asm("movf %s, w", name);
    codegen_write_asm("movwf %s", reg2);    /* store the dividend */
    codegen_write_asm("movf %s, w", reg1);  /* move the divisor into w */
    codegen_write_asm("clrf %s", reg1);     /* clear the result */
    codegen_write_label(label1);
    codegen_write_asm("subwf %s, f", reg2); /* sub the divisor from the dividend */
    codegen_write_asm("btfsc STATUS, C");
    codegen_write_asm("goto %s", label2);
    codegen_write_asm("incf %s, f", reg1);  /* increment the result */
    codegen_write_asm("goto %s", label1);
    codegen_write_label(label2);
    codegen_write_asm("movf %s, w", reg1);  /* move the result into w */
    break;
  case op_mod:
    reg1 = codegen_get_temp();
    reg2 = codegen_get_temp();
    label1 = codegen_next_label();
    codegen_write_asm("movwf %s", reg1);    /* store the divisor in temp*/
    codegen_write_asm("movf %s, w", name);
    codegen_write_asm("movwf %s", reg2);    /* store the dividend */
    codegen_write_asm("movf %s, w", reg1);  /* move the divisor into w */
    codegen_write_label(label1);
    codegen_write_asm("subwf %s, f", reg2); /* sub the divisor from the dividend */
    codegen_write_asm("btfss STATUS, C");
    codegen_write_asm("goto %s", label1);
    codegen_write_asm("addwf %s, w", reg2); /* move the modulus into w */
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
    reg1 = codegen_get_temp();
    reg2 = codegen_get_temp();
    label1 = codegen_next_label();
    label2 = codegen_next_label();
    codegen_write_asm("movwf %s", reg2);    /* store the number of shifts in temp*/
    codegen_write_asm("movwf %s", name);
    codegen_write_asm("movwf %s", reg1);    /* store the number to be shifted */
    codegen_write_asm("movf %s", reg2);     /* test number of shifts */
    codegen_write_asm("btfsc STATUS, Z");
    codegen_write_asm("goto %s", label2);
    codegen_write_label(label1);
    codegen_write_asm("bcf STATUS, C");
    codegen_write_asm("rlf %s, f", reg1); 
    codegen_write_asm("decfsz %s", reg2);
    codegen_write_asm("goto %s", label1);
    codegen_write_label(label2);
    codegen_write_asm("movf %s, w", reg1);  /* move the result into w */
    break;
  case op_rsh:
    reg1 = codegen_get_temp();
    reg2 = codegen_get_temp();
    label1 = codegen_next_label();
    label2 = codegen_next_label();
    codegen_write_asm("movwf %s", reg2);    /* store the number of shifts in temp*/
    codegen_write_asm("movwf %s", name);
    codegen_write_asm("movwf %s", reg1);    /* store the number to be shifted */
    codegen_write_asm("movf %s", reg2);     /* test number of shifts */
    codegen_write_asm("btfsc STATUS, Z");
    codegen_write_asm("goto %s", label2);
    codegen_write_label(label1);
    codegen_write_asm("bcf STATUS, C");
    codegen_write_asm("rrf %s, f", reg1); 
    codegen_write_asm("decfsz %s", reg2);
    codegen_write_asm("goto %s", label1);
    codegen_write_label(label2);
    codegen_write_asm("movf %s, w", reg1);  /* move the result into w */
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
    reg1 = codegen_get_temp();
    codegen_write_asm("movwf %s", reg1);
    codegen_write_asm("movwf %s", name);
    codegen_write_asm("subwf %s, w", reg1);
    codegen_write_asm("movf STATUS, w");
    codegen_write_asm("andlw 1");
    codegen_write_asm("xorlw 1");
    break;
  case op_lte: 
    reg1 = codegen_get_temp();
    codegen_write_asm("movwf %s", reg1);
    codegen_write_asm("movf %s, w", name);
    codegen_write_asm("subwf %s, w", reg1);
    codegen_write_asm("movf STATUS, w");
    codegen_write_asm("andlw 1");
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

  if (reg1)
    free(reg1);

  if (label1)
    free(label1);

  if (label2)
    free(label2);

  return;
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
    char *temp_name;
 
    /* it is a complex expression so save temp data */
    temp_name = codegen_get_temp();
    codegen_write_asm("movwf %s", temp_name); 
    gen_expr(lhs);
    gen_binop_symbol(expr->value.binop.op, temp_name);
    if (temp_name)
      free(temp_name);
  }

}

void
gen_expr(tree *expr)
{
  struct variable *var;

  switch(expr->tag) {
  case node_arg:
    var = get_global(ARG_NAME(expr));
    if (var->class == storage_extern) {
      codegen_banksel(var->alias);
      gen_get_mem(var->alias);
      codegen_banksel(LOCAL_DATA_LABEL);
    } else {
      gen_get_mem(var->alias);
    }
    break;
  case node_constant:
    gen_immed(expr->value.constant);    
    break;
  case node_symbol:
    var = get_global(expr->value.symbol);
    if (var->is_constant) {
      codegen_write_asm("movlw %i", var->value);
    } else {
      if (var->class == storage_extern) {
        codegen_banksel(var->alias);
        gen_get_mem(var->alias);
        codegen_banksel(LOCAL_DATA_LABEL);
      } else {
        gen_get_mem(var->alias);
      }      
    }
    break;
  case node_unop:
    gen_unop_expr(expr);
    break;
  case node_binop:
    gen_binop_expr(expr);
    break;
  default:
    assert(0);
  }

}
