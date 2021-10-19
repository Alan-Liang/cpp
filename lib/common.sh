#!/bin/bash

if [ -z $1 ]; then
  if [ -n "$DESC" ]; then echo "$0: $DESC"; fi
  echo "Usage: $0 <Problem ID>"
  echo "Example: $0 1000"
  exit 1
fi

SRC="src/$1.cpp"
EXE="./bin/$1"
INFILE="./src/$1.in"
GEN="./src/$1.gen"

BROWSER="firefox-developer-edition"
IDE="codium"
