#include "python_token.hpp"

PythonToken::PythonToken(const PythonTokenType &_type, const std::string &_lexeme) {
    this->type = _type;
    this->lexeme = _lexeme;
}

PythonTokenType PythonToken::getType(void) {
    return this->type;
}

std::string PythonToken::getLexeme(void) {
    return this->lexeme;
}
