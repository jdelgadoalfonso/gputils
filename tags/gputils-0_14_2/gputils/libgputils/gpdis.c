/* Disassemble memory
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

#define DECODE_ARG0 snprintf(buffer, sizeof_buffer, "%s", instruction->name)

#define DECODE_ARG1(ARG1) snprintf(buffer, sizeof_buffer, "%s\t%#x", \
                                  instruction->name,\
                                  ARG1)

#define DECODE_ARG1WF(ARG1, ARG2) snprintf(buffer, sizeof_buffer, "%s\t%#x, %s", \
                                          instruction->name,\
                                          ARG1, \
                                          (ARG2 ? "f" : "w"))

#define DECODE_ARG2(ARG1, ARG2) snprintf(buffer, sizeof_buffer, "%s\t%#x, %#x", \
                                        instruction->name,\
                                        ARG1, \
                                        ARG2)

#define DECODE_ARG3(ARG1, ARG2, ARG3) snprintf(buffer, sizeof_buffer, "%s\t%#x, %#x, %#x", \
                                             instruction->name,\
                                             ARG1, \
                                             ARG2, \
                                             ARG3)

#define DECODE_MOVINDF(ARG1, ARG2, ARG3) snprintf(buffer, sizeof_buffer, "%s\t%s%#x%s", \
                                             instruction->name,\
                                             ARG1, \
                                             ARG2, \
                                             ARG3)

gp_boolean gp_decode_mnemonics = false;
gp_boolean gp_decode_extended = false;

int
gp_disassemble(MemBlock *m,
               int byte_address,
               proc_class_t class,
               char *buffer,
               size_t sizeof_buffer)
{
  int value;
  unsigned short opcode;
  const struct insn *instruction = NULL;
  int num_words = 1;

  if (class->find_insn == NULL) {
    snprintf(buffer, sizeof_buffer, "unsupported processor class");
    return 0;
  }

  class->i_memory_get(m, byte_address, &opcode);

  /* special case for pic14 enhanced moviw k[FSRn] & movwi k[FSRn] */
  if (PROC_CLASS_PIC14E == class) {
    int masked = opcode & 0x3f80;
    const char *instr = NULL;
    if (0x3f00 == masked)
       instr = "moviw";
    else if (0x3f80 == masked)
       instr = "movwi";

    if (instr) {
      /* twos complement number */
      int neg;

      value = opcode & 0x3f;
      if (value & 0x20) {
        value = (value ^ 0x3f) + 1;
        neg = 1;
      } else {
        neg = 0;
      }
      snprintf(buffer, sizeof_buffer, "%s\t%s.%d[%#x]", instr, neg ? "-" : "", value,
               (opcode & 0x40) ? 6 : 4);
      return num_words;
    }
  }

  instruction = class->find_insn(class, opcode);

  if (instruction == NULL)  {
    snprintf(buffer, sizeof_buffer, "dw\t%#x", opcode);
    return num_words;
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
    case INSN_CLASS_LIT5:
      DECODE_ARG1(opcode & 0x1f);
      break;
    case INSN_CLASS_LIT6:
      DECODE_ARG1(opcode & 0x3f);
      break;
    case INSN_CLASS_LIT7:
      DECODE_ARG1(opcode & 0x7f);
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
    case INSN_CLASS_LITFSR_14: {
        int neg;

        value = (opcode & 0x3f);
        if (value & 0x20) {
          value = (value ^ 0x3f) + 1;
          neg = 1;
        } else {
          neg = 0;
        }
        snprintf(buffer, sizeof_buffer, "%s\t%#x, %s.%d", instruction->name,
                 ((opcode >> 6) & 0x3) ? 6 : 4, neg ? "-" : "", value);
      }
      break;
    case INSN_CLASS_LITFSR_16:
      DECODE_ARG2(((opcode >> 6) & 0x3), (opcode & 0x3f));
      break;
    case INSN_CLASS_RBRA8:
      value = (opcode & 0xff);
      /* twos complement number */
      if (value & 0x80) {
        value = -((value ^ 0xff) + 1);
      }
      value = gp_processor_byte_to_org(class, byte_address + value * 2 + 2);
      DECODE_ARG1(value);
      break;
    case INSN_CLASS_RBRA9:
      value = (opcode & 0x1ff);
      /* twos complement number */
      if (value & 0x100) {
        value = -((value ^ 0x1ff) + 1);
      }
      value = gp_processor_byte_to_org(class, byte_address + value * 2 + 2);
      DECODE_ARG1(value);
      break;
    case INSN_CLASS_RBRA11:
      value = opcode  & 0x7ff;
      /* twos complement number */
      if (value & 0x400) {
        value = -((value ^ 0x7ff) + 1);
      }
      value = gp_processor_byte_to_org(class, byte_address + value * 2 + 2);
      DECODE_ARG1(value);
      break;
    case INSN_CLASS_LIT20:
      {
        short unsigned int dest;

        num_words = 2;
        class->i_memory_get(m, byte_address + 2, &dest);
        dest = (dest & 0xfff) << 8;
        dest |= opcode & 0xff;
        DECODE_ARG1(gp_processor_byte_to_org(class, dest * 2));
      }
      break;
    case INSN_CLASS_CALL20:
      {
        short unsigned int dest;

        num_words = 2;
        class->i_memory_get(m, byte_address + 2, &dest);
        dest = (dest & 0xfff) << 8;
        dest |= opcode & 0xff;
        snprintf(buffer, sizeof_buffer, "%s\t%#x, %#x",
                instruction->name,
                 gp_processor_byte_to_org(class, dest * 2),
                (opcode >> 8) & 1);
      }
      break;
    case INSN_CLASS_FLIT12:
      {
        unsigned short k;
        unsigned short file;

        num_words = 2;
        class->i_memory_get(m, byte_address + 2, &k);
        k = ((opcode & 0xf) << 8) | (k & 0xff);
        file = (opcode >> 4) & 0x3;
        DECODE_ARG2(file, k);
      }
      break;
    case INSN_CLASS_FF:
      {
        unsigned short file1;
        unsigned short file2;

        num_words = 2;
        file1 = opcode & 0xfff;
        class->i_memory_get(m, byte_address + 2, &file2);
        file2 &= 0xfff;
        DECODE_ARG2(file1, file2);
      }
      break;
    case INSN_CLASS_FP:
      DECODE_ARG2((opcode & 0xff), ((opcode >> 8) & 0x1f));
      break;
    case INSN_CLASS_PF:
      DECODE_ARG2(((opcode >> 8) & 0x1f), (opcode & 0xff));
      break;
    case INSN_CLASS_SF:
      {
        unsigned short offset;
        unsigned short file;

        num_words = 2;
        offset = opcode & 0x7f;
        class->i_memory_get(m, byte_address + 2, &file);
        file &= 0xfff;
        DECODE_ARG2(offset, file);
      }
      break;
    case INSN_CLASS_SS:
      {
        unsigned short offset1;
        unsigned short offset2;

        num_words = 2;
        offset1 = opcode & 0x7f;
        class->i_memory_get(m, byte_address + 2, &offset2);
        offset2 &= 0x7f;
        DECODE_ARG2(offset1, offset2);
      }
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
            strncpy(operator, "*", sizeof(operator));
            break;
          case 1:
            strncpy(operator, "*+", sizeof(operator));
            break;
          case 2:
            strncpy(operator, "*-", sizeof(operator));
            break;
          case 3:
            strncpy(operator, "+*", sizeof(operator));
            break;
          default:
            assert(0);
          }

        snprintf(buffer,
                 sizeof_buffer,
                 "%s\t%s",
                 instruction->name,
                 operator);
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
    case INSN_CLASS_MOVINDF:
      DECODE_MOVINDF((opcode & 0x02) ? "" : ((opcode & 0x01) ? "--" : "++"),
                     (opcode & 0x04) ? 6 : 4,
                     (opcode & 0x02) ? ((opcode & 0x01) ? "--" : "++") : "");
      break;
    default:
      assert(0);
    }

  return num_words;
}

int
gp_disassemble_byte(MemBlock *m,
                    int byte_address,
                    proc_class_t class,
                    char *buffer,
                    size_t sizeof_buffer)
{
  unsigned char byte;

  b_memory_assert_get(m, byte_address, &byte);
  snprintf(buffer, sizeof_buffer, "db\t%#x", (unsigned int)byte);
  return 1;
}

int
gp_disassemble_word(MemBlock *m,
                    int byte_address,
                    proc_class_t class,
                    char *buffer,
                    size_t sizeof_buffer)
{
  unsigned short word;

  class->i_memory_get(m, byte_address, &word);
  snprintf(buffer, sizeof_buffer, "dw\t%#x", word);
  return 2;
}

int
gp_disassemble_size(MemBlock *m,
                    int byte_address,
                    proc_class_t class,
                    char *buffer,
                    size_t sizeof_buffer,
                    unsigned int size)
{
  if (size == 1)
    return gp_disassemble_byte(m, byte_address, class, buffer, sizeof_buffer);
  else if (size == 2) {
    char dasmbuf[512];
    int num_words;

    num_words = gp_disassemble(m, byte_address, class, dasmbuf, sizeof(dasmbuf));
    if (num_words != 1)
      return gp_disassemble_word(m, byte_address, class, buffer, sizeof_buffer);
    else {
      strncpy(buffer, dasmbuf, sizeof_buffer);
      return 2 * num_words;
    }
  }
  return 2 * gp_disassemble(m, byte_address, class, buffer, sizeof_buffer);
}
