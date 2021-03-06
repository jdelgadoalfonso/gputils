/* Disassemble memory
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

#define DECODE_ARG0 sprintf(buffer, "%s", instruction->name)

#define DECODE_ARG1(ARG1) sprintf(buffer, "%s\t%#lx", \
                                  instruction->name,\
                                  ARG1)

#define DECODE_ARG1WF(ARG1, ARG2) sprintf(buffer, "%s\t%#lx, %s", \
                                          instruction->name,\
                                          ARG1, \
                                          (ARG2 ? "f" : "w"))

#define DECODE_ARG2(ARG1, ARG2) sprintf(buffer, "%s\t%#lx, %#lx", \
                                        instruction->name,\
                                        ARG1, \
                                        ARG2)

#define DECODE_ARG3(ARG1, ARG2, ARG3) sprintf(buffer, "%s\t%#lx, %#lx, %#lx", \
                                             instruction->name,\
                                             ARG1, \
                                             ARG2, \
                                             ARG3)

void
gp_disassemble(MemBlock *m, int *org, enum proc_class class, char *buffer)
{
  int i;
  long int opcode;
  struct insn *instruction = NULL;

  opcode = i_memory_get(m, *org) & 0xffff;

  switch (class) {
  case PROC_CLASS_EEPROM8:
  case PROC_CLASS_GENERIC:
    sprintf(buffer, "unsupported processor class");
    return;
  case PROC_CLASS_PIC12:
    for(i = 0; i < num_op_12c5xx; i++)
      if((op_12c5xx[i].mask & opcode) == op_12c5xx[i].opcode)
        instruction = &op_12c5xx[i];
    break;
  case PROC_CLASS_SX:
    for(i = 0; i < num_op_sx; i++)
      if((op_sx[i].mask & opcode) == op_sx[i].opcode)
        instruction = &op_sx[i];
    break;
  case PROC_CLASS_PIC14:
    for(i = 0; i < num_op_16cxx; i++)
      if((op_16cxx[i].mask & opcode) == op_16cxx[i].opcode)
        instruction = &op_16cxx[i];
    break;
  case PROC_CLASS_PIC16:
    for(i = 0; i < num_op_17cxx; i++)
      if((op_17cxx[i].mask & opcode) == op_17cxx[i].opcode)
        instruction = &op_17cxx[i];
    break;
  case PROC_CLASS_PIC16E:
    for(i = 0; i < num_op_18cxx; i++)
      if((op_18cxx[i].mask & opcode) == op_18cxx[i].opcode)
        instruction = &op_18cxx[i];
    break;
  default:
    assert(0);
  }

  if (instruction == NULL)  {
    sprintf(buffer, "dw\t%#lx  ;unknown opcode", opcode);
    return;
  }

  switch (instruction->class)
    {
    case INSN_CLASS_LIT3_BANK:
      DECODE_ARG1((opcode & 0x7) << 5); 
      break;
    case INSN_CLASS_LIT3_PAGE:
      DECODE_ARG1((opcode & 0x7) << 9); 
      break;
    case INSN_CLASS_LIT1:
      DECODE_ARG1(opcode & 1); 
      break;
    case INSN_CLASS_LIT4:
      DECODE_ARG1(opcode & 0xf); 
      break;
    case INSN_CLASS_LIT4S:
      DECODE_ARG1((opcode & 0xf0) >> 4); 
      break;
    case INSN_CLASS_LIT8:
    case INSN_CLASS_LIT8C12:
    case INSN_CLASS_LIT8C16:
      DECODE_ARG1(opcode & 0xff); 
      break;
    case INSN_CLASS_LIT9:
      DECODE_ARG1(opcode & 0x1ff); 
      break;
    case INSN_CLASS_LIT11:
      DECODE_ARG1(opcode & 0x7ff); 
      break;
    case INSN_CLASS_LIT13:
      DECODE_ARG1(opcode & 0x1fff); 
      break;
    case INSN_CLASS_RBRA8:
      DECODE_ARG1((((opcode & 0xff) + (*org + 1)) * 2) & 0xff); 
      break;
    case INSN_CLASS_RBRA11:
      DECODE_ARG1((((opcode & 0x7ff) + (*org + 1)) * 2) & 0x7ff); 
      break;
    case INSN_CLASS_LIT20:
      {
        long int dest;

        *org += 1;
        dest = (i_memory_get(m, *org) & 0xfff) << 8;
        dest |= opcode & 0xff;      
        DECODE_ARG1(dest * 2); 
      }
      break;
    case INSN_CLASS_CALL20:
      {
        long int dest;

        *org += 1;
        dest = (i_memory_get(m, *org) & 0xfff) << 8;
        dest |= opcode & 0xff;      
	sprintf(buffer, "%s\t%#lx, %#lx",
                instruction->name,
                dest * 2,
		(opcode >> 8) & 1);
      }
      break;
    case INSN_CLASS_FLIT12:
      {
        long int k;
        long int file;

        *org += 1;
        k = i_memory_get(m, *org) & 0xff;
        k |= ((opcode & 0xf) << 8);
	file = (opcode >> 4) & 0x3;
        DECODE_ARG2(file, k);
      }
      break;
    case INSN_CLASS_FF:
      {
        long int file1;
        long int file2;

        *org += 1;
        file1 = opcode & 0xfff;
        file2 = i_memory_get(m, *org) & 0xfff;
        DECODE_ARG2(file1, file2);
      }
      break;
    case INSN_CLASS_FP:
      DECODE_ARG2((opcode & 0xff), ((opcode >> 8) & 0x1f));
      break;
    case INSN_CLASS_PF:
      DECODE_ARG2(((opcode >> 8) & 0x1f), (opcode & 0xff));
      break;
    case INSN_CLASS_OPF5:
      DECODE_ARG1(opcode & 0x1f);
      break;
    case INSN_CLASS_OPWF5:
      DECODE_ARG1WF((opcode & 0x1f), ((opcode >> 5) & 1));
      break;
    case INSN_CLASS_B5:
      DECODE_ARG2((opcode & 0x1f), ((opcode >> 5) & 7));
      break;
    case INSN_CLASS_B8:
      DECODE_ARG2((opcode & 0xff), ((opcode >> 8) & 7));
      break;
    case INSN_CLASS_OPF7:
      DECODE_ARG1(opcode & 0x7f);
      break;
    case INSN_CLASS_OPF8:
      DECODE_ARG1(opcode & 0xff);
      break;
    case INSN_CLASS_OPWF7:
      DECODE_ARG1WF((opcode & 0x7f), ((opcode >> 7) & 1));
      break;
    case INSN_CLASS_OPWF8:
      DECODE_ARG1WF((opcode & 0xff), ((opcode >> 8) & 1));
      break;
    case INSN_CLASS_B7:
      DECODE_ARG2((opcode & 0x7f), ((opcode >> 7) & 7));
      break;
    case INSN_CLASS_OPFA8:
      DECODE_ARG2((opcode & 0xff), ((opcode >> 8) & 1));
      break;
    case INSN_CLASS_BA8:
      DECODE_ARG3((opcode & 0xff), ((opcode >> 9) & 7), ((opcode >> 8) & 1));
      break;
    case INSN_CLASS_OPWFA8:
      DECODE_ARG3((opcode & 0xff), ((opcode >> 9) & 1), ((opcode >> 8) & 1));
      break;
    case INSN_CLASS_IMPLICIT:
      DECODE_ARG0;
      break;
    case INSN_CLASS_TBL:
      {
        char operator[5]; 

	switch(opcode & 0x3)
	  {
	  case 0:
	    strcpy(operator, "*");
	    break;
	  case 1:
	    strcpy(operator, "*+");
	    break;
	  case 2:
	    strcpy(operator, "*-");
	    break;
	  case 3:
	    strcpy(operator, "+*");
	    break;
	  default:
	    assert(0);
	  }

        sprintf(buffer, "%s\t%s", instruction->name, operator);
      }
      break;
    case INSN_CLASS_TBL2:
      DECODE_ARG2(((opcode >> 9) & 1), (opcode & 0xff));
      break;
    case INSN_CLASS_TBL3:
      DECODE_ARG3(((opcode >> 9) & 1), 
                  ((opcode >> 8) & 1), 
		   (opcode & 0xff));
      break;
    default:
      assert(0);
    }
}
