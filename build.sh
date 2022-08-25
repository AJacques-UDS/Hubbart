#!/bin/bash

# This will generate the python.yy.h containing the tokens with their proper value
# so that the lexer can used them
bison --defines --debug python.y

# Produce the needed source file to be compiled so we would parse Python Code
# The debug option makes sure that bison explain himself properly
flex python.l
bison python.y --debug

# This creates the PythonParser executable
gcc lex.yy.c python.tab.c -lfl -o ./build/PythonParser