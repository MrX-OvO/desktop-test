#include <iostream>

#include "Unary_node.h"

namespace expr_space
{
    Unary_node::Unary_node(const std::string &s, Expr node) : op(s), opnd(node) {}

    void Unary_node::print(std::ostream &os) const { os << "(" << op << opnd << ")"; }

    int Unary_node::eval() const
    {
        if (op == "-")
            return -opnd.eval();
        throw "error, bad op " + op + " int UnaryNode";
    }
}