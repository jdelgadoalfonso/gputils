%option noyywrap
%x incl
%x define
%x definition

%{
/* lexical analyser
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
#include "parse.h"

#define OPERATOR(x)  return (yylval.i = (x))
/* YY_UNPUT not used, suppress the warning */
#define YY_NO_UNPUT

static int found_eof(void);
int stringtolong(char *string, int radix);

%}

HEXCHAR [0-9a-f]
DECCHAR [0-9]

%%
<<EOF>>			{ 
			  if (found_eof())
			    yyterminate();
			}
"const"			{ return CONST_TYPE; }
"begin"			{ return BEGIN_KEY; }
"bit"			{ return BIT_SIZE; }
"byte"			{ return BYTE_SIZE; }
"else"			{ return ELSE; }
"elsif"			{ return ELSIF; }
"end"			{ return END; }
"extern"		{ return EXTERN_STORAGE; }
"function"		{ return FUNCTION_TOK; }
"if"			{ return IF; }
"is"			{ return IS; }
"loop"			{ return LOOP; }
"pragma"		{ return PRAGMA; }
"procedure"		{ return PROCEDURE; }
"public"		{ return PUBLIC_STORAGE; }
"return"		{ return RETURN; }
"then"			{ return THEN; }
"var"			{ return VAR_TYPE; }
"volatile"		{ return VOLATILE_STORAGE; }
"while"			{ return WHILE; }
"with"			{ return WITH; }
[_a-z][_0-9a-z]*		{
			  yylval.s = strdup(yytext);
			  return IDENT;
			}
0x{HEXCHAR}+		{
			  yylval.i = stringtolong(yytext + 2, 16);
                          return NUMBER;
			}
{DECCHAR}+		{
			  yylval.i = stringtolong(yytext, 10);
			  return NUMBER;
			}
"<<"			OPERATOR(LSH);
">>"			OPERATOR(RSH);
">="			OPERATOR(GREATER_EQUAL);
"<="			OPERATOR(LESS_EQUAL);
"=="			OPERATOR(EQUAL);
"!="			OPERATOR(NOT_EQUAL);
"&&"			OPERATOR(LOGICAL_AND);
"||"			OPERATOR(LOGICAL_OR);

--[^\n]*		{ }
[\n]			{ state.src->line_number++; }
[ \t\v\f]		{ }
.			{ 
			  yylval.i = yytext[0];
		          return yytext[0];
			}

%%

void open_src(char *name, gp_boolean is_with, gp_boolean is_source_with)
{
  extern FILE *yyin;
  struct source_context *new = malloc(sizeof(*new));
  char *file_name;
  int length;

  if (is_with) {
    /* construct the public file name */
    length = strlen(name);
    length += strlen(".pub") + 1;
    file_name = malloc(length);
    strcpy(file_name, name);
    strcat(file_name, ".pub");
  } else {
    file_name = strdup(name);
  }

  if (state.src)
    state.src->yybuf = YY_CURRENT_BUFFER;

  new->f = fopen(file_name, "rt");
  if (new->f == NULL) {
    if (is_source_with) {
      /* source files aren't required to have public files */
      free(new);
      free(file_name);
      return;
    } else {
      perror(file_name);
      exit(1);
    }
  }

#ifdef PARSE_DEBUG
  {
    extern int yydebug;
    yydebug = 1;
  }
#endif

  yyin = new->f;

  if (state.src) {
    yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
  }

  new->name = file_name;
  if (is_source_with)
    new->type = source_with;
  else if (is_with)
    new->type = with;
  else
    new->type = source;
  new->line_number = 1;
  new->prev = state.src;
  
  state.src = new;
}

static
int found_eof(void)
{
  struct source_context *old;
  int terminate = 0;

  /* switch to previous buffer */
  old = state.src;
  state.src = state.src->prev;

  /* close the old file */
  if (old->f != NULL) {
    fclose(old->f);
  }
  free(old->name);
  free(old);

  if (state.src) {
    /* Just a with file */
    yy_delete_buffer(YY_CURRENT_BUFFER);
    yy_switch_to_buffer(state.src->yybuf);
  } else {
    /* flush the buffer so we are ready for next parse */
    if (YY_CURRENT_BUFFER)
      yy_flush_buffer(YY_CURRENT_BUFFER);

    terminate = 1;
  }

  return terminate;
}

int
stringtolong(char *string, int radix)
{
  char *endptr;
  int value;
  
  value = strtol(string, &endptr, radix);                           
  if ((endptr == NULL) || (*endptr != '\0')) {
    char complaint[80];

    sprintf(complaint,
            isprint(*endptr) ?
            "Illegal character '%c' in numeric constant " :
            "Illegal character %#x in numeric constant" ,
            *endptr);
    gp_error("%s", complaint);
  }

  return value;
}
