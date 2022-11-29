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
%token TOKEN_EOL
%token TOKEN_COLON

%token TOKEN_ARITH_ADD TOKEN_ARITH_SUB
%token TOKEN_ARITH_MUL TOKEN_ARITH_DIV TOKEN_ARITH_MOD
%token TOKEN_ARITH_POWER
%token TOKEN_ASSIGN
%token TOKEN_PAREN_OPEN TOKEN_PAREN_CLOSE

%type <ast> importation from_kw import_kw identifier
%type <ast> instantiation instantiate_int instantiate_float int_kw float_kw
%type <ast> literal_int literal_float
%type <ast> arith_expr factor power term assign
%start input

%%
input: /* empty */
    | input importation TOKEN_EOL
    | input instantiation TOKEN_EOL
    | input assign TOKEN_EOL
    | input TOKEN_EOL
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

assign: identifier TOKEN_ASSIGN arith_expr { $$ = ast_init_assign($1, $3); };

primary_expr: TOKEN_PAREN_OPEN expression TOKEN_PAREN_CLOSE {  };
;

expression: assignment_expression
;

power_expression:
    // Here we add **

multiplicative_expression: power_expression
    // Here we add *, / and %
;

additive_expression: multiplicative_expression
    // Here we add + and -
;

shift_expression: additive_expression
    // Here we add << and >>
;

relational_expression: shift_expression
    // Here we add <, >, <=, >=
;

equality_expression: relational_expression
    // Here we add == and !=
;

and_expression: equality_expression
    // Here we add ^
;

exclusive_or_expression: and_expression
    // Here we add &
;

inclusive_or_expression: exclusive_or_expression
    // Here we add |
;

logical_and_expression: inclusive_or_expression
    // Here we add &&
;

logical_or_expression: logical_and_expression
    // Here we add ||
    | identifier TOKEN_ASSIGN arith_expr { $$ = ast_init_assign($1, $3); };
;

assignment_expression: logical_or_expression
    // Here we have =
    | identifier TOKEN_ASSIGN arith_expr { $$ = ast_init_assign($1, $3); };
;


arith_expr: factor
    | arith_expr TOKEN_ARITH_ADD factor { $$ = ast_init_arith_op($3, "+", $1); };
    | arith_expr TOKEN_ARITH_SUB factor { $$ = ast_init_arith_op($3, "-", $1); };
;

factor: power { $$ = ast_init_arith_op($1, NULL, NULL); };
    | factor TOKEN_ARITH_MUL power { $$ = ast_init_arith_op($3, "*", $1); };
    | factor TOKEN_ARITH_DIV power { $$ = ast_init_arith_op($3, "/", $1); };
    | factor TOKEN_ARITH_MOD power { $$ = ast_init_arith_op($3, "%", $1); };
;

power: term
    | power TOKEN_ARITH_POWER term { $$ = ast_init_arith_op($3, "**", $1); }

term: identifier;
    | literal_int;
    | literal_float;
    | TOKEN_PAREN_OPEN term TOKEN_PAREN_CLOSE { $$ = $2; };
;

%%
void yyerror(const char *msg) {
    fprintf(stderr, "error: %s\n", msg);
}
