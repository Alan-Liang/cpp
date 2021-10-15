#!/bin/bash

DESC="Compile and run the code, with input if exists"
. lib/common.sh

if [ ! -e "$SRC" ]; then
  echo "Source file does not exist; refusing to run."
  exit 1
fi

g++ --debug "$SRC" -o "$EXE" || exit $?
if [ "$2" = "-v" ]; then EXE="valgrind $EXE"; fi
if [ -e "$INFILE" ]; then time $EXE < "$INFILE"; else time "$EXE"; fi
