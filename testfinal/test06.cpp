#include <iostream>

class Class
{
public:
    Class() { std::cout << "call default constructor of Class...\n"; }
    virtual ~Class() { std::cout << "call virtual destructor of Class...\n"; }
};

class Base : virtual public Class
{
public:
    Base() { std::cout << "call default constructor of Base...\n"; }
    Base(const Base &) { std::cout << "call copy constructor of Base...\n"; }
    Base(int) { std::cout << "call constructor of Base...\n"; }
    virtual ~Base() { std::cout << "call virtual destructor of Base...\n"; }
};

class D1 : virtual public Base
{
public:
    D1() { std::cout << "call default constructor of D1...\n"; }
    D1(const D1 &d1) : Base(d1) { std::cout << "call copy constructor of D1...\n"; }
    D1(int i) : Base(i) { std::cout << "call constructor of D1...\n"; }
    virtual ~D1() { std::cout << "call virtual destructor of D1...\n"; }
};

class D2 : virtual public Base
{
public:
    D2() { std::cout << "call default constructor of D2...\n"; }
    D2(const D2 &d2) : Base(d2) { std::cout << "call copy constructor of D2...\n"; }
    D2(int i) : Base(i) { std::cout << "call constructor of D2...\n"; }
    virtual ~D2() { std::cout << "call virtual destructor of D2...\n"; }
};

class MI : public D1, public D2
{
public:
    MI() { std::cout << "call default constructor of MI...\n"; }
    MI(const MI &mi) : D1(mi), D2(mi) { std::cout << "call copy constructor of MI...\n"; }
    MI(int i) : D1(i), D2(i) { std::cout << "call constructor of MI...\n"; }
    virtual ~MI() { std::cout << "call virtual destructor of MI...\n"; }
};

class Final : public MI, virtual public Class
{
public:
    Final() { std::cout << "call default constructor of Final...\n"; }
    Final(const Final &f) : MI(f) { std::cout << "call copy constructor of Final...\n"; }
    Final(int i) : MI(i) { std::cout << "call constructor of Final...\n"; }
    virtual ~Final() { std::cout << "call virtual destructor of Final...\n"; }
};

int main(int argc, char const *argv[])
{
    Final f;
    f.~Final();
    std::cout << "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n";

    Base *pb;
    Class *pc;
    MI *pmi;
    D2 *pd2;

    //pb = new Class; // 不能将"Class *"类型的值分配到"Base *"类型的实体
    pc = new Final;
    delete pc;
    std::cout << "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n";
    //pmi = pb; // 不能将"Base *"类型的值分配到"MI *"类型的实体
    pd2 = pmi;

    return 0;
}
