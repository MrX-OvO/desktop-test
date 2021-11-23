#include <iostream>

#include "Int_node.h"

namespace expr_space
{
    Int_node::Int_node(int k) : n(k) {}

    void Int_node::print(std::ostream &os) const { os << n; }

    int Int_node::eval() const { return n; }
}