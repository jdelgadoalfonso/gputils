/* analyze semantics
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
#include "scan.h"
#include "symbol.h"

#ifdef STDC_HEADERS
#include <stdarg.h>
#endif

/* prototypes */
void analyze_statements(tree *statement);

static gp_linked_list *data_memory;
static gp_linked_list *last_link;

/* create a linked list of all the data memory used */

static void
add_link(struct variable *var)
{
  gp_linked_list *new = gp_list_make();

  gp_list_annotate(new, var);

  if (data_memory) {
    new->prev = last_link;
    last_link->next = new;
    last_link = new;
  } else {
    data_memory = new;
    last_link = new;
  }

}

void 
analyze_error(tree *node, const char *format, ...)
{
  va_list args;
  char buffer[BUFSIZ]; 

  gp_num_errors++;

  if (gp_quiet != 0)
    return;

  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);

  if (node) {
    printf("%s:%d: error: %s\n",
           get_compile(node->file_id),
           node->line_number,
           buffer);
  } else {
    printf("error %s\n", buffer);
  }

  return;
}

static void 
analyze_warning(tree *node, const char *format, ...)
{
  va_list args;
  char buffer[BUFSIZ]; 

  gp_num_warnings++;

  if (gp_quiet != 0)
    return;

  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);

  if (node) {
    printf("%s:%d: warning: %s\n",
           get_compile(node->file_id),
           node->line_number,
           buffer);
  } else {
    printf("warning %s\n", buffer);
  }


  return;
}

static
int list_length(tree *L)
{
  if (L == NULL) {
    return 0;
  } else {
    return 1 + list_length(L->next);
  }
}

/* convert a private procedure to public */

static void
make_proc_public(struct variable *var, tree *prot)
{
  tree *def = NULL;
  tree *head = NULL;
  tree *arg = NULL;
  struct variable *arg_var = NULL;

  /* FIXME: need to check that the prototype matches the definition */

  /* make the procedure public */
  var->class = storage_public;

  def = var->node;

  if (def->tag == node_proc) {
    head = PROC_HEAD(def);
  } else if (def->tag == node_func) {
    head = FUNC_HEAD(def);
  } else {
    assert(0);
  }

  arg = HEAD_ARGS(head);

  while (arg) {
    assert(arg->tag == node_decl);
    arg_var = get_global(DECL_NAME(arg));
    assert(arg_var != NULL);
    arg_var->class = storage_public;
    arg = arg->next;
  }

  return;
}

/* Add all the the arguments from a procedure or function to the 
   global symbol table */

static void
add_arg_symbols(tree *node, char *name, enum node_storage storage)
{
  tree *head = NULL;
  tree *arg = NULL;
  struct variable *var;

  if (node->tag == node_proc) {
    head = PROC_HEAD(node);
  } else if (node->tag == node_func) {
    head = FUNC_HEAD(node);
  } else {
    print_node(node, 0);
    assert(0);
  }

  arg = HEAD_ARGS(head);

  while (arg) {
    assert(arg->tag == node_decl);
    var = add_global_symbol(DECL_NAME(arg), name, arg, storage);
    if ((var->class == storage_private) ||
        (var->class == storage_public)) {    
      add_link(var);
    }
    arg = arg->next;
  }

  return;
}

/* can the expression be evaluated at compile time */

int
can_evaluate(tree *p)
{
  struct variable *var;

  switch (p->tag) {
  case node_constant:
    return 1;
  case node_symbol:
    var = get_global(p->value.symbol);
    if (var) {
      if (var->is_constant) {
        return 1;
      } else {
        analyze_error(p, "symbol is not a constant (%s)", p->value.symbol);    
        return 0;
      }
    } else {
      analyze_error(p, "symbol not previously defined (%s)", p->value.symbol);    
      return 0;
    }
  case node_unop:
    return can_evaluate(p->value.unop.p0);
  case node_binop:
    return can_evaluate(p->value.binop.p0) && can_evaluate(p->value.binop.p1);
  case node_string:
    analyze_error(p, "illegal argument (%s)", p->value.string);
    return 0;
  default:
    assert(0);
  }

  return 0;
}

int
evaluate(tree *p)
{
  struct variable *var;
  int p0, p1;

  switch (p->tag) {
  case node_constant:
    return p->value.constant;
  case node_symbol:
    var = get_global(p->value.symbol);
    return var->value;
  case node_unop:
    switch (p->value.unop.op) {
    case op_not:
      return !evaluate(p->value.unop.p0);
    case op_add:
      return  evaluate(p->value.unop.p0);
    case op_neg:
      return -evaluate(p->value.unop.p0);
    case op_com:
      return ~evaluate(p->value.unop.p0);
    default:
      assert(0);
    }
  case node_binop:
    p0 = evaluate(p->value.binop.p0);
    p1 = evaluate(p->value.binop.p1);
    switch (p->value.binop.op) {
    case op_add:   return p0 + p1;
    case op_sub:   return p0 - p1;
    case op_mult:  return p0 * p1;
    case op_div:
      if (p1 == 0){
        analyze_error(p->value.binop.p1, "divide by 0");
        return 0;
      } else {
        return p0 / p1;
      }
    case op_mod:   return p0 % p1;
    case op_and:   return p0 & p1;
    case op_or:    return p0 | p1;
    case op_xor:   return p0 ^ p1;
    case op_lsh:   return p0 << p1;
    case op_rsh:   return p0 >> p1;
    case op_eq:    return p0 == p1;
    case op_lt:    return p0 < p1;
    case op_gt:    return p0 > p1;
    case op_ne:    return p0 != p1;
    case op_gte:   return p0 >= p1;
    case op_lte:   return p0 <= p1;
    case op_land:  return p0 && p1;
    case op_lor:   return p0 || p1;
    default:
      assert(0); /* Unhandled binary operator */
    }
  default:
    assert(0); /* Unhandled parse node tag */
  }

  return (0); /* Should never reach here */
}

int
maybe_evaluate(tree *p)
{
  int r;

  if (p && can_evaluate(p)) {
    r = evaluate(p);
  } else {
    r = 0;
  }

  return r;
}

static int
test_symbol(tree *node)
{
  struct symbol *sym;

  /* FIXME: need to test symbol type too.  Can't use procedure name in 
     and expression. */

  sym = get_symbol(state.top, node->value.symbol);
  if (sym == NULL) {
    analyze_error(node, "unknown symbol \"%s\"", node->value.symbol);
    return 1;
  }

  return 0;
}

/* scan the tree and make sure all of the symbols are valid */

static void
scan_tree(tree *expr)
{

  if (expr == NULL)
    return;

  switch (expr->tag) {
  case node_binop:
    scan_tree(BINOP_LEFT(expr));
    scan_tree(BINOP_RIGHT(expr));
    break;
  case node_constant:
    break;
  case node_unop:
    scan_tree(BINOP_RIGHT(expr));
    break;
  case node_symbol:
    test_symbol(expr);
    break;
  default:
    assert(0);
  }

}

void
analyze_call(tree *call)
{
  struct variable *var;
  tree *def;
  tree *head;
  tree *def_args;
  tree *call_args;
  struct variable *def_var;

  var = get_global(CALL_NAME(call));
  if (var) {
    def = var->node;
    if (def->tag == node_proc) {
      head = PROC_HEAD(var->node);
    } else if (def->tag == node_func) {
      head = FUNC_HEAD(var->node);
    } else {
      analyze_error(call, "name in call is not a function or procedure");
      return;
    }
  } else {
    analyze_error(call, "unknown symbol \"%s\"", CALL_NAME(call));
    return;
  }

  call_args = CALL_ARGS(call);
  def_args = HEAD_ARGS(head);

  if (list_length(call_args) != list_length(def_args)) {
    /* FIXME: should also check argument type */
    analyze_error(call, "incorrect number of arguments in call");
    return;
  }

  while (call_args) {
    assert(def_args->tag == node_decl);

    /* write the expression */
    codegen_expr(call_args);

    /* store the result in the memory mapped argument */
    def_var = get_global(DECL_NAME(def_args));
    assert(def_var != NULL);
    if (def_var->class == storage_extern) {
      codegen_put_mem(def_var, true);
      codegen_banksel(LOCAL_DATA_LABEL);
    } else {
      codegen_put_mem(def_var, false);
    }
  
    def_args = def_args->next;
    call_args = call_args->next;
  }

  codegen_call(var->alias, var->class);

  return;
}

void
analyze_cond(tree *cond)
{
  char *end_label = NULL;

  /* else doesn't have a condition */
  if (COND_TEST(cond)) {
    end_label = codegen_next_label();
    codegen_test(COND_TEST(cond), end_label);
  }
  
  /* write the body of the code */
  analyze_statements(COND_BODY(cond));
  
  /* if there is a condition generate a label at the end of the body */
  if (COND_TEST(cond)) {
    codegen_write_label(end_label);
    if (end_label)
      free(end_label);
  }
  
  /* generate next conditional block, if there is one */
  if(COND_NEXT(cond))
    analyze_cond(COND_NEXT(cond));

  return;
}

void
analyze_loop(tree *loop)
{
  char *start_label = NULL;  

  analyze_statements(LOOP_INIT(loop));

  /* place the label for looping */
  start_label = codegen_next_label();
  codegen_write_label(start_label);

  /* write the loop body */
  analyze_statements(LOOP_BODY(loop));

  /* write the increment statements*/
  analyze_statements(LOOP_INCR(loop));

  /* write the exit statements */
  if (LOOP_EXIT(loop)) {
    codegen_test(LOOP_EXIT(loop), start_label);
  } else {
    codegen_jump(start_label);
  }

  if (start_label)
    free(start_label);

  return;
}

void
analyze_expr(tree *expr)
{
  tree *left;
  tree *right;
  struct variable *var;

  if ((expr->tag != node_binop) || (BINOP_OP(expr) != op_eq)) {
    analyze_error(expr, "expression is missing \"=\"");
    return;
  }
  
  left = BINOP_LEFT(expr);
  right = BINOP_RIGHT(expr);
 
  if (left->tag != node_symbol) {
    analyze_error(expr, "invalid lvalue in assignment");
    return;
  }

  /* verify all symbols in the expression are in the symbol table */
  test_symbol(left);
  scan_tree(right);

  /* write the expression */
  codegen_expr(right);

  /* fetch the symbols alias */
  var = get_global(left->value.symbol);
  assert(var != NULL);

  /* put the result in memory */
  if (var->class == storage_extern) {
    codegen_put_mem(var, true);
    codegen_banksel(LOCAL_DATA_LABEL);
  } else {
    codegen_put_mem(var, false);
  }
}

static void
analyze_assembly(tree *assembly)
{
  /* FIXME: need to figure out how to check the asm blocks */

  codegen_assembly(assembly);
}

void
analyze_statements(tree *statement)
{

  if (statement == NULL)
    return;

  while(statement) {
    switch(statement->tag) {
    case node_assembly:
      analyze_assembly(statement);
      break;
    case node_call:
      analyze_call(statement);
      break;
    case node_cond:
      analyze_cond(statement);  
      break;
    case node_loop:
      analyze_loop(statement);
      break; 
    default:
      analyze_expr(statement);
    }
    statement = statement->next;
  } 

  return;
}

void
analyze_procedure(tree *procedure, gp_boolean is_func)
{
  tree *head;
  tree *body;
  struct variable *var;
  char *proc_name;
  tree *args;
  tree *decl;
  tree *statements;

  /* local symbol table */
  state.top = push_symbol_table(state.top, 1);

  if (is_func) {
    head = FUNC_HEAD(procedure);
    body = FUNC_BODY(procedure);
  } else {
    head = PROC_HEAD(procedure);
    body = PROC_BODY(procedure);
  }

  assert(head->tag == node_head);  
  assert(body->tag == node_body); 
  args = HEAD_ARGS(head);
  decl = BODY_DECL(body);
  statements = BODY_STATEMENTS(body); 

  var = get_global(find_node_name(procedure));
  assert(var != NULL);
  proc_name = var->alias;

  /* local data */
  while (decl) {
    assert(decl->tag == node_decl);
    if (DECL_TYPE(decl) == type_var) {
      add_link(add_global_symbol(DECL_NAME(decl), 
               proc_name,
               decl,
               storage_private));
    } else if (DECL_TYPE(decl) == type_const) {
      if (DECL_INIT(decl)) {
        add_constant(DECL_NAME(decl), maybe_evaluate(DECL_INIT(decl)), decl);
      } else {
        analyze_error(decl, "missing constant value");
      }
    } else {
      assert(0);    
    }

    decl = decl->next;
  }

  /* write the procedure to the assembly file */
  codegen_init_proc(proc_name, var->class, is_func);
  if (var->class == storage_public) {
    codegen_banksel(LOCAL_DATA_LABEL);
  }
  analyze_statements(statements);
  codegen_finish_proc();

  /* scan the local data, if a location is used add it to the list */
  if (state.optimize.trival_expressions) {
  
    
  }
  
  /* remove the local table */
  state.top = pop_symbol_table(state.top);

  return;
}

void
analyze_declarations(void)
{
  gp_linked_list *list = data_memory;
  struct variable *var;

  while(list) {
    var = gp_list_get(list);
    codegen_write_data(var->alias, var->class);
    list = list->next;
  }

}

#define LINE_SIZ 520

void
analyze_select_processor(tree *expr, char *name)
{
  struct px *found = NULL;
  char file_name[LINE_SIZ];

  if (state.cmd_processor) {
    analyze_warning(expr, "processor superseded by command line");
  } else {
    found = gp_find_processor(name);
    if (found) {
      if (state.processor == no_processor) {
        state.processor = found->tag;
        state.processor_info = found;
        sprintf(file_name, "%s.inc", found->names[1]);
        if (state.read_header) {
          scan_header(file_name);
        }
      } else if (state.processor != found->tag ) {
        analyze_warning(expr, "redefining processor");
      }
    } else {
      analyze_error(expr, "unknown processor \"%s\"", name);
    }
   
    /* load the instruction sets if necessary */
    if ((state.processor_chosen == false) && 
        (state.processor != no_processor)) {
      /* FIXME select the correct code generator */
      state.processor_chosen = true;
    }
  }
}

static void
analyze_pragma(tree *expr, enum source_type type)
{
  tree *lhs;
  tree *rhs;

  switch (expr->tag) {
  case node_binop:
    lhs = expr->value.binop.p0;
    rhs = expr->value.binop.p1;
    if ((expr->value.binop.op != op_eq) ||
        (lhs->tag != node_symbol)) {
      analyze_error(expr, "unknown pragma");
    } else {
      if (strcasecmp(lhs->value.string, "processor") == 0) {
        if (rhs->tag != node_string) {
          analyze_error(expr, "processor name must be a string");        
        } else {
          analyze_select_processor(rhs, rhs->value.string);
        }
      } else if (strcasecmp(lhs->value.symbol, "code_section") == 0) {
        if (rhs->tag != node_string) {
          analyze_error(expr, "code section name must be a string");
        } else {
          if (type == source_with) {            
            if ((state.section.code) && 
                (strcmp(rhs->value.string, state.section.code) == 0)) {
              state.section.code_default = storage_local;
            } else {
              state.section.code_default = storage_extern;
            }
          } else {
            if (type == source_module) {
              analyze_warning(expr, "section pragma's should be in a public");
            }
            if (state.section.code) {
              analyze_error(expr, "duplicate code section name");
            } else {
              state.section.code = rhs->value.string;
            }
          }        
        }
      } else if (strcasecmp(lhs->value.string, "udata_section") == 0) {
        if (rhs->tag != node_string) {
          analyze_error(expr, "udata section name must be a string");
        } else {
          if (type == source_with) {            
            if ((state.section.udata) &&
                (strcmp(rhs->value.string, state.section.udata) == 0)) {
              state.section.udata_default = storage_local;
            } else {
              state.section.udata_default = storage_extern;
            }
          } else {
            if (type == source_module) {
              analyze_warning(expr, "section pragma's should be in a public");
            }
            if (state.section.code) {
              analyze_error(expr, "duplicate udata section name");
            } else {
              state.section.udata = rhs->value.string;
            }
          }        
        }
      } else if (strcasecmp(lhs->value.symbol, "code_address") == 0) {
        if (rhs->tag != node_constant) {
          analyze_error(expr, "code address must be a constant");
        } else if (type == source_module) {            
          state.section.code_addr = rhs->value.constant;
          state.section.code_addr_valid = true;
        } else {
          analyze_error(expr, "udata section addresses can only be in modules");
        }
      } else if (strcasecmp(lhs->value.symbol, "udata_address") == 0) {
        if (rhs->tag != node_constant) {
          analyze_error(expr, "udata address must be a constant");
        } else if (type == source_module) {            
          state.section.udata_addr = rhs->value.constant;
          state.section.udata_addr_valid = true;
        } else {
          analyze_error(expr, "udata section addresses can only be in modules");
        }
      } else {
        analyze_error(expr, "unknown pragma \"%s\"", lhs->value.symbol);
      }
    }
    break;
  default:
    analyze_error(expr, "unknown pragma");
  }
  
  return;
}

/* FIXME: make sure public proc don't have bodies, but modules do */

static void
analyze_module(tree *file)
{
  tree *current;
  char *name;

  current = FILE_BODY(file);
  while (current) {
    switch (current->tag) {
    case node_pragma:
      analyze_pragma(current->value.pragma, FILE_TYPE(file));
      break;
    case node_decl:
    case node_proc:
    case node_func:
      break;
    default:
      assert(0);
    }
    current = current->next;
  }

  current = FILE_BODY(file);
  while (current) {
    switch (current->tag) {
    case node_pragma:
      break;
    case node_decl:
      name = find_node_name(current);
      add_link(add_global_symbol(name, NULL, current, storage_private));
      break;
    case node_proc:
    case node_func:
      name = find_node_name(current);
      add_global_symbol(name, NULL, current, storage_private);
      add_arg_symbols(current, name, storage_private);     
      break;
    default:
      assert(0);
    }
    current = current->next;
  }

  return;
}

static void
analyze_public(tree *file)
{
  tree *current;
  char *name;
  struct variable *var;

  current = FILE_BODY(file);
  while (current) {
    switch (current->tag) {
    case node_pragma:
      analyze_pragma(current->value.pragma,  FILE_TYPE(file));
      break;
    case node_decl:
    case node_proc:
    case node_func:
      break;
    default:
      assert(0);
    }
    current = current->next;
  }

  current = FILE_BODY(file);
  while (current) {
    switch (current->tag) {
    case node_pragma:
      break;
    case node_decl:
    case node_proc:
    case node_func:
      name = find_node_name(current);
      if (FILE_TYPE(file) == source_public) {
        var = get_global(name);
        if (var) {
          if (current->tag == node_decl) {
            var->class = storage_public;       
          } else {
            make_proc_public(var, current);
          }
        } else {
          analyze_error(current, "missing definition"); 
        }
      } else if (FILE_TYPE(file) == source_with) {
        add_global_symbol(name, NULL, current, state.section.code_default);
        if (current->tag != node_decl) {
          add_arg_symbols(current, name, state.section.udata_default);
        }
      } else {
        assert(0);
      }
      break;
    default:
      assert(0);
    }
    current = current->next;
  }

  return;
}

static void
analyze_module_contents(tree *file)
{
  tree *current = FILE_BODY(file);

  while (current) {
    switch (current->tag) {
    case node_pragma:
    case node_decl:
      /* do nothing */
      break;
    case node_proc:
      analyze_procedure(current, 0);
      break;
    case node_func:
      analyze_procedure(current, 1);
      break;
    default:
      assert(0);
    }
    current = current->next;
  }

  return;
}

void
analyze(void)
{
  tree *current;
  tree *module = NULL;
  gp_boolean found_module = false;

  /* FIXME: manage memory better or at least try */
  data_memory = NULL;

  /* add all procedures and data to the global symbol table */
  current = state.root;
  while (current) {
    if (FILE_TYPE(current) == source_module) {
      if (found_module) {
        analyze_error(current, "found multiple modules in one file");
      } else {
        analyze_module(current);
        module = current;
      }
      found_module = true;
    }
    current = current->next;
  }

  /* add all prototypes and externs to global symbol table */
  current = state.root;
  while (current) {
    if ((FILE_TYPE(current) == source_public) ||
        (FILE_TYPE(current) == source_with)) {
      analyze_public(current);
    }
    current = current->next;
  }

  if (!state.processor_chosen) {
    analyze_error(module, "processor not selected");
    return;
  }

  /* don't bother generating code if there are errors */
  if (gp_num_errors)
    return;

  /* open the output file */
  codegen_init_asm();

  /* scan though each procedure and function */
  current = state.root;
  while (current) {
    if (FILE_TYPE(current) == source_module) {
      analyze_module_contents(current);
    }
    current = current->next;
  }

  /* scan though each declaration */
  codegen_init_data();
  analyze_declarations();
  codegen_finish_data();

  /* close the assembly output */
  codegen_close_asm();

  return;
}
