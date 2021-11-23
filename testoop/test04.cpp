#include <iostream>
class Base
{
public:
    virtual void f1() { std::cout << "virtual void Base::f1()\n"; }
};

class D1 : public Base
{
public:
    using Base::f1;
    void f1(int i) { std::cout << "void D1::f1(int) " << i << std::endl; }
    virtual void f2() { std::cout << "virtual void D1::f2()\n"; }
};

class D2 : public D1
{
public:
    void f1() { std::cout << "virtual void D2::f1()\n"; }
    void f1(int i) { std::cout << "void D2::f1(int) " << i << std::endl; }
    void f2() { std::cout << "virtual void D2::f2()\n"; }
};

int main(int argc, char const *argv[])
{
    Base bobj;
    D1 d1obj;
    D2 d2obj;

    std::cout << "========= bobj =========\n";
    bobj.f1();
    std::cout << "\n========= d1obj =========\n";
    d1obj.Base::f1();
    d1obj.f1();
    d1obj.f1(1);
    d1obj.f2();
    std::cout << "\n========= bd2bj =========\n";
    d2obj.Base::f1();
    d2obj.f1();
    d2obj.f1(1);
    d2obj.f2();

    Base *pb1 = &bobj;
    Base *pb2 = &d1obj;
    Base *pb3 = &d2obj;

    std::cout << "\n=== point of Base -> void f1() ===\n";
    pb1->f1();
    pb2->f1();
    pb3->f1();

    D1 *pd1 = &d1obj;
    D2 *pd2 = &d2obj;

    std::cout << "\n=== point of Base, D1, D2 -> void f2() ===\n";
    // pb2->f2(); // "Base"没有成员"f2" (pb2是Base类型的指针)
    // pb3->f2(); // "Base"没有成员"f2" (pb3是Base类型的指针)
    pd1->f2();
    pd2->f2();

    Base *p1 = &d2obj;
    D1 *p2 = &d2obj;
    D2 *p3 = &d2obj;

    std::cout << "\n== point of Base, D1, D2 -> void f1() or void f1(int) ==\n";
    p1->f1();
    p2->f1(1);
    p3->f1();
    p3->f1(1);

    std::cout << "\n== point of D1, D2 -> void f2() ==\n";
    p2->f2();
    p3->f2();

    return 0;
}
