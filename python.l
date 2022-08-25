%{
#include <stdio.h>

#define TOKEN_NUMBER 258
#define TOKEN_IDENTIFIER 259
#define TOKEN_IDENTATION 260
#define TOKEN_ASSIGN 261
#define TOKEN_EQUAL 262
#define TOKEN_NOT_EQUAL 263
#define TOKEN_GREATER_THAN 264
#define TOKEN_GREATER_OR_EQUAL 265
#define TOKEN_SHIFT_RIGHT 266
#define TOKEN_SMALLER_THAN 267
#define TOKEN_SMALLER_OR_EQUAL 268
#define TOKEN_SHIFT_LEFT 269
#define TOKEN_ADD 270
#define TOKEN_SUB 271
#define TOKEN_ARROW 272
#define TOKEN_MUL 273
#define TOKEN_DIV 274
#define TOKEN_POW 275
#define TOKEN_ACC_ADD 276
#define TOKEN_ACC_SUB 277
#define TOKEN_ACC_MUL 278
#define TOKEN_ACC_DIV 279
#define TOKEN_AMP 280
#define TOKEN_PIPE 281
#define TOKEN_XOR 282
#define TOKEN_TILDE 283
#define TOKEN_DOT 284
#define TOKEN_COMMA 285
#define TOKEN_SEMICOLON 286
#define TOKEN_COLON 287
#define TOKEN_LEFT_PAREN 288
#define TOKEN_LEFT_SQUARE_BRACK 289
#define TOKEN_LEFT_CURLY_BRACK 290
#define TOKEN_RIGHT_CURLY_BRACK 291
#define TOKEN_RIGHT_SQUARE_BRACK 292
#define TOKEN_RIGHT_PAREN 293
#define TOKEN_WHITE 294
#define TOKEN_KEYWORD_INIT 295
#define TOKEN_KEYWORD_AND 296
#define TOKEN_KEYWORD_BOOL 297
#define TOKEN_KEYWORD_BREAK 298
#define TOKEN_KEYWORD_BYTES 299
#define TOKEN_KEYWORD_CLASS 300
#define TOKEN_KEYWORD_DEF 301
#define TOKEN_KEYWORD_ELIF 302
#define TOKEN_KEYWORD_ELSE 303
#define TOKEN_KEYWORD_FALSE 304
#define TOKEN_KEYWORD_FOR 305
#define TOKEN_KEYWORD_FROM 306
#define TOKEN_KEYWORD_GLOBAL 307
#define TOKEN_KEYWORD_IF 308
#define TOKEN_KEYWORD_IN 309
#define TOKEN_KEYWORD_INT 310
#define TOKEN_KEYWORD_IMPORT 311
#define TOKEN_KEYWORD_NOT 312
#define TOKEN_KEYWORD_NONE 313
#define TOKEN_KEYWORD_OR 314
#define TOKEN_KEYWORD_RETURN 315
#define TOKEN_KEYWORD_SELF 316
#define TOKEN_KEYWORD_SET 317
#define TOKEN_KEYWORD_TRUE 318
#define TOKEN_KEYWORD_TUPLE 319
#define TOKEN_KEYWORD_WHILE 320
#define TOKEN_KEYWORD_WITH 321

int displayToken(int);
void yyerror(char *sp);
%}

numbers         ((0|[1-9][0-9]*)(\.[0-9]+)?)
identifiers     ([a-zA-Z\_][0-9a-zA-Z\_]*)
identation      (^\t+)
whites          (\ |\t|\r|\n)+

%%
"__init__"      { return displayToken(TOKEN_KEYWORD_INIT); }
"and"           { return displayToken(TOKEN_KEYWORD_AND); }
"bool"          { return displayToken(TOKEN_KEYWORD_BOOL); }
"break"         { return displayToken(TOKEN_KEYWORD_BREAK); }
"bytes"         { return displayToken(TOKEN_KEYWORD_BYTES); }
"class"         { return displayToken(TOKEN_KEYWORD_CLASS); }
"def"           { return displayToken(TOKEN_KEYWORD_DEF); }
"elif"          { return displayToken(TOKEN_KEYWORD_ELIF); }
"else"          { return displayToken(TOKEN_KEYWORD_ELSE); }
"False"         { return displayToken(TOKEN_KEYWORD_FALSE); }
"for"           { return displayToken(TOKEN_KEYWORD_FOR); }
"from"          { return displayToken(TOKEN_KEYWORD_FROM); }
"global"        { return displayToken(TOKEN_KEYWORD_GLOBAL); }
"if"            { return displayToken(TOKEN_KEYWORD_IF); }
"in"            { return displayToken(TOKEN_KEYWORD_IN); }
"int"           { return displayToken(TOKEN_KEYWORD_INT); }
"import"        { return displayToken(TOKEN_KEYWORD_IMPORT); }
"not"           { return displayToken(TOKEN_KEYWORD_NOT); }
"None"          { return displayToken(TOKEN_KEYWORD_NONE); }
"or"            { return displayToken(TOKEN_KEYWORD_OR); }
"return"        { return displayToken(TOKEN_KEYWORD_RETURN); }
"self"          { return displayToken(TOKEN_KEYWORD_SELF); }
"set"           { return displayToken(TOKEN_KEYWORD_SET); }
"True"          { return displayToken(TOKEN_KEYWORD_TRUE); }
"tuple"         { return displayToken(TOKEN_KEYWORD_TUPLE); }
"while"         { return displayToken(TOKEN_KEYWORD_WHILE); }
"with"          { return displayToken(TOKEN_KEYWORD_WITH); }

{numbers}       { return displayToken(TOKEN_NUMBER); }
{identifiers}   { return displayToken(TOKEN_IDENTIFIER); }
{identation}    { return displayToken(TOKEN_IDENTATION); }
{whites}        { return displayToken(TOKEN_WHITE); }

"="             { return displayToken(TOKEN_ASSIGN); }
"=="            { return displayToken(TOKEN_EQUAL); }
"!="            { return displayToken(TOKEN_NOT_EQUAL); }
">"             { return displayToken(TOKEN_GREATER_THAN); }
">="            { return displayToken(TOKEN_GREATER_OR_EQUAL); }
">>"            { return displayToken(TOKEN_SHIFT_RIGHT); }
"<"             { return displayToken(TOKEN_SMALLER_THAN); }
"<="            { return displayToken(TOKEN_SMALLER_OR_EQUAL); }
"<<"            { return displayToken(TOKEN_SHIFT_LEFT); }
"+"             { return displayToken(TOKEN_ADD); }
"-"             { return displayToken(TOKEN_SUB); }
"->"            { return displayToken(TOKEN_ARROW); }
"*"             { return displayToken(TOKEN_MUL); }
"/"             { return displayToken(TOKEN_DIV); }
"**"            { return displayToken(TOKEN_POW); }
"+="            { return displayToken(TOKEN_ACC_ADD); }
"-="            { return displayToken(TOKEN_ACC_SUB); }
"*="            { return displayToken(TOKEN_ACC_MUL); }
"/="            { return displayToken(TOKEN_ACC_DIV); }
"&"             { return displayToken(TOKEN_AMP); }
"|"             { return displayToken(TOKEN_PIPE); }
"^"             { return displayToken(TOKEN_XOR); }
"~"             { return displayToken(TOKEN_TILDE); }
"."             { return displayToken(TOKEN_DOT); }
","             { return displayToken(TOKEN_COMMA); }
";"             { return displayToken(TOKEN_SEMICOLON); }
":"             { return displayToken(TOKEN_COLON); }

"("             { return displayToken(TOKEN_LEFT_PAREN); }
"["             { return displayToken(TOKEN_LEFT_SQUARE_BRACK); }
"{"             { return displayToken(TOKEN_LEFT_CURLY_BRACK); }
"}"             { return displayToken(TOKEN_RIGHT_CURLY_BRACK); }
"]"             { return displayToken(TOKEN_RIGHT_SQUARE_BRACK); }
")"             { return displayToken(TOKEN_RIGHT_PAREN); }

.               { yyerror("Unknown token!!!"); }
%%

int displayToken(int token) {

#ifdef DEBUG

    printf("Token ID %d (", token);

    switch (token) {
    case TOKEN_NUMBER :
        printf("TOKEN_NUMBER)");
        break;
    case TOKEN_IDENTIFIER :
        printf("TOKEN_IDENTIFIER)");
        break;
    case TOKEN_IDENTATION :
        printf("TOKEN_IDENTATION)");
        break;
    case TOKEN_ASSIGN :
        printf("TOKEN_ASSIGN)");
        break;
    case TOKEN_EQUAL :
        printf("TOKEN_EQUAL)");
        break;
    case TOKEN_NOT_EQUAL :
        printf("TOKEN_NOT_EQUAL)");
        break;
    case TOKEN_GREATER_THAN :
        printf("TOKEN_GREATER_THAN)");
        break;
    case TOKEN_GREATER_OR_EQUAL :
        printf("TOKEN_GREATER_OR_EQUAL)");
        break;
    case TOKEN_SHIFT_RIGHT :
        printf("TOKEN_SHIFT_RIGHT)");
        break;
    case TOKEN_SMALLER_THAN :
        printf("TOKEN_SMALLER_THAN)");
        break;
    case TOKEN_SMALLER_OR_EQUAL :
        printf("TOKEN_SMALLER_OR_EQUAL)");
        break;
    case TOKEN_SHIFT_LEFT :
        printf("TOKEN_SHIFT_LEFT)");
        break;
    case TOKEN_ADD :
        printf("TOKEN_ADD)");
        break;
    case TOKEN_SUB :
        printf("TOKEN_SUB)");
        break;
    case TOKEN_ARROW :
        printf("TOKEN_ARROW)");
        break;
    case TOKEN_MUL :
        printf("TOKEN_MUL)");
        break;
    case TOKEN_DIV :
        printf("TOKEN_DIV)");
        break;
    case TOKEN_POW :
        printf("TOKEN_POW)");
        break;
    case TOKEN_ACC_ADD :
        printf("TOKEN_ACC_ADD)");
        break;
    case TOKEN_ACC_SUB :
        printf("TOKEN_ACC_SUB)");
        break;
    case TOKEN_ACC_MUL :
        printf("TOKEN_ACC_MUL)");
        break;
    case TOKEN_ACC_DIV :
        printf("TOKEN_ACC_DIV)");
        break;
    case TOKEN_AMP :
        printf("TOKEN_AMP)");
        break;
    case TOKEN_PIPE :
        printf("TOKEN_PIPE)");
        break;
    case TOKEN_XOR :
        printf("TOKEN_XOR)");
        break;
    case TOKEN_TILDE :
        printf("TOKEN_TILDE)");
        break;
    case TOKEN_DOT :
        printf("TOKEN_DOT)");
        break;
    case TOKEN_COMMA :
        printf("TOKEN_COMMA)");
        break;
    case TOKEN_SEMICOLON :
        printf("TOKEN_SEMICOLON)");
        break;
    case TOKEN_COLON :
        printf("TOKEN_COLON)");
        break;
    case TOKEN_LEFT_PAREN :
        printf("TOKEN_LEFT_PAREN)");
        break;
    case TOKEN_LEFT_SQUARE_BRACK :
        printf("TOKEN_LEFT_SQUARE_BRACK)");
        break;
    case TOKEN_LEFT_CURLY_BRACK :
        printf("TOKEN_LEFT_CURLY_BRACK)");
        break;
    case TOKEN_RIGHT_CURLY_BRACK :
        printf("TOKEN_RIGHT_CURLY_BRACK)");
        break;
    case TOKEN_RIGHT_SQUARE_BRACK :
        printf("TOKEN_RIGHT_SQUARE_BRACK)");
        break;
    case TOKEN_RIGHT_PAREN :
        printf("TOKEN_RIGHT_PAREN)");
        break;
    case TOKEN_WHITE :
        printf("TOKEN_WHITE)");
        break;
    case TOKEN_KEYWORD_INIT :
        printf("TOKEN_KEYWORD_INIT)");
        break;
    case TOKEN_KEYWORD_AND :
        printf("TOKEN_KEYWORD_AND)");
        break;
    case TOKEN_KEYWORD_BOOL :
        printf("TOKEN_KEYWORD_BOOL)");
        break;
    case TOKEN_KEYWORD_BREAK :
        printf("TOKEN_KEYWORD_BREAK)");
        break;
    case TOKEN_KEYWORD_BYTES :
        printf("TOKEN_KEYWORD_BYTES)");
        break;
    case TOKEN_KEYWORD_CLASS :
        printf("TOKEN_KEYWORD_CLASS)");
        break;
    case TOKEN_KEYWORD_DEF :
        printf("TOKEN_KEYWORD_DEF)");
        break;
    case TOKEN_KEYWORD_ELIF :
        printf("TOKEN_KEYWORD_ELIF)");
        break;
    case TOKEN_KEYWORD_ELSE :
        printf("TOKEN_KEYWORD_ELSE)");
        break;
    case TOKEN_KEYWORD_FALSE :
        printf("TOKEN_KEYWORD_FALSE)");
        break;
    case TOKEN_KEYWORD_FOR :
        printf("TOKEN_KEYWORD_FOR)");
        break;
    case TOKEN_KEYWORD_FROM :
        printf("TOKEN_KEYWORD_FROM)");
        break;
    case TOKEN_KEYWORD_GLOBAL :
        printf("TOKEN_KEYWORD_GLOBAL)");
        break;
    case TOKEN_KEYWORD_IF :
        printf("TOKEN_KEYWORD_IF)");
        break;
    case TOKEN_KEYWORD_IN :
        printf("TOKEN_KEYWORD_IN)");
        break;
    case TOKEN_KEYWORD_INT :
        printf("TOKEN_KEYWORD_INT)");
        break;
    case TOKEN_KEYWORD_IMPORT :
        printf("TOKEN_KEYWORD_IMPORT)");
        break;
    case TOKEN_KEYWORD_NOT :
        printf("TOKEN_KEYWORD_NOT)");
        break;
    case TOKEN_KEYWORD_NONE :
        printf("TOKEN_KEYWORD_NONE)");
        break;
    case TOKEN_KEYWORD_OR :
        printf("TOKEN_KEYWORD_OR)");
        break;
    case TOKEN_KEYWORD_RETURN :
        printf("TOKEN_KEYWORD_RETURN)");
        break;
    case TOKEN_KEYWORD_SELF :
        printf("TOKEN_KEYWORD_SELF)");
        break;
    case TOKEN_KEYWORD_SET :
        printf("TOKEN_KEYWORD_SET)");
        break;
    case TOKEN_KEYWORD_TRUE :
        printf("TOKEN_KEYWORD_TRUE)");
        break;
    case TOKEN_KEYWORD_TUPLE :
        printf("TOKEN_KEYWORD_TUPLE)");
        break;
    case TOKEN_KEYWORD_WHILE :
        printf("TOKEN_KEYWORD_WHILE)");
        break;
    case TOKEN_KEYWORD_WITH :
        printf("TOKEN_KEYWORD_WITH)");
        break;
    default:
        yyerror("Unknown token !!!");
    }

    printf("\r\n");

#endif

    return token;
}