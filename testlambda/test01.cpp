/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-04 22:59:46
 * @LastEditTime : 2021-08-05 11:09:13
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testlambda/test01.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>

void f(const int &a)
{
    auto f2 = [a](const int &b) -> int
    { return a + b; };
    auto res2 = f2(4);
    std::cout << "lambda f2 => res2 = f2(4) = " << res2 << std::endl;
    std::cout << "call void f(const int &) " << a << std::endl;
}

int main(int argc, char const *argv[])
{
    auto f1 = [](const int &a, const int &b) -> int
    { return a + b; };
    auto res1 = f1(1, 2);
    std::cout << "lambda f1 => res1 = f1(1,2) = " << res1 << std::endl;

    f(3);

    int i = 5;
    auto f3 = [&i]() -> bool
    {
        while (i != 0)
            --i;
        return i == 0 ? true : false;
    };
    bool res2 = f3();
    std::cout << "lambda f3 => res2 = f3() = " << std::boolalpha << res2 << std::endl;

    return 0;
}
