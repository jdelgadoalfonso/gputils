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
  unsigned int num_block_freed = 0;
  unsigned int num_node_freed = 0;

  while(head_block) {
   prev = head_block;
   head_block = head_block->next;
   free(prev);
   num_block_freed++;
  }

  num_node_freed = (num_block_freed * NODES_PER_BLOCK) + next_node;

  gp_debug("freed %i tree nodes (%i bytes of memory)", 
           num_node_freed,
           num_node_freed * sizeof(tree));

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
  new->file_id = state.src->file_id;
  new->line_number = state.src->line_number;

  return new;
}

tree *
mk_assembly(char *assembly)
{
  tree *new = mk_node(node_assembly);
  new->value.assembly = assembly;
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
mk_decl(enum node_type type,
        enum node_size size,
        char *name,
        tree *init)
{
  tree *new = mk_node(node_decl);
  new->value.decl.type = type;
  new->value.decl.size = size;
  new->value.decl.name = name;
  new->value.decl.init = init;
  
  return new;
}

tree *
mk_file(tree *body, enum source_type type)
{
  tree *new = mk_node(node_file);
  new->value.file.body = body;
  new->value.file.type = type;
  
  return new;
}

tree *
mk_func(tree *head, enum node_size ret, tree *body)
{
  tree *new = mk_node(node_func);
  new->value.func.head = head;
  new->value.func.ret = ret;
  new->value.func.body = body;
 
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
mk_pragma(tree *pragma)
{
  tree *new = mk_node(node_pragma);
  new->value.pragma = pragma;
  
  return new;
}

tree *
mk_proc(tree *head, tree *body)
{
  tree *new = mk_node(node_proc);
  new->value.proc.head = head;
  new->value.proc.body = body;
  
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

tree *
node_list(tree *head, tree *tail)
{
  head->next = tail;
  if (tail)
    tail->prev = head;

  return head;
}

char *
find_node_name(tree *node)
{
  tree *head;
  char *name = NULL;

  switch(node->tag) {
  case node_decl:
    name = DECL_NAME(node);
    break;
  case node_func:
    head = FUNC_HEAD(node);
    name = HEAD_NAME(head);
    break;
  case node_proc:
    head = PROC_HEAD(node);
    name = HEAD_NAME(head);
    break;
  default:
    assert(0);
  }   

  return name;
}

tree *
find_node(tree *search, char *name, enum node_tag tag)
{
  tree *found = NULL;
  char *node_name;

  while (search != NULL) {
    if (search->tag == tag) {
      node_name = find_node_name(search);
      if (strcasecmp(node_name, name) == 0) {
        found = search;
        break;
      }
    }
    search = search->next;
  }

  return found;
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
    if (BODY_DECL(node) != NULL) {
      print_space(level);
      printf("declarations\n");
      print_node(BODY_DECL(node), level);
    }
    if (BODY_STATEMENTS(node) != NULL) {
      print_space(level);
      printf("statements\n");
      print_node(BODY_STATEMENTS(node), level);
    }
    break;
  case node_binop:
    print_space(level);
    printf("node_binop %i \n", BINOP_OP(node));
    print_space(level);
    printf("arg 1\n");
    print_node(BINOP_LEFT(node), level);
    print_space(level);
    printf("arg 2\n");
    print_node(BINOP_RIGHT(node), level);
    break;
  case node_call:
    print_space(level);
    printf("node_call %s\n", CALL_NAME(node));
    break;
  case node_constant:
    print_space(level);
    printf("node_constant = %i\n", node->value.constant);
    break;
  case node_cond:
    print_space(level);
    printf("node_cond\n");
    if (COND_TEST(node) != NULL) {
      print_space(level);
      printf("condition\n");
      print_node(COND_TEST(node), level);
    }
    if (COND_BODY(node) != NULL) {
      print_space(level);
      printf("body\n");
      print_node(COND_BODY(node), level);
    }
    if (COND_NEXT(node) != NULL) {
      print_space(level);
      printf("next\n");
      print_node(COND_NEXT(node), level);
    }
    break;
  case node_decl:
    print_space(level);
    printf("node_decl type=%i, size=%i, name=%s\n",
            DECL_TYPE(node),
            DECL_SIZE(node),
            DECL_NAME(node));
    if (DECL_INIT(node)) {
      print_node(DECL_INIT(node), level);
    }
    break;
  case node_file:
    print_space(level);
    printf("node_file\n");
    if (FILE_BODY(node) != NULL)  
      print_node(FILE_BODY(node), level);
    break;
  case node_func:
    print_space(level);
    printf("node_func that returns %i\n", node->value.func.ret);
    if (FUNC_HEAD(node) != NULL)  
      print_node(FUNC_HEAD(node), level);
    if (FUNC_BODY(node) != NULL)
      print_node(FUNC_BODY(node), level);
    break;
  case node_head:
    print_space(level);
    printf("node_head %s\n", HEAD_NAME(node));
    if (HEAD_ARGS(node) != NULL) {
      print_space(level);
      printf("arguments\n");
      print_node(HEAD_ARGS(node), level);
    }
    break;
  case node_loop:
    print_space(level);
    printf("node_loop\n");
    if (LOOP_INIT(node) != NULL) {
      print_space(level);
      printf("init\n");
      print_node(LOOP_INIT(node), level);
    }
    if (LOOP_EXIT(node) != NULL) {
      print_space(level);
      printf("exit\n");
      print_node(LOOP_EXIT(node), level);
    }
    if (LOOP_INCR(node) != NULL) {
      print_space(level);
      printf("increment\n");
      print_node(LOOP_INCR(node), level);
    }
    if (LOOP_BODY(node) != NULL) {
      print_space(level);
      printf("body\n");
      print_node(LOOP_BODY(node), level);
    }
    break;
  case node_proc:
    print_space(level);
    printf("node_proc\n");
    if (PROC_HEAD(node) != NULL)  
      print_node(PROC_HEAD(node), level);
    if (PROC_BODY(node) != NULL)
      print_node(PROC_BODY(node), level);
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
    printf("unop %i \n", UNOP_OP(node));
    print_space(level);
    printf("arg\n");
    print_node(UNOP_ARG(node), level);
  default:
    assert(0);
  }

}


