/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 22:50:46
 * @LastEditTime : 2021-08-09 14:24:34
 * @LastEditors  : MrX-OvO
 * @Description  : 行为像值的类
 * @FilePath     : /test/testclassdesign/test01.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <string>

class HasPtr
{
    friend void swap(HasPtr &, HasPtr &);

public:
    HasPtr() = default;
    HasPtr(const std::string &s) : ps(new std::string(s)), i(s.size()) {}
    HasPtr(const HasPtr &hasPtr) : ps(new std::string(*hasPtr.ps)), i(hasPtr.i) {}
    HasPtr(HasPtr &&hasPtr) noexcept : ps(hasPtr.ps), i(hasPtr.i) { hasPtr.ps = nullptr; }
    HasPtr &operator=(HasPtr rhs)
    {
        swap(*this, rhs);
        return *this;
    }
    ~HasPtr()
    {
        if (ps)
            delete ps;
    }
    void print() const
    {
        if (!ps)
            std::cout << "std::string => , size = " << i;
        else
            std::cout << "std::string => " << *ps << ", size = " << i;
    }

private:
    std::string *ps = nullptr;
    size_t i = 0;
};

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

int main(int argc, char const *argv[])
{
    std::string s = "HasPtr string";
    HasPtr h1, h2(s);

    std::cout << "print h1\n";
    h1.print();
    std::cout << std::endl;

    std::cout << "\nprint h2\n";
    h2.print();
    std::cout << std::endl;

    return 0;
}