#include "parser_exception.hpp"
#include "spdlog/spdlog.h"

const std::string PARSER_EXCEPTION_ENTITY = std::string("PARSER");

ParserException::ParserException(const std::string &msg): HubbartException(LEXER_EXCEPTION_ENTITY, msg) {
    
}