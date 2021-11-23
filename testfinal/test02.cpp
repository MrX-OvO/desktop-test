#include <iostream>
class A
{
public:
    A() { std::cout << "call default constructor of A...\n"; }
    virtual ~A() { std::cout << "call destructor of A...\n"; }
};

class B : public A
{
public:
    B() : A() { std::cout << "call default constructor of B...\n"; }
    virtual ~B() { std::cout << "call destructor of B...\n"; }
};

class C : public B
{
public:
    C() : B() { std::cout << "call default constructor of C...\n"; }
    virtual ~C() { std::cout << "call destructor of C...\n"; }
};

class X
{
public:
    X() { std::cout << "call default constructor of X...\n"; }
    virtual ~X() { std::cout << "call destructor of X...\n"; }
};

class Y
{
public:
    Y() { std::cout << "call default constructor of Y...\n"; }
    virtual ~Y() { std::cout << "call destructor of Y...\n"; }
};

class Z : public X, public Y
{
public:
    Z() : X(), Y() { std::cout << "call default constructor of Z...\n"; }
    virtual ~Z() { std::cout << "call destructor of Z...\n"; }
};

class MI : public C, public Z
{
public:
    MI() : Z(), C() { std::cout << "call default constructor of MI...\n"; }
    ~MI() { std::cout << "call destructor of MI...\n"; }
};

class D : public X, public C
{
public:
    D() : X(), C() { std::cout << "call default constructor of D...\n"; }
    ~D() { std::cout << "call destructor of D...\n"; }
};

int main(int argc, char const *argv[])
{
    MI mi;

    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
    D *pd = new D;
    X *px = pd;
    A *pa = pd;
    B *pb = pd;
    C *pc = pd;
    delete pd;
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

    return 0;
}
