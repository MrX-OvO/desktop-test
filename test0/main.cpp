/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-07-27 14:17:19
 * @LastEditTime : 2021-07-27 16:03:50
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/main.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <ctime>
#include <unistd.h>
class Base
{
private:
    static int count;
    char *cur;

public:
    Base();
    virtual ~Base();
    virtual void print() const { std::cout << "Base count: " << count << std::endl; }
};

int Base::count = 0;

Base::Base()
{
    ++count;
    time_t now = time(0);
    cur = ctime(&now);
    std::cout << "Base created at " << cur;
}

Base::~Base()
{

    time_t now = time(0);
    cur = ctime(&now);
    std::cout << "Base destroyed at " << cur;
    --count;
    std::cout << "Base count: " << count << std::endl;
}

class Derived : public Base
{
private:
    static int count;
    char *cur;

public:
    Derived();
    virtual ~Derived();
    virtual void print() const { std::cout << "Derived count: " << count << std::endl; }
};

int Derived::count = 0;

Derived::Derived() : Base()
{
    ++count;
    time_t now = time(0);
    cur = ctime(&now);
    std::cout << "Derived created at " << cur;
}

Derived::~Derived()
{

    time_t now = time(0);
    cur = ctime(&now);
    std::cout << "Derived destroyed at " << cur;
    --count;
    std::cout << "Derived count: " << count << std::endl;
}

int main()
{
    std::cout << "=+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+=\n";
    Base base;
    std::cout << "addr of base: " << &base << std::endl;
    base.print();
    std::cout << "=+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+=\n";
    sleep(2);

    std::cout << "=+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+=\n";
    Derived derived;
    std::cout << "addr of derived: " << &derived << std::endl;
    derived.print();
    base.print();
    std::cout << "=+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+=\n";
    sleep(2);

    std::cout << "=+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+=\n";
    Base *p = new Derived;
    std::cout << "addr of p: " << p << std::endl;
    p->print();
    std::cout << "=+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+=\n";

    p = &base;
    std::cout << "addr of p: " << p << ", addr of base: " << &base << std::endl;
    std::cout << (p == &base ? "p == &base\n" : "p != &base\n");
    p->print();
    p = &derived;
    std::cout << "=+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+=\n";
    std::cout << "addr of p: " << p << ", addr of derived: " << &derived << std::endl;
    std::cout << (p == &derived ? "p == &derived\n" : "p != &derived\n");
    p->print();
    std::cout << "=+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+==+=+=+=+=+=+=+=+=+=\n";
    sleep(2);

    //p = nullptr;
    //delete p;

    return 0;
}