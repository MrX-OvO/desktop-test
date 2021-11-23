#include <iostream>

#include "Expr.h"

int main(int argc, char const *argv[])
{
    Expr e = Expr("*", Expr("-", 5), Expr("+", 3, 4));
    std::cout << e << std::endl;

    return 0;
}
