/* inc to pub file converter
   Copyright (C) 2004
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
#include "libgpasm.h"
#include "gpasm.h"

#ifdef STDC_HEADERS
#include <stdarg.h>
#endif

#define GP2PUB_VERSION_STRING ("gp2pub-" VERSION " alpha")

/* Generate a public file for gpal. */

void write_pub(void)
{
  FILE *f;
  int i;
  struct symbol **lst, **ps, *s;
  struct variable *var;
  char *processor_name;
  char pub_name[BUFSIZ];

  processor_name = gp_processor_name(state.processor, 1);

  strcpy(pub_name, processor_name);
  strcat(pub_name, ".pub");  

  f = fopen(pub_name, "wt");
  if (f == NULL) {
    perror(pub_name);
    exit(1);
  }

  fprintf(f, "-- %s\n", pub_name);
  fprintf(f, "-- automatically generated by gp2pub\n\n");

  fprintf(f, "public %s is\n\n", processor_name);

  ps = lst = malloc(state.stGlobal->count * sizeof(lst[0]));

  for (i = 0; i < HASH_SIZE; i++)
    for (s = state.stGlobal->hash_table[i]; s; s = s->next) 
      *ps++ = s;

  assert(ps == &lst[state.stGlobal->count]);

  qsort(lst, state.stGlobal->count, sizeof(lst[0]), symbol_compare);

  for (i = 0; i < state.stGlobal->count; i++) {
    var = get_symbol_annotation(lst[i]);
    assert(var != NULL);
    fprintf(f, "  %-18s : ", get_symbol_name(lst[i])); 
    if (!var->register_file) {
      fprintf(f, "constant "); 
    }
    if ((var->register_file) || (var->value < 0x100)) {
      fprintf(f, "uint8 ");
    } else if (var->value < 0x10000) {
      fprintf(f, "uint16 ");
    } else if (var->value < 0x1000000) {
      fprintf(f, "uint24 ");
    } else {
      fprintf(f, "uint32 ");
    }
    if (var->register_file) {
      fprintf(f, "at ");
    } else {
      fprintf(f, "= ");
    }
    fprintf(f, "%#x;\n", var->value);
  }

  fprintf(f, "\nend public;\n\n");

  fclose(f);
  
  return;
}

void show_usage(void)
{
  printf("Usage: gp2pub [options] file\n");
  printf("Options: [defaults in brackets after descriptions]\n");
  printf("  -h, --help                 Show this usage message.\n");
  printf("  -v, --version              Show version.\n");
  printf("\n");
  printf("Report bugs to:\n");
  printf("%s\n", BUG_REPORT_URL);
  exit(0);
}

#define GET_OPTIONS "?hv"

  static struct option longopts[] =
  {
    { "help",        0, 0, 'h' },
    { "version",     0, 0, 'v' },
    { 0, 0, 0, 0 }
  };

#define GETOPT_FUNC getopt_long(argc, argv, GET_OPTIONS, longopts, 0)


int 
main(int argc, char *argv[])
{
  extern int optind;
  int c;
  int usage = 0;

  while ((c = GETOPT_FUNC) != EOF) {
    switch (c) {
    case '?':
    case 'h':
      usage = 1;
      break;
    case 'v':
      fprintf(stderr, "%s\n", GP2PUB_VERSION_STRING);
      exit(0);
    }
    if (usage)
      break;
  }

  if ((optind + 1) == argc) {
    state.srcfilename = argv[optind];
  } else {
    usage = 1;
  }

  if (usage) {
    show_usage();
  }

  init();

  if (gp_header_path) {
    add_path(gp_header_path);
  }

  /* disable standard gpasm outputs */
  state.codfile = suppress;
  state.hexfile = suppress;
  state.lstfile = suppress;
  state.objfile = suppress;

  if ((gp_num_errors > 0) || (assemble() == EXIT_FAILURE))  {
    return EXIT_FAILURE;
  } else {
    write_pub();
  }

  return EXIT_SUCCESS;
}
