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
#include "symbol.h"
#include "analyze.h"
#include "codegen.h"
#include "scan.h"

#ifdef STDC_HEADERS
#include <stdarg.h>
#endif

/* prototypes */
void analyze_statements(tree *statement);

static gp_linked_list *data_memory;
static gp_linked_list *last_link;

static gp_boolean generating_function;
static gp_boolean found_return;
static enum size_tag scan_size;

#define RETURN_STACK_SIZE 8
static enum size_tag return_stack[RETURN_STACK_SIZE];
static int return_stack_index;  /* next available stack location */

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

void 
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
    assert(0);
  }

  arg = HEAD_ARGS(head);

  while (arg) {
    assert(arg->tag == node_arg);
    var = add_global_symbol(ARG_NAME(arg),
                            name,
                            arg,
                            sym_udata,
                            storage,
                            ARG_TYPE(arg));
    if (var->type->tag == type_array) {
      analyze_error(arg, "arguments can not be arrays");     
    }
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
can_evaluate(tree *p, gp_boolean gen_errors)
{
  struct variable *var;

  switch (p->tag) {
  case node_constant:
    return 1;
  case node_symbol:
    var = get_global(SYM_NAME(p));
    if (var) {
      if ((var->tag == sym_const) || (var->tag == sym_equ)) {
        return 1;
      } else {
        if (gen_errors) { 
          analyze_error(p, "symbol is not a constant (%s)", SYM_NAME(p));    
        }
        return 0;
      }
    } else {
      if (gen_errors) {
        analyze_error(p, "symbol not previously defined (%s)", SYM_NAME(p));    
      }
      return 0;
    }
  case node_unop:
    return can_evaluate(p->value.unop.p0, gen_errors);
  case node_binop:
    return can_evaluate(p->value.binop.p0, gen_errors) && 
           can_evaluate(p->value.binop.p1, gen_errors);
  case node_string:
    if (gen_errors) {
      analyze_error(p, "illegal argument (%s)", p->value.string);
    }
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
    var = get_global(SYM_NAME(p));
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

  if (p && can_evaluate(p, true)) {
    r = evaluate(p);
  } else {
    r = 0;
  }

  return r;
}

static int
test_symbol(tree *node, char *name, enum size_tag size)
{
  struct variable *var;

  var = get_global(name);
  if (var == NULL) {
    analyze_error(node, "unknown symbol \"%s\"", name);
    return 1;
  }

  /* If it is not an unchecked conversion, verify the types match */
  if ((size != size_unknown) && 
      (var->type) &&
      (prim_type(var->type) != size)) {
    analyze_error(node, "type mismatch in symbol \"%s\"", name);
    return 1;
  }

  /* Save the size for scanning expressions with an unknown type */
  if ((size == size_unknown) && (var->type)) {     
    enum size_tag temp_size = prim_type(var->type);

    if (temp_size != size_unknown) {
      scan_size = temp_size;
    }
  }

  return 0;
}

/* scan the tree and make sure all of the symbols are valid */

static int
scan_tree(tree *expr, enum size_tag size)
{

  if (expr == NULL)
    return 1;

  switch (expr->tag) {
  case node_arg:
    return test_symbol(expr, ARG_NAME(expr), size);
  case node_binop:
    return scan_tree(BINOP_LEFT(expr), size) ||
           scan_tree(BINOP_RIGHT(expr), size);
  case node_call:
    return test_symbol(expr, CALL_NAME(expr), size);
  case node_constant:
    return 0;
  case node_unop:
    return scan_tree(BINOP_RIGHT(expr), size);
  case node_symbol:
    return test_symbol(expr, SYM_NAME(expr), size);
  default:
    assert(0);
  }

  return 1;
}

int
analyze_check_array(tree *symbol, struct variable *var)
{
  int offset;

  offset = evaluate(SYM_OFST(symbol));
  if ((offset < var->type->start) || (offset > var->type->end)) {
    analyze_error(symbol, "array index %i is out of range", offset);
  }

  /* In memory, the arrays always start at 0. */
  offset = offset - var->type->start;

  /* scale the offset by the size of the array elements */
  offset = offset * type_size(var->type->prim);

  return offset;
}

static tree *
arg_to_symbol(tree *arg)
{
  tree *symbol;
  
  symbol = mk_symbol(ARG_NAME(arg), NULL);
  symbol->file_id = arg->file_id;
  symbol->line_number = arg->line_number;

  return symbol;
}

static void
push_return_stack(tree *func, enum size_tag size)
{
  if (return_stack_index < RETURN_STACK_SIZE) {
    return_stack[return_stack_index++] = size;
  } else {
    analyze_error(func, "too many nested function calls");
  }
}

static enum size_tag
pop_return_stack(tree *ret)
{
  return_stack_index--;
  
  if (return_stack_index < 0) {
    analyze_error(ret, "no function to return from");  
    return size_unknown;
  }

  return return_stack[return_stack_index];
}

void
analyze_call(tree *call, gp_boolean in_expr)
{
  struct variable *var;
  tree *def;
  tree *head;
  tree *def_args;
  tree *call_args;
  tree *assignment;

  var = get_global(CALL_NAME(call));
  if (var) {
    def = var->node;
    if (def->tag == node_proc) {
      head = PROC_HEAD(var->node);
      if (in_expr) {
        analyze_error(call, "procedures can not be called in expressions");
        return;
      }
    } else if (def->tag == node_func) {
      head = FUNC_HEAD(var->node);
      if (!in_expr) {
        analyze_error(call, "functions can only be called in expressions");
        return;
      }
      push_return_stack(call, prim_type(get_type(FUNC_RET(var->node))));
    } else {
      analyze_error(call, "name in the call is not a function or procedure");
      return;
    }
  } else {
    analyze_error(call, "unknown symbol \"%s\"", CALL_NAME(call));
    return;
  }

  call_args = CALL_ARGS(call);
  def_args = HEAD_ARGS(head);

  if (list_length(call_args) != list_length(def_args)) {
    analyze_error(call, "incorrect number of arguments in call");
    return;
  }

  /* write data into the in/inout of the function or procedure */
  while (call_args) {
    assert(def_args->tag == node_arg);

    if ((ARG_DIR(def_args) == dir_in) ||
        (ARG_DIR(def_args) == dir_inout)) {
      assignment = mk_binop(op_eq, arg_to_symbol(def_args), call_args);
      assignment->file_id = call_args->file_id;
      assignment->line_number = call_args->line_number;
      analyze_expr(assignment);
    }

    def_args = def_args->next;
    call_args = call_args->next;
  }

  codegen_call(var->alias, var->class);

  /* FIXME: any outs in the function call will over write the result in w */

  /* read data from the inout/out of the function or procedure */
  call_args = CALL_ARGS(call);
  def_args = HEAD_ARGS(head);
  while (call_args) {
    assert(def_args->tag == node_arg);

    if ((ARG_DIR(def_args) == dir_inout) ||
        (ARG_DIR(def_args) == dir_out)) {
      if (call_args->tag == node_symbol) {
        assignment = mk_binop(op_eq, call_args, def_args);
        assignment->file_id = call_args->file_id;
        assignment->line_number = call_args->line_number;
        analyze_expr(assignment);
      } else {
        analyze_error(call_args, "call argument must be a symbol");
      }
    }

    def_args = def_args->next;
    call_args = call_args->next;
  }

  return;
}

static int
analyze_test(tree *test, char *end_label)
{
  enum size_tag size;

  scan_size = size_unknown;

  /* Scan first to check for valid symbols and to determine what the
     default size is. */
  if (scan_tree(test, size_unknown)) {
    return 1;
  }
  
  size = scan_size;

  /* check the symbol sizes */
  if (scan_tree(test, size)) {
    return 1;
  }
 
  codegen_test(test, end_label, size);

  return 0;
}

void
analyze_cond(tree *cond, char *last_label)
{
  char *end_label = NULL;
  char *local_label = NULL;

  if (last_label) {
    local_label = last_label;
  } else {
    local_label = codegen_next_label();
  }

  /* else doesn't have a condition */
  if (COND_TEST(cond)) {
    end_label = codegen_next_label();
    if (analyze_test(COND_TEST(cond), end_label))
      return;
  }
  
  /* write the body of the code */
  analyze_statements(COND_BODY(cond));

  /* executed one clause so jump to the end */
  if (COND_NEXT(cond)) {
    codegen_jump(local_label);
  }
  
  /* if there is a condition generate a label at the end of the body */
  if (COND_TEST(cond)) {
    codegen_write_label(end_label);
    if (end_label)
      free(end_label);
  }
  
  /* generate next conditional block, if there is one */
  if (COND_NEXT(cond)) {
    analyze_cond(COND_NEXT(cond), local_label);
  }

  /* this is the top level cond block so write the last label */
  if (last_label == NULL) {
    codegen_write_label(local_label);
    if (local_label)
      free(local_label);
  }

  return;
}

void
analyze_loop(tree *loop)
{
  char *start_label = NULL;
  char *end_label = NULL;

  start_label = codegen_next_label();

  analyze_statements(LOOP_INIT(loop));

  /* place the label for looping */
  codegen_write_label(start_label);

  /* write the exit statements */
  if (LOOP_EXIT(loop)) {
    end_label = codegen_next_label();
    if (analyze_test(LOOP_EXIT(loop), end_label))
      return;
  }

  /* write the loop body */
  analyze_statements(LOOP_BODY(loop));

  /* write the increment statements*/
  analyze_statements(LOOP_INCR(loop));
  
  /* jump to the beginning of the loop */
  codegen_jump(start_label);

  /* place the label for exiting */
  if (LOOP_EXIT(loop)) {  
    codegen_write_label(end_label);
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
  enum size_tag size;
  gp_boolean constant_offset = true;
  int offset = 0;

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
  
  var = get_global(SYM_NAME(left));
  if (var == NULL) {
    analyze_error(left, "unknown symbol \"%s\"", SYM_NAME(left));  
    return;
  }

  /* fetch the symbols primative type */
  assert(var->type != NULL);
  size = prim_type(var->type);

  /* Verify all symbols in the expression are in the symbol table and
     that they are the same type as the lvalue. */
  if (scan_tree(right, size))
    return;

  /* calculate the offset for indirect accesses if necessary */
  if (SYM_OFST(left)) {
    if (var->type->tag == type_array) {
      if (can_evaluate(SYM_OFST(left), false)) {
        /* direct access with an offset */
        constant_offset = true;
        offset = analyze_check_array(left, var);
      } else {
        /* indirect access */
        constant_offset = false;
        codegen_indirect(var, SYM_OFST(left));
      }
    } else {
      analyze_error(left, "lvalue \"%s\" is not an array", SYM_NAME(left));
      return;
    }
  }

  /* write the expression */
  codegen_expr(right, size);

  /* put the result in memory */
  codegen_store(var, constant_offset, offset, SYM_OFST(left));

}

static void
analyze_return(tree *ret)
{
  enum size_tag return_size;
  
  found_return = true;
 
  if (generating_function) {
    return_size = pop_return_stack(ret);
    
    if (scan_tree(ret->value.ret, return_size))
      return;
    codegen_expr(ret->value.ret, return_size);
    codegen_write_asm("return");
  } else {
    analyze_error(ret, "returns can only appear in a function body");
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
      analyze_call(statement, false);
      break;
    case node_cond:
      analyze_cond(statement, NULL);  
      break;
    case node_loop:
      analyze_loop(statement);
      break; 
    case node_return:
      analyze_return(statement);
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
  found_return = false;
  
  if (is_func) {
    generating_function = true;
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
    if (DECL_KEY(decl) == key_var) {
      add_link(add_global_symbol(DECL_NAME(decl), 
                                 proc_name,
                                 decl,
                                 sym_udata,
                                 storage_private,
                                 DECL_TYPE(decl)));
    } else if (DECL_KEY(decl) == key_const) {
      if (DECL_INIT(decl)) {
        add_constant(DECL_NAME(decl),
                     maybe_evaluate(DECL_INIT(decl)),
                     decl,
                     DECL_TYPE(decl));
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
    codegen_write_asm("banksel %s", LOCAL_DATA_LABEL);
  }
  analyze_statements(statements);
  codegen_finish_proc(!generating_function);

  if ((is_func) && (!found_return)) {
    analyze_error(procedure, "function is missing return");
  }

  /* scan the local data, if a location is used add it to the list */
  if (state.optimize.trival_expressions) {

  }

  /* remove the local table */
  state.top = pop_symbol_table(state.top);
  generating_function = false;

  return;
}

void
analyze_declarations(void)
{
  gp_linked_list *list = data_memory;
  struct variable *var;

  while(list) {
    var = gp_list_get(list);
    assert(var != NULL);
    assert(var->type != NULL);
    codegen_write_data(var->alias, type_size(var->type), var->class);
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
        state.class = gp_processor_class(state.processor);
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
      state.processor_chosen = true;
      codegen_select(expr);
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
      } else if (strcasecmp(SYM_NAME(lhs), "code_section") == 0) {
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
      } else if (strcasecmp(SYM_NAME(lhs), "code_address") == 0) {
        if (rhs->tag != node_constant) {
          analyze_error(expr, "code address must be a constant");
        } else if (type == source_module) {            
          state.section.code_addr = rhs->value.constant;
          state.section.code_addr_valid = true;
        } else {
          analyze_error(expr, "udata section addresses can only be in modules");
        }
      } else if (strcasecmp(SYM_NAME(lhs), "udata_address") == 0) {
        if (rhs->tag != node_constant) {
          analyze_error(expr, "udata address must be a constant");
        } else if (type == source_module) {            
          state.section.udata_addr = rhs->value.constant;
          state.section.udata_addr_valid = true;
        } else {
          analyze_error(expr, "udata section addresses can only be in modules");
        }
      } else {
        analyze_error(expr, "unknown pragma \"%s\"", SYM_NAME(lhs));
      }
    }
    break;
  default:
    analyze_error(expr, "unknown pragma");
  }
  
  return;
}

/* add all of the types to the type table */

static void
analyze_type(tree *type)
{
  int enum_num;
  tree *list;
  int start;
  int end;

  if (TYPE_LIST(type)) {
    /* enumerated type */
    add_type_enum(TYPE_TYPE(type));
    enum_num = 0;
    list = TYPE_LIST(type);
    while (list) {
      if (list->tag == node_symbol) {
        /* add the constant to the global symbol table */
        add_constant(SYM_NAME(list), enum_num++, list, TYPE_TYPE(type));
      } else {
        analyze_error(list, "enumerated list must be symbols");
      }
      list = list->next;
    }
  } else if (TYPE_START(type)) {
    /* array type */
    if ((can_evaluate(TYPE_START(type), true)) && 
         can_evaluate(TYPE_END(type), true)) {
      start = evaluate(TYPE_START(type));
      end = evaluate(TYPE_END(type));
      add_type_array(TYPE_TYPE(type), start, end, TYPE_OF(type));
    }
  } else {
    /* alias */
    add_type_alias(TYPE_TYPE(type), TYPE_OF(type));
  }


}

/* FIXME: make sure public proc don't have bodies, but modules do */

static void
analyze_module(tree *file)
{
  tree *current;
  char *name;
  struct variable *var;

  current = FILE_BODY(file);
  while (current) {
    switch (current->tag) {
    case node_pragma:
      analyze_pragma(current->value.pragma, FILE_TYPE(file));
      break;
    case node_type:
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
    case node_type:
      analyze_type(current);
      break;
    case node_decl:
      if (DECL_KEY(current) == key_var) {
        var = add_global_symbol(DECL_NAME(current), 
                                NULL,
                                current, 
                                sym_udata,
                                storage_private,
                                DECL_TYPE(current));
        add_link(var);
      } else {
        if (DECL_INIT(current)) {
          add_constant(DECL_NAME(current),
                       maybe_evaluate(DECL_INIT(current)),
                       current,
                       DECL_TYPE(current));
        } else {
          analyze_error(current, "missing constant value");
        }
      }
      break;
    case node_proc:
      name = find_node_name(current);
      add_global_symbol(name,
                        NULL,
                        current,
                        sym_proc,
                        storage_private,
                        NULL);
      add_arg_symbols(current, name, storage_private);     
      break;
    case node_func:
      name = find_node_name(current);
      add_global_symbol(name,
                        NULL,
                        current,
                        sym_func,
                        storage_private,
                        NULL);
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
    case node_type:
      analyze_type(current);
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
    case node_type:
      break;
    case node_decl:
      name = find_node_name(current);
      if (FILE_TYPE(file) == source_public) {
        var = get_global(name);
        if (var) {
          var->class = storage_public;       
        } else {
          analyze_error(current, "missing definition for \"%s\"", name); 
        }
      } else if (FILE_TYPE(file) == source_with) {
        add_global_symbol(name,
                          NULL,
                          current,
                          sym_udata,
                          state.section.code_default,
                          DECL_TYPE(current));
      } else {
        assert(0);
      }
      break;
    case node_proc:
      name = find_node_name(current);
      if (FILE_TYPE(file) == source_public) {
        var = get_global(name);
        if (var) {
          make_proc_public(var, current);
        } else {
          analyze_error(current, "missing definition for \"%s\"", name); 
        }
      } else if (FILE_TYPE(file) == source_with) {
        add_global_symbol(name,
                          NULL,
                          current,
                          sym_proc,
                          state.section.code_default,
                          NULL);
        add_arg_symbols(current, name, state.section.udata_default);
      } else {
        assert(0);
      }
      break;
    case node_func:
      name = find_node_name(current);
      if (FILE_TYPE(file) == source_public) {
        var = get_global(name);
        if (var) {
          make_proc_public(var, current);
        } else {
          analyze_error(current, "missing definition for \"%s\"", name); 
        }
      } else if (FILE_TYPE(file) == source_with) {
        add_global_symbol(name,
                          NULL,
                          current,
                          sym_func,
                          state.section.code_default,
                          NULL);
        add_arg_symbols(current, name, state.section.udata_default);
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
    case node_type:
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
  return_stack_index = 0;
  generating_function = false;

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
