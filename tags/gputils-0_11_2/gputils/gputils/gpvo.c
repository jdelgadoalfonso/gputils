/* GNU PIC view object
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
#include "gpvo.h"

struct gpvo_state state;

void print_header(gp_object_type *object) 
{
  char *time = ctime(&object->time);
  char *processor_name = gp_processor_name(object->processor, 2);
  
  /* strip the newline from time */
  time[strlen(time)-1] = '\0';

  printf("COFF File and Optional Headers\n");
  printf("Processor Type       %s\n",   processor_name);
  printf("Time Stamp           %s\n",   time);
  printf("Number of Sections   %li\n",  object->num_sections);
  printf("Number of Symbols    %li\n",  object->num_symbols);
  printf("Characteristics      %#x\n",  object->flags);

  if (object->flags & F_RELFLG) {
    printf("  Relocation info has been stripped.\n");
  }
  if (object->flags & F_EXEC) {
    printf("  File is executable.\n");
  }
  if (object->flags & F_LNNO) {
    printf("  Line numbers have been stripped.\n");
  }
  if (object->flags & L_SYMS) {
    printf("  Local symbols have been stripped.\n");
  }
  if (object->flags & F_GENERIC) {
    printf("  Processor independant file for a core.\n");
  }

  printf("\n");
  return;
}

void print_reloc_list(gp_reloc_type *relocation)
{
  printf("Relocations Table\n");
  printf("Address    Offset     Type   Symbol\n");

  while (relocation != NULL) {
    printf("%#-10lx %#-10x %#-6x %-s\n", 
           relocation->address,
           relocation->offset,
           relocation->type,
           relocation->symbol->name);
    
    relocation = relocation->next;
  }

  printf("\n");

}

void print_linenum_list(gp_linenum_type *linenumber)
{
  char *filename;

  printf("Line Number Table\n");
  printf("Line     Address  Symbol\n");

  while (linenumber != NULL) {
    if (state.suppress_names) {
      filename = linenumber->symbol->name;
    } else {
      filename = linenumber->symbol->aux_list->_aux_symbol._aux_file.filename;
    }

    printf("%-8i %#-8lx %s\n", 
           linenumber->line_number,
           linenumber->address,
           filename);
  
    linenumber = linenumber->next;
  }

  printf("\n");

}

void print_data(enum proc_class class, MemBlock *data, int org, int disassemble)
{
  int memory;
  char buffer[BUFSIZ];
  
  buffer[0] = '\0';
  
  printf("Data\n");
  while (1) {
    memory = i_memory_get(data, org);
    if ((memory && MEM_USED_MASK) == 0)
      break;
    
    if (disassemble)
      gp_disassemble(data, &org, class, buffer);

    printf("%06x:  %04x  %s\n", org, memory & 0xffff, buffer);
    org++;
  }
  printf("\n");

}

void print_sec_header(gp_section_type *section)
{

  printf("Section Header\n");
  printf("Name                    %s\n",   section->name);
  printf("Address                 %#lx\n", section->address);
  printf("Size of Section         %li\n",  section->size);
  printf("Number of Relocations   %i\n",   section->num_reloc);
  printf("Number of Line Numbers  %i\n",   section->num_lineno);
  printf("Flags                   %#lx\n", section->flags); 
  if (section->flags & STYP_TEXT) {
    printf("  Executable code.\n");
  }
  if (section->flags & STYP_DATA) {
    printf("  Initialized data.\n");
  }
  if (section->flags & STYP_BSS) {
    printf("  Uninitialized data.\n");
  }
  if (section->flags & STYP_DATA_ROM) {
    printf("  Initialized data for ROM.\n");
  }
  if (section->flags & STYP_ABS) {
    printf("  Absolute.\n");
  }
  if (section->flags & STYP_SHARED) {
    printf("  Shared across banks.\n");
  }
  if (section->flags & STYP_OVERLAY) {
    printf("  Overlaid with other sections from different objects modules.\n");
  }
  if (section->flags & STYP_ACCESS) {
    printf("  Available using access bit.\n");
  }
  if (section->flags & STYP_ACTREC) {
    printf("  Contains the activation record for a function.\n");
  }

  printf("\n"); 

}

void print_sec_list(gp_object_type *object)
{
  gp_section_type *section = object->sections;

  while (section != NULL) {
    print_sec_header(section);

    if (section->size) {
      print_data(object->class,
                 section->data,
                 section->address,
                 section->flags & STYP_TEXT);
    }
    if (section->num_reloc) {
      print_reloc_list(section->relocations);
    }
    if (section->num_lineno) {
      print_linenum_list(section->line_numbers);
    }
    
    section = section->next;
  }

}

void print_sym_table (gp_object_type *object)
{
  gp_symbol_type *symbol;
  gp_aux_type *aux;
  char *section;
  int i;

  symbol = object->symbols;

  printf("Symbol Table\n");
  printf("Name                     Section          Value      Type  Class  NumAux \n");

  while (symbol != NULL) {
    
    if (symbol->section_number == N_DEBUG) {
      section = "DEBUG";
    } else if (symbol->section_number == N_ABS) {
      section = "ABSOLUTE";
    } else if (symbol->section_number == N_UNDEF) {
      section = "UNDEFINED";
    } else {
      assert(symbol->section != NULL);
      section = symbol->section->name;
    }    
    
    printf("%-24s %-16s %#-10lx %-4i  %-4i   %-4i\n", 
           symbol->name,
           section,
           symbol->value,
           symbol->type,
           symbol->class,
           symbol->num_auxsym);

    if (symbol->num_auxsym != 0) {
      aux = symbol->aux_list;
      
      switch (aux->type) {
      case AUX_FILE:
        if (!state.suppress_names) {
          printf("  file = %s\n", 
                 aux->_aux_symbol._aux_file.filename);
        }
        printf("  line included = %li\n", 
               aux->_aux_symbol._aux_file.line_number);
        break;
      case AUX_SCN:
        printf("  length = %li\n", 
               aux->_aux_symbol._aux_scn.length);
        printf("  number of relocations = %i\n", 
               aux->_aux_symbol._aux_scn.nreloc);
        printf("  number of line numbers = %i\n", 
               aux->_aux_symbol._aux_scn.nlineno);
        break;
      default:
        printf("  ");
        for (i = 0; i < SYMBOL_SIZE; i++)
          printf("%2x", aux->_aux_symbol.data[i]);
      }
    }

    symbol = symbol->next;
  }

  printf("\n"); 

  return;
}

void print_binary(char *data, long int file_size) 
{

  long int i, j;
  int memory;
  char c;

  printf("\nObject file size = %li bytes\n", file_size);

  printf("\nBinary object file contents:");
  for (i = 0; i < file_size; i += 16) {
    printf("\n%06lx", i);

    for(j = 0; j < 16; j += 2) {
      memory = data[i + j];
      memory = ((memory << 8) & 0xff00) | (data[i+j+1] & 0xff); 
      if ((i+j) >= file_size) {
        printf("     ");      
      } else {
        printf(" %04x", memory);
      }
    }

    printf(" ");
    
    for(j = 0; j < 16; j += 2) {
      if ((i+j) < file_size) {      
        c = data[i + j] & 0xff;
        putchar( (isprint(c)) ? c : '.');

        c = data[i + j + 1] & 0xff;
        putchar( (isprint(c)) ? c : '.');
      }
    }
    
  }

  printf("\n\n");

  return;
}

void show_usage(void)
{
  printf("Usage: gpvo [options] file\n");
  printf("Options: [defaults in brackets after descriptions]\n");
  printf("  -b, --binary               Print binary data.\n");
  printf("  -f, --file                 File header.\n");
  printf("  -h, --help                 Show this usage message.\n");
  printf("  -n, --no-names             Suppress filenames.\n");
  printf("  -s, --section              Section data.\n");
  printf("  -t  --symbol               Symbol table.\n");
  printf("  -v, --version              Show version.\n");
  printf("\n");
  printf("Report bugs to:\n");
  printf("%s\n", BUG_REPORT_URL);
  exit(0);
}

#define GET_OPTIONS "?bfhnstv"

  /* Used: himpsv */
  static struct option longopts[] =
  {
    { "binary",      0, 0, 'b' },
    { "file",        0, 0, 'f' },
    { "help",        0, 0, 'h' },
    { "no-names",    0, 0, 'n' },
    { "section",     0, 0, 's' },
    { "symbol",      0, 0, 't' },
    { "version",     0, 0, 'v' },
    { 0, 0, 0, 0 }
  };

#define GETOPT_FUNC getopt_long(argc, argv, GET_OPTIONS, longopts, 0)

int main(int argc, char *argv[])
{
  extern int optind;
  int c;
  int usage = 0;

  /* initalize */
  state.quiet = 0;
  state.dump_flags = 0;
  state.suppress_names = 0;

  while ((c = GETOPT_FUNC) != EOF) {
    switch (c) {
    case '?':
    case 'h':
      usage = 1;
      break;
    case 'b':
      state.dump_flags |= PRINT_BINARY;
      break;
    case 'f':
      state.dump_flags |= PRINT_HEADER;
      break;
    case 'n':
      state.suppress_names = 1;
      break;
    case 's':
      state.dump_flags |= PRINT_SECTIONS;
      break;
    case 't':
      state.dump_flags |= PRINT_SYMTBL;
      break;
    case 'v':
      fprintf(stderr, "%s\n", GPVO_VERSION_STRING);
      exit(0);
    }
    if (usage)
      break;
  }

  if (optind < argc) {
    state.filename = argv[optind];
  } else {
    usage = 1;
  }

  if (usage) {
    show_usage();
  }

  if (!state.dump_flags) {
    /* no command line flags were set so print everything */
    state.dump_flags = 0xff;
  }

  if (gp_identify_coff_file(state.filename) != object_file) {
    gp_error("\"%s\" is not a valid object file", state.filename);
    exit(1);
  }

  state.object = gp_read_coff(state.filename);
  state.file = gp_read_file(state.filename);
  
  if (state.dump_flags & PRINT_BINARY) {
    print_binary(state.file->file, state.file->size);
  }

  if (state.dump_flags & PRINT_HEADER) {
    print_header(state.object);
  }

  if (state.dump_flags & PRINT_SECTIONS) {
    print_sec_list(state.object);
  }

  if (state.dump_flags & PRINT_SYMTBL) {
    print_sym_table(state.object);
  }

  return EXIT_SUCCESS;

}
