%option noyywrap
%{
#include <stdio.h>

#include "python.tab.h"

void yyerror(const char *);
int yyival;
double yyfval;
%}

%option noyywrap noinput nounput

integers        (-?0|[1-9][0-]*)
floats          ((0|[1-9][0-9]*)(\.[0-9]+))
identifiers     ([a-zA-Z\_][0-9a-zA-Z\_]*)
identation      (^\t+)
whites          (\ |\t)+
eol             (\r|\n)

%%
"float"         { return TOKEN_KEYWORD_FLOAT; }
"from"          { return TOKEN_KEYWORD_FROM; }
"import"        { return TOKEN_KEYWORD_IMPORT; }
"int"           { return TOKEN_KEYWORD_INT; }
"List"          { return TOKEN_KEYWORD_LIST; }

"["             { return TOKEN_OPEN_SQUARE_BRACK; }
"]"             { return TOKEN_CLOSE_SQUARE_BRACK; }

"="             { return TOKEN_ASSIGN; }
":"             { return TOKEN_COLON; }
","             { return TOKEN_COMMA; }

{integers}      { yyival = atoi(yytext); return TOKEN_INTEGER; }
{floats}        { yyfval = atof(yytext); return TOKEN_FLOAT; }
{identifiers}   { return TOKEN_IDENTIFIER; }
{eol}           { return TOKEN_EOL; }
{whites}        { }

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
#ifdef DEBUG
    printf("Starting\r\n");
#endif
    yyparse();
}