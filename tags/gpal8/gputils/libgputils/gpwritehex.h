/* ".HEX" file output for gputils
   Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003
   James Bowman, Craig Franklin

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

#ifndef __GPWRITEHEX_H__
#define __GPWRITEHEX_H__

enum formats { inhx8m, inhx8s, inhx16, inhx32 };

int writehex (char *basefilename, 
              MemBlock *m,   
              enum formats hex_format,
              int numerrors,
              int byte_words,
              int dos_newlines);

int check_writehex(MemBlock *m, enum formats hex_format);

#endif
