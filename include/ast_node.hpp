#ifndef __HUBBART_AST_NODE_HPP
#define __HUBBART_AST_NODE_HPP

#include "python_token.hpp"

class BaseAstNode {
private:
    PythonToken token;
public:
    virtual ~BaseAstNode() {}
};

class NumberAstNode : BaseAstNode {
public:
    NumberAstNode (const PythonToken&);
};

class IdentifierAstNode : BaseAstNode {
public:
    IdentifierAstNode (const PythonToken &);
}

class ExpressionAstNode : BaseAstNode {
public:
    ExpressionAstNode (const PythonToken &);
}

#endif