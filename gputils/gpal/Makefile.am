## Process this file with automake to produce Makefile.in

bin_PROGRAMS = gpal

CPPFLAGS = @CPPFLAGS@ -I${top_srcdir}/libgputils -I${top_srcdir}/include

gpal_SOURCES=\
	codegen.c \
	codegen14.c \
	gpal.c \
	parse.y \
	scan.l \
	tree.c \
	codegen.h \
	codegen14.h \
	gpal.h \
	scan.h \
	tree.h

gpal_LDADD = ${top_builddir}/@LIBGPUTILS@ ${top_builddir}/@LIBIBERTY@

YFLAGS = -dvt
LFLAGS = -i

EXTRA_DIST = scan.h parse.h
