//===-- python_token_type.hpp - Instruction class definition ----*- C++ -*-===//
//
// Part of the Hubbart Project, under the MIT License.
// See https://mit-license.org/ for license information.
// SPDX-License-Identifier: MIT License
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Enumerates all class handles by Hubbart Lexer
///
//===----------------------------------------------------------------------===//

#ifndef __HUBBART_PYTHON_TOKEN_TYPE_HPP
#define __HUBBART_PYTHON_TOKEN_TYPE_HPP

/**
 * @brief All Hubbart Token Classes
 * 
 */
enum PythonTokenType {
    // Keywords

    BREAK_TOKEN,
    CLASS_TOKEN,
    DEF_TOKEN,
    ELIF_TOKEN,
    ELSE_TOKEN,
    FALSE_TOKEN,
    FOR_TOKEN,
    FROM_TOKEN,
    GLOBAL_TOKEN,
    IF_TOKEN,
    IN_TOKEN,
    IMPORT_TOKEN,
    NONE_TOKEN,
    RETURN_TOKEN,
    SELF_TOKEN,
    TRUE_TOKEN,
    WHILE_TOKEN,
    WITH_TOKEN,

    // Types

    BOOL_TOKEN,
    BYTES_TOKEN,
    FLOAT_TOKEN,
    INT_TOKEN,
    LIST_TOKEN,
    SET_TOKEN,
    TUPLE_TOKEN,
    
    // Built-in

    INIT_TOKEN,
    NAME_TOKEN,

    // Operators

    AND_TOKEN,
    NOT_TOKEN,
    OR_TOKEN,
    ADD_TOKEN,
    SUB_TOKEN,
    MUL_TOKEN,
    DIV_TOKEN,
    MOD_TOKEN,
    POW_TOKEN,
    FLOOR_DIV_TOKEN,
    ASSIGN_TOKEN,
    ACC_ADD_TOKEN,
    ACC_SUB_TOKEN,
    ACC_MUL_TOKEN,
    ACC_DIV_TOKEN,
    ACC_MOD_TOKEN,
    ACC_FLOOR_DIV_TOKEN,
    ACC_POW_TOKEN,
    ACC_AMP_TOKEN,
    ACC_PIPE_TOKEN,
    ACC_XOR_TOKEN,
    ACC_SHIFT_LEFT_TOKEN,
    ACC_SHIFT_RIGHT_TOKEN,
    EQUAL_TOKEN,
    NOT_EQUAL_TOKEN,
    GREATER_THAN_TOKEN,
    SMALLER_THAN_TOKEN,
    GREATER_OR_EQUAL_TOKEN,
    SMALLER_OR_EQUAN_TOKEN,
    AMP_TOKEN,
    PIPE_TOKEN,
    XOR_TOKEN,
    TILDE_TOKEN,
    SHIFT_LEFT_TOKEN,
    SHIFT_RIGHT_TOKEN,

    // Wrappers, separators and ponctuation

    LEFT_PAREN_TOKEN,
    RIGHT_PAREN_TOKEN,
    LEFT_SQUARE_BRACK_TOKEN,
    RIGHT_SQUARE_BRACK_TOKEN,
    LEFT_CURLY_BRACK_TOKEN,
    RIGHT_CURLY_BRACK_TOKEN,
    COLON_TOKEN,
    COMMA_TOKEN,
    SEMICOLON_TOKEN,
    DOT_TOKEN,
    ARROW_TOKEN,

    // Other

    IDENTIFIER_TOKEN,                     // [a-zA-Z\_][a-zA-Z0-9\_]*
    NUMBER_TOKEN,                         // (\-|\+)?\d(\.?\d?)(e?(\-|\+)?\d)?, 0b[0-1]+ (binary), 0x[0-9a-fA-F]+ (hexadecimal)
    NEWLINE_TOKEN,                        // \n and \r\n
    INDENTATION_TOKEN,                    // only support for 4 spaces for now
    SPACE_TOKEN,
    EOF_TOKEN,
    COMMENT_TOKEN,
};

#endif