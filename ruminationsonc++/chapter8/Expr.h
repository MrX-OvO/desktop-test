#include <string>

#ifndef _EXPR
#define _EXPR 1

namespace expr_space
{
    class Expr_node;
    class Expr
    {
        friend class Expr_node;
        friend std::ostream &operator<<(std::ostream &, const Expr &);

        Expr_node *pnode;

    public:
        Expr(int n);                                 // 创建一个Int_node
        Expr(const std::string &, Expr);             // 创建一个Unary_node
        Expr(const std::string &, Expr, Expr);       // 创建一个Binary_node
        Expr(const std::string &, Expr, Expr, Expr); // 创建一个Ternary_node
        Expr(const Expr &e);
        Expr &operator=(const Expr &rhs) &;
        ~Expr();

        int eval() const;
    };
} // namespace

#endif // !1