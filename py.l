%option noyywrap
%{
#include <stdio.h>
#include <string.h>

#include "py.tab.h"

void yyerror(const char *);
%}

%option noyywrap noinput nounput

identifiers     ([a-zA-Z\_][0-9a-zA-Z\_]*)
integers        ([0-9]|([1-9][0-9]+))
floats          ([0-9]+\.[0-9]+)
eol             (\r|\n)
white           (\ |\t)

%%

{integers}        { yylval.str = strdup(yytext); return TOK_LIT_INT; }
{floats}          { yylval.str = strdup(yytext); return TOK_LIT_FLOAT; }

"if"            { return TOK_IF; }
"elif"          { return TOK_ELIF; }
"else"          { return TOK_ELSE; }
"for"           { return TOK_FOR; }
"in"            { return TOK_IN; }
"while"         { return TOK_WHILE; }
"def"           { return TOK_DEF; }
"int"           { return TOK_INT; }
"float"         { return TOK_FLOAT; }
"complex"       { return TOK_COMPLEX; }
"list"          { return TOK_LIST; }
"tuple"         { return TOK_TUPLE; }
"None"          { return TOK_NONE; }
"True"          { return TOK_TRUE; }
"False"         { return TOK_FALSE; }
"and"           { return TOK_AND; }
"or"            { return TOK_OR; }
"not"           { return TOK_NOT; }


"("             { return '('; }
")"             { return ')'; }
"["             { return '['; }
"]"             { return ']';}
"."             { return '.'; }
","             { return ','; }
":"             { return ':'; }

"->"            { return TOK_FUNC_TYPE_HINT; }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }
"**"            { return TOK_EXPONENT; }
"//"            { return TOK_FLOOR_DIV; }

"="             { return '='; }
"+="            { return TOK_ADD_ASSIGN; }
"-="            { return TOK_SUB_ASSIGN; }
"*="            { return TOK_MUL_ASSIGN; }
"/="            { return TOK_DIV_ASSIGN; }
"%="            { return TOK_MOD_ASSIGN; }
"**="           { return TOK_EXPONENT_ASSIGN; }
"//="           { return TOK_FLOOR_DIV_ASSIGN; }
"&="            { return TOK_BIN_AND_ASSIGN; }
"|="            { return TOK_BIN_OR_ASSIGN; }
"^="            { return TOK_BIN_XOR_ASSIGN; }
">>="           { return TOK_SHIFT_RIGHT_ASSIGN; }
"<<="           { return TOK_SHIFT_LEFT_ASSIGN; }

"=="            { return TOK_EQUALS; }
"!="            { return TOK_NOT_EQUALS; }
"<"             { return '<'; }
">"             { return '>'; }
"<="            { return TOK_SMALLER_OR_EQUAL; }
">="            { return TOK_GREATER_OR_EQUAL; }

"&"             { return '&'; }
"|"             { return '|'; }
"^"             { return '^'; }
"~"             { return '~'; }
"<<"            { return TOK_BIT_LEFT_SHIFT; }
">>"            { return TOK_BIT_RIGHT_SHIFT; }

{identifiers}   { yylval.str = strdup(yytext); return TOK_ID; }

{eol}           { return TOK_EOL; }

{white}         { }

.               { yyerror("Unknown token!!!"); }
%%

int main (int argc, char **argv) {
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return 1;
        }
    }

#ifdef YYDEBUG
    yydebug = 1;
#endif
    yyparse();
}