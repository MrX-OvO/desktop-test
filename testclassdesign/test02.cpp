/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-09 13:28:44
 * @LastEditTime : 2021-08-09 14:24:06
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testclassdesign/test02.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>

class numbered
{
    //friend void f(numbered);
    friend void f(const numbered &);

public:
    numbered() {}
    numbered(const numbered &s)
    {
        if (this != &s)
            mysn = s.mysn;
    }

private:
    int mysn = 0;
};

//void f(numbered s) { std::cout << s.mysn << std::endl; }

void f(const numbered &s) { std::cout << s.mysn << std::endl; }

int main(int argc, char const *argv[])
{
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);

    return 0;
}
