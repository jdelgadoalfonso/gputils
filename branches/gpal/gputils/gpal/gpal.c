/* top level functions for gpal
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
#include "tree.h"
#include "analyze.h"

struct gpal_state state;

int yyparse(void);

#define GET_OPTIONS "?I:acdhk:lo:O:p:Stqv"

/* Used: acdDehiIlmopqrwv */
static struct option longopts[] =
{
  { "archive",     0, 0, 'a' },
  { "object",      0, 0, 'c' },
  { "debug",       0, 0, 'd' },
  { "include",     1, 0, 'I' },
  { "help",        0, 0, 'h' },
  { "options",     1, 0, 'k' },
  { "list-chips",  0, 0, 'l' },
  { "output",      1, 0, 'o' },
  { "optimize",    1, 0, 'O' },
  { "processor",   1, 0, 'p' },
  { "compile",     0, 0, 'S' },
  { "save-temps",  0, 0, 't' },
  { "quiet",       0, 0, 'q' },
  { "version",     0, 0, 'v' },
  { 0, 0, 0, 0 }
};

void
init(void)
{
  /* restore gpal to its initialized state */
  state.compile_only = false;
  state.no_link = false;
  state.archive = false;
  state.delete_temps = true;
  state.options = NULL;
  state.optimize.level = 0;
  state.path_num = 0;
  state.num_files = 0;
  state.file_list = NULL;
  state.cmd_processor = false;
  state.processor = no_processor;
  state.processor_chosen = false;
  state.outfilename = NULL;

  /* create the global symbol table that is case insensitive */
  state.top = state.global = push_symbol_table(NULL, 1);
   
  return;
}

static void 
add_path(char *path)
{
  if(state.path_num < MAX_PATHS) {
    state.paths[state.path_num++] = strdup(path);
  } else {
    fprintf(stderr, "too many -I paths\n");
    exit(1);
  }
}

void
select_processor(char *name)
{
  struct px *found = NULL;

  if (state.cmd_processor) {
    gp_warning("processor superseded by command line");
  } else {
    found = gp_find_processor(name);
    if (found) {
      if (state.processor == no_processor) {
        state.processor = found->tag;
        state.processor_info = found;
        scan_header();
        /* FIXME: should the processor name be defined as a symbol? */
      } else if (state.processor != found->tag ) {
        gp_warning("redefining processor");
      }
    } else {
      gp_error("unknown processor \"%s\"", name);
    }
   
    /* load the instruction sets if necessary */
    if ((state.processor_chosen == false) && 
        (state.processor != no_processor)) {
      /* FIXME select the correct code generator */
      state.processor_chosen = true;
    }
  }
}

static tree *last_node;

void
add_entity(tree *node)
{

  if (state.root == NULL) {
    state.root = node;
    last_node = node;
  } else {
    node->prev = last_node;
    last_node->next = node;
    last_node = node;
  }

}

static void
set_optimize_level(void)
{

  /* default */
  state.optimize.auto_inline = false;
  state.optimize.constant_folding = false;
  state.optimize.dead_code = false;
  state.optimize.peep = false;
  state.optimize.strength_reduction = false;
  state.optimize.tail_calls = false;
  state.optimize.tree_shape = false;
  state.optimize.trival_expressions = false;

  switch(state.optimize.level) {
  case 3:
    state.optimize.auto_inline = true;
    /* fall through */
  case 2:
    state.optimize.dead_code = true;
    state.optimize.tail_calls = true;
    /* fall through */
  case 1:
    state.optimize.constant_folding = true;
    state.optimize.peep = true;
    state.optimize.strength_reduction = true;
    state.optimize.tree_shape = true;
    state.optimize.trival_expressions = true;
    break;
  case 0:
    break;
  default:
    gp_error("invalid optimization level");
  }

  return;
}

static void
show_usage(void)
{
  printf("Usage: gpal [options] file\n");
  printf("Options: [defaults in brackets after descriptions]\n");
  printf("  -a, --archive                  Compile or assemble, then archive.\n");
  printf("  -c, --object                   Compile or assemble, but don't link.\n");
  printf("  -d, --debug                    Output debug messages.\n");
  printf("  -h, --help                     Show this usage message.\n");
  printf("  -I DIR, --include DIR          Specify include directory.\n");
  printf("  -k \"OPT\", --options \"OPT\"      Extra link or lib options.\n");
  printf("  -l, --list-chips               List supported processors.\n");
  printf("  -o FILE, --output FILE         Alternate name of output file.\n");
  printf("  -O OPT, --optimize OPT         Optimization level.\n");
  printf("  -p PROC, --processor PROC      Select processor.\n");
  printf("  -q, --quiet                    Quiet.\n");
  printf("  -S, --compile                  Compile only, don't assemble or link.\n");
  printf("  -t, --save-temps               Do not delete intermediate files.\n");
  printf("  -v, --version                  Show version.\n");
  printf("\n");
  printf("Report bugs to:\n");
  printf("%s\n", BUG_REPORT_URL);
  exit(0);
}

void
process_args( int argc, char *argv[])
{
  extern char *optarg;
  extern int optind;
  int c;
  int usage = 0;

  /* first pass through options */
  while ((c = getopt_long(argc, argv, GET_OPTIONS, longopts, 0)) != EOF) {
    switch (c) {
    case 'O':
      state.optimize.level = atoi(optarg);
      break;
    }
  }

  /* reset the getopt_long index for the next call */
  optind = 1;

  set_optimize_level();

  /* second pass through options */
  while ((c = getopt_long(argc, argv, GET_OPTIONS, longopts, 0)) != EOF) {
    switch (c) {
    case '?':
    case 'h':
      usage = 1;
      break;
    case 'a':
      state.archive = true;
      break;    
    case 'c':
      state.no_link = true;
      break;    
    case 'd':
      gp_debug_disable = 0;
      break;
    case 'I':
      add_path(optarg);
      break;    
    case 'k':
      state.options = optarg;
      break;
    case 'l':
      gp_dump_processor_list();
      exit(0);
      break;
    case 'o':
      state.outfilename = strdup(optarg);
      break;
    case 'O':
      /* do nothing */
      break;
    case 'p':
      select_processor(optarg);
      state.cmd_processor = true;
      break;
    case 'q':
      gp_quiet = 1;
      break;
    case 'S':
      state.compile_only = true;
      break;    
    case 't':
      state.delete_temps = false;
      break;    
    case 'v':
      fprintf(stderr, "%s\n", GPAL_VERSION_STRING);
      exit(0);
      
    }
    if (usage)
      break;
  }
  
  if (optind < argc) {
    for ( ; optind < argc; optind++) {
      state.file_name[state.num_files] = argv[optind];
      if (state.num_files >= MAX_FILE_NAMES) {
        gp_error("exceeded maximum number of source files");
        break;
      }
      state.num_files++;
    }
  } else {
    usage = 1;
  }

  if (usage) {
    show_usage();
  }

}

static void
compile(void)
{
  /* symbol table */
  state.top = push_symbol_table(state.top, 1);

  init_nodes();
  state.root = NULL;

  /* remove section names */
  state.section.code = NULL;
  state.section.code_addr = 0;
  state.section.code_addr_valid = false;
  state.section.code_default = storage_extern;

  state.section.udata = NULL;
  state.section.udata_addr = 0;
  state.section.udata_addr_valid = false;
  state.section.udata_default = storage_extern;
 
  /* open and parse the source public file */
  state.src = NULL;
  open_src(state.basefilename, source_with);
  if (state.src)
    yyparse();

  /* open input file */
  open_src(state.srcfilename, source);

  /* parse the input file */
  yyparse();

  /* don't bother analyzing if there are already errors */
  if (gp_num_errors)
    return;

  /* check for semantic errors and write the code */
  analyze();

  /* destory symbol table for the current module */
  state.top = pop_symbol_table(state.top);

  /* free all the memory */
  free_nodes();

  return;
}

static void
assemble(char *file_name, gp_boolean asm_source)
{
  char command[BUFSIZ];

  if ((gp_num_errors) || (state.compile_only == true))
    return;

  if (state.processor_chosen == false) {
    gp_error("processor not selected");
    exit(1);
  }

  strcpy(command, "gpasm -c ");

  if (gp_quiet) {
    strcat(command, "-q ");
  }  

  strcat(command, file_name);
  strcat(command, ".asm ");

  if (!gp_quiet) {
    printf("%s\n", command);
  }
  if (system(command)) {
    gp_num_errors++;
  } else if (state.delete_temps == true) {
    if (asm_source == false) {
      sprintf(command, "%s.asm", file_name);
      unlink(command);
    }
    sprintf(command, "%s.lst", file_name);
    unlink(command);
  }

  return;
}

static gp_linked_list *last_file;

static void
add_file_list(char *file_name)
{
  gp_linked_list *new;
  char *name;

  name = malloc(strlen(file_name) + 3);
  strcpy(name, file_name);
  strcat(name, ".o");

  new = gp_list_make();
  gp_list_annotate(new, name);

  if (state.file_list) {
    new->prev = last_file;
    last_file->next = new;
    last_file = new;
  } else {
    state.file_list = new;
    last_file = new;
  }

  return;
}

/* Either link or archive the objects */

static void
combine_output(void)
{
  char command[BUFSIZ];
  gp_linked_list *list = state.file_list;

  /* only link if commanded */
  if ((state.compile_only == true) || (state.no_link == true))
    return;

  /* don't bother linking if there are errors */
  if (gp_num_errors)
    return;

  if (state.archive == true) {
    strcpy(command, "gplib -c ");
  } else {
    strcpy(command, "gplink ");
  }
  
  if (gp_quiet) {
    strcat(command, "-q ");
  }

  if (state.options) {
    strcat(command, state.options);
    strcat(command, " ");
  }

  if (state.outfilename == NULL) {
    if (state.archive == true) {
      gp_message("using \"library.a\" for archive name");
      strcat(command, "library.a ");
    }
  } else {
    if (state.archive == false) {
      strcat(command, "-o ");    
    }
    strcat(command, state.outfilename);
    strcat(command, " ");
  }
  
  if (list == NULL) {
    gp_error("no files to link or archive");
  } else {
    while(list != NULL) {
      strcat(command, gp_list_get(list)); 
      strcat(command, " ");
      list = list->next;
    }
  }
  
  if (!gp_quiet) {
    printf("%s\n", command);
  }
  if (system(command)) {
    gp_num_errors++;
  } else if (state.delete_temps == true) {
    list = state.file_list;
    while(list != NULL) {
      unlink(gp_list_get(list));
      list = list->next;
    }    
  
  }

  return;
}

int 
main(int argc, char *argv[])
{
  int i;
  char *pc;

  init();
  process_args(argc, argv);

  for (i = 0; i < state.num_files; i++) {
    state.basefilename = strdup(state.file_name[i]);
    pc = strrchr(state.basefilename, '.');
    *pc++ = 0;
    state.srcfilename = state.file_name[i];
    
    if (strcasecmp(pc, "pal") == 0) {
      /* compile it */
      compile();
      assemble(state.basefilename, false);
      add_file_list(state.basefilename);
    } else if (strcasecmp(pc, "pub") == 0) {
      gp_error("public files are not compiled \"%s\"", state.file_name[i]);
    } else if (strcasecmp(pc, "asm") == 0) {
      /* assemble it */
      assemble(state.basefilename, true);
      add_file_list(state.basefilename);
    } else if ((strcasecmp(pc, "o") == 0) || (strcasecmp(pc, "a") == 0)) {
      /* add it to the list for linking */
      add_file_list(state.basefilename);
    } else {
      gp_error("unknown extension of \"%s\"", state.file_name[i]);
      exit(1);
    }

    /* free the new filename */
    if (state.basefilename)
      free(state.basefilename);
  }

  combine_output();

  if (gp_num_errors > 0)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
