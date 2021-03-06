/* parse tree
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

#define NODES_PER_BLOCK 1000

typedef struct node_block_struct tree_block;

typedef struct node_block_struct {
  tree nodes[NODES_PER_BLOCK];
  tree_block *next;
} node_block;

static tree_block *head_block;
static tree_block *current_block;
static unsigned int next_node;

static tree_block *
create_block(void)
{
  tree_block *new;
  
  new = malloc(sizeof(tree_block));
  new->next = NULL;

  return new;
}

void
init_nodes(void)
{
  current_block = create_block();
  head_block = current_block;
  next_node = 0;
}

void
free_nodes(void)
{
  tree_block *prev;
  unsigned int num_freed = 0;

  while(head_block) {
   prev = head_block;
   head_block = head_block->next;
   free(prev);
   num_freed++;
  }

  gp_debug("freed %i block(s) of tree nodes (%i bytes of memory)", 
           num_freed,
           num_freed * sizeof(tree_block));

  gp_debug("used %i nodes of the current block", next_node);

}

tree *
mk_node(enum node_tag tag)
{
  tree *new;

  if (next_node >= NODES_PER_BLOCK) {
    current_block->next = create_block();
    current_block = current_block->next;  
    next_node = 0;
  }
  
  new = &current_block->nodes[next_node++];
  new->tag = tag;
  new->prev = NULL;
  new->next = NULL;
  new->file_name = state.src->name;
  new->line_number = state.src->line_number;

  return new;
}

tree *
mk_body(tree *decl, tree *statements)
{
  tree *new = mk_node(node_body);
  new->value.body.decl = decl;
  new->value.body.statements = statements;
  return new;
}

tree *
mk_binop(enum node_op op, tree *p0, tree *p1)
{
  tree *new = mk_node(node_binop);
  new->value.binop.op = op;
  new->value.binop.p0 = p0;
  new->value.binop.p1 = p1;
  return new;
}

tree *
mk_call(char *name, tree *args)
{
  tree *new = mk_node(node_call);
  new->value.call.name = strdup(name);
  new->value.call.args = args;
  return new;
}

tree *
mk_constant(int value)
{
  tree *new = mk_node(node_constant);
  new->value.constant = value;
  return new;
}

tree *
mk_cond(tree *cond, tree *body, tree *next)
{
  tree *new = mk_node(node_cond);
  new->value.cond.cond = cond;
  new->value.cond.body = body;
  new->value.cond.next = next;
  
  return new;
}

tree *
mk_decl(enum node_type type, enum node_size size, enum node_storage storage, tree *expr)
{
  tree *new = mk_node(node_decl);
  new->value.decl.type = type;
  new->value.decl.size = size;
  new->value.decl.storage = storage;
  new->value.decl.expr = expr;
  
  return new;
}

tree *
mk_func(tree *head, enum node_storage storage, enum node_size ret, tree *body)
{
  tree *new = mk_node(node_func);
  new->value.func.head = head;
  new->value.func.storage = storage;
  new->value.func.ret = ret;
  new->value.func.body = body;
 
  return new;
}

tree *
mk_func_prot(tree *head, enum node_storage storage, enum node_size ret)
{
  tree *new = mk_node(node_func);
  new->value.func_prot.head = head;
  new->value.func_prot.storage = storage;
  new->value.func_prot.ret = ret;
 
  return new;
}

tree *
mk_head(char *name, tree *args)
{
  tree *new = mk_node(node_head);
  new->value.head.name = strdup(name);
  new->value.head.args = args;
  return new;
}

tree *
mk_list(tree *head, tree *tail)
{
  tree *new = mk_node(node_list);
  new->value.list.head = head;
  new->value.list.tail = tail;
  return new;
}

tree *
mk_loop(tree *init, tree *exit, tree *incr, tree *body)
{
  tree *new = mk_node(node_loop);
  new->value.loop.init = init;
  new->value.loop.exit = exit;  
  new->value.loop.incr = incr;
  new->value.loop.body = body;
  
  return new;
}

tree *
mk_proc(tree *head, enum node_storage storage, tree *body)
{
  tree *new = mk_node(node_proc);
  new->value.proc.head = head;
  new->value.proc.storage = storage;
  new->value.proc.body = body;
  
  return new;
}

tree *
mk_proc_prot(tree *head, enum node_storage storage)
{
  tree *new = mk_node(node_proc);
  new->value.proc_prot.head = head;
  new->value.proc_prot.storage = storage;
  
  return new;
}

tree *
mk_string(char *value)
{
  tree *new = mk_node(node_string);
  new->value.string = value;
  return new;
}

tree *
mk_symbol(char *value)
{
  tree *new = mk_node(node_symbol);
  new->value.symbol = strdup(value);
  return new;
}

tree *
mk_unop(enum node_op op, tree *p0)
{
  tree *new = mk_node(node_unop);
  new->value.unop.op = op;
  new->value.unop.p0 = p0;
  return new;
}

void
print_space(int number)
{
  int i;

  for (i = 0; i < number; i++)
    printf(" ");
}

void
print_node(tree *node, int level)
{

  /* indent this node */
  level += 2;

  switch(node->tag) {
  case node_unknown:
    print_space(level);
    printf("node_unknown\n");
    break;
  case node_body:
    print_space(level);
    printf("node_body\n");
    if (node->value.body.decl != NULL) {
      print_space(level);
      printf("declarations\n");
      print_node(node->value.body.decl, level);
    }
    if (node->value.body.statements != NULL) {
      print_space(level);
      printf("statements\n");
      print_node(node->value.body.statements, level);
    }
    break;
  case node_binop:
    print_space(level);
    printf("node_binop %i \n", node->value.binop.op);
    print_space(level);
    printf("arg 1\n");
    print_node(node->value.binop.p0, level);
    print_space(level);
    printf("arg 2\n");
    print_node(node->value.binop.p1, level);
    break;
  case node_call:
    print_space(level);
    printf("node_call %s\n", node->value.call.name);
    break;
  case node_constant:
    print_space(level);
    printf("node_constant = %i\n", node->value.constant);
    break;
  case node_cond:
    print_space(level);
    printf("node_cond\n");
    if (node->value.cond.cond != NULL) {
      print_space(level);
      printf("condition\n");
      print_node(node->value.cond.cond, level);
    }
    if (node->value.cond.body != NULL) {
      print_space(level);
      printf("body\n");
      print_node(node->value.cond.body, level);
    }
    if (node->value.cond.next != NULL) {
      print_space(level);
      printf("next\n");
      print_node(node->value.cond.next, level);
    }
    break;
  case node_decl:
    print_space(level);
    printf("node_decl type=%i, size=%i, storage=%i\n",
            node->value.decl.type,
            node->value.decl.size,
            node->value.decl.storage);
    print_node(node->value.decl.expr, level);
    break;
  case node_func:
    print_space(level);
    printf("node_func that returns %i\n", node->value.func.ret);
    if (node->value.proc.head != NULL)  
      print_node(node->value.proc.head, level);
    if (node->value.cond.body != NULL)
      print_node(node->value.cond.body, level);
    break;
  case node_func_prot:
    print_space(level);
    printf("node_func_prot that returns %i\n", node->value.func.ret);
    if (node->value.proc_prot.head != NULL)  
      print_node(node->value.proc_prot.head, level);
    break;
  case node_head:
    print_space(level);
    printf("node_head %s\n", node->value.head.name);
    if (node->value.head.args != NULL) {
      print_space(level);
      printf("arguments\n");
      print_node(node->value.proc.head, level);
    }
    break;
  case node_list:
    print_space(level);
    printf("node_list\n");
    if (node->value.list.head != NULL) {
      print_space(level);
      printf("head\n");
      print_node(node->value.list.head, level);
    }
    if (node->value.list.tail != NULL) {
      print_space(level);
      printf("tail\n");
      print_node(node->value.list.tail, level);
    }
    break;
  case node_loop:
    print_space(level);
    printf("node_loop\n");
    if (node->value.loop.init != NULL) {
      print_space(level);
      printf("init\n");
      print_node(node->value.loop.init, level);
    }
    if (node->value.loop.exit != NULL) {
      print_space(level);
      printf("exit\n");
      print_node(node->value.loop.exit, level);
    }
    if (node->value.loop.incr != NULL) {
      print_space(level);
      printf("increment\n");
      print_node(node->value.loop.incr, level);
    }
    if (node->value.loop.body != NULL) {
      print_space(level);
      printf("body\n");
      print_node(node->value.loop.body, level);
    }
    break;
  case node_proc:
    print_space(level);
    printf("node_proc\n");
    if (node->value.proc.head != NULL)  
      print_node(node->value.proc.head, level);
    if (node->value.cond.body != NULL)
      print_node(node->value.cond.body, level);
    break;
  case node_proc_prot:
    print_space(level);
    printf("node_proc_prot\n");
    if (node->value.proc_prot.head != NULL)  
      print_node(node->value.proc_prot.head, level);
    break;
  case node_string:
    print_space(level);
    printf("node_string %s\n", node->value.string);
    break;
  case node_symbol:
    print_space(level);
    printf("node_symbol %s\n", node->value.symbol);
    break;
  case node_unop:
    print_space(level);
    printf("unop %i \n", node->value.unop.op);
    print_space(level);
    printf("arg\n");
    print_node(node->value.unop.p0, level);
  default:
    assert(0);
  }

}


