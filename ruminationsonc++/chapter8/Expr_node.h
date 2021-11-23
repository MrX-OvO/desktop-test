#include <iostream>

#ifndef _EXPR_NODE
#define _EXPR_NODE 1

namespace expr_space
{
    class Expr_node
    {
        friend class Expr;
        friend std::ostream &operator<<(std::ostream &, const Expr_node &);

    protected:
        Expr_node();
        virtual void print(std::ostream &) const = 0;
        virtual int eval() const = 0;
        virtual ~Expr_node();

    private:
        unsigned use;
    };
} // namespace

#endif // !1
