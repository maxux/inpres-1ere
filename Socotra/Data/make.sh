#!/bin/bash
PROJ="socotra"
CC="i686-pc-linux-gnu-gcc"
CFLAGS="-O2 -Wall -ansi -pedantic -lncurses"

for i in *.c; do
	if [ "$i" != "Win32Console.c" ]; then
		EXECIT="$CC -c $i $CFLAGS"
		echo $EXECIT
		$EXECIT
	fi
done

EXECIT="$CC *.o -o $PROJ $CFLAGS"
echo $EXECIT
$EXECIT
