#include "python_parser.h"

PythonLexer::PythonLexer(const std::list<PythonToken &tokens) {
    this->tokens = tokens;
}