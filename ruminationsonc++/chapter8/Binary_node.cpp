#include <iostream>

#include "Binary_node.h"

namespace expr_space
{
    Binary_node::Binary_node(const std::string &s, Expr l, Expr r) : op(s), left(l), right(r) {}

    void Binary_node::print(std::ostream &os) const { os << "(" << left << op << right << ")"; }

    int Binary_node::eval() const
    {
        int op1 = left.eval();
        int op2 = right.eval();
        if (op == "-")
            return op1 - op2;
        if (op == "+")
            return op1 + op2;
        if (op == "*")
            return op1 * op2;
        if (op == "/" && op2 != 0)
            return op1 / op2;
        throw "error, bad op " + op + " in BinaryNode";
    }
}