#!/bin/bash

rm ./build/*

# This will generate the python.yy.h needed for the lexer and the python.yy.c
# needed to compile the parser.
bison -d --debug python.y

# Produce the lex.yy.c needed to compile the lexer used by the parser.
flex python.l

gcc -g -c symtable.c -I ./include -o ./build/symtable.o
gcc -g -c ast.c -I ./include -o ./build/ast.o

# This creates the PythonParser executable
gcc lex.yy.c python.tab.c ./build/ast.o -I ./include -lfl -o ./build/PythonParser