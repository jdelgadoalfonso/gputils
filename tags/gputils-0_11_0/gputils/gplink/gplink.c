/* GNU PIC Linker
   Copyright (C) 2001, 2002, 2003
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
#include "gplink.h"
#include "scan.h"
#include "map.h"

struct gplink_state state;

int yyparse(void);

/* return the number of missing symbols */
int count_missing(void)
{
  return state.symbol.missing->count;
}

void object_append(gp_object_type *file, char *name)
{
  /* append the entry to the list */
  if (state.object == NULL) {
    state.object = file;
    /* store the processor type from the first object file */
    state.processor = file->processor;
  } else {
    gp_object_type *list = state.object;

    while(list->next != NULL){
      list = list->next;
    }
    list->next = file;
    
    if (file->processor != state.processor)
      gp_error("processor mismatch in \"%s\"", file->filename);
  }

  return;
}

void archive_append(gp_archive_type *file, char *name)
{
  struct archivelist *new;

  /* make the new entry */  
  new = (struct archivelist *)malloc(sizeof(*new));
  new->name = strdup(name); 
  new->archive = file;
  new->next = NULL;
  
  /* append the entry to the list */
  if (state.archives == NULL) {
    state.archives = new;
  } else {
    struct archivelist *list = state.archives;

    while(list->next != NULL){
      list = list->next;
    }
    list->next = new;
  }

  return;
}

/* Scan the archive for missing symbol definitions.  This has to be done
   recursively.  The order of the archive members is unknown and there
   might be inter member dependancies.  Scan the archive muliple times.  
   Stop whenever a complete pass through the archive happens and no
   objects are added. */

int scan_index(struct symbol_table *table, gp_archive_type *archive)
{
  struct symbol *s;
  struct symbol *m;
  gp_archive_type *member;
  gp_object_type *object;
  int i;
  int num_added = 1; /* initalize to 1 so while loop can be entered */
  char *name;
  char *object_name;

  while (num_added != 0) {
    num_added = 0;
    for (i = 0; i < HASH_SIZE; i++) {
      for (s = state.symbol.missing->hash_table[i]; s; s = s->next) {
	name = get_symbol_name(s);
        assert(name != NULL);
        /* Search for missing symbol name in archive symbol table */
        m = get_symbol(table, name);
        if (m != NULL) {
          /* Fetch the archive member, convert its binary data to an object 
	     file, and add the object to the object list */ 
          member = get_symbol_annotation(m);
          object_name = gp_archive_member_name(member);
          object = gp_convert_file(object_name, member->file);
          object_append(object, object_name);	
          gp_link_add_symbols(state.symbol.definition, 
                              state.symbol.missing, 
			      object);		
          /* The symbol tables have been modified.  Need to take another
	     pass to make sure we get everything. */
          num_added++;
          free(object_name);
          /* This branch of the table has been modified. Go to the next one */
	  break;
	}      
      }
    }
  }

  return 0;
}
    
int scan_archive(gp_archive_type *archive, char *name)
{
  state.symbol.archive = push_symbol_table(NULL, 0);

  /* If necessary, build a symbol index for the archive. */
  if (gp_archive_have_index(archive) == 0) {
    struct symbol_table *archive_tbl = NULL;
  
    archive_tbl = push_symbol_table(NULL, 1);
    gp_archive_make_index(archive, archive_tbl);
    archive = gp_archive_add_index(archive_tbl, archive);
    gp_warning("\"%s\" is missing symbol index", name);
    archive_tbl = pop_symbol_table(archive_tbl);
  }

  /* Read the symbol index */
  gp_archive_read_index(state.symbol.archive, archive);

  /* Scan the symbol index for symbols in the missing symbol table.  If
     found, add the object to state.objects. */
  scan_index(state.symbol.archive, archive);

  state.symbol.archive = pop_symbol_table(state.symbol.archive);

  return 0;
}

/* Build the symbol tables.  Determine which objects from the archives are 
   required for linking */
    
void build_tables(void)
{
  gp_object_type *list = state.object;
  struct archivelist *arlist = state.archives;

  /* Create the object file symbol tables */  
  while (list != NULL) {
    gp_link_add_symbols(state.symbol.definition, 
                        state.symbol.missing, 
			list);
    list = list->next;
  }

  /* All of the objects have been scanned.  If there are remaining references
     to symbols, then the archives must contain the missing references. */
  if (count_missing()) {
    while (arlist != NULL) {
      scan_archive(arlist->archive, arlist->name);
      if (count_missing() == 0) {
        /* No more missing references, no need to continue. */
        break;
      }
      arlist = arlist->next;
    }
  }

  if (count_missing()) {
    gp_error("missing definitions for external references");
    exit(1);
  }

  return;
}

/* Read a coff object or archive.  gplink doesn't care about file extensions.
   This allows alternate extensions such as .a archives and .obj coff 
   objects.  */

void gplink_open_coff(char *name)
{
  gp_object_type *object;
  gp_archive_type *archive;
  
  /* FIXME:  need to add include pathes to this search */

  switch(gp_identify_coff_file(name)) {
  case object_file:
    /* read the object */  
    object = gp_read_coff(name);
    object_append(object, name);
    break;
  case archive_file:
    /* read the archive */  
    archive = gp_archive_read(name);
    archive_append(archive, name);
    break;
  case sys_err_file:
    gp_error("can't open file \"%s\"", name);     
    break;
  case unknown_file:
    gp_error("\"%s\" is not a valid coff object or archive", name);     
    break; 
  default:
    assert(0);
  }

}   

void gplink_add_path(char *path)
{
  if(state.numpaths < MAX_PATHS) {
    state.paths[state.numpaths++] = strdup(path);
  } else {
    gp_error("too many -I paths");
  }
}

void show_usage(void)
{
  printf("Usage: gplink [options] [objects] [libraries] \n");
  printf("Options: [defaults in brackets after descriptions]\n");
  printf("  -a FMT, --hex-format FMT       Select hex file format.\n");
  printf("  -c, --object                   Output executable object file.\n");
  printf("  -d, --debug                    Output debug messages.\n");
  printf("  -h, --help                     Show this usage message.\n");
  printf("  -I DIR, --include DIR          Specify include directory.\n");
  printf("  -m, --map                      Output a map file.\n");
  printf("  -o FILE, --output FILE         Alternate name of output file.\n");
  printf("  -q, --quiet                    Quiet.\n");
  printf("  -s FILE, --script FILE         Linker script.\n");
  printf("  -v, --version                  Show version.\n");
  printf("\n");
  printf("Report bugs to:\n");
  printf("%s\n", BUG_REPORT_URL);
  exit(0);
}

#define GET_OPTIONS "?a:cdhI:mo:qs:v"

  static struct option longopts[] =
  {
    { "hex-format",  1, 0, 'a' },
    { "object",      0, 0, 'c' },
    { "debug",       0, 0, 'd' },
    { "help",        0, 0, 'h' },
    { "include",     1, 0, 'I' },
    { "map",         0, 0, 'm' },
    { "output",      1, 0, 'o' },
    { "quiet",       0, 0, 'q' },
    { "script",      1, 0, 'r' },
    { "version",     0, 0, 'v' },
    { 0, 0, 0, 0 }
  };

#define GETOPT_FUNC getopt_long(argc, argv, GET_OPTIONS, longopts, 0)

int main(int argc, char *argv[])
{
  extern char *optarg;
  extern int optind;
  int c;
  int usage = 0;
  char *pc;

  /* initialize */
  state.mode = _hex;
  state.hex_format = inhx32;
  state.srcfilename = NULL;
  state.object  = NULL;
  state.archives = NULL;
  state.map.enabled = 0;

  /* The symbols are case sensitive */
  state.symbol.definition = push_symbol_table(NULL, 0);
  state.symbol.missing = push_symbol_table(NULL, 0);
  state.section.definition = push_symbol_table(NULL, 0);
  state.section.logical = push_symbol_table(NULL, 0);

  #ifdef PARSE_DEBUG
  {
    extern int yydebug;
    yydebug = 1; /* enable parse debug */
  }
  #endif
 
  while ((c = GETOPT_FUNC) != EOF) {
    switch (c) {
    case 'a':

      break;
    case 'c':
      state.mode = _object;
      break;
    case 'd':
      gp_debug_disable = 0;
      break;
    case '?':
    case 'h':
      usage = 1;
      break;
    case 'I':
      gplink_add_path(optarg);
      break;
    case 'm':
      state.map.enabled = 1;
      break;
    case 'o':
      strcpy(state.basefilename, optarg);
      pc = strrchr(state.basefilename, '.');
      if (pc)
        *pc = 0;
      break;
    case 'q':
      gp_quiet = 1;
      break;
    case 's':
      state.srcfilename = optarg;
      break;
    case 'v':
      fprintf(stderr, "%s\n", GPLINK_VERSION_STRING);
      exit(0);
    }
    if (usage)
      break;
  }

  /* FIXME: Remove this test, scripts can also specify the files. Later in
    check that there is at least one object name passed to linker */
  if (optind >= argc) {
    usage = 1;
  }

  if (usage) {
    show_usage();
  }

  if(state.basefilename[0] == '\0') {
    /* set default output filename to be a.o, a.hex, a.cod, a.map */
    strcpy(state.basefilename, "a");
  }

  /* setup output filenames */
  strcpy(state.codfilename, state.basefilename);
  strcat(state.codfilename, ".cod");  
  strcpy(state.hexfilename, state.basefilename);
  strcat(state.hexfilename, ".hex");  
  strcpy(state.mapfilename, state.basefilename);
  strcat(state.mapfilename, ".map");  
  strcpy(state.objfilename, state.basefilename);
  strcat(state.objfilename, ".o");  

  /* Open all objects and archives in the file list. */ 
  for ( ; optind < argc; optind++) {
    gplink_open_coff(argv[optind]);
  }

  /* Read the script */
  if (state.srcfilename != NULL) {
    open_src(state.srcfilename, 0);
    yyparse();
  } else {
    /* FIXME: Maybe add a default script so a user supplied one isn't always 
       necessary. */ 
    gp_error("linker command file not specified");
  }

  /* Construct the symbol tables. Determine which archive members are 
     required to resolve external references.  */
  build_tables();  

  /* relocate the sections */
  gp_cofflink_reloc(state.object, 
                    state.section.definition, 
                    state.section.logical);  
	
  /* patch raw data with the relocated symbol values */
  gp_cofflink_patch(state.object, state.symbol.definition);

  /* clean up symbol table */
  gp_cofflink_clean_table(state.object);

  /* modify the executable object data */
  state.object->filename = strdup(state.objfilename);
  state.object->flags |= F_EXEC;

  /* write output file */
  if (state.mode == _object) {
    /* write the executable object in memory */
    gp_write_coff(state.object, gp_num_errors);
  } else {
    MemBlock *m;
     
    /* convert the executable object into a hex file */
    m = gp_cofflink_make_memory(state.object);
    writehex(state.basefilename,
             m,
             state.hex_format,
             gp_num_errors,
             0,
             0);
    i_memory_free(m);

    /* convert the executable object into a cod file */

  }

  /* write map file */
  make_map();
  
  if (gp_num_errors > 0)
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;

}
