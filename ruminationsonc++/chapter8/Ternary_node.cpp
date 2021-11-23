#include <iostream>

#include "Ternary_node.h"

namespace expr_space
{
    Ternary_node::Ternary_node(const std::string &s, Expr l, Expr m, Expr r) : op(s), left(l), middle(m), right(r) {}

    void Ternary_node::print(std::ostream &os) const { os << "(" << left << "?" << middle << ":" << right << ")"; }

    int Ternary_node::eval() const
    {
        if (left.eval())
            return middle.eval();
        else
            return right.eval();
    }
}