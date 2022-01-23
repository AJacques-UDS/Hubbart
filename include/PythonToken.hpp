#ifndef __HUBBART_PYTHON_TOKEN_HPP
#define __HUBBART_PYTHON_TOKEN_HPP

#include <string>

#include "PythonTokenType.hpp"

class PythonToken {
private:
    PythonTokenType type;
    std::string lexeme;
public:
    PythonToken(const PythonTokenType &, const std::string &);

    std::string toString(void);
};

#endif