#!/bin/sh

# generate Makefile.am and processor.pub from gpal's processor list

MAKE_FILE=Makefile.am
PROC_PUB_FILE=processor.pub

# create the Makefile
cat > $MAKE_FILE <<\_ACEOF
## This file was automatically generated by Makefile.sh

noinst_PROGRAMS = gp2pub

AM_CPPFLAGS = -I${top_srcdir}/libgputils -I${top_srcdir}/include -I${top_srcdir}/gpasm

gp2pub_SOURCES = gp2pub.c

gp2pub_LDADD = ${top_builddir}/gpasm/libgpasm.a ${top_builddir}/@LIBGPUTILS@ ${top_builddir}/@LIBIBERTY@

pkgdatadir = @GPUTILS_PUB_PATH@

PUB_FILES =\
_ACEOF

# create the processor list
cat > $PROC_PUB_FILE <<\_ACEOF
-- This file was automatically generated by Makefile.sh.  Do not modify it.

public processor is

  type family_type is (
    PIC12,    -- 12xx
    PIC14,    -- 14xx
    PIC16,    -- 17xx
    PIC16E);  -- 18xx

  type name_type is (
_ACEOF

# count the number of items in the list
let count=0
for x in `gpal -l | sort`
  do
    let count=count+1
  done

# output the file list
let number=0
for x in `gpal -l | sort`
  do
    let number=number+1
    if [ -e ../header/$x.inc ]; then
      if [ $number -eq $count ]; then
        echo "	$x.pub" >> Makefile.am
        echo "    "$x");" | tr [a-z] [A-Z] >> $PROC_PUB_FILE
      else
        echo "	$x.pub \\" >> Makefile.am
        echo "    "$x, | tr [a-z] [A-Z] >> $PROC_PUB_FILE
      fi
    else
      echo "../header/$x.inc doesn't exist"
    fi
  done

# finish Makefile
cat >> $MAKE_FILE <<\_ACEOF

%.asm: ${top_srcdir}/header/%.inc
	echo "  processor" `echo $@ | sed -e 's%.asm% %g'` > $@
	echo "  include" $< >> $@
	echo "  end" >> $@

%.pub: %.asm
	./gp2pub $<

pkgdata_DATA = $(PUB_FILES) processor.pub

EXTRA_DIST = $(PUB_FILES) processor.pub Makefile.sh

MAINTAINERCLEANFILES = $(PUB_FILES)

CLEANFILES = *.asm
_ACEOF

# finish processor list
cat >> $PROC_PUB_FILE <<\_ACEOF

end public;

_ACEOF
