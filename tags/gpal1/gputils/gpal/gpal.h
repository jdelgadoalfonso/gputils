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

typedef struct entity_struct entity;
struct entity_struct {
  tree *node;
  entity *next;
};

typedef struct list_struct file_list;
struct list_struct {
  char *name;
  struct list_struct *next;
};

extern struct gpal_state {
  gp_boolean compile_only;		/* compile, but don't assemble or link */
  gp_boolean no_link;			/* compile and assemble, but don't link */
  gp_boolean archive;			/* compile and assemble, then link */
  gp_boolean delete_temps;			/* delete temporary files */
  char *options;			/* extre link or lib options */
  int path_num;                 	/* number of paths in the list */
  char *paths[MAX_PATHS];       	/* the list of include paths */
  int num_files;               		/* number of filenames in the list */
  char *file_name[MAX_FILE_NAMES];  	/* the list of file names */
  file_list *link_list;			/* list of files to link */
  gp_boolean cmd_processor;		/* processor chose on command line */
  char *processor_name;			/* processor name */
  enum pic_processor processor;
  struct px *processor_info;    	/* Processor identifiers (e.g. name) */
  gp_boolean processor_chosen;		/* Nonzero after processor-specific init */
  struct {				/* Processor data */
    enum proc_class class;      	/* Processor class */
    int core_size;			/* Processor core size  */
    int config_address;			/* configuration address */
    int id_location;			/* location for idlocs for 12 and 14 bit proc */
    int bsr_boundary;			/* 18xx bsr boundary location */
  } device;
  struct symbol_table
    *stBuiltin,				/* Built-ins: instructions, pseudo-ops */
    *stGlobal;				/* Global symbols */
  entity *list;				/* list of functions and procedures */
  struct source_context *src;		/* Top of the stack of source files */
  char *srcfilename;			/* source filename */
  char *outfilename;			/* output filename */
  char asmfilename[BUFSIZ];		/* asm output filename */
  struct {
    FILE *f;  				/* output assembly file */
  } output;
} state;

struct source_context {
  char *name;
  enum src_types { source, with } type;
  FILE *f;
  struct yy_buffer_state *yybuf;
  unsigned int line_number;
  struct source_context *prev;
};

void select_processor(char *name);

#endif
