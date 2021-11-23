#include <iostream>

class Base1
{
public:
    Base1() { std::cout << "call default constructor of Base1...\n"; }
    virtual ~Base1() { std::cout << "call destructor of Base1...\n"; }
    virtual void print() { std::cout << "call virtual void Base1::print()\n"; }
};

class Base2
{
public:
    Base2() { std::cout << "call default constructor of Base2...\n"; }
    virtual ~Base2() { std::cout << "call destructor of Base2...\n"; }
    virtual void print() { std::cout << "call virtual void Base2::print()\n"; }
};

class D1 : public Base1
{
public:
    D1() { std::cout << "call default constructor of D1...\n"; }
    virtual ~D1() { std::cout << "call destructor of D1...\n"; }
    void print() override { std::cout << "call virtual void D1::print()\n"; }
};

class D2 : public Base2
{
public:
    D2() { std::cout << "call default constructor of D2...\n"; }
    virtual ~D2() { std::cout << "call destructor of D2...\n"; }
    void print() override { std::cout << "call virtual void D2::print()\n"; }
};

class MI : public D1, public D2
{
public:
    MI() { std::cout << "call default constructor of MI...\n"; }
    ~MI() { std::cout << "call destructor of MI...\n"; }
    void print() override { std::cout << "call virtual void MI::print()\n"; }
};

int main(int argc, char const *argv[])
{
    Base1 *pb1 = new MI;
    Base2 *pb2 = new MI;
    pb1->print();
    pb2->print();
    delete pb1;
    delete pb2;
    std::cout << "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n";

    D1 *pd1 = new MI;
    D2 *pd2 = new MI;
    pd1->print();
    pd2->print();
    delete pd1;
    delete pd2;
    std::cout << "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n";

    MI mi;
    mi.print();

    return 0;
}
