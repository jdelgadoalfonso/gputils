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

#include "stdhdr.h"

#include "libgputils.h"
#include "gpal.h"
#include "symbol.h"
#include "analyze.h" 
#include "codegen.h"
#include "codegen14.h"

/* prototypes */
static void gen_expr(tree *expr);

static int label_number;
static int temp_number;
static int max_temp_number;
static int codegen_working_bytes;
static enum size_tag codegen_size;
int codegen_bytes;

static struct function_pointer_struct *func_ptr;

/* code generation function pointer */
typedef void code_func(enum node_op op, 
                       enum size_tag size,
                       gp_boolean is_const,
                       int value,
                       char *name);

/* load constant function pointer */
typedef void data_func1(int value, enum size_tag size);

/* data movement function pointers */
typedef void data_func2(char *name,
                        enum size_tag size,
                        int offset,
                        gp_boolean add_banksel);

#define CODEGEN (*(code_func*)func_ptr->codegen)
#define LOAD_CONSTANT (*(data_func1*)func_ptr->load_constant)
#define LOAD_FILE (*(data_func2*)func_ptr->load_file)
#define STORE_FILE (*(data_func2*)func_ptr->store_file)
#define LOAD_INDIRECT (*(data_func2*)func_ptr->load_indirect)
#define STORE_INDIRECT (*(data_func2*)func_ptr->store_indirect)

/****************************************************************************/
/* Common Assembly Functions                                                */
/****************************************************************************/

void 
codegen_write_asm(const char *format, ...)
{
  va_list args;
  char buffer[BUFSIZ]; 

  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);

  fprintf(state.output.f, "  %s\n", buffer);

  return;
}

void 
codegen_write_comment(const char *format, ...)
{
  va_list args;
  char buffer[BUFSIZ]; 

  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
   
  fprintf(state.output.f, "; %s\n", buffer);

  return;
}

void
codegen_line_number(tree *node)
{
  fprintf(state.output.f, "#line %d\n", node->line_number);
}

char *
codegen_next_label(void)
{
  char label[BUFSIZ];
  sprintf(label, "_%i", label_number++);
  return strdup(label);
}

void
codegen_write_label(char *label)
{
  fprintf(state.output.f, "%s:\n", label);
}

/****************************************************************************/
/* Common directives and instructions                                       */
/****************************************************************************/

void
codegen_jump(char *label)
{
  codegen_write_asm("goto %s", label);
}

void
codegen_call(char *label, enum node_storage storage)
{
 
  if (storage == storage_extern) {
    codegen_write_asm("pagesel %s", label);
  }
  codegen_write_asm("call %s", label);

}

void
codegen_assembly(tree *assembly)
{

  fprintf(state.output.f, "%s\n", assembly->value.assembly);

  return;
}

/****************************************************************************/
/* Memory access                                                            */
/****************************************************************************/

/* calculate the byte address of the data and put it in FSR */

void
codegen_indirect(tree *offset,
                 struct variable *var,
                 int element_size,
                 gp_boolean new_expr)
{

  /* FIXME: the default pointer size needs to be selected (size_uint8 for
     now ) */

  /* indirect access */
  if (new_expr) {
    codegen_expr(offset, size_uint8);
  } else {
    gen_expr(offset);
  }
  if (var->type->start != 0) {
    /* shift the offset for the first element */
    CODEGEN(op_add, size_uint8, true, 0 - var->type->start, NULL);
  }
  if (element_size != 1) {
    /* scale the offset by the element size */
    CODEGEN(op_mult, size_uint8, true, element_size, NULL);
  }
  codegen_write_asm("addlw %s", var->alias); 
  codegen_write_asm("movwf FSR"); 

}

/* load the register file into the working register */

static void
codegen_load_file(tree *symbol, struct variable *var)
{
  int offset;
  int element_size;

  if ((symbol->tag == node_symbol) && (SYM_OFST(symbol))) {
    /* access an array */
    element_size = type_size(var->type->prim);

    if ((var) && (var->type) && (var->type->tag == type_array)) {
      if (can_evaluate(SYM_OFST(symbol), false)) {
        /* direct access */
        offset = analyze_check_array(symbol, var) * element_size;
        if (var->storage == storage_extern) {
          LOAD_FILE(var->alias, codegen_size, offset, true);
        } else {
          LOAD_FILE(var->alias, codegen_size, offset, false);
        }
      } else {
        codegen_indirect(SYM_OFST(symbol), var, element_size, false);
        if (var->storage == storage_extern) {
          LOAD_INDIRECT(var->alias, codegen_size, 0, true);
        } else {
          LOAD_INDIRECT(var->alias, codegen_size, 0, false);
        }
      }
    } else {
      analyze_error(symbol, "symbol %s is not an array",
                    SYM_NAME(symbol));
    }
  } else {
    if (var->storage == storage_extern) {
      LOAD_FILE(var->alias, codegen_size, 0, true);
    } else {
      LOAD_FILE(var->alias, codegen_size, 0, false);
    }
  }

  return;
}

/* store the working register in memory */

void
codegen_store(struct variable *var,
              gp_boolean constant_offset,
              int offset,
              tree *offset_expr)
{

  if (offset_expr) {
    if (constant_offset) {
      if (var->storage == storage_extern) {
        STORE_FILE(var->alias, codegen_size, offset, true);
      } else {
        STORE_FILE(var->alias, codegen_size, offset, false);
      }    
    } else {
      if (var->storage == storage_extern) {
        STORE_INDIRECT(var->alias, codegen_size, 0, true);
      } else {
        STORE_INDIRECT(var->alias, codegen_size, 0, false);
      }
    }
  } else {
    if (var->storage == storage_extern) {
      STORE_FILE(var->alias, codegen_size, 0, true);
    } else {
      STORE_FILE(var->alias, codegen_size, 0, false);
    }
  }

}

/****************************************************************************/
/* Expression generation                                                    */
/****************************************************************************/

static void
gen_unop_expr(tree *expr)
{

  gen_expr(expr->value.unop.p0);
  switch (expr->value.unop.op) {
  case op_add:
    break;
  case op_not:
  case op_neg:
    CODEGEN(expr->value.unop.op, codegen_size, true, 0, NULL);
    break;
  default:
    assert(0);
  }

}

static void
gen_binop_expr(enum node_op op, tree *p0, tree *p1)
{
  char *reg1 = NULL;
  char *reg2 = NULL;
  struct variable *var;

  gen_expr(p1);

  if (p0->tag == node_call) {
    reg1 = codegen_get_temp(codegen_size);
    STORE_FILE(reg1, codegen_size, 0, false);
    analyze_call(p0, true, codegen_size);    
    CODEGEN(op, codegen_size, false, 0, reg1);
  } else if (p0->tag == node_constant) {
    CODEGEN(op, codegen_size, true, p0->value.constant, NULL);
  } else if (p0->tag == node_symbol) { 
    var = get_global(SYM_NAME(p0));
    if (var->tag == sym_const) {
      CODEGEN(op, codegen_size, true, var->value, NULL);
    } else if (SYM_OFST(p0)) {
      /* it is a complex expression, so save temp data */
      reg1 = codegen_get_temp(codegen_size);
      reg2 = codegen_get_temp(codegen_size);
      STORE_FILE(reg1, codegen_size, 0, false);
      codegen_load_file(p0, var);
      STORE_FILE(reg2, codegen_size, 0, false);
      LOAD_FILE(reg1, codegen_size, 0, false);
      CODEGEN(op, codegen_size, false, 0, reg2);
    } else {
      CODEGEN(op, codegen_size, false, 0, var->alias);
    }
  } else {
    /* it is a complex expression so save temp data */
    reg1 = codegen_get_temp(codegen_size);
    STORE_FILE(reg1, codegen_size, 0, false);
    gen_expr(p0);
    CODEGEN(op, codegen_size, false, 0, reg1);
  }

  if (reg1)
    free(reg1);
  if (reg2)
    free(reg2);

}

static void
gen_expr(tree *expr)
{
  struct variable *var;

  switch(expr->tag) {
  case node_arg:
    var = get_global(ARG_NAME(expr));
    codegen_load_file(expr, var);
    break;
  case node_call:
    analyze_call(expr, true, codegen_size);    
    break;
  case node_constant:
    LOAD_CONSTANT(expr->value.constant, codegen_size);
    break;
  case node_symbol:
    var = get_global(SYM_NAME(expr));
    if (var->tag == sym_const) {
      LOAD_CONSTANT(var->value, codegen_size); 
    } else {
      codegen_load_file(expr, var);
    }
    break;
  case node_unop:
    gen_unop_expr(expr);
    break;
  case node_binop:
    if (expr->value.binop.op == op_assign) {
      analyze_error(expr, "assign operator = should be equal operator ==");
    } else if ((expr->value.binop.op == op_lsh) ||
               (expr->value.binop.op == op_rsh)) {
      /* for shifts it is best to calculate the left side first */
      gen_binop_expr(expr->value.binop.op,
                     expr->value.binop.p1,
                     expr->value.binop.p0);
    } else {
      /* for all others calculate the right side first */
      gen_binop_expr(expr->value.binop.op,
                     expr->value.binop.p0,
                     expr->value.binop.p1);
    }
    break;
  default:
    assert(0);
  }

}

/* Store the number of bytes required for the working register */

static int
codegen_setup(enum size_tag size)
{
  codegen_size = size;
  codegen_bytes = prim_size(size);

  if (codegen_bytes > codegen_working_bytes) {
    codegen_working_bytes = codegen_bytes;
  }
  
  if (codegen_bytes != 1) {
    /* The w register isn't used as the working register so save data
       memory. */
    return codegen_bytes;
  }

  return 0;
}

void
codegen_test(tree *node, char *label, enum size_tag size)
{

  temp_number = codegen_setup(size);

  gen_expr(node);
  codegen_write_asm("btfsc STATUS, Z");
  codegen_write_asm("goto %s", label);

  if (temp_number > max_temp_number)
    max_temp_number = temp_number;

}

void
codegen_expr(tree *statement, enum size_tag size)
{

  temp_number = codegen_setup(size);

  gen_expr(statement);

  if (temp_number > max_temp_number)
    max_temp_number = temp_number;

  return;
}

/****************************************************************************/
/* Write procedures and functions                                           */
/****************************************************************************/

void
codegen_init_proc(char *name, enum node_storage storage, gp_boolean is_func)
{
  if (is_func) {
    codegen_write_comment("function %s", name);
  } else {
    codegen_write_comment("procedure %s", name);
  }

  codegen_write_label(name);
  if (storage == storage_public)
    codegen_write_asm("global %s", name);

}

void
codegen_finish_proc(gp_boolean add_return)
{
  if (add_return) {
    codegen_write_asm("return");
  }
  fprintf(state.output.f, "\n");
}

/****************************************************************************/
/* Write data memory section and externs                                    */
/****************************************************************************/

void
codegen_init_data()
{
  codegen_write_comment("declarations");

  if (state.section.udata) {
    if (state.section.udata_addr_valid) {
      fprintf(state.output.f, "%s udata %#x\n", 
              state.section.udata,
              state.section.udata_addr);
    } else {
      fprintf(state.output.f, "%s udata\n", state.section.udata);
    }
  } else {
    if (state.section.udata_addr_valid) {
      fprintf(state.output.f, ".udata_%s udata %#x\n",
              FILE_NAME(state.module),
              state.section.udata_addr);
    } else {
      fprintf(state.output.f, ".udata_%s udata\n", FILE_NAME(state.module));
    }  
  }

  codegen_write_label(LOCAL_DATA_LABEL);
  
}

void
codegen_write_data(char *label, int size, enum node_storage storage)
{

  fprintf(state.output.f, "%s res %i\n", label, size);

  if (storage == storage_public)
    codegen_write_asm("global %s", label);

}

void
codegen_temp_data()
{
  int i;

  /* extended math used so a working register is required */
  if (codegen_working_bytes != 1) {  
    codegen_write_label(WORKING_LABEL);
  }

  for (i = 0; i < max_temp_number; i++) 
    fprintf(state.output.f, "_%s_temp_%d res 1\n", FILE_NAME(state.module), i);

}

char *
codegen_get_temp(enum size_tag size)
{
  char temp_name[BUFSIZ];
 
  sprintf(temp_name, "_%s_temp_%d", FILE_NAME(state.module), temp_number);

  temp_number += prim_size(size);

  return strdup(temp_name);
}

/****************************************************************************/
/* File operations                                                          */
/****************************************************************************/

void
codegen_init_asm()
{
  char buffer[BUFSIZ];

  /* open output filename */
  strcpy(state.asmfilename, state.basefilename);
  strcat(state.asmfilename, ".asm");
  state.output.f = fopen(state.asmfilename, "w");
  if (state.output.f == NULL) {
    perror(state.asmfilename);
    exit(1);
  }

  label_number = 0;
  max_temp_number = 0;
  codegen_working_bytes = 1;
  codegen_size = size_uint8;
  codegen_bytes = prim_size(codegen_size);

  gp_date_string(buffer);

  fprintf(state.output.f, "; %s\n", state.asmfilename);
  fprintf(state.output.f, "; generated by %s on %s\n\n",
          GPAL_VERSION_STRING,
          buffer);

  fprintf(state.output.f, "#file \"%s\"\n\n", state.srcfilename);

  if (state.processor_chosen) {
    fprintf(state.output.f, "  processor %s\n", 
            state.processor_info->names[1]);
    fprintf(state.output.f, "  include \"%s.inc\"\n\n",
            state.processor_info->names[1]);
  } else {
    gp_error("processor not selected");
  } 

  if (state.section.code) {
    if (state.section.code_addr_valid) {
      fprintf(state.output.f, "%s code %#x\n", 
              state.section.code,
              state.section.code_addr);
    } else {
      fprintf(state.output.f, "%s code\n", state.section.code);
    }
  } else {
    if (state.section.code_addr_valid) {
      fprintf(state.output.f, ".code_%s code %#x\n", 
              FILE_NAME(state.module),
              state.section.code_addr);
    } else {
      fprintf(state.output.f, ".code_%s code\n", FILE_NAME(state.module));
    }
  }

  return;
}

void
codegen_close_asm(void)
{
  struct variable *var;

  var = get_global("main");
  if ((var) && (var->node->tag == node_proc)) {
    /* a procedure named "main" exists so add the startup code */
    codegen_write_comment("startup and interrupt vectors");
    fprintf(state.output.f, "STARTUP code\n");
    codegen_line_number(var->node);
    fprintf(state.output.f, "  pagesel %s\n", var->alias);
    fprintf(state.output.f, "  goto %s\n\n", var->alias);
  }

  fprintf(state.output.f, "#eof\n\n");
  fprintf(state.output.f, "  end\n\n");

  fclose(state.output.f);

  return;
}

void
codegen_select(tree *expr)
{

  switch (state.class) {
  case PROC_CLASS_EEPROM8:
  case PROC_CLASS_GENERIC:
  case PROC_CLASS_PIC12:
  case PROC_CLASS_SX:
    analyze_error(expr, "unsupported processor class");
    break;
  case PROC_CLASS_PIC14:
    func_ptr = &codegen14_func;
    break;
  case PROC_CLASS_PIC16:
  case PROC_CLASS_PIC16E:
    analyze_error(expr, "unsupported processor class");
    break;
  default:
    assert(0);
  }

}
