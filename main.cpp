#include <iostream>
#include <iomanip>

#include <string>

#include "spdlog/spdlog.h"
#include "python_token.hpp"
#include "python_lexer.hpp"

int main (int argc, char** argv) {
    spdlog::info("Welcome to Hubbart Python Lexer for LLVM");

    std::string myString = "from hubbart import sqrt\n";
    PythonLexer lexer(myString);
    size_t cursor = 0;
    size_t frame = 0;

    if (lexer.nextAlpha(&cursor, &frame)) {
        std::string tok = myString.substr(cursor, frame - cursor);
        spdlog::info("The lexeme extracted is \"{}\".", tok);
        PythonToken token(FROM_TOKEN, tok);
    }

    return 0;
}
