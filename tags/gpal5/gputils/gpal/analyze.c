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

#ifdef STDC_HEADERS
#include <stdarg.h>
#endif

/* prototypes */
void analyze_statements(tree *statement);

static linked_list *data_memory;
static linked_list *last_link;

/* create a linked list of all the data memory used */

static void
add_link(struct variable *var)
{
  linked_list *new;

  new = malloc(sizeof(linked_list));
  new->item = var;
  new->prev = NULL;
  new->next = NULL;

  if (data_memory) {
    new->prev = last_link;
    last_link->next = new;
    last_link = new;
  } else {
    data_memory = new;
    last_link = new;
  }

}

static void 
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

  printf("%s:%d:error %s\n", node->file_name, node->line_number, buffer);

  return;
}

#if 0

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

  printf("%s:%d:warning %s\n", node->file_name, node->line_number, buffer);

  return;
}

#endif

static
int list_length(tree *L)
{
  if (L == NULL) {
    return 0;
  } else {
    return 1 + list_length(L->next);
  }
}

/* FIXME: this function is common with gpasm/scan.l */

static char *
to_lower_case(char *name)
{
  char *new;
  char *ptr;

  ptr = new = strdup(name);

  while (*ptr != '\0') {
    *ptr = tolower(*ptr);
    ptr++;
  }

  return new;
}

struct variable *
add_global(char *name, char *alias, tree *node)
{
  struct symbol *sym;
  struct variable *var;
  tree *other_def;

  sym = get_symbol(state.global, name);
  if (sym == NULL) {
    sym = add_symbol(state.global, name);
    var = malloc(sizeof(*var));
    annotate_symbol(sym, var);
    var->alias = to_lower_case(alias);
    var->class = storage_unknown;
    var->size = 0;
    var->bitsize = 0;
    var->nelts = 0;
    var->is_init = false;
    var->is_equ = false;
    var->is_constant = false;
    var->value = 0;
    var->node = node;
  } else {
    var = get_symbol_annotation(sym);
    other_def = var->node;
    analyze_error(node,
                  "redefinition of \"%s\",\n\t\talso defined in %s:%i:",
                  name,
                  other_def->file_name,
                  other_def->line_number);
  }
  
  return var;
}

struct variable *
add_constant(char *name, int value, tree *node)
{
  struct variable *var;

  var = add_global(name, name, node);
  var->is_constant = true;
  var->value = value;

  return var;
}

struct variable *
get_global(char *name)
{
  struct symbol *sym;
  struct variable *var = NULL;

  sym = get_symbol(state.global, name);
  if (sym != NULL) {
    var = get_symbol_annotation(sym);
  }

  return var;
}

/* add one symbol to the global table */

static struct variable *
add_global_symbol(char *name,
                  char *prefix,
                  tree *symbol,
                  enum node_storage class)
{
  char buffer[BUFSIZ];
  struct variable *var;

  if (prefix)
    sprintf(buffer, "%s_%s", prefix, name);
  else
    sprintf(buffer, "%s", name);

  var = add_global(name, buffer, symbol);
  if (var)
    var->class = class;

  return var;
}

/* convert a private procedure to public */

static void
make_proc_public(struct variable *var, tree *prot)
{
  tree *def;
  tree *head;
  tree *arg;
  struct variable *arg_var;

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
add_arg_symbols(tree *node, char *name, enum node_storage class)
{
  tree *head;
  tree *arg;
  struct variable *var;

  if (node->tag == node_proc) {
    head = PROC_HEAD(node);
  } else if (node->tag == node_proc_prot) {
    head = PROC_PROT_HEAD(node);
  } else if (node->tag == node_func) {
    head = FUNC_HEAD(node);
  } else if (node->tag == node_func_prot) {
    head = FUNC_PROT_HEAD(node);
  } else {
    print_node(node, 0);
    assert(0);
  }

  arg = HEAD_ARGS(head);

  while (arg) {
    assert(arg->tag == node_decl);
    var = add_global_symbol(DECL_NAME(arg), name, arg, class);
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

  sym = get_symbol(state.global, node->value.symbol);
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
  struct variable *arg_var;

  var = get_global(CALL_NAME(call));
  if (var) {
    def = var->node;
    if (def->tag == node_proc) {
      head = PROC_HEAD(var->node);
    } else if (def->tag == node_proc_prot) {
      head = PROC_PROT_HEAD(var->node);
    } else if (def->tag == node_func) {
      head = FUNC_HEAD(var->node);
    } else if (def->tag == node_func_prot) {
      head = FUNC_PROT_HEAD(var->node);
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

    /* select the local bank */
    if (var->class == storage_extern) {
      codegen_banksel(LOCAL_DATA_LABEL);
    }

    /* write the expression */
    codegen_expr(call_args);

    /* store the result in the memory mapped argument */
    arg_var = get_global(DECL_NAME(def_args));
    assert(arg_var != NULL);
    if (var->class == storage_extern) {
      codegen_put_mem(arg_var, true);
    } else {
      codegen_put_mem(arg_var, false);
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

void
analyze_statements(tree *statement)
{

  if (statement == NULL)
    return;

  while(statement) {
    switch(statement->tag) {
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
  state.global = push_symbol_table(state.global, 1);

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
  state.global = pop_symbol_table(state.global);

  return;
}

void
analyze_declarations(void)
{
  linked_list *list = data_memory;
  struct variable *var;

  while(list) {
    var = list->item;
    codegen_write_data(var->alias, var->class);
    list = list->next;
  }

}

void
analyze(void)
{
  tree *current;
  char *name;
  struct variable *var;
  enum node_storage class;

  /* FIXME: manage memory better or at least try */
  data_memory = NULL;

  /* open the output file */
  codegen_init_asm();

  /* add all procedures and data to the global symbol table */
  current = state.root;
  while (current) {
    switch (current->tag) {
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
    case node_decl_prot:
    case node_proc_prot:
    case node_func_prot:
      /* do nothing */
      break;
    default:
      assert(0);
    }
    current = current->next;
  }

  /* add all prototypes and externs to global symbol table */
  current = state.root;
  while (current) {
    switch (current->tag) {
    case node_decl:
    case node_proc:
    case node_func:
      /* do nothing */
      break;
    case node_decl_prot:
    case node_proc_prot:
    case node_func_prot:
      name = find_node_name(current);
      class = determine_storage(current);
      if (class == storage_public) {
        var = get_global(name);
        if (var) {
          if (current->tag == node_decl_prot) {
            var->class = storage_public;       
          } else {
            make_proc_public(var, current);
          }
        } else {
          analyze_error(current, "missing definition"); 
        }
      } else if (class == storage_extern) {
        add_global_symbol(name, NULL, current, storage_extern);
        if (current->tag != node_decl_prot) {
          add_arg_symbols(current, name, storage_extern);
        }
      } else {
        assert(0);
      }
      /* remove the prototype */
      if (current == state.root) {
        state.root = current->next;
      } else {
        current->prev->next = current->next;      
      }     
      break;
    default:
      assert(0);
    }
    current = current->next;
  }

  /* scan though each procedure and function */
  current = state.root;
  while (current) {
    switch (current->tag) {
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
      print_node(current, 0);
      assert(0);
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
