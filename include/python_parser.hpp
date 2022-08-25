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

#ifndef __HUBBART_PYTHON_PARSER_HPP
#define __HUBBART_PYTHON_PARSER_HPP

#include <list>
#include <string>

class PythonParser {
private:
    std::list<PythonToken> tokens;

public:
    PythonParser(const std:list<PythonToken>&)
}

#endif