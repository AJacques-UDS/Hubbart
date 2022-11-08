#ifndef __SYMTABLE_H
#define __SYMTABLE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SYMTABLE_MAX_SIZE 100

typedef struct __symbol {
    char* identifier;
    char* type;
    int yylineno;
    // keep scope (would probably point to the "root" node of the AST where the value is reacheables)
    struct __symbol* next;
} symbol;

void initHashElement(const char*);
void initSymbol(const char*);
void disposeSymbol(symbol *);

void initSymTable(void);
void disposeSymTable(void);
int hashSymbol(const char*);

short addSymbol(const char*);
void printSymTable(void);

#endif