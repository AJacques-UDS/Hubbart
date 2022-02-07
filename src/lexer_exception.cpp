#include "lexer_exception.hpp"
#include "spdlog/spdlog.h"

LexerException::LexerException(const std::string &msg) {
    this->message = msg;
    spdlog::warn("Lexer Exception Occured: {}", this->message);
}

std::string LexerException::getMessage(void) {
    return this->message;
}