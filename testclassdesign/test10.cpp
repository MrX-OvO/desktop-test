#include <iostream>
class A
{
    friend void f();
};

inline void f() { std::cout << "f"; }

class B
{
    friend void f();
};

inline void f() {}

int main(int argc, char const *argv[])
{
    f();
    return 0;
}
