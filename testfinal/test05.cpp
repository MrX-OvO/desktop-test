#include <iostream>

struct Base
{
    void bar(int i) { std::cout << "call void Base::bar(int i), i = " << i << std::endl; }

protected:
    int ival;
};

struct Derived1 : virtual public Base
{
    void bar(char c)
    {
        std::cout << "call void Derived1::bar(char c), c = ";
        std::cout.put(c);
        std::cout << std::endl;
    }
    void foo(char c)
    {
        std::cout << "call void Derived1::foo(char c), c = ";
        std::cout.put(c);
        std::cout << std::endl;
    }

protected:
    char cval;
};

struct Derived2 : virtual public Base
{
    void foo(int i) { std::cout << "call void Derived2::foo(int i), i = " << i << std::endl; }

protected:
    int ival;
    char cval;
};

struct VMI : public Derived1, public Derived2
{
    void f()
    {
        Base::ival = 1;
        ival = 2;
        Derived1::cval = 'a';
        Derived2::cval = 'b';

        Base::bar(Base::ival);
        bar(Derived1::cval);
        Derived1::foo(Derived1::cval);
        Derived2::foo(ival);
    }
};

int main(int argc, char const *argv[])
{
    VMI vmi;
    vmi.f();

    return 0;
}
