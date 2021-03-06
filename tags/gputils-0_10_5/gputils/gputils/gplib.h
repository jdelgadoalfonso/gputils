/* gplib - GNU PIC librarian
   Copyright (C) 2001 Craig Franklin
 
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

#ifndef GPLIB_H
#define GPLIB_H

enum lib_modes { 
  ar_create, 
  ar_delete, 
  ar_extract, 
  ar_list,
  ar_replace, 
  ar_symbols,
  ar_null 
};

#define GPLIB_VERSION_STRING ("gplib-" VERSION " pre-alpha")
#define MAX_NAMES 256

extern struct gplib_state {
  enum lib_modes mode;          /* operating mode */
  struct {			/* Totals for errors, warnings, messages */
    int errors;
    int warnings;
  } num;
  int numobjects;               /* number of objects in the list */
  int  quiet;                   /* suppress outputs when 1 */ 
  char *filename;               /* library file name */
  char *objectname[MAX_NAMES];  /* the list of object filenames */
  struct coff_archive *archive; /* internal archive format */
} state;

#endif
