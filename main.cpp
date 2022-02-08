#include <iostream>
#include <list>

#include <string>

#include "spdlog/spdlog.h"
#include "python_token.hpp"
#include "python_lexer.hpp"

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
        std::cout << "<" << tok.getType() << ", \"";
        if (tok.getType() == NEWLINE_TOKEN) std::cout << "\\n>" ;
        else std::cout << tok.getLexeme() << "\">";
        std::cout << std::endl;
    }

    return 0;
}
