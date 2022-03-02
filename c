#!/bin/bash

DESC="Create boilerplate code"
. lib/common.sh

if [ -e "$SRC" ]; then
  echo "Source file already exists, refusing to overwrite"
  exit 1
fi

cp skel/skel.cpp "$SRC"

if [ -n "$2" ]; then
  touch "$INFILE"
  $IDE "$INFILE"
fi

$IDE "$SRC"
