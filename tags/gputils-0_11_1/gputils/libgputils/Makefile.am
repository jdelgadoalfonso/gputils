# Makefile.am
# Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003
# James Bowman, Craig Franklin
# 
# This file is part of gputils.
# 
# gputils is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
# 
# gputils is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with gputils; see the file COPYING.  If not, write to
# the Free Software Foundation, 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.

AUTOMAKE_OPTIONS = foreign

CPPFLAGS = @CPPFLAGS@ -I${top_srcdir}/include

noinst_LIBRARIES = libgputils.a

libgputils_a_SOURCES =\
	gparchive.c \
	gpcod.c \
	gpcoffgen.c \
	gpcofflink.c \
	gpdis.c \
	gpmemory.c \
	gpmessage.c \
	gpopcode.c \
	gpprocessor.c \
	gpreadhex.c \
	gpreadobj.c \
	gpsymbol.c \
	gpsystem.c \
	gpwritehex.c \
	gpwriteobj.c \
	gparchive.h \
	gpcod.h \
        gpcoff.h \
	gpcoffgen.h \
	gpcofflink.h \
	gpdis.h \
	gpmemory.h \
	gpmessage.h \
	gpopcode.h \
	gpprocessor.h \
	gpreadhex.h \
	gpreadobj.h \
	gpsymbol.h \
	gpsystem.h \
	gptypes.h \
	gpwritehex.h \
	gpwriteobj.h \
	libgputils.h
