%option noyywrap
%x asm_block

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

#define ASM_BUF_SIZ 8096
static char asm_buffer[ASM_BUF_SIZ];
static int asm_index;

%}

HEXCHAR [0-9a-f]
DECCHAR [0-9]

%%
<<EOF>>			{ 
			  if (found_eof())
			    yyterminate();
			}
"asm"	 		{
			  asm_index = 0;
			  BEGIN(asm_block);
			}
<asm_block>"end"[ \t]+"asm" {
			  BEGIN(INITIAL);
			  asm_buffer[asm_index++] = '\0';
			  yylval.s = strdup(asm_buffer);
                          return ASM;
			}
<asm_block>(.|\n)	{
			  if (asm_index < ASM_BUF_SIZ) {
			    asm_buffer[asm_index++] = *yytext;
			  } else {
	  		    gp_error("asm block exceeds %i bytes",
	  		             ASM_BUF_SIZ);
	  		    exit(1);
			  }
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
[_a-z][_0-9a-z]*	{
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

void open_src(char *name, enum src_types type)
{
  extern FILE *yyin;
  struct source_context *new = malloc(sizeof(*new));
  char *file_name;
  int length;

  if ((type == with) || (type == source_with)) {
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
    if (type == source_with) {
      /* source files aren't required to have public files */
      free(new);
      free(file_name);
      return;
    } else {
      perror(file_name);
      exit(1);
    }
  }

  yyin = new->f;

  if (state.src) {
    yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
  }

#ifdef PARSE_DEBUG
  {
    extern int yydebug;
    yydebug = 1;
  }
#endif

  new->name = file_name;
  new->type = type;
  new->line_number = 1;
  new->prev = state.src;
  
  state.src = new;
}

static void
close_file(void)
{
  struct source_context *old;

  /* switch to previous buffer */
  old = state.src;
  state.src = state.src->prev;

  /* close the old file */
  if (old->f != NULL) {
    fclose(old->f);
  }
  free(old->name);
  free(old);
}

static
int found_eof(void)
{
  int terminate = 0;

  close_file();
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
