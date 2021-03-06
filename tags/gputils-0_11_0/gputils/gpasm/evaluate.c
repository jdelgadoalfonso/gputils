/* evaluates variables
   Copyright (C) 2002, 2003
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
#include "gpasm.h"
#include "evaluate.h"
#include "directive.h"
#include "gperror.h"
#include "parse.h"
#include "coff.h"

extern int _16bit_core;

int enforce_arity(int arity, int must_be)
{
  if (arity == must_be)
    return 1;
  else {
    if (arity < must_be) {
      gperror(GPE_MISSING_ARGU, NULL);
    } else {
      gperror(GPE_TOO_MANY_ARGU, NULL);
    }
    return 0;
  }
}

int enforce_simple(struct pnode *p)
{
  if (p->tag == symbol) {
    return 1;
  } else {
    gperror(GPE_ILLEGAL_ARGU, NULL);
    return 0;
  }
}

int list_length(struct pnode *L)
{
  if (L == NULL) {
    return 0;
  } else {
    return 1 + list_length(TAIL(L));
  }
}

int can_evaluate_concatenation(struct pnode *p)
{
  char buf[BUFSIZ];

  switch (p->tag) {
  case constant:
    return 1;
  case symbol:
    return 1;
  case unop:
    return can_evaluate_concatenation(p->value.unop.p0);
  case binop:
    return can_evaluate_concatenation(p->value.binop.p0) 
           && can_evaluate_concatenation(p->value.binop.p1);
  case string:
    sprintf(buf, "Illegal argument (%s).", p->value.string);
    gperror(GPE_ILLEGAL_ARGU, buf);
    return 0;
  default:
    assert(0);
  }

  return 0;
}

int can_evaluate(struct pnode *p)
{
  char buf[BUFSIZ];

  if ((p->tag == binop) && (p->value.binop.op == CONCAT)) {
    return can_evaluate_concatenation(p);
  }
  switch (p->tag) {
  case constant:
    return 1;
  case symbol:
    {
      struct symbol *s;

      /* '$' means current org, which we can always evaluate */
      if (strcmp(p->value.symbol, "$") == 0) {
	return 1;
      } else {
        struct variable *var = NULL;

	/* Otherwise look it up */
	s = get_symbol(state.stTop, p->value.symbol);

        if (s == NULL) {
          sprintf(buf, "Symbol not previously defined (%s).", p->value.symbol);
          gperror(GPE_NOSYM, buf);    
	} else {
          var = get_symbol_annotation(s);

          if (var == NULL) {
            sprintf(buf, "Symbol not assigned a value (%s).", p->value.symbol);
            gpwarning(GPW_UNKNOWN, buf);    
          }
        }  
 
	return ((s != NULL) && (var != NULL));
      }
    }
  case unop:
    return can_evaluate(p->value.unop.p0);
  case binop:
    return can_evaluate(p->value.binop.p0) && can_evaluate(p->value.binop.p1);
  case string:
    sprintf(buf, "Illegal argument (%s).", p->value.string);
    gperror(GPE_ILLEGAL_ARGU, buf);
    return 0;
  default:
    assert(0);
  }

  return 0;
}

char *evaluate_concatenation(struct pnode *p)
{
  switch (p->tag) {
  case symbol:
    return p->value.symbol;
  case binop:
    assert(p->value.binop.op == CONCAT);
    {
      char *s[2], *new;

      s[0] = evaluate_concatenation(p->value.binop.p0);
      s[1] = evaluate_concatenation(p->value.binop.p1);
      new = malloc(strlen(s[0]) + 1 + strlen(s[1]) + 1);
      strcpy(new, s[0]);
      strcat(new, s[1]);
      return new;
    }
  case unop:
    assert(p->value.unop.op == VAR);
    {
      char buf[80];
      sprintf(buf, "%d", maybe_evaluate(p->value.unop.p0));
      return (strdup(buf));
    }
  default:
    assert(0);
  }

  return NULL;
}

gpasmVal evaluate(struct pnode *p)
{
  struct variable *var;
  gpasmVal p0, p1;

  if (((p->tag == binop) && (p->value.binop.op == CONCAT)) ||
      ((p->tag == unop) && (p->value.unop.op == VAR))) {
    char *string = evaluate_concatenation(p);
    struct symbol *s;

    s = get_symbol(state.stTop, string);
    if (s == NULL) {
      char buf[BUFSIZ];
      sprintf(buf, "Symbol not previously defined (%s).", string);
      gperror(GPE_NOSYM, buf); 
      return 0;
    } else {
      var = get_symbol_annotation(s);
      assert(var != NULL);
      return var->value;
    }
  }
  
  switch (p->tag) {
  case constant:
    return p->value.constant;
  case symbol:
    {
      struct symbol *s;

      if (strcmp(p->value.symbol, "$") == 0) {
	return state.org << _16bit_core;
      } else {
	s = get_symbol(state.stTop, p->value.symbol);
	var = get_symbol_annotation(s);
	assert(var != NULL);
	return var->value;
      }
    }
  case unop:
    switch (p->value.unop.op) {
    case '!':
      return !evaluate(p->value.unop.p0);
    case '+':
      return  evaluate(p->value.unop.p0);
    case '-':
      return -evaluate(p->value.unop.p0);
    case '~':
      return ~evaluate(p->value.unop.p0);
    case UPPER:
      return (evaluate(p->value.unop.p0) >> 16) & 0x3f;
    case HIGH:
      return (evaluate(p->value.unop.p0) >> 8) & 0xff;
    case LOW:
      return evaluate(p->value.unop.p0) & 0xff;
    case INCREMENT:  
      return evaluate(p->value.unop.p0) + 1;
    case DECREMENT:          
      return evaluate(p->value.unop.p0) - 1;
    default:
      assert(0);
    }
  case binop:
    p0 = evaluate(p->value.binop.p0);
    p1 = evaluate(p->value.binop.p1);
    switch (p->value.binop.op) {
    case '+':      return p0 + p1;
    case '-':      return p0 - p1;
    case '*':      return p0 * p1;
    case '/':
      if (p1 == 0){
        gperror(GPE_DIVBY0, NULL);
        return 0;
      } else {
        return p0 / p1;
      }
    case '%':      return p0 % p1;
    case '&':      return p0 & p1;
    case '|':      return p0 | p1;
    case '^':      return p0 ^ p1;
    case LSH:      return p0 << p1;
    case RSH:      return p0 >> p1;
    case EQUAL:    return p0 == p1;
    case '<':      return p0 < p1;
    case '>':      return p0 > p1;
    case NOT_EQUAL:          return p0 != p1;
    case GREATER_EQUAL:      return p0 >= p1;
    case LESS_EQUAL:         return p0 <= p1;
    case LOGICAL_AND:        return p0 && p1;
    case LOGICAL_OR:         return p0 || p1;
    case '=': 
      gperror(GPE_BADCHAR, "Illegal character (=)");     
      return 0;
    default:
      assert(0); /* Unhandled binary operator */
    }
  default:
    assert(0); /* Unhandled parse node tag */
  }
  return (0); /* Should never reach here */
}

/* Attempt to evaluate expression 'p'.  Return its value if
 * successful, otherwise generate an error message and return 0.  */

gpasmVal maybe_evaluate(struct pnode *p)
{
  gpasmVal r;

  if (p && can_evaluate(p)) {
    r = evaluate(p);
  } else {
    r = 0;
  }

  return r;
}

/* count the number of relocatable addesses in the expression */

int count_reloc(struct pnode *p)
{
  struct symbol *s;
  struct variable *var;
  char *string;

  if (state.mode == absolute)
    return 0;

  if ((p->tag == binop) && (p->value.binop.op == CONCAT)) {
    string = evaluate_concatenation(p);
    s = get_symbol(state.stTop, string);
    if (s != NULL) {
      var = get_symbol_annotation(s);
      assert(var != NULL);
      switch(var->type) {
      case gvt_extern:
      case gvt_global:
      case gvt_static:
      case gvt_address:
        return 1;
      default:
        return 0;        
      }      
    }
    return 0;
  }
  switch (p->tag) {
  case constant:
    return 0;
  case symbol:
    s = get_symbol(state.stTop, p->value.symbol);
    if (s != NULL) {
      var = get_symbol_annotation(s);
      if (var != NULL) {
        switch(var->type) {
        case gvt_extern:
        case gvt_global:
        case gvt_static:
        case gvt_address:
          return 1;
        default:
          return 0;        
        }
      }
    }  
    return 0;
  case unop:
    return count_reloc(p->value.unop.p0);
  case binop:
    return count_reloc(p->value.binop.p0) + count_reloc(p->value.binop.p1);
  default:
    assert(0);
  }

  return 0;
}

/* When generating object files, operands with relocatable addresses can only be 
   [HIGH|LOW]([<relocatable address>] + [<offset>]) */

static void
add_reloc(struct pnode *p, short offset, unsigned short type)
{
  char *string;
  struct symbol *s;
  struct variable *var;

  if ((p->tag == binop) && (p->value.binop.op == CONCAT)) {
    string = evaluate_concatenation(p);
    s = get_symbol(state.stTop, string);
    if (s != NULL) {
      var = get_symbol_annotation(s);
      assert(var != NULL);
      switch(var->type) {
      case gvt_extern:
      case gvt_global:
      case gvt_static:
      case gvt_address:
        coff_reloc(var->coff_num, offset, type);
        return;
      default:
        return;        
      }      
    }
    return;
  }
  switch (p->tag) {
  case symbol:
    s = get_symbol(state.stTop, p->value.symbol);
    if (s != NULL) {
      var = get_symbol_annotation(s);
      if (var != NULL) {
        switch(var->type) {
        case gvt_extern:
        case gvt_global:
        case gvt_static:
        case gvt_address:
          coff_reloc(var->coff_num, offset, type);
          return;
        default:
          return;        
        }
      }
    }  
    return;
  case unop:
    switch (p->value.unop.op) {
    case UPPER:
      add_reloc(p->value.unop.p0, offset, RELOCT_UPPER);
      return;
    case HIGH:
      add_reloc(p->value.unop.p0, offset, RELOCT_HIGH);
      return;
    case LOW:
      add_reloc(p->value.unop.p0, offset, RELOCT_LOW);
      return;
    case '!':
    case '+':
    case '-':
    case '~':
    case INCREMENT:  
    case DECREMENT:          
      gperror(GPE_UNRESOLVABLE, NULL);
      return;
    default:
      assert(0);
    }
  case binop:
    switch (p->value.binop.op) {
    case '+':
      /* The symbol can be in either position */
      if (count_reloc(p->value.binop.p0) == 1) {
        add_reloc(p->value.binop.p0, maybe_evaluate(p->value.binop.p1), type);
      } else {
        add_reloc(p->value.binop.p1, maybe_evaluate(p->value.binop.p0), type);
      }
      return;
    case '-':
      /* The symbol has to be first */
      if (count_reloc(p->value.binop.p0) == 1) {
        add_reloc(p->value.binop.p0, -maybe_evaluate(p->value.binop.p1), type);
      } else {
        gperror(GPE_UNRESOLVABLE, NULL);
      }
      return;
    case '*':
    case '/':
    case '%':
    case '&':
    case '|':
    case '^':
    case LSH:
    case RSH:
    case EQUAL:
    case '<':
    case '>':
    case NOT_EQUAL:
    case GREATER_EQUAL:
    case LESS_EQUAL:
    case LOGICAL_AND:
    case LOGICAL_OR:
    case '=': 
      gperror(GPE_UNRESOLVABLE, NULL);
      return;
    default:
      assert(0); /* Unhandled binary operator */
    }
    return;
  case constant:
  default:
    assert(0);
  }

  return;
}

/* Determine if the expression is the difference between two symbols in 
   the same section */

/* FIXME: This needs some help.  Need a better definition of what is legal
   syntax.  Concatenations are not supported and should be. */

static int
same_section(struct pnode *p)
{
  struct pnode *p0;
  struct pnode *p1;
  gp_symbol_type *symbol0;
  gp_symbol_type *symbol1;

  if(!state.obj.enabled)
    return 0;
  
  if ((p->tag != binop) ||
      (p->value.binop.op != '-') ||
      (count_reloc(p->value.binop.p0) != 1))
    return 0;

  p0 = p->value.binop.p0;
  p1 = p->value.binop.p1;
 
  if ((p0->tag != symbol) ||
      (p1->tag != symbol))
    return 0;
  
  symbol0 = gp_coffgen_findsymbol(state.obj.object, p0->value.symbol);
  symbol1 = gp_coffgen_findsymbol(state.obj.object, p1->value.symbol);
  
  if ((symbol0->section_number < 1) || 
      (symbol0->section != symbol1->section))
    return 0;
    
  return 1;

}

gpasmVal reloc_evaluate(struct pnode *p, unsigned short type)
{
  gpasmVal r = 0;
  int count = 0;

  if (state.mode == absolute) {
    r = maybe_evaluate(p);
  } else {
    count = count_reloc(p);
    if (count == 0) {
      /* no relocatable addresses */
      r = maybe_evaluate(p);
    } else if (count > 1) {
      if ((count == 2) && (same_section(p))) {
         /* It is valid to take the difference between two symbols in the same 
           section.  Evaluate, but don't add a relocation. */
        r = maybe_evaluate(p);
      } else {
        /* too many relocatable addresses */
        gperror(GPE_UNRESOLVABLE, NULL);
        r = 0;
      }
    } else {
      /* add the coff relocation */
      add_reloc(p, 0, type);
      r = 0;
    }
  }
  
  return r;
}

/* evaluate the number of passes for the "fill" directive*/
int eval_fill_number(struct pnode *p)
{
  int number;

  number = maybe_evaluate(p);
  if(_16bit_core) {
    /* For 16 bit core devices number is bytes not words */ 
    if ((number & 0x1) == 1){
      /* The number is divided by two, so it can't be odd */
      gperror(GPE_FILL_ODD, NULL);
    } else {
      number = number / 2;
    }	
  }

  return number;
}
