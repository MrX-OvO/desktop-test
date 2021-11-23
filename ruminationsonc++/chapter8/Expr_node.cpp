#include "Expr_node.h"

namespace expr_space
{
    Expr_node::Expr_node() : use(1) {}

    Expr_node::~Expr_node() = default;

    std::ostream &operator<<(std::ostream &os, const Expr_node &e)
    {
        e.print(os);
        return os;
    }
}