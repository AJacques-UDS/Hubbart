%option noyywrap
%{
#include <stdio.h>
#include <string.h>

#include "python.tab.h"

void yyerror(const char *);
%}

%option noyywrap noinput nounput

integers        (-?0|[1-9][0-]*)
floats          ((0|[1-9][0-9]*)(\.[0-9]+))
identifiers     ([a-zA-Z\_][0-9a-zA-Z\_]*)
indentation     (^\t+)
whites          (\ |\t)+
eol             (\r|\n)

%%
"from"          { yylval.str = strdup(yytext); return TOKEN_KEYWORD_FROM; }
"import"        { yylval.str = strdup(yytext); return TOKEN_KEYWORD_IMPORT; }

"float"         { yylval.str = strdup(yytext);  return TOKEN_KEYWORD_FLOAT; }
"int"           { yylval.str = strdup(yytext);  return TOKEN_KEYWORD_INT; }

"List"          { /* yylval.str = strdup(yytext);  return TOKEN_KEYWORD_LIST; */ }

"["             { /* return TOKEN_OPEN_SQUARE_BRACK; */ }
"]"             { /* return TOKEN_CLOSE_SQUARE_BRACK; */ }

"="             { return TOKEN_ASSIGN; }
":"             { return TOKEN_COLON; }
","             { /* return TOKEN_COMMA; */ }

"("             { puts("("); return TOKEN_PAREN_OPEN;  }
")"             { puts(")"); return TOKEN_PAREN_CLOSE; }
"**"            { puts("op **"); return TOKEN_ARITH_POWER; }
"*"             { puts("op *"); return TOKEN_ARITH_MUL;   }
"/"             { puts("op /"); return TOKEN_ARITH_DIV;   }
"%"             { puts("op %"); return TOKEN_ARITH_MOD;   }
"+"             { puts("op +"); return TOKEN_ARITH_ADD;   }
"-"             { puts("op -"); return TOKEN_ARITH_SUB;   }

{identifiers}   { printf("id %s\n", yytext); yylval.str = strdup(yytext); return TOKEN_IDENTIFIER; }

{integers}      { yylval.str = strdup(yytext); return TOKEN_INTEGER; }
{floats}        { yylval.str = strdup(yytext); return TOKEN_FLOAT; }
{eol}           { return TOKEN_EOL; }
{indentation}   { /* return TOKEN_INDENT; */ }
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
    yyparse();
}