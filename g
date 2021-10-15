#!/bin/bash

DESC="Generate input using a script"
. lib/common.sh

node "$GEN" > "$INFILE"
