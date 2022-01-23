#include "PythonToken.hpp"

PythonToken::PythonToken(const PythonTokenType &_type, const std::string &_lexeme) {
    this->type = _type;
    this->lexeme = _lexeme;
}

std::string PythonToken::toString(void) {
    std::string result = "<" + tokenName[this->type] + ", \"" + this->lexeme + "\">";
    
    return result;
}