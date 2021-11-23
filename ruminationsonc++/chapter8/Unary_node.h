#include <string>

#include "Expr_node.h"
#include "Expr.h"

#ifndef _UNARY_NODE
#define _UNARY_NODE 1

namespace expr_space
{
    class Unary_node : public Expr_node
    {
        friend class Expr;
        std::string op;
        Expr opnd;
        Unary_node(const std::string &, Expr);
        void print(std::ostream &) const override;
        int eval() const override;
    };
} // namespace

#endif // !1