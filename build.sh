#!/bin/bash

flex --outfile=src/tokens/lex.yy.c src/tokens/minitokens
gcc -o src/tokens/minitokens /src/tokens/lex.yy.c -lfl

flex --outfile=src/scanner/lex.yy.c sr/scanner/miniscanner
gcc -o src/scanner/miniscanner /src/scanner/lex.yy.c -lfl

make -C src/scanner+parser

















