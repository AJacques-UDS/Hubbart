#!/bin/bash

# This will generate the python.yy.h needed for the lexer and the python.yy.c
# needed to compile the parser.
bison -d --debug python.y

# Produce the lex.yy.c needed to compile the lexer used by the parser.
flex python.l

# This creates the PythonParser executable
gcc lex.yy.c python.tab.c -lfl -o ./build/PythonParser