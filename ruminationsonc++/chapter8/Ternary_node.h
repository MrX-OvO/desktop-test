#include <string>

#include "Expr_node.h"
#include "Expr.h"

#ifndef _TERNARY_NODE
#define _TERNARY_NODE 1

namespace expr_space
{
    class Ternary_node : public Expr_node
    {
        friend class Expr;
        std::string op;
        Expr left;
        Expr middle;
        Expr right;
        Ternary_node(const std::string &, Expr, Expr, Expr);
        void print(std::ostream &) const override;
        int eval() const override;
    };
} // namespace

#endif // !1
