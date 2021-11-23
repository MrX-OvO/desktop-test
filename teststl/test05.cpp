/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-05 11:40:05
 * @LastEditTime : 2021-08-05 12:06:22
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/teststl/test05.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>

int main(int argc, char const *argv[])
{
    std::istream_iterator<int> in_iter(std::cin), eof;
    std::vector<int> vec(in_iter, eof);
    std::ostream_iterator<int> out_iter(std::cout, " ");
    std::copy(vec.begin(), vec.end(), out_iter);
    std::cout << std::endl;
    auto sum = std::accumulate(in_iter, eof, 0);
    std::cout << "sum of cin: " << sum << std::endl;

    return 0;
}
