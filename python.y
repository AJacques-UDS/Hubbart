%{
    // #pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"

    int yylex();
    void yyerror(const char* msg);
%}

%union {
    struct node_t *ast;
    char *str;
}

%define parse.error verbose

%token <str> TOKEN_KEYWORD_IMPORT 
%token <str> TOKEN_KEYWORD_FROM 
%token <str> TOKEN_IDENTIFIER
%token <str> TOKEN_KEYWORD_INT 
%token TOKEN_COLON TOKEN_ASSIGN
%token <str> TOKEN_INTEGER 
%token <str> TOKEN_KEYWORD_FLOAT 
%token <str> TOKEN_FLOAT
%token TOKEN_COMMA TOKEN_OPEN_SQUARE_BRACK TOKEN_CLOSE_SQUARE_BRACK TOKEN_KEYWORD_LIST TOKEN_INDENT
%token TOKEN_EOL
%type <ast> importation instantiate from_def import_def import_kw identifier from_kw inst_int int_kw a_int inst_float float_kw a_float
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
     | from_def import_def { $$ = ast_init_import($2, $1); print_node($$); };
;

import_def: import_kw identifier { $$ = ast_init_import($2, NULL); };
from_def: from_kw identifier { $$ = ast_init_from($2); };

import_kw: TOKEN_KEYWORD_IMPORT { $$ = ast_init_kw($1); };
from_kw: TOKEN_KEYWORD_FROM { $$ = ast_init_kw($1); };

/* INSTANTIATE RULES */

instantiate: inst_int
           | inst_float
           // | inst_array_int
;

inst_int: identifier TOKEN_COLON int_kw TOKEN_ASSIGN a_int { $$ = ast_init_inst($1, $3, $5); };
inst_float: identifier TOKEN_COLON float_kw TOKEN_ASSIGN a_float { $$ = ast_init_inst($1, $3, $5); };

identifier: TOKEN_IDENTIFIER { $$ = ast_init_identifier($1); };
int_kw: TOKEN_KEYWORD_INT { $$ = ast_init_type($1); };
float_kw: TOKEN_KEYWORD_FLOAT { $$ = ast_init_type($1); };
a_int: TOKEN_INTEGER { $$ = ast_init_value($1); };
a_float: TOKEN_FLOAT { $$ = ast_init_value($1); };

/* ARRAYS */

// inst_array_int: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_KEYWORD_LIST TOKEN_OPEN_SQUARE_BRACK TOKEN_KEYWORD_INT TOKEN_CLOSE_SQUARE_BRACK TOKEN_ASSIGN array_int;

// array_int: TOKEN_OPEN_SQUARE_BRACK list_int TOKEN_CLOSE_SQUARE_BRACK;

// list_int: /* empty */
//         | list_int TOKEN_INTEGER TOKEN_COMMA
//         | list_int TOKEN_INTEGER
// ;

// inst_array_float: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_KEYWORD_LIST TOKEN_OPEN_SQUARE_BRACK TOKEN_KEYWORD_FLOAT TOKEN_CLOSE_SQUARE_BRACK TOKEN_ASSIGN array_float;

// array_float: TOKEN_OPEN_SQUARE_BRACK list_float TOKEN_CLOSE_SQUARE_BRACK;

// list_float: /* empty */
//         | list_float TOKEN_INTEGER TOKEN_COMMA
//         | list_float TOKEN_INTEGER
// ;


%%

void yyerror(const char *msg) {
    fprintf(stderr, "error: %s\n", msg);
}
