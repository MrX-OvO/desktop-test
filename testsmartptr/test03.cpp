/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 16:36:50
 * @LastEditTime : 2021-08-08 19:08:53
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testsmartptr/test03.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main(int argc, char const *argv[])
{
    size_t n = 10;
    std::allocator<std::string> alloc;
    auto const p = alloc.allocate(n);
    std::cout << "&p = " << &p << std::endl;
    auto q = p;
    std::cout << "&q = " << &q << std::endl;
    alloc.construct(q, n, 'q');
    std::cout << "q = " << *q << ", &q = " << &q << std::endl;

    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::allocator<int> allocint;
    auto const r = allocint.allocate(vec.size() * 2); // r -> int *const
    std::cout << "r = " << *r << ", &r = " << &r << std::endl;
    auto s = std::uninitialized_copy(vec.begin(), vec.end(), r); // s -> int *
    std::cout << "s = " << *s << ", &s = " << &s << std::endl;
    auto t = std::uninitialized_fill_n(s, vec.size(), 6); // t -> int *
    std::cout << "t = " << *t << ", &t = " << &t << std::endl;

    std::cout << "r = " << *r << ", &r = " << &r << std::endl;
    std::cout << "s = " << *s << ", &s = " << &s << std::endl;
    std::cout << "t = " << *t << ", &t = " << &t << std::endl;

    for (int *iter = r; iter != t;)
        std::cout << *iter++ << " ";
    std::cout << std::endl;

    return 0;
}
