#include <iostream>
#include <list>

#include "PythonToken.hpp"

int main (int argc, char** argv) {
    std::list<PythonToken> tokens;

    PythonToken breakToken(PythonTokenType::BREAK_TOKEN, "break");
    std::cout << "Token " << breakToken.toString() << std::endl;

    PythonToken classToken(PythonTokenType::CLASS_TOKEN, "class");
    std::cout << "Token " << classToken.toString() << std::endl;

    PythonToken defToken(PythonTokenType::DEF_TOKEN, "def");
    std::cout << "Token " << defToken.toString() << std::endl;

    return 0;
}