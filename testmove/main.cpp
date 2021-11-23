/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-07-31 15:54:47
 * @LastEditTime : 2021-07-31 18:31:02
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testmove/main.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <typeinfo>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "mystring.hpp"
#include "mystringnomove.hpp"

template <typename T>
void output_data(const T &myStr)
{
    std::cout << typeid(myStr).name() << "--\n";
    std::cout << "默认构造函数调用次数 dctor: " << T::getDCtor() << ", "
              << "构造函数调用次数 dctor: " << T::getCtor() << ", "
              << "拷贝构造函数调用次数 dctor: " << T::getCCtor() << ", "
              << "拷贝赋值调用次数 dctor: " << T::getCAsgn() << ", "
              << "移动构造函数调用次数 dctor: " << T::getMCtor() << ", "
              << "移动赋值调用次数 dctor: " << T::getMAsgn() << ", "
              << "析够函数调用次数 dctor: " << T::getDtor() << "\n";
}

template <typename M, typename NM>
void test_moveable(M c1, NM c2, long &value)
{
    char buf[10];
    using m_iter = typename M::iterator;
    using v1_type = typename std::iterator_traits<m_iter>::value_type;
    clock_t start, end, duration;
    start = clock();
    for (long i = 0; i < value; ++i)
    {
        snprintf(buf, 10, "%s", rand());
        auto iter = c1.end();
        c1.insert(iter, v1_type(buf));
    }
    end = clock();
    duration = start - end;
    std::cout << "construction, milli-seconds: " << duration << "\t size() = " << c1.size() << std::endl;
    output_data(*(c1.end()));
    M c11(c1);
    M c12(std::move(c1));
}

int main(int argc, char const *argv[])
{
    using M = std::vector<mystring>;

    using NM = std::vector<mystringnomove>;
    M c1;
    NM c2;
    long value = 50000;
    test_moveable<M, NM>(c1, c2, value);

    return 0;
}
