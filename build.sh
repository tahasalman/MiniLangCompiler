#!/bin/bash

flex --outfile=src/tokens/lex.yy.c src/tokens/minitokens.l
gcc -o src/tokens/minitokens src/tokens/lex.yy.c -lfl

flex --outfile=src/scanner/lex.yy.c src/scanner/miniscanner.l
gcc -o src/scanner/miniscanner src/scanner/lex.yy.c -lfl

make --directory=src/scanner+parser/

















