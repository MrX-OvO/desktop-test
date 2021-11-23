#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <typeinfo>

class A
{
public:
    A() = default;
    virtual ~A() = default;
};

class B : public A
{
public:
    B() = default;
    virtual ~B() = default;
};

class C : public B
{
public:
    C() = default;
    virtual ~C() = default;
};

int main(int argc, char const *argv[])
{
    A *pa = new C;
    std::cout << "typeid(pa).name() = " << typeid(pa).name() << std::endl;
    std::cout << "typeid(*pa).name() = " << typeid(*pa).name() << std::endl;
    std::cout << "typeid(&pa).name() = " << typeid(&pa).name() << std::endl;
    delete pa;
    pa = nullptr;
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

    C objc;
    std::cout << "typeid(objc).name() = " << typeid(objc).name() << std::endl;
    std::cout << "typeid(&objc).name() = " << typeid(&objc).name() << std::endl;
    A &ra = objc;
    std::cout << "typeid(ra).name() = " << typeid(ra).name() << std::endl;
    std::cout << "typeid(&ra).name() = " << typeid(&ra).name() << std::endl;
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

    B *pb = new B;
    std::cout << "typeid(pb).name() = " << typeid(pb).name() << std::endl;
    std::cout << "typeid(*pb).name() = " << typeid(*pb).name() << std::endl;
    std::cout << "typeid(&pb).name() = " << typeid(&pb).name() << std::endl;
    A &ra1 = *pb;
    std::cout << "typeid(ra1).name() = " << typeid(ra1).name() << std::endl;
    std::cout << "typeid(&ra1).name() = " << typeid(&ra1).name() << std::endl;
    delete pb;
    pb = nullptr;
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

    std::cout << "typeid(bool).name() = " << typeid(bool).name() << std::endl;
    std::cout << "typeid(char).name() = " << typeid(char).name()
              << ", typeid(signed char).name() = " << typeid(signed char).name()
              << ", typeid(unsigned char).name() = " << typeid(unsigned char).name() << std::endl;
    std::cout << "typeid(wchar_t).name() = " << typeid(wchar_t).name()
              << ", typeid(char16_t).name() = " << typeid(char16_t).name()
              << ", typeid(char32_t).name() = " << typeid(char32_t).name() << std::endl;
    std::cout << "typeid(short).name() = " << typeid(short).name() << std::endl;
    std::cout << "typeid(unsigned).name() = " << typeid(unsigned int).name()
              << ", typeid(signed int).name() = " << typeid(signed int).name()
              << ", typeid(unsigned int).name() = " << typeid(unsigned int).name() << std::endl;
    std::cout << "typeid(int).name() = " << typeid(int).name() << std::endl;
    std::cout << "typeid(long).name() = " << typeid(long).name()
              << ", typeid(long long).name() = " << typeid(long long).name() << std::endl;
    std::cout << "typeid(float).name() = " << typeid(float).name()
              << ", typeid(double).name() = " << typeid(double).name()
              << ", typeid(long double).name() = " << typeid(long double).name() << std::endl;
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

    std::cout << "typeid(bool[]).name() = " << typeid(bool[]).name()
              << ", typeid(char[]).name() = " << typeid(char[]).name()
              << ", typeid(short[]).name() = " << typeid(short[]).name()
              << ", typeid(int[]).name() = " << typeid(int[]).name()
              << ", typeid(long[]).name() = " << typeid(long[]).name()
              << ", typeid(long long[]).name() = " << typeid(long long[]).name() << std::endl
              << "typeid(float[]).name() = " << typeid(float[]).name()
              << ", typeid(double[]).name() = " << typeid(double[]).name()
              << ", typeid(long double[]).name() = " << typeid(long double[]).name() << std::endl;
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

    std::cout << "typeid(std::array<bool, 10>).name() = " << typeid(std::array<bool, 10>).name() << std::endl;
    std::cout << "typeid(std::string).name() = " << typeid(std::string).name() << std::endl;
    std::cout << "typeid(std::vector<char>).name() = " << typeid(std::vector<char>).name() << std::endl;
    std::cout << "typeid(std::deque<short>).name() = " << typeid(std::deque<short>).name() << std::endl;
    std::cout << "typeid(std::list<int>).name() = " << typeid(std::list<int>).name() << std::endl;
    std::cout << "typeid(std::forward_list<long>).name() = " << typeid(std::forward_list<long>).name() << std::endl;
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

    std::cout << "typeid(std::map<char,int>).name() = " << typeid(std::map<char, int>).name() << std::endl;
    std::cout << "typeid(std::multimap<int, bool>).name() = " << typeid(std::multimap<int, bool>).name() << std::endl;
    std::cout << "typeid(std::unordered_map<int,int>).name() = " << typeid(std::unordered_map<int, int>).name() << std::endl;
    std::cout << "typeid(std::unordered_multimap<int, std::string>).name() = " << typeid(std::unordered_multimap<int, std::string>).name() << std::endl;
    std::cout << "typeid(std::set<int>).name() = " << typeid(std::set<int>).name() << std::endl;
    std::cout << "typeid(std::multiset<long>).name() = " << typeid(std::multiset<long>).name() << std::endl;
    std::cout << "typeid(std::unordered_set<char>).name() = " << typeid(std::unordered_set<char>).name() << std::endl;
    std::cout << "typeid(std::unordered_multiset<bool>).name() = " << typeid(std::unordered_multiset<bool>).name() << std::endl;
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

    std::cout << "typeid(std::stack<int>).name() = " << typeid(std::stack<int>).name() << std::endl;
    std::cout << "typeid(std::queue<char>).name() = " << typeid(std::queue<char>).name() << std::endl;
    std::cout << "typeid(std::priority_queue<std::string>).name() = " << typeid(std::priority_queue<std::string>).name() << std::endl;

    return 0;
}
