#include <iostream>
#include <list>

#include <string>

#include "spdlog/spdlog.h"
#include "python_token.hpp"
#include "python_lexer.hpp"

const std::string TOKEN_NAME[] = {
    "BREAK_TOKEN",
    "CLASS_TOKEN",
    "DEF_TOKEN",
    "ELIF_TOKEN",
    "ELSE_TOKEN",
    "FALSE_TOKEN",
    "FOR_TOKEN",
    "FROM_TOKEN",
    "GLOBAL_TOKEN",
    "IF_TOKEN",
    "IN_TOKEN",
    "IMPORT_TOKEN",
    "NONE_TOKEN",
    "RETURN_TOKEN",
    "SELF_TOKEN",
    "TRUE_TOKEN",
    "WHILE_TOKEN",
    "WITH_TOKEN",
    "BOOL_TOKEN",
    "BYTES_TOKEN",
    "FLOAT_TOKEN",
    "INT_TOKEN",
    "LIST_TOKEN",
    "SET_TOKEN",
    "TUPLE_TOKEN",
    "INIT_TOKEN",
    "NAME_TOKEN",
    "AND_TOKEN",
    "NOT_TOKEN",
    "OR_TOKEN",
    "ADD_TOKEN",
    "SUB_TOKEN",
    "MUL_TOKEN",
    "DIV_TOKEN",
    "MOD_TOKEN",
    "POW_TOKEN",
    "FLOOR_DIV_TOKEN",
    "ASSIGN_TOKEN",
    "ACC_ADD_TOKEN",
    "ACC_SUB_TOKEN",
    "ACC_MUL_TOKEN",
    "ACC_DIV_TOKEN",
    "ACC_MOD_TOKEN",
    "ACC_FLOOR_DIV_TOKEN",
    "ACC_POW_TOKEN",
    "ACC_AMP_TOKEN",
    "ACC_PIPE_TOKEN",
    "ACC_XOR_TOKEN",
    "ACC_SHIFT_LEFT_TOKEN",
    "ACC_SHIFT_RIGHT_TOKEN",
    "EQUAL_TOKEN",
    "NOT_EQUAL_TOKEN",
    "GREATER_THAN_TOKEN",
    "SMALLER_THAN_TOKEN",
    "GREATER_OR_EQUAL_TOKEN",
    "SMALLER_OR_EQUAN_TOKEN",
    "AMP_TOKEN",
    "PIPE_TOKEN",
    "XOR_TOKEN",
    "TILDE_TOKEN",
    "SHIFT_LEFT_TOKEN",
    "SHIFT_RIGHT_TOKEN",
    "LEFT_PAREN_TOKEN",
    "RIGHT_PAREN_TOKEN",
    "LEFT_SQUARE_BRACK_TOKEN",
    "RIGHT_SQUARE_BRACK_TOKEN",
    "LEFT_CURLY_BRACK_TOKEN",
    "RIGHT_CURLY_BRACK_TOKEN",
    "COLON_TOKEN",
    "COMMA_TOKEN",
    "SEMICOLON_TOKEN",
    "DOT_TOKEN",
    "ARROW_TOKEN",
    "IDENTIFIER_TOKEN",
    "NUMBER_TOKEN",
    "NEWLINE_TOKEN",
    "INDENTATION_TOKEN",
    "SPACE_TOKEN",
    "EOF_TOKEN",
    "COMMENT_TOKEN",
};

int main (int argc, char** argv) {
    spdlog::info("Welcome to Hubbart Python Lexer for LLVM");

    std::string code = "from Hubbart import sqr2t\nglobal value = 3\nglobal key = 7.19\nclass Point2d:\n    def __init__(self, x: float, y: float) -> float:\n        self.x = x\n        self.y = y\n";
    PythonLexer lexer(code);

    try {
        lexer.lex();
    } catch(LexerException lexEx) {
        spdlog::info("Error while lexing.");
    }

    std::list<PythonToken> tokens = lexer.getTokens();

    for (PythonToken tok: tokens) {
        std::cout << "<" << TOKEN_NAME[tok.getType()] << ", \"";
        if (tok.getType() == NEWLINE_TOKEN) std::cout << "\\n>\"" ;
        else std::cout << tok.getLexeme() << "\">";
        std::cout << std::endl;
    }

    return 0;
}
