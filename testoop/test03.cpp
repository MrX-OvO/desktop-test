#include <iostream>
struct Base
{
    void f() { std::cout << "void Base::f()\n"; }
};

struct Derived : Base
{
    void f(int i) { std::cout << "void Derived::f(int) " << i << std::endl; }
};

int main(int argc, char const *argv[])
{
    Base b;
    Derived d;
    b.f();
    d.f(0);
    //d.f();
    d.Base::f();

    return 0;
}
