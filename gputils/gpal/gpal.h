/* Common definitions for gpal
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

#ifndef __GPAL_H__
#define __GPAL_H__

#define GPAL_VERSION_STRING ("gpal-" VERSION " pre-alpha")

#define MAX_PATHS 100
#define MAX_FILE_NAMES 256

#include "tree.h"

typedef struct list_struct linked_list;

struct list_struct {
  void *item;
  struct list_struct *prev;
  struct list_struct *next;
};

extern struct gpal_state {
  gp_boolean compile_only;		/* compile, but don't assemble or link */
  gp_boolean no_link;			/* compile and assemble, but don't link */
  gp_boolean archive;			/* compile and assemble, then link */
  gp_boolean delete_temps;			/* delete temporary files */
  char *options;			/* extra link or lib options */
  struct {
    int level;
    gp_boolean auto_inline;
    gp_boolean constant_folding;
    gp_boolean dead_code;
    gp_boolean peep;
    gp_boolean strength_reduction;
    gp_boolean tail_calls;
    gp_boolean tree_shape;
    gp_boolean trival_expressions;
  } optimize;
  int path_num;                 	/* number of paths in the list */
  char *paths[MAX_PATHS];       	/* the list of include paths */
  int num_files;               		/* number of filenames in the list */
  char *file_name[MAX_FILE_NAMES];  	/* the list of file names */
  linked_list *file_list;		/* list of files to link */
  gp_boolean cmd_processor;		/* processor chose on command line */
  enum pic_processor processor;
  struct px *processor_info;    	/* Processor identifiers (e.g. name) */
  gp_boolean processor_chosen;		/* Nonzero after processor-specific init */
  struct {				/* Processor data */
    char *code;      			/* code section name */
    enum node_storage code_default;	/* pub file code on same page */
    char *udata;      			/* uninitialized data section name */
    enum node_storage udata_default;	/* pub file udata on same bank */
  } section;
  struct {				/* Processor data */
    enum proc_class class;      	/* Processor class */
    int core_size;			/* Processor core size  */
    int config_address;			/* configuration address */
    int id_location;			/* location for idlocs for 12 and 14 bit proc */
    int bsr_boundary;			/* 18xx bsr boundary location */
  } device;
  struct symbol_table
    *type,				/* Symbol Types */
    *global,				/* Global symbols */
    *data;				/* Data memory symbols */
  tree *root;				/* start of tree */
  struct source_context *src;		/* Top of the stack of source files */
  char *basefilename;			/* base filename */
  char *srcfilename;			/* source filename */
  char *outfilename;			/* output filename */
  char asmfilename[BUFSIZ];		/* asm output filename */
  struct {
    FILE *f;  				/* output assembly file */
  } output;
} state;

enum src_types { source, source_with, with };

struct source_context {
  char *name;
  enum src_types type;
  FILE *f;
  struct yy_buffer_state *yybuf;
  unsigned int line_number;
  struct source_context *prev;
};

void select_processor(char *name);
void add_entity(tree *node);

/* symbol data */

struct variable {
  char *alias;
  enum node_storage class;		/* storage class */
  int size;				/* size in bytes */
  int bitsize;				/* size in bits */
  int nelts;				/* number of elements */
  gp_boolean is_init;			/* the symbol has been initialized */
  gp_boolean is_equ;			/* true if processor header equate */
  gp_boolean is_constant;		/* true if constant symbol */
  int value;				/* value if constant symbol */
  tree *node;
};

#endif
