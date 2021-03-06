#!/bin/sh

# generate Makefile.am from the directory contents

MAKE_FILE=Makefile.am

cat > $MAKE_FILE <<\_ACEOF
## This file was automatically generated by Makefile.sh

pkgdatadir = @GPUTILS_HEADER_PATH@

HEADER_FILES =\
_ACEOF

# compile the header check program
rm -f header_check
gcc -Wall -pedantic -g -O2 -I../include -o header_check header_check.c

# count the number of items in the list
let count=0
for x in `ls *.inc | sort`
  do
    let count=count+1
  done

# output the file list
let number=0
for x in `ls *.inc | sort`
  do
    let number=number+1
    echo "testing $x"
    ./header_check $x
    if [ $number -eq $count ]; then
      echo "	$x" >> $MAKE_FILE
    else
      echo "	$x \\" >> $MAKE_FILE
    fi
  done

cat >> $MAKE_FILE <<\_ACEOF

pkgdata_DATA = $(HEADER_FILES)

EXTRA_DIST = $(HEADER_FILES) Makefile.sh header_check.c
_ACEOF

# clean up the temporary files
rm -f header_check
