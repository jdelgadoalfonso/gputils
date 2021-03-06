/* ".LST" file output for gpasm
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

#include "stdhdr.h"

#include "gpasm.h"
#include "gpsymbol.h"
#include "cod.h"

extern int _16bit_core;

void lst_throw()
{
  if(state.lst.f) {
    state.lst.page++;
    fprintf(state.lst.f,
	    "%s%-32s%-12s%-29sPAGE %2d\n%s\n%s\n",
	    (state.lst.page == 1) ? "" : "\f",
	    GPASM_VERSION_STRING,
	    state.srcfilename,
	    state.lst.startdate,
	    state.lst.page,
	    state.lst.title_name,
            state.lst.subtitle_name);
    state.lst.lineofpage = 4;
    cod_lst_line(COD_NORMAL_LST_LINE);
    cod_lst_line(COD_NORMAL_LST_LINE);
    cod_lst_line(COD_NORMAL_LST_LINE);
    state.lst.line_number += 3;
  }
}

void lst_line(char *line)
{
  if (state.lst.f) {
    if (state.lst.linesperpage != 0) {
      if ((state.lst.lineofpage++ % state.lst.linesperpage) == 0) {
        lst_throw();
        lst_line("LOC  OBJECT CODE     LINE SOURCE TEXT");
        lst_line("  VALUE");
        lst_line(" ");
      }
    }
    fprintf(state.lst.f, "%s\n", line);
    state.lst.line_number++;
    cod_lst_line(COD_NORMAL_LST_LINE);
  }
}

void lst_init()
{

  state.lst.linesperpage = 60;
  state.lst.memorymap = 1;
  state.lst.symboltable = 1;

  if (state.cmd_line.macro_expand == 0){
    state.lst.expand = 1;
  }  

  switch (state.lstfile) {
  case suppress:
    state.lst.f = NULL;
    state.lst.enabled = 0;
    break;
  case normal:
    strcpy(state.lstfilename, state.basefilename);
    strcat(state.lstfilename, ".lst");
  case named:
    /* Don't need to do anything - name is already set up */
    state.lst.f = fopen(state.lstfilename, "w");
    if (state.lst.f == NULL) {
      perror(state.lstfilename);
      exit(1);
    }
    state.lst.fc = add_file(ft_lst,state.lstfilename);
    state.lst.enabled = 1;
  }

  /* Determine state.startdate */
  {
    time_t now;
    struct tm *now_tm;

    time(&now);
    now_tm = localtime(&now);
    sprintf(state.lst.startdate,
	    "%d-%d-%d  %02d:%02d:%02d",
	    now_tm->tm_mon + 1,
	    now_tm->tm_mday,
	    1900 + now_tm->tm_year,
	    now_tm->tm_hour,
	    now_tm->tm_min,
	    now_tm->tm_sec);
  }

  state.lst.tabstop = 8;	/* Default tabstop every 8 */
  state.lst.line_number = 1;

  cod_lst_line(COD_FIRST_LST_LINE);

}

void lst_memory_map(MemBlock *m)
{
  char buf[BUFSIZ];
  char *e;
  int i, j, base, row_used;

  lst_line("");
  lst_line("");
  lst_line("MEMORY USAGE MAP ('X' = Used,  '-' = Unused)");
  lst_line("");

  while(m) {
    assert(m->memory != NULL);

    base = (m->base << I_MEM_BITS);

    for(i = 0; i<MAX_I_MEM; i+=64) {
      row_used = 0;

      for(j = 0; j<64; j++)
	if( m->memory[i+j] )
	  row_used = 1;

      if(row_used) {
        e = buf;
        sprintf(e, "%04x :", (i + base));
	e += strlen(e);
	for(j = 0; j<64; j++) {
          if ((j%16) == 0) {
	    *e++ = ' ';
          }
          if ((i_memory_get(m, i+j) & MEM_USED_MASK)) {
	    *e++ = 'X';
          } else {
	    *e++ = '-';
          }
        }

	*e = '\0';		/* terminate the new string */
        lst_line(buf);
      }
    }

    m = m->next;
  }

  lst_line("");
  lst_line("All other memory blocks unused.");
  lst_line("");

  sprintf(buf, "Program Memory Words Used: %i", i_memory_used(state.i_memory));
  lst_line(buf);

}

void lst_close()
{
  cod_lst_line(COD_LAST_LST_LINE);
  fprintf(state.lst.f,
	  "\n\n");
  fprintf(state.lst.f,
	  "Errors   : %7d\n",
	  state.num.errors);
  fprintf(state.lst.f,
	  "Warnings : %7d reported, %7d suppressed\n",
	  state.num.warnings,
          state.num.warnings_suppressed);
  fprintf(state.lst.f,
	  "Messages : %7d reported, %7d suppressed\n",
	  state.num.messages,
          state.num.messages_suppressed);
  fprintf(state.lst.f,
	  "\f\n");

  fclose(state.lst.f);
}

void lst_format_line(char *src_line, int value)
{
  char m[BUFSIZ];
  char *e;
  unsigned int emitted = 0;

  e = m;
  switch (state.lst.line.linetype) {
  case equ: 
  case set:
    sprintf(e, "  %08X", value);
    e += strlen(e);
    strcpy(e, "     ");
    e += 5;
    break;
  case org:
    sprintf(e, "%04X      ", state.org << _16bit_core);
    e += strlen(e);
    strcpy(e, "     ");
    e += 5;
    break;
  case idlocs:
    /* not used for 16 bit devices, config is used */
    sprintf(e, "%04X %04X %04X ",
            state.device.id_location,
            i_memory_get(state.i_memory, state.device.id_location) & 0xffff,
            i_memory_get(state.i_memory, 
		         state.device.id_location + 1) & 0xffff);
    e += strlen(e);
    break;
  case insn:
    sprintf(e, "%04X ", state.lst.line.was_org << _16bit_core);
    e += strlen(e);
    emitted = state.org - state.lst.line.was_org;
    if (emitted >= 1)
      sprintf(e, "%04X ", i_memory_get(state.i_memory, 
			               state.lst.line.was_org) & 0xffff);
    else
      sprintf(e, "     ");
    e += strlen(e);
    if (emitted >= 2)
      sprintf(e, "%04X ", i_memory_get(state.i_memory, 
			               state.lst.line.was_org + 1) & 0xffff);
    else
      sprintf(e, "     ");
      e += strlen(e);
    break;
  case config:
    if(_16bit_core) {
      /* config data is byte addressable, but we only want to print
	 words in the list file. */
      if (state.lst.config_address == CONFIG4L) {
        /* Special case */
        sprintf(e, "%06X %04X    ",   
                state.lst.config_address,
                i_memory_get(state.i_memory, 
			     state.lst.config_address >> 1) & 0xffff);
        e += strlen(e);	  
      } else if((state.lst.config_address & 0x1) == 0) {
        /* if it is an even address don't print anything */
	strcpy(e, "               ");
        e += 15;
      } else {
        sprintf(e, "%06X %04X    ",   
                state.lst.config_address - 1,
                i_memory_get(state.i_memory, 
			    (state.lst.config_address - 1) >> 1) & 0xffff);
        e += strlen(e);
      }
    } else {
      sprintf(e, "%06X %04X    ",   
              state.lst.config_address,
              i_memory_get(state.i_memory, 
		           state.lst.config_address) & 0xffff);
      e += strlen(e);
    }
    break;
  case dir:
  case none:
  default:
    strcpy(e, "               ");
    e += 15;
    break;
  }

  if (state.stGlobal == state.stTop) {
    sprintf(e, "%05d ", state.src->line_number);
  } else {		  
    sprintf(e, "    M ");
  }
  e += strlen(e);

  /* Now copy 'l' to 'e', expanding tabs as required */
  {
    int column = 0;
    char *old;
        
    old = src_line;

    while (*old) {
      if (*old == '\t') {
        *e++ = ' ';
        column++;
	while ((column % state.lst.tabstop) != 0) {
          *e++ = ' ';
          column++;
        }
      } else {
        *e++ = *old;
        column++;
      }
      old++;
    }
    *e = '\0';		/* terminate the new string */
  }

  /* Tell the .cod file that the next line(s) has an opcode(s) */
  state.cod.emitting = emitted;

  lst_line(m);

  if (state.lst.line.linetype == idlocs) {
    sprintf(m, "     %04X %04X ",
            i_memory_get(state.i_memory, 
		         state.device.id_location + 2) & 0xffff,
            i_memory_get(state.i_memory, 
		         state.device.id_location + 3) & 0xffff);      
    lst_line(m);   
  }

  if (emitted > 2) {
    int i;

    for (i = 2; i < emitted; i += 2) {
      if ((i + 1) < emitted)
        sprintf(m, "%04X %04X %04X",
                ((state.lst.line.was_org + i) << _16bit_core),
                i_memory_get(state.i_memory, 
                             state.lst.line.was_org + i) & 0xffff,
		i_memory_get(state.i_memory, 
                             state.lst.line.was_org + i + 1) & 0xffff);
      else
        sprintf(m, "%04X %04X",
		((state.lst.line.was_org + i) << _16bit_core),
		i_memory_get(state.i_memory, 
			     state.lst.line.was_org + i) & 0xffff);
        lst_line(m);
      }

    state.cod.emitting = 0;
  }
}

/* append the symbol table to the .lst file */

void lst_symbol_table(struct symbol_table *table)
{
  int i;
  const char *symbol_format = "%-32s  %08X";
  struct symbol **lst, **ps, *s;
  char buf[BUFSIZ];

  lst_line("SYMBOL TABLE");
  sprintf(buf, "%-32s  %-8s", "  LABEL", "  VALUE");
  lst_line(buf);
  lst_line("");

  ps = lst = malloc(table->count * sizeof(lst[0]));

  for (i = 0; i < HASH_SIZE; i++)
    for (s = table->hash_table[i]; s; s = s->next) 
      *ps++ = s;

  assert(ps == &lst[table->count]);

  qsort(lst, table->count, sizeof(lst[0]), symbol_compare);

  for (i = 0; i < table->count; i++) {
    struct variable *var;

    var = get_symbol_annotation(lst[i]);
    sprintf(buf,
            symbol_format, 
            get_symbol_name(lst[i]),
            var ? var->value : 0);
    lst_line(buf);
  }
  cod_write_symbols(lst,table->count);
}

void lst_defines_table(struct symbol_table *table)
{
  int i;
  const char *symbol_format = "%-32s  %s";
  struct symbol **lst, **ps, *s;
  char buf[BUFSIZ];

  ps = lst = malloc(table->count * sizeof(lst[0]));

  for (i = 0; i < HASH_SIZE; i++)
    for (s = table->hash_table[i]; s; s = s->next) 
      *ps++ = s;

  assert(ps == &lst[table->count]);

  qsort(lst, table->count, sizeof(lst[0]), symbol_compare);

  for (i = 0; i < table->count; i++) {
    char *defined_as;

    defined_as = get_symbol_annotation(lst[i]);
    sprintf(buf,
            symbol_format, 
            get_symbol_name(lst[i]),
            defined_as);
    lst_line(buf);
  }
}
