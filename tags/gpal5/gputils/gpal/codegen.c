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
#include "analyze.h"
#include "codegen.h"
#include "codegen14.h"

#ifdef STDC_HEADERS
#include <stdarg.h>
#endif

/* used for naming temporary data registers */
int temp_number;
int max_temp_number;

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

static int label_number;

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
codegen_banksel(char *label)
{
  codegen_write_asm("banksel %s", label);
}


void
codegen_test(tree *node, char *label)
{

  fprintf(state.output.f, ";#CSRC %s %d\n", 
          node->file_name,
          node->line_number);

  temp_number = 0;

  write_test(node, label);

  if (temp_number > max_temp_number)
    max_temp_number = temp_number;

}

void
codegen_expr(tree *statement)
{

  fprintf(state.output.f, ";#CSRC %s %d\n", 
          statement->file_name,
          statement->line_number);

  temp_number = 0;

  gen_expr(statement);

  if (temp_number > max_temp_number)
    max_temp_number = temp_number;

  return;
}

void
codegen_put_mem(struct variable *var, gp_boolean add_banksel)
{

  if (var->is_equ) { 
    /* This is an equate from the processor header file.  gpal doesn't
       get type information from that file.  It has to assume that 
       the constant is a register address */
    if (add_banksel) {
      codegen_write_asm("banksel %s", var->value);
    }    
    gen_put_reg(var->value);
  } else {
    if (add_banksel) {
      codegen_write_asm("banksel %s", var->alias);
    }
    gen_put_mem(var->alias);
  }

  return;
}

void
codegen_init_proc(char *name, enum node_storage storage, gp_boolean is_func)
{
  if (is_func) {
    fprintf(state.output.f, "; function %s\n", name);
  } else {
    fprintf(state.output.f, "; procedure %s\n", name);
  }

  codegen_write_label(name);
  if (storage == storage_public)
    codegen_write_asm("global %s", name);

}

void
codegen_finish_proc(void)
{
  fprintf(state.output.f, "  return\n\n");
}

void
codegen_init_data(void)
{
  fprintf(state.output.f, "; declarations \n");
  fprintf(state.output.f, ".udata_%s udata\n", state.basefilename);
  codegen_write_label(LOCAL_DATA_LABEL);
}

void
codegen_write_data(char *label, enum node_storage storage)
{

  fprintf(state.output.f, "%s res 1\n", label);

  if (storage == storage_public)
    codegen_write_asm("global %s", label);

}

void
codegen_finish_data(void)
{
  int i;

  for (i = 0; i < max_temp_number; i++) 
    fprintf(state.output.f, "%s_temp_%d res 1\n", state.basefilename, i);

  fprintf(state.output.f, "\n");

}

static void
write_header(void)
{
  char buffer[BUFSIZ];

  gp_date_string(buffer);

  fprintf(state.output.f, "; %s\n", state.asmfilename);
  fprintf(state.output.f, "; generated by gpal on %s\n\n", buffer);

  if (state.processor_chosen) {
    fprintf(state.output.f, "  processor %s\n", 
            state.processor_info->names[1]);
    fprintf(state.output.f, "  include \"%s.inc\"\n\n",
            state.processor_info->names[1]);
  } else {
    gp_error("processor not selected");
  } 

  fprintf(state.output.f, ".code_%s code\n", state.basefilename);

  return;
}

void
codegen_init_asm(void)
{

  /* open output filename */
  strcpy(state.asmfilename, state.basefilename);
  strcat(state.asmfilename, ".asm");
  state.output.f = fopen(state.asmfilename, "w");
  if (state.output.f == NULL) {
    perror(state.asmfilename);
    exit(1);
  }

  label_number = 0;

  write_header();

  return;
}

/* write all the external symbols in the global symbol table */

static void
write_externs(void)
{
  struct variable *var;
  int i;
  struct symbol *sym;
  gp_boolean first_time = true;

  for (i = 0; i < HASH_SIZE; i++) {
    for (sym = state.global->hash_table[i]; sym; sym = sym->next) {
      var = get_symbol_annotation(sym);
      if ((var) && (var->class == storage_extern)) {
        if (first_time == true)  {
          fprintf(state.output.f, "; external symbols\n");
          first_time = false;
        }
        fprintf(state.output.f, "  extern %s\n", var->alias);
      }
    }
  }

  if (first_time == false)
    fprintf(state.output.f, "\n");

  return;
}

static void
write_startup(void)
{
  struct variable *var;

  var = get_global("main");
  if ((var) && (var->node->tag == node_proc)) {
    /* a procedure named "main" exists so add the startup code */
    fprintf(state.output.f, "; startup and interrupt vectors\n");
    fprintf(state.output.f, "STARTUP code\n");
    fprintf(state.output.f, "  pagesel main\n");
    fprintf(state.output.f, "  goto main\n\n");
  }

}

static void
write_footer(void)
{
  fprintf(state.output.f, "  end\n\n");
}

void
codegen_close_asm(void)
{
  write_externs();
  write_startup();
  write_footer();  
  
  fclose(state.output.f);

  return;
}
