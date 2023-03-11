%{
    // #pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void yyerror(const char* msg);
%}

%union {
    int *i;
    float *f;
    char *str;
}

%define parse.error verbose

%token TOK_EOL
%token TOK_IF TOK_ELIF TOK_ELSE
%token TOK_FOR TOK_IN
%token TOK_WHILE
%token TOK_DEF
%token TOK_INT TOK_FLOAT TOK_COMPLEX TOK_LIST TOK_TUPLE
%token TOK_FUNC_TYPE_HINT
%token TOK_NONE TOK_TRUE TOK_FALSE
%token TOK_AND TOK_OR TOK_NOT
%token TOK_BIT_AND TOK_BIT_OR TOK_BIT_XOR TOK_BIT_NOT
%token TOK_EXPONENT TOK_FLOOR_DIV
%token TOK_ADD_ASSIGN TOK_SUB_ASSIGN TOK_MUL_ASSIGN TOK_DIV_ASSIGN TOK_MOD_ASSIGN TOK_EXPONENT_ASSIGN TOK_FLOOR_DIV_ASSIGN
%token TOK_BIN_AND_ASSIGN TOK_BIN_OR_ASSIGN TOK_BIN_XOR_ASSIGN TOK_SHIFT_RIGHT_ASSIGN TOK_SHIFT_LEFT_ASSIGN
%token TOK_EQUALS TOK_NOT_EQUALS TOK_SMALLER_OR_EQUAL TOK_GREATER_OR_EQUAL
%token TOK_BIT_LEFT_SHIFT TOK_BIT_RIGHT_SHIFT
%token <str> TOK_ID TOK_LIT_INT TOK_LIT_FLOAT

%start input

%%
input
	: 
    | input statement
    | input TOK_EOL
	;

statement
	: expression_statement
	;

datatype
	: TOK_INT
    | TOK_FLOAT
    | TOK_COMPLEX
    | TOK_LIST '[' datatype ']'
    | TOK_TUPLE '[' tupledatatypelist
	;

tupledatatypelist
	: datatype ',' tupledatatypelist
    | datatype ']'
	;

constant
	: TOK_LIT_INT
    | TOK_LIT_FLOAT
    ;

primary_expression
	: TOK_ID
    | constant
    | '(' expression ')'
    ;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' TOK_ID
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| unary_operator cast_expression
	;

unary_operator
	: '+'
	| '-'
	| '~'
	;

cast_expression
	: unary_expression
	| '(' datatype ')' cast_expression
	;

power_expression
    : cast_expression
    | power_expression TOK_EXPONENT cast_expression

multiplicative_expression
	: power_expression
	| multiplicative_expression '*' power_expression
	| multiplicative_expression '/' power_expression
	| multiplicative_expression '%' power_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression TOK_BIT_LEFT_SHIFT additive_expression
	| shift_expression TOK_BIT_RIGHT_SHIFT additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression TOK_SMALLER_OR_EQUAL shift_expression
	| relational_expression TOK_GREATER_OR_EQUAL shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression TOK_EQUALS relational_expression
	| equality_expression TOK_NOT_EQUALS relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
    : inclusive_or_expression
    | logical_and_expression TOK_AND inclusive_or_expression;

logical_or_expression
    : logical_and_expression
    | logical_or_expression TOK_OR logical_and_expression
    ;

assignment_operator
	: '='
	| TOK_EXPONENT_ASSIGN
	| TOK_MUL_ASSIGN
	| TOK_DIV_ASSIGN
	| TOK_FLOOR_DIV_ASSIGN
	| TOK_MOD_ASSIGN
	| TOK_ADD_ASSIGN
	| TOK_SUB_ASSIGN
	| TOK_SHIFT_LEFT_ASSIGN
	| TOK_SHIFT_RIGHT_ASSIGN
	| TOK_BIN_AND_ASSIGN
	| TOK_BIN_XOR_ASSIGN
	| TOK_BIN_OR_ASSIGN
	;

assignment_expression
    : logical_or_expression
    | unary_expression ':' datatype assignment_operator assignment_expression
	| unary_expression assignment_operator assignment_expression
    ;

expression
	: assignment_expression
    ;

expression_statement
	: expression TOK_EOL
	;

%%
void yyerror(const char *msg) {
    fprintf(stderr, "error: %s\n", msg);
}
