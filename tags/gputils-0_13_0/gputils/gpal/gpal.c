/* top level functions for gpal
   Copyright (C) 2003, 2004, 2005
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
#include "analyze.h"

int yyparse(void);

struct gpal_state state;

static gp_boolean lib_exists = false;

static gp_linked_list *last_path;

static void
add_path(char *path)
{
  gp_linked_list *new;

  new = gp_list_make();
  gp_list_annotate(new, strdup(path));

  if (state.path) {
    new->prev = last_path;
    last_path->next = new;
    last_path = new;
  } else {
    state.path = new;
    last_path = new;
  }

  return;
}

static gp_linked_list *last_file;
static int next_file_id;

int
add_file(char *name,
         char *extension,
         gp_boolean is_temp,
         gp_boolean is_link)
{
  char *file_name;
  gp_linked_list *new;
  struct file_struct *file_data;

  if (extension != NULL) {
    size_t len = strlen(name) + strlen(extension) + 2;
    file_name = malloc(len);
    strncpy(file_name, name, len);
    strncat(file_name, ".", len);
    strncat(file_name, extension, len);
  } else {
    file_name = strdup(name);
  }

  new = gp_list_make();
  file_data = malloc(sizeof(*file_data));  
  file_data->name = file_name;
  file_data->file_id = next_file_id++;
  file_data->is_temp = is_temp;
  file_data->is_link = is_link;
  gp_list_annotate(new, file_data);

  if (state.file) {
    new->prev = last_file;
    last_file->next = new;
    last_file = new;
  } else {
    state.file = new;
    last_file = new;
  }

  return file_data->file_id;
}

char *
get_file_name(int id)
{
  gp_linked_list *list = state.file;
  struct file_struct *file_data;
 
  while(list) {
    file_data = gp_list_get(list);
    if (file_data->file_id == id) {
      return file_data->name;
    }
    list = list->next;
  }  

  assert(0);

  return NULL;
}

static void
set_optimize_level(void)
{

  /* default */
  state.optimize.auto_inline = false;
  state.optimize.constant_folding = false;
  state.optimize.dead_code = false;
  state.optimize.peep = false;
  state.optimize.second_pass = false;
  state.optimize.strength_reduction = false;
  state.optimize.tail_calls = false;
  state.optimize.tree_shape = false;
  state.optimize.trival_expressions = false;
  state.optimize.unused_mem = false;

  switch(state.optimize.level) {
  case 3:
    state.optimize.auto_inline = true;
    state.optimize.second_pass = true;
    /* fall through */
  case 2:
    state.optimize.dead_code = true;
    state.optimize.peep = true;
    state.optimize.tail_calls = true;
    state.optimize.unused_mem = true;
    /* fall through */
  case 1:
    state.optimize.constant_folding = true;
    state.optimize.strength_reduction = true;
    state.optimize.tree_shape = true;
    state.optimize.trival_expressions = true;
    /* fall through */
  case 0:
    break;
  default:
    gp_error("invalid optimization level");
  }

  return;
}

#define GET_OPTIONS "?I:acdhk:lMo:O:p:Stquv"

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
  { "deps",        0, 0, 'M' },
  { "output",      1, 0, 'o' },
  { "optimize",    1, 0, 'O' },
  { "processor",   1, 0, 'p' },
  { "compile",     0, 0, 'S' },
  { "save-temps",  0, 0, 't' },
  { "quiet",       0, 0, 'q' },
  { "absolute",    0, 0, 'u' },
  { "version",     0, 0, 'v' },
  { 0, 0, 0, 0 }
};

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
  printf("  -M, --deps                     Output dependency file.\n");
  printf("  -o FILE, --output FILE         Alternate name of output file.\n");
  printf("  -O OPT, --optimize OPT         Optimization level [1].\n");
  printf("  -p PROC, --processor PROC      Select processor.\n");
  printf("  -q, --quiet                    Quiet.\n");
  printf("  -S, --compile                  Compile only, don't assemble or link.\n");
  printf("  -t, --save-temps               Do not delete intermediate files.\n");
  printf("  -u, --absolute                 Use absolute pathes. \n");
  printf("  -v, --version                  Show version.\n");
  printf("\n");
#ifdef USE_DEFAULT_PATHS
  if (gp_pub_path) {
    printf("Default public file path %s\n", gp_pub_path);
  } else {
    printf("Default public file path NOT SET\n");
  }
  printf("\n");
#endif
  printf("Report bugs to:\n");
  printf("%s\n", PACKAGE_BUGREPORT);
  exit(0);
}

static void
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
    case 'p':
      analyze_select_processor(NULL, optarg);
      state.cmd_processor = true;
      break;
    }
  }

  /* reset the getopt_long index for the next call */
  optind = 1;

  set_optimize_level();

  /* second pass through options */
  while ((c = getopt_long(argc, argv, GET_OPTIONS, longopts, 0)) != EOF) {
    switch (c) {
    case 'a':
      state.archive = true;
      break;    
    case 'c':
      state.no_link = true;
      break;    
    case 'd':
      {
        extern int yydebug;
        yydebug = 1;
        gp_debug_disable = false;
      }
      break;
    case '?':
    case 'h':
      usage = 1;
      break;
    case 'I':
      add_path(optarg);
      break;    
    case 'k':
      state.options = optarg;
      break;
    case 'l':
      gp_dump_processor_list(false, PROC_CLASS_PIC14);
      gp_dump_processor_list(false, PROC_CLASS_PIC16E);
      exit(0);
      break;
    case 'M':
      state.make_deps = true;
      break;
    case 'o':
      state.outfilename = strdup(optarg);
      break;
    case 'O':
      /* do nothing */
      break;
    case 'p':
      /* do nothing */
      break;
    case 'q':
      gp_quiet = true;
      break;
    case 'S':
      state.compile_only = true;
      break;    
    case 't':
      state.delete_temps = false;
      break;    
    case 'u':
      state.use_absolute_path = true;
      break;
    case 'v':
      fprintf(stderr, "%s\n", GPAL_VERSION_STRING);
      exit(0);
      
    }
    if (usage)
      break;
  }

  if (optind >= argc) {
    /* there are no files in the list */
    usage = 1;
  }

  if (usage) {
    show_usage();
  }

  /* Add the pub path to the include paths list last, so that the user
     specified directories are searched first */
  if (gp_pub_path) {
    add_path(gp_pub_path);
  }

}

void
parse(char *file_name)
{
  state.src = NULL;

  if (state.use_absolute_path) {
    file_name = gp_absolute_path(file_name);
  }

  /* open input file */
  open_src(file_name);

  /* parse the input file */
  if (state.src)
    yyparse();

  /* exit if there are parse errors */
  if (gp_num_errors) {
    exit(1);
  }

}

static void
compile(tree *module)
{

  /* create the global symbol table that is case insensitive */
  state.global = push_symbol_table(NULL, true);
  
  /* create a top symbol table for the symbol alias */
  state.top = push_symbol_table(state.global, true);

  /* create the type symbol table that is case insensitive */
  state.type = push_symbol_table(NULL, true);

  /* create a top type table for the type alias */
  state.type_top = push_symbol_table(state.type, true);
  
  add_type_prims();  

  /* initialize the compile */
  state.section.code = NULL;
  state.section.code_addr = 0;
  state.section.code_addr_valid = false;

  state.section.data = NULL;
  state.section.data_addr = 0;
  state.section.data_addr_valid = false;

  /* check for semantic errors and write the code, if there are no errors */
  analyze(module);

  /* destory symbol table for the current module */
  state.top = pop_symbol_table(state.top);
  state.global = pop_symbol_table(state.global);
  state.type = pop_symbol_table(state.type);
  state.type_top = pop_symbol_table(state.type_top);

  if (!gp_num_errors) {
    if (state.compile_only == true) {
      add_file(FILE_NAME(module), "asm", false, false);
    } else {
      add_file(FILE_NAME(module), "asm", true, false);
    }
  }

  return;
}

static void
assemble(tree *module)
{
  char command[BUFSIZ];

  if ((gp_num_errors) || (state.compile_only == true))
    return;

  if (state.processor_chosen == false) {
    gp_error("processor not selected");
    exit(1);
  }

  strncpy(command, "gpasm -c -g ", sizeof(command));

  if (gp_quiet) {
    strncat(command, "-q ", sizeof(command));
  }

  strncat(command, FILE_NAME(module), sizeof(command));
  strncat(command, ".asm ", sizeof(command));

  if (!gp_debug_disable) {
    printf("%s\n", command);
  }
  
  if (system(command)) {
    gp_num_errors++;
  } else {
    add_file(FILE_NAME(module), "lst", true, false);  
    if (state.no_link == true) {
      add_file(FILE_NAME(module), "o", false, true);
    } else {
      add_file(FILE_NAME(module), "o", true, true);
    }
  }

  return;
}

static void
check_lib(void)
{
  enum gp_coff_type type;

  if (state.outfilename) {
    type = gp_identify_coff_file(state.outfilename);
  } else {
    type = gp_identify_coff_file(GPAL_DEFAULT_LIB);
  }

  if (type == archive_file) {
    lib_exists = true;
  } else {
    lib_exists = false;
  }
  
  return;
}

/* Either link or archive the objects */

static void
combine_output(void)
{
  char command[BUFSIZ];
  gp_linked_list *list;
  struct file_struct *file_data;

  /* only link if commanded */
  if ((state.compile_only == true) || (state.no_link == true))
    return;

  /* don't bother linking if there are errors */
  if (gp_num_errors)
    return;

  if (state.archive == true) {
    check_lib();
    if (lib_exists) {
      strncpy(command, "gplib -r ", sizeof(command));
    } else {
      strncpy(command, "gplib -c ", sizeof(command));
    }
  } else {
    strncpy(command, "gplink ", sizeof(command));
  }
  
  if (gp_quiet) {
    strncat(command, "-q ", sizeof(command));
  }

  if (state.options) {
    strncat(command, state.options, sizeof(command));
    strncat(command, " ", sizeof(command));
  }

  if (state.outfilename == NULL) {
    if (state.archive == true) {
      strncat(command, GPAL_DEFAULT_LIB, sizeof(command));
      strncat(command, " ", sizeof(command));
    }
  } else {
    if (state.archive == false) {
      strncat(command, "-o ", sizeof(command));
    }
    strncat(command, state.outfilename, sizeof(command));
    strncat(command, " ", sizeof(command));
  }
  
  if (state.archive == false) {
    list = state.path;
    while(list) {
      strncat(command, "-I ", sizeof(command));
      strncat(command, gp_list_get(list), sizeof(command));
      strncat(command, " ", sizeof(command));
      list = list->next;
    }  
  }
  
  list = state.file;
  while(list) {
    file_data = gp_list_get(list);
    if (file_data->is_link) {
      strncat(command, file_data->name, sizeof(command));
      strncat(command, " ", sizeof(command));
    }
    list = list->next;
  }
  
  if (!gp_debug_disable) {
    printf("%s\n", command);
  }
  
  if (system(command)) {
    gp_num_errors++;
  }

  return;
}

static void
init(void)
{

  gp_init();

  /* restore gpal to its initialized state */
  state.compile_only = false;
  state.no_link = false;
  state.archive = false;
  state.delete_temps = true;
  state.use_absolute_path = false;
  state.make_deps = false;
  state.options = NULL;
  state.optimize.level = 1;
  state.path = NULL;
  state.file = NULL;
  state.cmd_processor = false;
  state.processor = no_processor;
  state.class = PROC_CLASS_GENERIC;
  state.processor_chosen = false;
  state.current_bank = NULL;
  state.current_ibank = NULL;
  state.current_page = NULL;
  state.root = NULL;
  state.outfilename = NULL;

  /* local data */
  next_file_id = 1;

  init_nodes();

  /* create the symbol tables for the modules and publics */ 
  state.modules = push_symbol_table(NULL, true);
  state.publics = push_symbol_table(NULL, true);
   
  return;
}

int 
main(int argc, char *argv[])
{
  extern char *optarg;
  extern int optind;
  gp_linked_list *list;
  struct file_struct *file_data;
  tree *node;

  init();
  process_args(argc, argv);

  /* parse all of the input files */
  for ( ; optind < argc; optind++) {
    parse(argv[optind]);
  }

  /* compile all the modules */
  node = state.root;
  while (node) {
    if (FILE_TYPE(node) == source_module) {
      compile(node);
      assemble(node);
    }  
    node = node->next;
  }

  combine_output();

  /* delete temps if no errors */
  if ((state.delete_temps == true) && (gp_num_errors == 0)) {
    list = state.file;
    while(list != NULL) {
      file_data = gp_list_get(list);
      if (file_data->is_temp) {
        unlink(file_data->name);
      }
      list = list->next;
    }
  }

  /* free all the memory */
  free_nodes();

  if (gp_num_errors)
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}
