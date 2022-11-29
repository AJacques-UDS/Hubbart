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

%token <str> TOKEN_KEYWORD_INT
%token <str> TOKEN_KEYWORD_FLOAT

%token <str> TOKEN_IDENTIFIER
%token <str> TOKEN_INTEGER
%token <str> TOKEN_FLOAT
%token TOKEN_ASSIGN
%token TOKEN_EOL
%token TOKEN_COLON
%type <ast> importation from_kw import_kw identifier
%type <ast> instantiation instantiate_int instantiate_float int_kw float_kw
%type <ast> literal_int literal_float
%start input

%%
input: /* empty */
    | input importation ending
    | input instantiation ending

ending : TOKEN_EOL
;

importation: from_kw identifier import_kw identifier { $$ = ast_init_importation($4, $2); }
    | import_kw identifier { $$ = ast_init_importation($2, NULL); }
;

import_kw: TOKEN_KEYWORD_IMPORT     { $$ = ast_init_kw($1); };
from_kw: TOKEN_KEYWORD_FROM         { $$ = ast_init_kw($1); };

instantiation: instantiate_int
    | instantiate_float
;

instantiate_int: identifier TOKEN_COLON int_kw TOKEN_ASSIGN literal_int { $$ = ast_init_instantiate($1, $3, $5); };
instantiate_float: identifier TOKEN_COLON float_kw TOKEN_ASSIGN literal_float { $$ = ast_init_instantiate($1, $3, $5); };

int_kw: TOKEN_KEYWORD_INT           { $$ = ast_init_kw($1); };
float_kw: TOKEN_KEYWORD_FLOAT       { $$ = ast_init_kw($1); };

identifier: TOKEN_IDENTIFIER        { $$ = ast_init_identifier($1); };
literal_int: TOKEN_INTEGER          { $$ = ast_init_integer($1); };
literal_float: TOKEN_FLOAT          { $$ = ast_init_float($1); };

%%
void yyerror(const char *msg) {
    fprintf(stderr, "error: %s\n", msg);
}
