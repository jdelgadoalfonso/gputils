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

void
yyerror(char *message)
{

  gp_num_errors++;

  if (gp_quiet != 0)
    return;

  assert(message != NULL);
  
  if (state.src) {
    printf("%s:%d:%s\n", state.src->name, state.src->line_number, message);
  } else {
    printf("error: %s\n", message);
  }

  return;
}

int yylex(void);

/* FIXME: Clean this up.  We need to read the pragmas then modify the data
   so the mod doesn't start after the pragma statement. Maybe use the
   parse tree to implement the pragmas. */

static void
process_pragma(tree *expr)
{
  tree *lhs;
  tree *rhs;

  switch (expr->tag) {
  case node_binop:
    lhs = expr->value.binop.p0;
    rhs = expr->value.binop.p1;
    if ((expr->value.binop.op != op_eq) ||
        (lhs->tag != node_symbol)) {
      gp_error("unknown pragma");
    } else {
      if (strcasecmp(lhs->value.symbol, "processor") == 0) {
        if (rhs->tag != node_symbol) {
          gp_error("invalid processor name");        
        } else {
          if (state.processor_chosen == false) {
            select_processor(rhs->value.symbol);
          }        
        }
      } else if (strcasecmp(lhs->value.symbol, "code_section") == 0) {
        if (rhs->tag != node_symbol) {
          /* FIXME: change from symbol to string */
          gp_error("invalid code section name");
        } else {
          if (state.src->type == with) {            
            if ((state.section.code) && 
                (strcmp(rhs->value.symbol, state.section.code) == 0)) {
              state.section.code_default = storage_local;
            } else {
              state.section.code_default = storage_extern;
            }
          } else {
            if (state.src->type == source) {
              gp_warning("section pragma's should be in .pub files");
            }
            if (state.section.code) {
              gp_error("duplicate code section name");
            } else {
              state.section.code = rhs->value.symbol;
            }
          }        
        }
      } else if (strcasecmp(lhs->value.symbol, "udata_section") == 0) {
        if (rhs->tag != node_symbol) {
          gp_error("invalid udata section name");
        } else {
          if (state.src->type == with) {            
            if ((state.section.udata) &&
                (strcmp(rhs->value.symbol, state.section.udata) == 0)) {
              state.section.udata_default = storage_local;
            } else {
              state.section.udata_default = storage_extern;
            }
          } else {
            if (state.src->type == source) {
              gp_warning("section pragma's should be in .pub files");
            }
            if (state.section.code) {
              gp_error("duplicate udata section name");
            } else {
              state.section.udata = rhs->value.symbol;
            }
          }        
        }
      } else if (strcasecmp(lhs->value.symbol, "code_address") == 0) {
        if (rhs->tag != node_constant) {
          gp_error("invalid code address");
        } else if (state.src->type == source) {            
          state.section.code_addr = rhs->value.constant;
          state.section.code_addr_valid = true;
        } else {
          gp_error("udata section addresses can only be in .pal files");
        }
      } else if (strcasecmp(lhs->value.symbol, "udata_address") == 0) {
        if (rhs->tag != node_constant) {
          gp_error("invalid udata address");
        } else if (state.src->type == source) {            
          state.section.udata_addr = rhs->value.constant;
          state.section.udata_addr_valid = true;
        } else {
          gp_error("udata section addresses can only be in .pal files");
        }
      } else {
        gp_error("unknown pragma \"%s\"", lhs->value.symbol);
      }
    }
    break;
  default:
    gp_error("unknown pragma");
  }
  
  return;
}

%}

/* Bison declarations */

%union {
  int i;
  char *s;
  tree *t;
  enum node_type y;
  enum node_size z;
  enum node_op o;
}

/* keywords */
%token <i> BEGIN_KEY, END, FUNCTION_TOK, IS, PRAGMA, PROCEDURE, WITH
%token <i> IF, THEN, WHILE, ELSIF, ELSE, LOOP, RETURN
%token <i> VAR_TYPE, CONST_TYPE 
%token <i> BIT_SIZE, BYTE_SIZE 
%token <i> EXTERN_STORAGE, PUBLIC_STORAGE, PRIVATE_STORAGE, VOLATILE_STORAGE
%token <i> MODULE

/* general */
%token <s> ASM
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
%type <s> entity
%type <t> element_list
%type <t> element
%type <i> '+', '-', '*', '/', '%', '!', '~'
%type <t> expr, e0, e1, e2, e3, e4, e5, e6, e7, e8,
%type <o> e1op, e2op, e3op, e4op, e5op, e6op, e7op, e8op
%type <t> head
%type <t> arg_list
%type <t> arg
%type <t> body
%type <t> decl_block
%type <t> decl
%type <y> decl_type
%type <z> decl_size
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
	program entity
	| 
	program error '\n'
	;

entity:
	PRAGMA expr ';'
	{
	  process_pragma($2);
	}
	|
	WITH IDENT ';'
	{
	  open_src($2, with);
	}
	|
	MODULE IS END MODULE ';' { }
	|
	MODULE IS element_list END MODULE ';'
	{
	  add_entity(mk_module($3));
	}
	|
	PUBLIC_STORAGE IS END PUBLIC_STORAGE ';' { }
	|
	PUBLIC_STORAGE IS element_list END PUBLIC_STORAGE ';'
	{
	  add_entity(mk_public($3));
	}
	;

element_list:
	element
	{
	  $$ = node_list($1, NULL);
	}
	|
	element element_list
	{
	  $$ = node_list($1, $2);
	}
	;

element:
	decl
	{
	  $$ = $1;
        }
	|
	PROCEDURE head body PROCEDURE ';'
	{ 
          if (state.src->type == source) {
            $$ = mk_proc($2, storage_private, $3);
          } else {
            yyerror("procedures can only be defined in modules");
          }
     	}
	|
	PROCEDURE head ';'
	{ 
	  if (state.src->type == source_with) {
            $$ = mk_proc_prot($2, storage_public);
	  } else if (state.src->type == with) {
            $$ = mk_proc_prot($2, state.section.code_default);
          } else {
            yyerror("procedure declarations can only be in a public");
          }
     	}
        |
	FUNCTION_TOK head RETURN decl_size body FUNCTION_TOK ';'
	{ 
	  if (state.src->type == source) {
            $$ = mk_func($2, storage_private, $4, $5);
          } else {
            yyerror("functions can only be defined in modules");
          }
     	}
        |
	FUNCTION_TOK head RETURN decl_size ';'
	{ 
	  if (state.src->type == source_with) {
            $$ = mk_func_prot($2, storage_public, $4);
	  } else if (state.src->type == with) {
            $$ = mk_func_prot($2, state.section.code_default, $4);
          } else {
            yyerror("function declarations can only be in a public");
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
	  $$ = node_list($1, NULL);
	}
	|
	arg ',' arg_list
	{
	  $$ = node_list($1, $3);
	}
	;	

arg:
	decl_size IDENT
	{	  
	  if (state.src->type == source_with) {
	    $$ = mk_decl(type_var, $1, storage_public, $2, NULL);
	  } else if (state.src->type == with) {
	    $$ = mk_decl(type_var, $1, state.section.udata_default, $2, NULL);
	  } else {
	    /* should only get here from inside a function or procedure */
	    $$ = mk_decl(type_var, $1, storage_private, $2, NULL);
	  }
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
	  $$ = node_list($1, NULL);
	}
	|
        decl decl_block
	{
	  $$ = node_list($1, $2);
	}
	;

decl:
	decl_type decl_size IDENT ';'
	{ 
	  if (state.src->type == source_with) {
	    $$ = mk_decl_prot($1, $2, storage_public, $3);
	  } else if (state.src->type == with) {
	    $$ = mk_decl_prot($1, $2, state.section.udata_default, $3);
	  } else {
	    /* should only get here from inside a function or procedure */
	    $$ = mk_decl($1, $2, storage_private, $3, NULL);
	  }
        }
	|
	decl_type decl_size IDENT '=' expr ';'
	{ 
	  if (state.src->type == source_with) {
	    yyerror("initialized data can only appear in pal files");
	    $$ = mk_decl_prot($1, $2, storage_public, $3);
	  } else if (state.src->type == with) {
	    yyerror("initialized data can only appear in pal files");
            $$ = mk_decl_prot($1, $2, state.section.udata_default, $3);
	  } else {
	    $$ = mk_decl($1, $2, storage_private, $3, $5);
	  }
        }
	;

decl_type:
	CONST_TYPE
	{
	  $$ = type_const;
	}
	|
	VAR_TYPE
	{
	  $$ = type_var;
	}
	;

decl_size:
	BIT_SIZE
	{
	  $$ = size_bit;
	}
	|
	BYTE_SIZE
	{
	  $$ = size_byte;
	}
	;

statement_block:
	statement
	{
	  $$ = node_list($1, NULL);
	}
	|
	statement statement_block
	{
	  $$ = node_list($1, $2);
	}
	;

statement:
	ASM ';'
	{
	  $$ = mk_assembly($1);
	}
	|
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
	  $$ = node_list($1, NULL);
	}
	|
	expr ',' parameter_list
	{
	  $$ = node_list($1, $3);
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

e8op:	'=' { $$ = op_eq; };

e7:
	e6
	|
	e7 e7op e6
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e7op:	  LOGICAL_AND { $$ = op_land; }
	| LOGICAL_OR  { $$ = op_lor; };

e6:
	e5
	|
	e6 e6op e5
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e6op:	  '&' { $$ = op_and; }
	| '|' { $$ = op_or; }
	| '^' { $$ = op_xor; };

e5:
	e4
	|
	e5 e5op e4
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e5op:	  '<'           { $$ = op_lt; }
	| '>'           { $$ = op_gt; }
	| EQUAL         { $$ = op_eq; }
	| NOT_EQUAL     { $$ = op_ne; }
	| GREATER_EQUAL { $$ = op_gte; }
	| LESS_EQUAL    { $$ = op_lte; };

e4:
	e3
	|
	e4 e4op e3
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e4op:	  LSH { $$ = op_lsh; }
	| RSH { $$ = op_rsh; };

e3:
	e2
	|
	e3 e3op e2
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e3op:     '+' { $$ = op_add; }
	| '-' { $$ = op_sub; };

e2:
	e1
	|
	e2 e2op e1
	{
	  $$ = mk_binop($2, $1, $3);
	}
	;

e2op:     '*' { $$ = op_mult; }
	| '/' { $$ = op_div; }
	| '%' { $$ = op_mod; };

e1:
	e0
	|
	e1op e0
	{
	  $$ = mk_unop($1, $2);
	}
	;

e1op:	  '-' { $$ = op_neg; }
	| '!' { $$ = op_not; }
	| '~' { $$ = op_com; }
	| '+' { $$ = op_add; };

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
