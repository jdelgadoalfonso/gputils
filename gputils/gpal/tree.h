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

#ifndef __TREE_H__
#define __TREE_H__

enum node_tag { 
  node_unknown,
  node_body,
  node_binop,
  node_call,
  node_constant, 
  node_cond,
  node_decl,
  node_func,  
  node_head,  
  node_list,
  node_loop,
  node_proc,
  node_string,
  node_symbol, 
  node_unop
};

typedef struct node_struct tree;

typedef struct node_struct {
  enum node_tag tag;
  union {
    struct {
      tree *decl;
      tree *statements;
    } body;
    struct {
      int op;
      tree *p0, *p1;
    } binop;
    struct {
      char *name;
      tree *args;
    } call;
    int constant;
    struct {
      /* conditional (if) */
      tree *cond;
      tree *body;
      tree *next; /* else or elsif */
    } cond;    
    struct {
      int type;
      int size;
      int storage;
      tree *expr;
    } decl;
    struct {
      tree *head;
      int storage;
      int ret;
      tree *body;
    } func;
    struct {
      char *name;
      tree *args;
    } head;
    struct {
      tree *head, *tail;
    } list;
    struct {
      /* for, while, ... */
      tree *init;   /* initalization code */
      tree *exit;   /* exit loop if not true */
      tree *incr;   /* code executed at the end of each pass (for loops) */
      tree *body;
    } loop;
    struct {
      tree *head;
      int storage;
      tree *body;
    } proc;
    char *string;
    char *symbol;
    struct {
      int op;
      tree *p0;
    } unop;
  } value;

  /* debug information */
  char *file_name;  
  int line_number;

} node;

#define HEAD(L) (L)->value.list.head
#define TAIL(L) (L)->value.list.tail

tree *mk_node(enum node_tag tag);
tree *mk_body(tree *decl, tree *statements);
tree *mk_binop(int op, tree *p0, tree *p1);
tree *mk_call(char *name, tree *args);
tree *mk_constant(int value);
tree *mk_cond(tree *cond, tree *body, tree *next);
tree *mk_decl(int type, int size, int storage, tree *expr);
tree *mk_func(tree *head, int storage, int ret, tree *body);
tree *mk_head(char *name, tree *args);
tree *mk_list(tree *head, tree *tail);
tree *mk_loop(tree *init, tree *exit, tree *incr, tree *body);
tree *mk_proc(tree *head, int storage, tree *body);
tree *mk_string(char *value);
tree *mk_symbol(char *value);
tree *mk_unop(int op, tree *p0);

void print_node(tree *node, int level);

#endif
