/* Read ".HEX" files and store it in memory
   Copyright (C) 2001, 2002, 2003, 2004, 2005
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

#define LINESIZ 520

char linebuf[LINESIZ];
char *linept;
int checksum;
FILE *infile;

/* Converts a single ASCII character into a number */
unsigned int a2n(char character)
{
  unsigned int number;
  if(character < 0x3A) {
    number = character-0x30;
  } else {
    /* convert lower case to upper */
    character &= 0xDF;
    number = character-0x37;
  } 
  return number;
}

unsigned int readbyte()
{
  unsigned int number;
  linept++;
  number = a2n(*linept) << 4;
  linept++;
  number |= a2n(*linept);
  checksum += number;
  return number;
} 

unsigned int readword()
{
  unsigned int number;
  number = readbyte();  
  number = (readbyte() << 8) | number; 
  return number; 
}

unsigned int swapword(unsigned int input)
{
  unsigned int number;
  number = ((input & 0xFF) << 8) | ((input & 0xFF00) >> 8); 
  return number; 
}

struct hex_data *
readhex(char *filename, MemBlock *m)
{
  struct hex_data *info = malloc(sizeof(*info));
  int length, address, type, data;
  int i;
  int page = 0;
  int length_step;

  info->hex_format = inhx8m;
  info->size = 0;
  info->error = 0;

  /* Open the input file */
  if ( (infile = fopen(filename,"rt")) == NULL ){
    perror(filename);
    exit(1);
  }
    
  /* go to the beginning of the file */
  fseek(infile, 0L, 0);	  

  /* set the line pointer to the beginning of the line buffer */
  linept = linebuf;

  /* read a line of data from the file, if NULL stop */
  while(fgets(linept, LINESIZ, infile))
  {
    /* set the line pointer to the beginning of the line buffer */
    linept = linebuf;

    checksum = 0;

    /* fetch the number of bytes */
    length = readbyte();
    if (length == 0) {
      fclose(infile);
      return info;
    }

    if (info->hex_format != inhx16) {
      length_step = 2;
    } else {
      length_step = 1;
    }
    
    /* fetch the address */
    address = readword();
    address = swapword(address);

    if (info->hex_format == inhx16) {
      address = address * 2;
    }
    
    /* read the type of record */
    type = readbyte();

    if (type == 4) {

      if (info->hex_format == inhx16) {
        printf("\nhex format error\n");
        fclose(infile);
        info->error = 1;
        return info;      
      }

      /* inhx32 segment line*/
      page = readword();
      info->hex_format = inhx32;

    } else {
      if ((length_step == 2) && ((address % 2) != 0)) {
        /* we're starting in the middle of a word */
        /* merge this byte with word already in memory */
        data = i_memory_get(m,
                     ((page << 16) | (address >> 1))) & 0xFF;
        data |= (readbyte() << 8);
        i_memory_put(m,
                     ((page << 16) | (address >> 1)),
                     data | MEM_USED_MASK);
        ++address;
        --length;
      }

      /* read the data (skipping last byte if at odd address) */
      for (i = 0; i < (length & ~0x1); i += length_step) {
        data = readword();
        if (info->hex_format == inhx16) {
          data = swapword(data);        
        }
        i_memory_put(m, 
                     ((page << 16) | (address + i)>>1),  
                     data | MEM_USED_MASK);
      }

      if ((length_step == 2) && ((length % 2) != 0)) {
        /* we're ending in the middle of a word */
        /* merge this byte with word already in memory */
        unsigned int word_address = (page << 16) | ((address+length) >> 1);
        data = i_memory_get(m, word_address) & 0xFF00;
        data |= readbyte();
        i_memory_put(m, word_address, data | MEM_USED_MASK);
      }

      info->size += (length * length_step); 

    }
    
    /* read the checksum, data is thrown away*/
    data = readbyte();
    
    if ((checksum & 0xFF) != 0) { 
      if (info->hex_format == inhx8m) {
        /*  first attempt at inhx8m failed, try inhx16 */
        fseek(infile, 0L, 0);	  
        info->hex_format = inhx16;
        info->size = 0;
        /* data in i_memory is trash */
        i_memory_free(m);
        m = i_memory_create();
      } else {
        printf("\nChecksum Error\n");
        fclose(infile);
        info->error = 1;
        return info;
      }
    }

    /* set the line pointer to the beginning of the line buffer */
    linept = linebuf;
     
  }

  fclose(infile);

  return info;
}
