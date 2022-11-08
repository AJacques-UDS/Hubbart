%{
    // #pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void yyerror(const char* msg);
%}

%define parse.error verbose

%token TOKEN_KEYWORD_IMPORT TOKEN_KEYWORD_FROM TOKEN_IDENTIFIER
%token TOKEN_KEYWORD_INT TOKEN_INTEGER TOKEN_COLON TOKEN_ASSIGN
%token TOKEN_KEYWORD_FLOAT TOKEN_FLOAT
%token TOKEN_COMMA TOKEN_OPEN_SQUARE_BRACK TOKEN_CLOSE_SQUARE_BRACK TOKEN_KEYWORD_LIST
%token TOKEN_EOL
%start input

%%
input: /* empty */
     | ending
     | input importation ending
     | input instantiate ending
;

ending : TOKEN_EOL
;

/* IMPORTATION RULES */
importation: import_def
     | from_def import_def
;

import_def: TOKEN_KEYWORD_IMPORT TOKEN_IDENTIFIER;

from_def: TOKEN_KEYWORD_FROM TOKEN_IDENTIFIER;

/* INSTANTIATE RULES */

instantiate: inst_int
           | inst_float
           | inst_array_int
;

inst_int: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_KEYWORD_INT TOKEN_ASSIGN TOKEN_INTEGER;

inst_float: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_KEYWORD_FLOAT TOKEN_ASSIGN TOKEN_FLOAT;

/* ARRAYS */

inst_array_int: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_KEYWORD_LIST TOKEN_OPEN_SQUARE_BRACK TOKEN_KEYWORD_INT TOKEN_CLOSE_SQUARE_BRACK TOKEN_ASSIGN array_int;

array_int: TOKEN_OPEN_SQUARE_BRACK list_int TOKEN_CLOSE_SQUARE_BRACK;

list_int: /* empty */
        | list_int TOKEN_INTEGER TOKEN_COMMA
        | list_int TOKEN_INTEGER
;

inst_array_float: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_KEYWORD_LIST TOKEN_OPEN_SQUARE_BRACK TOKEN_KEYWORD_FLOAT TOKEN_CLOSE_SQUARE_BRACK TOKEN_ASSIGN array_float;

array_float: TOKEN_OPEN_SQUARE_BRACK list_float TOKEN_CLOSE_SQUARE_BRACK;

list_float: /* empty */
        | list_float TOKEN_INTEGER TOKEN_COMMA
        | list_float TOKEN_INTEGER
;

%%

void yyerror(const char *msg) {
    fprintf(stderr, "error: %s\n", msg);
}
