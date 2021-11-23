/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-09 14:24:17
 * @LastEditTime : 2021-08-09 14:46:17
 * @LastEditors  : MrX-OvO
 * @Description  : 行为像指针的类
 * @FilePath     : /test/testclassdesign/test03.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <string>
#include <cstring>

class HasPtr
{
public:
    HasPtr() = default;
    HasPtr(const std::string &s) : ps(new std::string(s)), i(s.size()), use(new size_t(1)) {}
    HasPtr(const char *s) : ps(new std::string(s)), i(strlen(s)), use(new size_t(1)) {}
    HasPtr(const HasPtr &hasPtr) : ps(new std::string(*hasPtr.ps)), i(hasPtr.i), use(hasPtr.use) { ++*use; }
    HasPtr &operator=(const HasPtr &hasPtr)
    {
        ++*hasPtr.use;
        if (--*use == 0)
        {
            delete ps;
            delete use;
        }
        ps = hasPtr.ps;
        i = hasPtr.i;
        use = hasPtr.use;
        return *this;
    }
    ~HasPtr()
    {
        if (--*use == 0)
        {
            delete ps;
            delete use;
        }
    }
    void print() const
    {
        if (!ps)
            std::cout << "std::string => , size => " << i << ", reference count => ";
        else
            std::cout << "std::string => " << *ps << ", size => " << i << ", reference count => " << *use;
    }

private:
    std::string *ps = nullptr;
    size_t i = 0;
    size_t *use = nullptr;
};

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

    HasPtr h3(h2), h4("");

    std::cout << "\nprint h2\n";
    h2.print();
    std::cout << std::endl;

    std::cout << "\nprint h3\n";
    h3.print();
    std::cout << std::endl;

    std::cout << "\nprint h4\n";
    h4.print();
    std::cout << std::endl;

    return 0;
}