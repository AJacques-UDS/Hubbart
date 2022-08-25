//===-- lexer_exception.h - Instruction class definition --------*- C++ -*-===//
//
// Part of the Hubbart Project, under the MIT License.
// See https://mit-license.org/ for license information.
// SPDX-License-Identifier: MIT License
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of exception that can be thrown from the
/// Hubbart Python Lexer.
///
//===----------------------------------------------------------------------===//

#ifndef __HUBBART_LEXER_EXCEPTION_HPP
#define __HUBBART_LEXER_EXCEPTION_HPP

#include <string>

#include "hubbart_exception.hpp"

/**
 * @brief The default Hubbart Lexer exception
 * 
 */
class ParserException: std::exception { 
public:
    ParserException(const std::string &);
};

#endif
