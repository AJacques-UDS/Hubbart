%{
    // #pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void yyerror(const char* msg);
%}

%define parse.error verbose

%token TOKEN_KEYWORD_IMPORT TOKEN_KEYWORD_FROM TOKEN_IDENTIFIER
%token TOKEN_EOL
%start input

%%
input: /* empty */
     | input importation TOKEN_EOL

importation: import_def
     | from_def import_def
;

import_def: import identifier;

from_def: from identifier;

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

void yyerror(const char *msg) {
    fprintf(stderr, "error: %s\n", msg);
}
