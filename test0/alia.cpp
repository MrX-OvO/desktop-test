/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-07-29 13:46:57
 * @LastEditTime : 2021-07-29 18:12:44
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/alia.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>

template <typename T>
using func1 = T (*)(const T &, const T &);

template <typename T1, typename T2>
using func2 = delctype(func2<T1, T2>(T1(), T2())) (*)(const T1 &, const T2 &);

// add
template <typename T>
T add(const T &t1, const T &t2) { return t1 + t2; }

template <typename T1, typename T2>
auto add(const T1 &t1, const T2 &t2) -> decltype(t1 + t2) { return t1 + t2; }

// minus
template <typename T>
T minus(const T &t1, const T &t2) { return t1 - t2; }

template <typename T1, typename T2>
auto minus(const T1 &t1, const T2 &t2) -> decltype(t1 - t2) { return t1 - t2; }

// mul
template <typename T>
T mul(const T &t1, const T &t2) { return t1 * t2; }

template <typename T1, typename T2>
auto mul(const T1 &t1, const T2 &t2) -> decltype(t1 * t2) { return t1 * t2; }

// div
template <typename T>
T div(const T &t1, const T &t2) { return ((t2 != 0) ? (t1 / t2) : t2); }

template <typename T1, typename T2>
auto div(const T1 &t1, const T2 &t2) -> decltype((t2 != 0) ? (t1 / t2) : t2) { return ((t2 != 0) ? (t1 / t2) : t2); }

// void cal(T (*)(const T&, const T&), const T&, const T&)
template <typename T>
void cal(T (*f)(const T &, const T &), const T &t1, const T &t2) { std::cout << f(t1, t2) << std::endl; }

template <typename T1, typename T2>
void cal(T1 (*f)(const T1 &, const T2 &), const T1 &t1, const T2 &t2) { std::cout << f(t1, t2) << std::endl; }

int main(int argc, char const *argv[])
{
    func1<int> a[] = {add<int>, minus<int>, mul<int>};
    const char *c[] = {"add: ", "minus: ", "mul: ", "div: "};

    int i = 0;
    while (i < 4)
    {
        std::cout << "i = " << i << ", i + 1 = " << i + 1 << std::endl;
        std::cout << c[i];
        cal(a[i], i, i + 1);
        ++i;
        if (i == 3)
        {
            std::cout << "i = " << i << ", i + 1 = " << i + 1 << std::endl;
            std::cout << c[i];
            cal<float, int>(div, i, i + 1);
            ++i;
        }
    }

    return 0;
}
