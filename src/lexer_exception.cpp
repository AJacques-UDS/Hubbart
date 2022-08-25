#include "lexer_exception.hpp"
#include "spdlog/spdlog.h"

const std::string LEXER_EXCEPTION_ENTITY = std::string("LEXER");

LexerException::LexerException(const std::string &msg): HubbartException(LEXER_EXCEPTION_ENTITY, msg) {
    
}