%option noyywrap
%x define
%x definition
%x title
%x subtitle

%{
/* lexical analyser for gpasm
   Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003 
   James Bowman, Craig Franklin

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
#include "parse.h"
#include "scan.h"
#include "gperror.h"
#include "directive.h"
#include "macro.h"
#include "coff.h"

#define OPERATOR(x)  return (yylval.i = (x))
/* YY_UNPUT not used, suppress the warning */
#define YY_NO_UNPUT

enum identtype { defines, directives, globals, macros, opcodes, unknown_type };
enum identtype identify(char *);

static void push_string(char *str);
static int found_end();
static int found_eof();

static struct symbol *current_definition;	/* Used in #define */
static int quoted; /* Used to prevent #define expansion in ifdef and 
                      ifndef... */
static int force_decimal; /* Used to force decimal in errorlevel */

%}

IDENT  ([a-z_\x80-\xff?@][a-z_0-9\x80-\xff.?@]*)|([.][a-z_\x80-\xff.?@]*)
ESCCH  \\([abfnrtv\\?'"]|0[0-7]{2}|x[0-9a-f]{2})
STR_QCHAR  ([^"\n]|{ESCCH})
NUMCHAR [0-9a-f]

%%
<<EOF>>		 	 {
			   if (found_eof())
			     yyterminate();
			 }
end		         {
			   found_end();
			   yyterminate();
			 }
^[ \t]*title[ \t]*[<"]?  { BEGIN(title); }
<title>[^<"\r\n]*[>"]?   { /* got the title text */
#define LEN sizeof(state.lst.title_name)
                           yytext[yyleng - 1] = '\0';
                           strncpy(state.lst.title_name, yytext, LEN - 1);
                           state.lst.title_name[LEN - 1] = '\0';
                           BEGIN(INITIAL);
#undef LEN
                         }
^[ \t]*subtitle[ \t]*[<"]?  { BEGIN(subtitle); }
^[ \t]*subtitl[ \t]*[<"]?   { BEGIN(subtitle); }
^[ \t]*stitle[ \t]*[<"]?    { BEGIN(subtitle); }
<subtitle>[^<"\r\n]*[>"]?   { /* got the subtitle text */
#define LEN sizeof(state.lst.subtitle_name)
                           yytext[yyleng - 1] = '\0';
                           strncpy(state.lst.subtitle_name, yytext, LEN - 1);
                           state.lst.subtitle_name[LEN - 1] = '\0';
                           BEGIN(INITIAL);
#undef LEN
                         }
cblock			 {
			   return CBLOCK;
			 }
errorlevel		 {
			   /* Force decimal interpretation for errorlevel*/
			   force_decimal = 1;
			   yylval.s = strdup(yytext);
			   return IDENTIFIER;
			 }
endc			 {
			   return ENDC;
			 }
fill[ \t]*\(     	 {
			   /* fill with ( ) as first argument */
			   yylval.i = FILL;
			   return FILL;
			 }
^[ \t]*#define[ \t]+ 	 {
                           BEGIN(define);
			 }
<define>{IDENT}		 {
                           if((asm_enabled()) && (!state.mac_prev)) {
			     if ((get_symbol(state.stDefines, yytext) != NULL)
                                  && (state.pass == 1)) {
			       /* FIXME: find a more elegant way to do this */
			       state.pass = 2;
			       gperror(GPE_DUPLAB, NULL);
			       exit(1);
			     }
			     current_definition = add_symbol(state.stDefines, 
                                                             yytext);
                           }
			   BEGIN(definition);
			 }
<definition>.*$	 	 {
                           if((asm_enabled()) && (!state.mac_prev)) {
			     char *string_ptr = yytext;

			     /* Should have a #define in progress */
			     assert(current_definition != NULL);

			     /* if there is a comment remove it */
			     while(*string_ptr != '\0') {
                               if (*string_ptr == ';') {
                                 *string_ptr = '\0';
                                 break;
                               }                                 
                               string_ptr++;
			     }

			     /* remove leading spaces or tabs */
			     string_ptr = yytext;
			     while(*string_ptr == '\t' || *string_ptr == ' ') {
			       string_ptr++;
			     }

                             annotate_symbol(current_definition, 
                                             strdup(string_ptr));
			     current_definition = NULL;
                           }
			   BEGIN(INITIAL);
                         }
upper			 {
			   yylval.i = UPPER;
			   return UPPER;
			 }
high			 {
			   yylval.i = HIGH;
			   return HIGH;
			 }
low		     	 {
			   yylval.i = LOW;
			   return LOW;
			 }
list		     	 {
			  /* Force decimal interpretation for list*/
			  force_decimal = 1;
			  yylval.s = strdup(yytext);
			  return IDENTIFIER;
			 }
#?else   	 	 {
			   /* #else and else can appear in column 1 */
			   yylval.s = strdup(yytext);
			   return IDENTIFIER;
			 }
#endif  	 	 {
			   /* only #endif can appear in column 1 */
			   yylval.s = strdup(yytext);
			   return IDENTIFIER;
			 }
#?ifdef			 {
			   /* #ifdef and ifdef can appear in column 1 */
			   quoted = 1;
			   yylval.s = strdup(yytext);
			   return IDENTIFIER;
			 }
#?ifndef		 {
			   /* #ifndef and ifdef can appear in column 1 */
			   quoted = 1;
			   yylval.s = strdup(yytext);
			   return IDENTIFIER;
			 }
#?include   	 	 {
			   /* #include and include can appear in column 1 */
			   yylval.s = strdup(yytext);
			   return IDENTIFIER;
			 }
#undefine 	 	 {
			   /* #undefine can appear in column 1 */
			   quoted = 1;
			   yylval.s = strdup(yytext);
			   return IDENTIFIER;
			 }
^{IDENT}#v\(             {
                           yytext[strlen(yytext) - 3] = '\0';
                           yylval.s = strdup(yytext);
                           return VARLAB_BEGIN;
                         }
^{IDENT}:?		 { 
			   int has_collon = 0;
			   struct symbol *sym;
			   struct macro_head *h;
			   char *subst;
                           
			   if (yytext[strlen(yytext) - 1] == ':') {
			     yytext[strlen(yytext) - 1] = '\0';
			     has_collon = 1;
			   }
			   yylval.s = strdup(yytext);
                           switch(identify(yytext)) {
                             case defines:
                               sym = get_symbol(state.stTopDefines, yytext);
                               subst = get_symbol_annotation(sym);
                               push_string(subst);
                               break;
                             case directives:
                               gpwarning(GPW_DIR_COLUMN_ONE, NULL);
                               if (has_collon)
                                 gperror(GPE_BADCHAR, "Illegal character (:)");
                               return IDENTIFIER;
                               break;
                             case macros:
                               if(asm_enabled()) {
			         /* make sure macro definition on second pass
                                    is ignored */
			         sym = get_symbol(state.stMacros, yytext);
			         h = get_symbol_annotation(sym);
                                 if (h->line_number == state.src->line_number) {
			           return LABEL;
			         } else {
			           gpwarning(GPW_MACRO_COLUMN_ONE, NULL);
			           if (has_collon)
                                    gperror(GPE_BADCHAR, 
                                             "Illegal character (:)");
			           return IDENTIFIER;
			         }
                               } else {
                                 /* if assembly is not enabled don't issue 
                                 warnings about macro calls in column 1, they 
                                 could be an alternate definition */ 
                                 return LABEL;			   
                               }
                               break;
                             case opcodes:
                               gpwarning(GPW_OP_COLUMN_ONE, NULL);
                               if (has_collon)
                                 gperror(GPE_BADCHAR, "Illegal character (:)");
                               return IDENTIFIER;
                               break;
                             case unknown_type:
                               return LABEL;
                             default:
                               return LABEL;
                           }			   
			 }
{IDENT}#v\(              {
                           yytext[strlen(yytext) - 3] = '\0';
                           yylval.s = strdup(yytext);
                           return VAR_BEGIN;
                         }
\)[a-z_0-9\x80-\xff?.]+  {
                           yylval.s = strdup(yytext+1);
                           return VAR_END;
                         }
{IDENT}			 {
			   struct symbol *sym;

			   /* If not quoted, check for #define substitution */
			   if (!quoted &&
                               (sym = get_symbol(state.stTopDefines, yytext)) != NULL) {
			     char *subst = get_symbol_annotation(sym);
			     assert(subst != NULL);
 			     if (strcmp(yytext, subst) == 0) {
 			       /* if check for bad subsitution */
 			       yylval.s = strdup(yytext);
 			       return IDENTIFIER;
 			     } else {
 			       char buffer[BUFSIZ];
                               
                               /* Make the substitution with a leading space,
                                  that way it won't be a label */
                               buffer[0] = ' ';
                               buffer[1] = '\0';
                               strcat(buffer, subst);
                               push_string(buffer);
 			     }
			   } else {
                             yylval.s = strdup(yytext);
			     return IDENTIFIER;
			   }
			 }
1[24678][CFHL0][CERV]?[0-9X][0-9X][0-9]?[0-9ABC]? {
/* Ugh.  As a special case, treat processor names, such as 16C84
as identifiers rather than as hex numbers. */
                           yylval.s = strdup(yytext);
			   return IDENTIFIER;
			 }
0x{NUMCHAR}+             {
                           yylval.i = stringtolong(yytext + 2, 16);
			   return NUMBER;
			 }
{NUMCHAR}+b              {
                           if (state.radix == 16) {
                             yylval.i = stringtolong(yytext, 16);                           
			   } else {
			     yytext[yyleng - 1] = '\0';
                             yylval.i = stringtolong(yytext, 2);
			   }
			   return NUMBER;
			 }
b'-?{NUMCHAR}+'          {
                           yytext[yyleng - 1] = '\0';
			   yylval.i = stringtolong(yytext + 2, 2);
			   return NUMBER;
			 }
{NUMCHAR}+[oq]           {			 
                           yytext[yyleng - 1] = '\0';
                           yylval.i = stringtolong(yytext, 8);
			   return NUMBER;
			 }
[oq]'-?{NUMCHAR}+'       {
                           yytext[yyleng - 1] = '\0';
			   yylval.i = stringtolong(yytext + 2, 8);
			   return NUMBER;
			 }
{NUMCHAR}+d              {
                           if (state.radix == 16) {
                             yylval.i = stringtolong(yytext, 16);                           
			   } else {
			     yytext[yyleng - 1] = '\0';
                             yylval.i = stringtolong(yytext, 10);
			   }
			   return NUMBER;
			 }
d'-?{NUMCHAR}+'          {
                           yytext[yyleng - 1] = '\0';
			   yylval.i = stringtolong(yytext + 2, 10);
			   return NUMBER;
			 }			
"."{NUMCHAR}+	         {
                           yylval.i = stringtolong(yytext + 1, 10);
			   return NUMBER;
			 }
{NUMCHAR}+h              {			 
                           yytext[yyleng - 1] = '\0';
                           yylval.i = stringtolong(yytext, 16);
			   return NUMBER;
			 }			 
h'-?{NUMCHAR}+'          {
                           yytext[yyleng - 1] = '\0';
			   yylval.i = stringtolong(yytext + 2, 16);
			   return NUMBER;
			 }
{NUMCHAR}+		 {
                           if (force_decimal) {
                             yylval.i = stringtolong(yytext, 10);
                           }else {
                             yylval.i = stringtolong(yytext, state.radix);
                           }
   			   return NUMBER;
			 }
\"{STR_QCHAR}\"          {
                           yylval.i = gpasm_magic(yytext + 1);
			   return NUMBER;
                         }
\"{STR_QCHAR}*\"?        {
			   char *pc = &yytext[yyleng - 1];
			   if (*pc == '"')
			     *pc = '\0';
                           else
			     gpwarning(GPW_MISSING_QUOTE, NULL);                           
                           yylval.s = strdup(yytext + 1);
			   return STRING;
                         }
\<[^<"\r\n;]*\>          {
			   /* treat include pathes as strings */
			   char *pc = &yytext[yyleng - 1];
			   *pc = '\0';
                            yylval.s = strdup(yytext + 1);
 			   return STRING;
                         }
'{STR_QCHAR}'            {
                           yylval.i = gpasm_magic(yytext + 1);
			   return NUMBER;
                         }
A'{STR_QCHAR}'           {
                           yylval.i = yytext[2];
			   return NUMBER;
                         }
"<<"			 OPERATOR(LSH);
">>"			 OPERATOR(RSH);
">="			 OPERATOR(GREATER_EQUAL);
"<="			 OPERATOR(LESS_EQUAL);
"=="			 OPERATOR(EQUAL);
"!="			 OPERATOR(NOT_EQUAL);
"&&"			 OPERATOR(LOGICAL_AND);
"||"			 OPERATOR(LOGICAL_OR);

"+="			 OPERATOR(ASSIGN_PLUS);
"-="			 OPERATOR(ASSIGN_MINUS);
"*="			 OPERATOR(ASSIGN_MULTIPLY);
"/="			 OPERATOR(ASSIGN_DIVIDE);
"%="			 OPERATOR(ASSIGN_MODULUS);
"<<="			 OPERATOR(ASSIGN_LSH);
">>="			 OPERATOR(ASSIGN_RSH);
"&="			 OPERATOR(ASSIGN_AND);
"|="			 OPERATOR(ASSIGN_OR);
"^="			 OPERATOR(ASSIGN_XOR);

"++"			 OPERATOR(INCREMENT);
"--"			 OPERATOR(DECREMENT);

"*+"			 OPERATOR(TBL_POST_INC);
"*-"			 OPERATOR(TBL_POST_DEC);
"+*"			 OPERATOR(TBL_PRE_INC);

[ \t\r]*
[\n]		         {
			   quoted = 0;
			   force_decimal = 0;
 			   return yytext[0];
			 }
;.*			 {  }
.			 { 
			   yylval.i = yytext[0];
		           return yytext[0];
			 }
%%

void open_src(char *name, int isinclude)
{
  extern FILE *yyin;
  struct source_context *new = malloc(sizeof(*new));
  if (state.src)
    state.src->yybuf = YY_CURRENT_BUFFER;

  new->f = fopen(name, "rt");
  if(new->f)
	  new->name = strdup(name);
  else if(isinclude && (strchr(name, PATH_CHAR) == 0)) { 
	  /* If include file and no PATH_CHAR in name, try searching include 
             path */
	  char tryname[BUFSIZ];
	  int i;

	  for(i = 0; i < n_include_paths; i++) {
		  strcpy(tryname, include_paths[i]);
		  strcat(tryname, COPY_CHAR);
		  strcat(tryname, name);
		  new->f = fopen(tryname, "rt");
		  if(new->f) {
			  new->name = strdup(tryname);
			  break;
		  }
	  }
  }
  if(new->f)
    new->lst.f = fopen(new->name, "rt");

  yyin = new->f;
  if (new->f == NULL) {
    if (state.src) {
      char complaint[BUFSIZ];

      sprintf(complaint,
	      "Unable to open file \"%s\" - %s",
	      name,
	      strerror(errno));
      state.pass = 2; /* Ensure error actually gets displayed */
      gperror(GPE_UNKNOWN, complaint);
    } else {
      perror(name);
    }
    exit(1);
  }

  if (state.src) {
    yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
  }

#ifdef PARSE_DEBUG
  {
    extern int yydebug;
    if (state.pass == 2)
      yydebug = 1;
    else
      yydebug = 0;
  }
#endif

  new->type = file;
  new->line_number = 1;
  new->file_symbol = coff_add_filesym(new->name, isinclude);
  new->prev = state.src;

  state.src = new;
  state.src->fc = add_file(ft_src, new->name); 
}

void execute_macro(struct macro_head *h)
{
  struct source_context *new = malloc(sizeof(*new));
  yy_size_t macro_src_size = 0;
  char *macro_src;

  assert(state.src != NULL);
  state.src->yybuf = YY_CURRENT_BUFFER;
  /* store the stack so it can be returned when the macro is complete */
  state.src->astack = state.astack;

  macro_src = make_macro_buffer(h);
  macro_src_size = strlen(macro_src) + 2;

  /* create new source_context */
  new->name = strdup(h->src_name);
  new->type = macro;
  new->line_number = h->line_number + 1;
  new->file_symbol = h->file_symbol;
  new->f = NULL;
  new->lst.m = h->body;
  
  new->prev = state.src;
  state.src = new;

  state.src->fc = add_file(ft_src, new->name); /* scan list for fc */
  YY_CURRENT_BUFFER = yy_scan_buffer(macro_src, macro_src_size);

}

static void push_string(char *str)
{
  struct source_context *new = malloc(sizeof(*new));

  assert(state.src != NULL);
  state.src->yybuf = YY_CURRENT_BUFFER;

  new->name = strdup(state.src->name);
  new->type = substitution;
  new->line_number = state.src->line_number;
  new->file_symbol = state.src->file_symbol;
  new->f = NULL;
  new->lst.f = NULL;
  new->fc = add_file(ft_src, new->name); /* scan list for fc */

  yy_scan_string(str);

  new->prev = state.src;
  state.src = new;
}

void close_file()
{
  struct source_context *old;

  old = state.src;
  state.src = state.src->prev;

  if (old->type == file) {
    if (old->f != NULL) {
      fclose(old->f);
    }
    if (old->lst.f != NULL)
      fclose(old->lst.f);
    free(old->name);
    coff_add_eofsym();
  } else if (old->type == macro) {
    state.stTop = pop_symbol_table(state.stTop);
    state.stTopDefines = pop_symbol_table(state.stTopDefines);
    if (state.src->astack != state.astack) {
      gperror(GPE_ILLEGAL_NESTING, NULL);
    }
    assert(state.stTop != NULL);
    assert(state.stTopDefines != NULL);
    free(old->name);
  }  
  free(old);
}

void execute_exitm()
{
  struct amode *previous;
  struct amode *old;

  /* The macro is ended early, so return the stack to its previous state */
  previous = state.src->prev->astack;
  while ((state.astack != NULL) &&
         (state.astack != previous)) {
    old = state.astack;
    state.astack = state.astack->prev; 
    free(old);
  }

  close_file();
  if (state.src) {
    yy_delete_buffer(YY_CURRENT_BUFFER);
    yy_switch_to_buffer(state.src->yybuf);
  }

}

/* found end directive, close all files and stop the parser */
static int found_end()
{
  if (state.while_head) {
    state.mac_body = NULL;    
    state.mac_prev = NULL;
    state.while_head = NULL;
    gperror(GPE_EXPECTED, "Expected (ENDW)");
  }

  if ((state.astack != NULL) && (state.astack->enabled)) {
    struct amode *old;

    while (state.astack) {
      old = state.astack;
      state.astack = state.astack->prev; 
      free(old);
    }
    gpwarning(GPW_EXPECTED, "Expected (ENDIF)");
  }

  if (state.mac_prev != NULL) {
    gperror(GPW_EXPECTED,"Expected (ENDM)");
  }

  /* close all open files */
  while(state.src) {
    close_file();
  }

  /* make sure the buffer is empty when pass 2 starts */
  if (YY_CURRENT_BUFFER)
    yy_flush_buffer(YY_CURRENT_BUFFER);

  return 1;
}

static int found_eof()
{
  int terminate = 0;

  close_file();
  if (state.src) {
    /* Just an include file */
    yy_delete_buffer(YY_CURRENT_BUFFER);
    yy_switch_to_buffer(state.src->yybuf);
  } else {
    gperror(GPE_ILLEGAL_COND, 
            "Illegal condition (EOF encountered before END)");
    terminate = found_end();
  }

  return terminate;
}

enum identtype identify(char *text)
{
  enum identtype type;  
  struct symbol *sym;

  if ((sym = get_symbol(state.stTopDefines, text)) != NULL) {
    type = defines;
  } else if ((sym = get_symbol(state.stDirective, text)) != NULL) {
    type = directives;
  } else if ((sym = get_symbol(state.stBuiltin, text)) != NULL) {
    type = opcodes;
  } else if ((sym = get_symbol(state.stGlobal, text)) != NULL) {
    type = globals;
  } else if ((sym = get_symbol(state.stMacros, text)) != NULL) {
    type = macros;
  } else {
    type = unknown_type;
  }

  return type;
}

