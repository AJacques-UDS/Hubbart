%{
    #pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
%}

%define parse.error verbose

%token TOKEN_KEYWORD_IMPORT TOKEN_KEYWORD_FROM TOKEN_IDENTIFIER TOKEN_WHITE
%start input

%%
input: import_def
     | from_def TOKEN_WHITE import_def
;

import_def: import TOKEN_WHITE identifier;

from_def: from TOKEN_WHITE identifier;

import: TOKEN_KEYWORD_IMPORT {
    printf("found import\n");
};

from: TOKEN_KEYWORD_FROM {
    printf("found from\n");
};

identifier: TOKEN_IDENTIFIER {
    printf("found an identifier\n");
};

%%

int main (int argc, char **argv) {
    #ifdef YYDEBUG
    yydebug = 1;
    #endif
    #ifdef DEBUG
    printf("Starting\r\n");
    #endif
    yyparse();
}

int yywrap(void)
{
   return 1;
}

int yyerror(char *s) {
    fprintf(stderr, "error: %s\n", s);
    exit(1);
}