/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-05 15:45:44
 * @LastEditTime : 2021-08-05 17:06:57
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/teststl/test07.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <vector>
#include <set>
#include <map>

template <typename T>
void print(const T &t)
{
    for (auto &&item : t)
        std::cout << item << " ";
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    std::vector<int> vec;
    for (std::vector<int>::size_type i = 0; i < 10; ++i)
    {
        vec.push_back(i);
        vec.push_back(i);
    }
    std::cout << "vec value: \n";
    print<std::vector<int>>(vec);

    std::set<int> set(vec.cbegin(), vec.cend());
    std::cout << "set value: \n";
    print<std::set<int>>(set);

    std::multiset<int> multiset(vec.cbegin(), vec.cend());
    std::cout << "multiset value: \n";
    print<std::multiset<int>>(multiset);

    std::map<int, int> map;
    for (std::map<int, int>::size_type i = 0; i < 10; ++i)
        map.insert({i, i});
    std::cout << "map: size = " << map.size() << std::endl;
    std::cout << "{";
    for (auto iter = map.cbegin(); iter != map.cend(); ++iter)
        std::cout << "{key = " << iter->first << ", value = " << iter->second << (iter == --map.cend() ? "}" : "}; ");
    std::cout << "}\n";

    std::multimap<int, int> multimap;
    for (std::multimap<int, int>::size_type i = 0; i < 10; ++i)
    {
        multimap.insert({i, i});
        multimap.insert({i, i});
    }
    std::cout << "multimap: size = " << multimap.size() << std::endl;
    std::cout << "{";
    for (auto iter = multimap.cbegin(); iter != multimap.cend(); ++iter)
        std::cout << "{key = " << iter->first << ", value = " << iter->second << (iter == --multimap.cend() ? "}" : "}; ");
    std::cout << "}\n";

    return 0;
}
