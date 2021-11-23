/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-01 15:24:23
 * @LastEditTime : 2021-08-01 15:53:50
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/teststl/test01.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main(int argc, char const *argv[])
{
    std::vector<int> v({100, 2, 3, 45, 21, 79});
    std::cout << "vector v 中大于20的元素个数:\n";
    std::cout << std::count_if(v.begin(), v.end(), std::not1(std::bind2nd(std::less<int>(), 20)));

    return 0;
}
