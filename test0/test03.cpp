/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-03 15:44:46
 * @LastEditTime : 2021-08-03 16:12:24
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/test03.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
class Y;
class X
{
private:
    Y *m_y = nullptr;

public:
    X() = default;
    X(Y *y) : m_y(y) {}
    X(const X &x) { m_y = x.m_y; }
    X &operator=(const X &x)
    {
        if (this != &x)
            m_y = x.m_y;
        return *this;
    }
    void getPY() { std::cout << m_y; }
};

class Y
{
private:
    X m_x;

public:
    Y() = default;
    Y(const X &x) : m_x(x) {}
    Y(const Y &y) { m_x = y.m_x; }
    Y &operator=(const Y &y)
    {
        if (this != &y)
            m_x = y.m_x;
        return *this;
    }
    void getOX() { std::cout << &m_x; }
};

int main(int argc, char const *argv[])
{
    X x1;
    Y y1;
    std::cout << "==================================================\n";
    std::cout << "&x1 = " << &x1 << ", &y1 = " << &y1 << std::endl;
    std::cout << "&x1.m_y = ";
    x1.getPY();
    std::cout << ", &y1.m_x = ";
    y1.getOX();
    std::cout << std::endl;
    std::cout << "==================================================\n";

    std::cout << "==================================================\n";
    X x2(&y1);
    Y y2(x1);
    std::cout << "&x2 = " << &x2 << ", &y2 = " << &y2 << std::endl;
    std::cout << "&x2.m_y = ";
    x2.getPY();
    std::cout << ", &y2.m_x = ";
    y2.getOX();
    std::cout << std::endl;
    std::cout << "==================================================\n";

    return 0;
}
