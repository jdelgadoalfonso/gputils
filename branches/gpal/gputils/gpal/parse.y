%{
/* Parser
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
#include "scan.h"

void yyerror(char *message)
{
  gp_error("%s:%d:%s",
           state.src->name,
	   state.src->line_number,
	   message);
}

int yylex(void);

%}

/* Bison declarations */

%union {
  int i;
  char *s;
  tree *t;
}

/* keywords */
%token <i> BEGIN_KEY, END, FUNCTION_TOK, IS, PRAGMA, PROCEDURE, WITH
%token <i> IF, THEN, WHILE, ELSIF, ELSE, LOOP, RETURN
%token <i> VAR_TYPE, CONST_TYPE 
%token <i> BIT_SIZE, BYTE_SIZE 
%token <i> EXTERN_STORAGE, PUBLIC_STORAGE, PRIVATE_STORAGE, VOLATILE_STORAGE

/* general */
%token <s> IDENT
%token <i> NUMBER
%token <s> STRING
%token <i> ';'

/* operators */
%token <i> LSH, RSH
%token <i> GREATER_EQUAL, LESS_EQUAL, EQUAL, NOT_EQUAL, '<', '>'
%token <i> '&', '|', '^'
%token <i> LOGICAL_AND, LOGICAL_OR
%token <i> '='

/* types */
%type <s> line
%type <i> '+', '-', '*', '/', '%', '!', '~'
%type <t> expr, e0, e1, e2, e3, e4, e5, e6, e7, e8,
%type <i> e1op, e2op, e3op, e4op, e5op, e6op, e7op, e8op
%type <t> head
%type <t> arg_list
%type <t> arg
%type <t> body
%type <t> decl_block
%type <t> decl
%type <i> decl_type
%type <i> decl_size
%type <t> statement_block
%type <t> statement
%type <t> if_body
%type <t> loop_statement
%type <t> parameter_list

%start program

%%
/* Grammar rules */

program:
	/* can be nothing */
	|
	program line
	| 
	program error '\n'
	;

line:
	PRAGMA expr ';'
	{
	  process_pragma($2);
	}
	|
	WITH IDENT ';'
	{
	  open_src($2, true, false);
	}
	|
	decl
	{
	  if (state.src->type == source_with) {
            $1->value.decl.storage = PUBLIC_STORAGE;
	  } else if (state.src->type == with) {
            $1->value.decl.storage = EXTERN_STORAGE;
          }
	  add_entity($1);
        }
	|
	PROCEDURE head body PROCEDURE ';'
	{ 
          if (state.src->type == source) {
            add_entity(mk_proc($2, PRIVATE_STORAGE, $3));
          } else {
            gp_error("procedures can only be defined in .pal files");
          }
     	}
	|
	PROCEDURE head ';'
	{ 
	  if (state.src->type == source_with) {
            add_entity(mk_proc($2, PUBLIC_STORAGE, NULL));
	  } else if (state.src->type == with) {
            add_entity(mk_proc($2, EXTERN_STORAGE, NULL));
          } else {
            gp_error("procedure declarations can only be in .pub files");
          }
     	}
        |
	FUNCTION_TOK head RETURN decl_size body FUNCTION_TOK ';'
	{ 
	  if (state.src->type == source) {
            add_entity(mk_func($2, PRIVATE_STORAGE, $4, $5));
          } else {
            gp_error("functions can only be defined in .pal files");
          }
     	}
        |
	FUNCTION_TOK head RETURN decl_size ';'
	{ 
	  if (state.src->type == source_with) {
            add_entity(mk_func($2, PUBLIC_STORAGE, $4, NULL));
	  } else if (state.src->type == with) {
            add_entity(mk_func($2, EXTERN_STORAGE, $4, NULL));
          } else {
            gp_error("function declarations can only be in .pub files");
          }
     	}
	;

head:
	IDENT
	{
 	  $$ = mk_head($1, NULL);
     	}
	|
	IDENT '(' arg_list ')'
	{
 	  $$ = mk_head($1, $3);
     	}
        ;

arg_list:
	arg
	{
	  $$ = mk_list($1, NULL);
	}
	|
	arg ',' arg_list
	{
	  $$ = mk_list($1, $3);
	}
	;	

arg:
	decl_size IDENT
	{	  
	  $$ = mk_decl(0, $1, 0, mk_symbol($2));
        }
	;

body:
	IS decl_block BEGIN_KEY statement_block END
	{
 	  $$ = mk_body($2, $4);
     	}
	|
	IS BEGIN_KEY statement_block END
	{
 	  $$ = mk_body(NULL, $3);
     	}
        ;

decl_block:
	decl
	{
	  $$ = mk_list($1, NULL);
	}
	|
        decl decl_block
	{
	  $$ = mk_list($1, $2);
	}
	;

decl:
	decl_type decl_size parameter_list ';'
	{ 
	  $$ = mk_decl($1, $2, PRIVATE_STORAGE, $3);
        }
	;

decl_type:
	CONST_TYPE
	{
	  $$ = CONST_TYPE;
	}
	|
	VAR_TYPE
	{
	  $$ = VAR_TYPE;
	}
	;

decl_size:
	BIT_SIZE
	{
	  $$ = BIT_SIZE;
	}
	|
	BYTE_SIZE
	{
	  $$ = BYTE_SIZE;
	}
	;

statement_block:
	statement
	{
	  $$ = mk_list($1, NULL);
	}
	|
	statement statement_block
	{
	  $$ = mk_list($1, $2);
	}
	;

statement:
	IF expr THEN statement_block END IF ';'
	{
	  $$ = mk_cond($2, $4, NULL);
	}
	|
	IF expr THEN statement_block if_body END IF ';'
	{
	  $$ = mk_cond($2, $4, $5);
	}
	|
	WHILE expr loop_statement
	{
	  $$= mk_loop(NULL, $2, NULL, $3);	
	}
	|
	loop_statement
	{
	  $$= mk_loop(NULL, NULL, NULL, $1);
	}
	|
	expr ';'
	{
	  $$ = $1;
	}
	;

if_body:
	ELSIF expr THEN statement_block
	{
	  /* last statement is elsif */
	  $$ = mk_cond($2, $4, NULL);
	}
	|
	ELSIF expr THEN statement_block if_body
	{
	  $$ = mk_cond($2, $4, $5);
	}
	|
	ELSE statement_block
	{
	  /* last statement is else */
	  $$ = mk_cond(NULL, $2, NULL);
	}	
	;

loop_statement:
	LOOP statement_block END LOOP ';'
	{
	  $$ = $2;
	}
	;

parameter_list:
	expr
	{
	  $$ = mk_list($1, NULL);
	}
	|
	expr ',' parameter_list
	{
	  $$ = mk_list($1, $3);
	}
	;

expr:
	e8
	|
	STRING
        {
	  $$ = mk_string($1);
        }
	;

e8:
	e7
	|
	e8 e8op e7
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e8op:	'=' ;

e7:
	e6
	|
	e7 e7op e6
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e7op:	LOGICAL_AND | LOGICAL_OR;

e6:
	e5
	|
	e6 e6op e5
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e6op:	'&' | '|' | '^' ;

e5:
	e4
	|
	e5 e5op e4
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e5op:	'<' | '>' | EQUAL | NOT_EQUAL | GREATER_EQUAL | LESS_EQUAL ;

e4:
	e3
	|
	e4 e4op e3
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e4op:	LSH | RSH ;

e3:
	e2
	|
	e3 e3op e2
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e3op:   '+' | '-' ;

e2:
	e1
	|
	e2 e2op e1
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e2op:   '*' | '/' | '%';

e1:
	e0
	|
	e1op e0
	{
	  $$ = mk_unop($1, $2);
	}
	;

e1op:	'-' | '!' | '~' | '+';

e0:
	IDENT
        {
	  $$ = mk_symbol($1);
        }
	|
	IDENT '(' ')'
	{
	  /* function or procedure call */
	  $$ = mk_call($1, NULL);
	}
	|
	IDENT '(' parameter_list ')'
	{
	  /* function or procedure call with arguments */
	  $$ = mk_call($1, $3);
	}
	|
	NUMBER
	{
	  $$ = mk_constant($1);
	}
	|
	'(' expr ')'
	{
	  $$ = $2;
	}
	;

%%
