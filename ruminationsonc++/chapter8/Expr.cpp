#include <iostream>

#include "Expr.h"
#include "Int_node.h"
#include "Unary_node.h"
#include "Binary_node.h"
#include "Ternary_node.h"

namespace expr_space
{
    Expr::Expr(int n) { pnode = new Int_node(n); }

    Expr::Expr(const std::string &s, Expr e) { pnode = new Unary_node(s, e); }

    Expr::Expr(const std::string &s, Expr l, Expr r) { pnode = new Binary_node(s, l, r); }

    Expr::Expr(const std::string &s, Expr l, Expr m, Expr r) { pnode = new Ternary_node(s, l, m, r); }

    Expr::Expr(const Expr &e)
    {
        pnode = e.pnode;
        ++pnode->use;
    }

    Expr &Expr::operator=(const Expr &rhs) &
    {
        ++rhs.pnode->use;
        if (--pnode->use == 0)
            delete pnode;
        pnode = rhs.pnode;
        return *this;
    }

    Expr::~Expr()
    {
        if (--pnode->use == 0)
            delete pnode;
    }

    int Expr::eval() const { return pnode->eval(); }

    std::ostream &operator<<(std::ostream &os, const Expr &e)
    {
        e.pnode->print(os);
        return os;
    }
}