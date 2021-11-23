/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-05 14:16:41
 * @LastEditTime : 2021-08-05 15:11:46
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/teststl/test06.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <ctime>

void print(const std::vector<int> &vec)
{
    for (auto &&v : vec)
        std::cout << v << " ";
}

int main(int argc, char const *argv[])
{
    time_t t;
    time(&t);
    srand((unsigned int)t);
    std::cout << "从1970年1月1日至今的秒数: " << t << "s" << std::endl;
    std::cout << "当前时间: " << ctime(&t);

    std::vector<int> vec1;
    auto insert_iter = std::back_inserter(vec1);
    for (size_t i = 0; i < 20; ++i)
        insert_iter = rand() % 100;
    std::cout << "vec: \n";
    print(vec1);
    std::cout << std::endl;

    std::reverse(vec1.begin(), vec1.end());
    std::cout << "reverse vec1: \n";
    print(vec1);
    std::cout << std::endl;

    auto remove_iter = std::remove_if(vec1.begin(), vec1.end(), [](const int &i)
                                      { return i % 2; });
    vec1.erase(remove_iter, vec1.end());
    std::cout << "remove odd from vec1: \n";
    print(vec1);
    std::cout << std::endl;

    std::vector<int> vec2(vec1.size());
    auto dest = vec2.begin();
    std::reverse_copy(vec1.begin(), vec1.end(), dest);
    std::cout << "reverse_copy vec1 to vec2: \n";
    print(vec2);
    std::cout << std::endl;

    std::remove_copy_if(vec1.begin(), vec1.end(), std::back_inserter(vec2), [](const int &i)
                        { return i % 3 == 0; });
    vec2.erase(vec2.begin(), vec2.begin() + vec1.size());
    std::cout << "remove odd and (i % 3 == 0) from vec2: \n";
    print(vec2);
    std::cout << std::endl;

    return 0;
}
