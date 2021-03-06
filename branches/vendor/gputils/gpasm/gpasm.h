/* Common definitions for gpasm
   Copyright (C) 1998,1999,2000,2001 James Bowman, Craig Franklin

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

#if !defined(__GPASM_H)
#define __GPASM_H

#include <stdio.h>
#include "processor.h"
#include "gpmemory.h"
#include "gpwritehex.h"

#define GPASM_VERSION_STRING ("gpasm-" VERSION " alpha")

/* This symbol will get placed into the symbol table for the 16bit cores
 * and thus allow compile-time selection of the proper macro set */
#define __16bit_core_	"__16bit_core_"

#define STRCMP(s1, s2)	(state.case_insensitive ? \
			 strcasecmp((s1), (s2)) : \
			 strcmp((s1), (s2)))
			 
typedef int gpasmVal; 		/* The type that internal arithmetic uses */
enum gpasmValTypes {gvt_constant, gvt_cblock, gvt_org, gvt_address};

enum outfile { normal, suppress, named };
enum file_types { ft_src, ft_hex, ft_lst, ft_cod, ft_other }; /* allowed file types */

extern struct gpasm_state {
  int radix;
  enum formats hex_format;
  int case_insensitive;
  int quiet;
  int error_level;		/* 0, 1, 2 */
  struct {			/* Command line override flags */
    int radix;			/* When 1, the value is specified by the */
    int hex_format;		/* command line */
    int error_level;
    int macro_expand;		
    int processor;
  } cmd_line;
  enum pic_processor processor;
  struct px *processor_info;    /* Processor identifiers (e.g. name) */
  struct {			/* Processor data */
    int core_size;		/* processor core size  */
    int config_address;		/* configuration address */
    int id_location;		/* location for idlocs for 12 and 14 bit proc */
  } device;
  int pass;			/* 1 or 2 */
  int processor_chosen;		/* Nonzero after processor-specific init */
  struct symbol_table
  *stBuiltin,			/* Built-ins: instructions, pseudo-ops */
    *stDirective,               /* bottom half of Builtin with directives */
    *stGlobal,			/* Global symbols */
    *stTop,			/* Top of locals stack (stGlobal is base) */
    *stDefines,			/* Preprocessor #defines */
    *stMacros;			/* Macros */
  MemBlock *i_memory;		/* Instruction memory linked list */
  unsigned int c_memory_base;	/* Base address of configuration memory */
  char badram[MAX_RAM];		/* nonzero indicates illegal memory */
  unsigned int maxram;		/* Highest legal memory location */
  unsigned int org;		/* Current code-generation point */
  enum outfile
    lstfile,			/* List output file control */
    hexfile,			/* Hex output file control */
    codfile;			/* Symbol output file control */
  char *srcfilename,		/* Source (.asm) file name */
    basefilename[BUFSIZ],	/* basename for generating hex,list,symbol filenames */
    hexfilename[BUFSIZ],	/* Hex (.hex) file name */
    lstfilename[BUFSIZ],	/* List (.lst) file name */
    codfilename[BUFSIZ];	/* Symbol (.cod) file name */
  struct {			/* List file state: */
    FILE *f;			/*   List file output */
    unsigned int
      lineofpage,		/*   What line are we at within the page */
      page,			/*   What page are we at */
      linesperpage,		/*   Lines per page */
      line_number,              /*   What line are we at within the file */
      memorymap,		/*   Memory Map dump enabled */
      symboltable;		/*   Symbol table dump enabled */
    struct {
      unsigned int was_org;	/*   value of state.org at start of line */
		    		/*   What kind of line was it? */
      enum { none,		/*     Nothing - blank line */
	     org,		/*     ORG pseudo-op */
	     dir,		/*     Directive, non-code generating */
	     idlocs,		/*     ID locations for 12 and 14 bit cores */
	     insn,		/*     Some other instruction or pseudo */
	     equ,		/*     An equate */
	     set,		/*     A SET or '=' */
	     config }           /*     A __config line */
        linetype;
    } line;
    char startdate[80];		/*   When assembly started */
    int enabled;		/*   nonzero if listing is enabled */
    int expand;			/*   1 if the macro listings are expanded */
    int config_address;		/*   list config address for 16 bit devices */
    char title_name[80];	/*   given in TITLE directive */
    char subtitle_name[80];	/*   given in SUBTITLE directive */
    int tabstop;		/*   tab-stop distance */
    struct file_context *fc;    /*   Position in the file context stack */
  } lst;
  struct {			/* Symbol file state: */
    FILE *f;			/*   Symbol file output */
    int enabled;		/*   nonzero if symbol file is enabled */
    int emitting;               /*   flag indicating when an opcode is emitted */
  } cod;
  struct source_context *src;	/* Top of the stack of source files */
  struct file_context *files;   /* Top of the stack of all files */
  struct {			/* Totals for errors, warnings, messages */
    int errors;
    int warnings;
    int messages;
    int warnings_suppressed;
    int messages_suppressed;
  } num;
  struct amode *astack;		/* Stack of amodes (macros, etc) */
  gpasmVal cblock;		/* cblock constant */
  struct macro_head *mac_head;  /* Starting a macro... */
  struct macro_body **mac_prev; /* Stitching ptr */
  struct macro_body *mac_body;	/* While we're building a macro */
  struct macro_head *while_head;/* WHILEs work a lot like macros... */
} state;

struct variable {
  int value;
  enum gpasmValTypes type;
};

#define MAX_INCLUDE_PATHS 100
extern char *include_paths[];
extern int n_include_paths;

/************************************************************************/

/* Parse node: created by the parser, interpreted by the 'backend' */

struct pnode {
  enum pnode_tag { constant, symbol, string, list, binop, unop } tag;
  union {
    int constant;
    char *symbol;
    struct {
      struct pnode *head, *tail;
    } list;
    struct {
      int op;
      struct pnode *p0, *p1;
    } binop;
    struct {
      int op;
      struct pnode *p0;
    } unop;
    char *string;
  } value;
};

/************************************************************************/

/* file_context: a structure to keep track of all files that have been
		 opened.  Used to create the list of project files
		 that can be found in the .cod file.  */

struct file_context {
  char *name;                     /* file name */
  unsigned int id;                /* Unique identifier */
  enum file_types ft;             /* allowed file types */
  struct file_context *prev;      /* Previous in list pointer */
  struct file_context *next;      /* Next in list pointer */
};

struct source_context {
  char *name;
  FILE *f, *f2;
  struct yy_buffer_state *yybuf;
  unsigned int line_number;
  struct source_context *prev;
  struct file_context *fc;    /*   Position in the file context stack */
  char line[BUFSIZ];
};

enum globalLife { TEMPORARY, PERMANENT };

void yyerror(char *s);
int gpasm_number(char *);
int gpasm_magic(char *);
gpasmVal do_or_append_insn(char *op, struct pnode *parms);
void set_global(char *name,
		gpasmVal value,
		enum globalLife lifetime,
		enum gpasmValTypes type);
void select_errorlevel(int level);
void select_expand(char *expand);
void select_hexformat(char *format_name);
void select_radix(char *name);
struct file_context *add_file(unsigned int type, char *name);
void free_files(void);
void macro_append(void);

/************************************************************************/

struct macro_head {
  int pass;			/* Pass in which macro was defined: 1 or 2 */
  struct pnode *parms;
  struct macro_body *body;
  char *src_name;
  int line_number;
};

struct macro_body {
  char *label;			/* Label for the line */
  char *op;			/* Operation (or NULL) */
  struct pnode *parms;		/* Parameters for op (or NULL) */
  char *src_line;		/* Original source line - for listing */
  struct macro_body *next;	/* Next line in listing */
};

struct amode {
  enum { in_then, in_else } mode;
  int enabled;	/* Are we currently enabled? */
  int prev_enabled;
  struct amode *prev;
};

#endif
