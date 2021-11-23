/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-04 15:34:53
 * @LastEditTime : 2021-08-04 17:39:56
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/teststl/test03.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <forward_list>
#include <stack>
#include <string>

int main(int argc, char const *argv[])
{
    /*     std::list<int> lst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "lst: ";
    for (auto &&l : lst)
    {
        std::cout << l << std::setw(2);
    }
    std::cout << std::endl;
    std::cout << "flst: ";
    for (auto &&fl : flst)
    {
        std::cout << fl << std::setw(2);
    }
    std::cout << std::endl;

    auto it = lst.begin();
    while (it != lst.end())
    {
        if (*it % 2 == 1)
            it = lst.erase(it);
        else
            ++it;
    }
    std::cout << "even in lst: ";
    for (auto &&l : lst)
    {
        std::cout << l << std::setw(2);
    }
    std::cout << std::endl;
    auto prev = flst.before_begin();
    auto curr = flst.begin();
    while (curr != flst.end())
    {
        if (*curr % 2 == 1)
            curr = flst.erase_after(prev);
        else
        {
            prev = curr;
            ++curr;
        }
    }
    std::cout << "even in flst: ";
    for (auto &&fl : flst)
    {
        std::cout << fl << std::setw(2);
    }
    std::cout << std::endl;

    std::vector<int> vec;
    std::cout << "vec size: " << vec.size() << ", vec canpacity: " << vec.capacity() << std::endl;
    using type = std::vector<int>::size_type;
    for (type i = 0; i < 24; ++i)
    {
        vec.push_back(i);
        std::cout << "vec size: " << vec.size() << ", vec canpacity: " << vec.capacity() << std::endl;
    } */

    std::stack<char> cal;
    const char *expr = "(6-4)";
    for (auto &&c : std::string(expr))
    {
        int a, b;
        char op, res;

        switch (c)
        {
        case ')':
            std::cout << c << std::endl;

            a = cal.top() - '0';
            cal.pop();
            op = cal.top();
            cal.pop();
            b = cal.top() - '0';
            cal.pop();
            cal.pop();

            if ('+' == op)
            {
                res = static_cast<char>(b + a);
                cal.push(res);
                std::cout << "cal.top() = " << cal.top() << ", cal.size() = " << cal.size() << std::endl;
            }
            else if ('-' == op)
            {
                res = static_cast<char>(b - a);
                cal.push(res);
                std::cout << "cal.top() = " << static_cast<int>(cal.top()) << ", cal.size() = " << cal.size() << std::endl;
            }
            else if ('*' == op)
            {
                res = static_cast<char>(b * a);
                cal.push(res);
                std::cout << "cal.top() = " << cal.top() << ", cal.size() = " << cal.size() << std::endl;
            }
            else if ('/' == op)
            {
                res = static_cast<char>(b / a);
                cal.push(res);
                std::cout << "cal.top() = " << cal.top() << ", cal.size() = " << cal.size() << std::endl;
            }
            else
            {
                res = static_cast<char>(b % a);
                cal.push(res);
                std::cout << "cal.top() = " << cal.top() << ", cal.size() = " << cal.size() << std::endl;
            }
            break;

        default:
            cal.push(c);
            std::cout << "cal.top() = " << cal.top() << ", cal.size() = " << cal.size() << std::endl;
            break;
        }
    }

    return 0;
}
