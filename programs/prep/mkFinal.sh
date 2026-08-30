#!/bin/sh -xv

GENOBJ="$HOME/Support/data/genObject"

if [ -d $GENOBJ ]; then
	rm -fr $GENOBJ
	mkdir -p $GENOBJ
	cp -R models/* $GENOBJ/
fi
