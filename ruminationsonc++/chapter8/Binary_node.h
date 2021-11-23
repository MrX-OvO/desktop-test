#include <string>

#include "Expr_node.h"
#include "Expr.h"

#ifndef _BINARY_NODE
#define _BINARY_NODE 1

namespace expr_space
{
    class Binary_node : public Expr_node
    {
        friend class Expr;
        std::string op;
        Expr left;
        Expr right;
        Binary_node(const std::string &, Expr, Expr);
        void print(std::ostream &) const override;
        int eval() const override;
    };
} // namespace

#endif // !1
