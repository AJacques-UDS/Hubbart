%{
#include <stdio.h>

#include "python.tab.h"

void yyerror(const char *);
%}

%option noyywrap noinput nounput

numbers         ((0|[1-9][0-9]*)(\.[0-9]+)?)
identifiers     ([a-zA-Z\_][0-9a-zA-Z\_]*)
identation      (^\t+)
whites          (\ |\t|\r|\n)+

%%
"from"          { return TOKEN_KEYWORD_FROM; }
"import"        { return TOKEN_KEYWORD_IMPORT; }

{identifiers}   { return TOKEN_IDENTIFIER; }
{whites}        { return TOKEN_WHITE; }

.               { yyerror("Unknown token!!!"); }
%%
