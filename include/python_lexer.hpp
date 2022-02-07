//===-- python_lexer.hpp - Instruction class definition ---------*- C++ -*-===//
//
// Part of the Hubbart Project, under the MIT License.
// See https://mit-license.org/ for license information.
// SPDX-License-Identifier: MIT License
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Responsible to generate the list of Python Token from a source code.
///
//===----------------------------------------------------------------------===//

#ifndef __HUBBART_PYTHON_LEXER_HPP
#define __HUBBART_PYTHON_LEXER_HPP

#include <list>
#include <map>
#include <string>

#include "lexer_exception.hpp"
#include "spdlog/spdlog.h"
#include "python_token.hpp"

/**
 * @brief The Hubbart Python Lexer
 * 
 */
class PythonLexer {
private:
    std::string source;
    std::list<PythonToken> tokens;
public:
    /**
     * @brief Construct a new Python Lexer object
     * 
     */
    PythonLexer(const std::string &);

    /**
     * @brief Build the tokens' list.
     * 
     * @return true when no errors
     * @return false otherwise
     */
    bool lex(void);

    /**
     * @brief Frame the next alphanumerical lexemes
     * 
     * @return true when no errors
     * @return false otherwise
     * @todo This MUST BE moved to private
     */
    bool nextAlpha(size_t*, size_t*);

    /**
     * @brief Frame the next invisible lexemes. Includes the space, the tab and
     * new lines characters.
     * 
     * @return true when no errors
     * @return false otherwise
     * @todo This MUST BE moved to private
     */
    bool nextInvisible(size_t*, size_t*);

    /**
     * @brief Extracts the framed lexemes
     * 
     * @return std::string 
     * @todo This MUST BE moved to private
     */
    std::string extract(size_t *, size_t*);

    /**
     * @brief Add the alphanumerical lexeme with its proper token type into the
     * tokens' list.
     * 
     * @return true when no errors
     * @return false otherwise
     * @todo This MUST BE moved to private
     */
    bool addAlpha(const std::string &);

    /**
     * @brief Add the invisible lexeme with its proper token type into the
     * tokens' list.
     * 
     * @return true when no errors 
     * @return false otherwise
     */
    bool addInvisible(const std::string &);

    /**
     * @brief Get the Tokens' list
     * 
     * @return std::list<PythonToken> 
     */
    std::list<PythonToken> getTokens(void);
};


#endif