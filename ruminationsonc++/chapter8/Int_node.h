#include <iostream>

#include "Expr_node.h"

#ifndef _INT_NODE
#define _INT_NODE 1

namespace expr_space
{
    class Int_node : public Expr_node
    {
        friend class Expr;
        int n;
        Int_node(int);
        void print(std::ostream &) const override;
        int eval() const override;
    };
} // namespace

#endif // !1
