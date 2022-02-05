#ifndef __HUBBART_PYTHON_LEXER_HPP
#define __HUBBART_PYTHON_LEXER_HPP

#include <ctype.h>
#include <list>
#include <map>
#include <string>
#include <stdexcept>

#include "python_token.hpp"

class PythonLexer {
private:
    std::list<PythonToken> tokens;
    std::string source;

    PythonToken init_lexer(size_t *);

    PythonToken handling_alpha(size_t *, size_t *);
    PythonToken handling_digit(size_t *, size_t *);
    PythonToken handling_punct(size_t *, size_t *);

    PythonToken next_token(size_t *, size_t *);
public:
    PythonLexer(const std::string &);

    void lex(void);
    std::list<PythonToken> getTokens(void);
};

#endif