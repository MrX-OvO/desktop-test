/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-07-27 18:50:07
 * @LastEditTime : 2021-07-30 16:39:15
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/t.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <bitset>
#include <algorithm>
#include <tuple>
#include <string>

#if 0

template <typename T>
void print(const T &arg)
{
    std::cout << arg << std::endl;
}
template <typename... Ts>
void print(const Ts &...args)
{
    print(args...);
}

template <typename T, typename... Ts>
void print(const T &firstArg, const Ts &...args)
{
    std::cout << firstArg << std::endl;
    print(args...);
}

template <typename Tuple, std::size_t N>
struct PRINT_TUPLE
{
    static void print(std::ostream &out, const Tuple &t)
    {
        PRINT_TUPLE<Tuple, N - 1>::print(out, t);
        out << ", " << std::get<N - 1>(t);
    }
};

template <typename Tuple>
struct PRINT_TUPLE<Tuple, 1>
{
    static void print(std::ostream &out, const Tuple &t)
    {
        out << "[" << std::get<0>(t);
    }
};

template <typename... args>
std::ostream &operator<<(std::ostream &out, const std::tuple<args...> &t)
{
    PRINT_TUPLE<decltype(t), sizeof...(args)>::print(out, t);
    return out << "]\n";
}

#elif 1

template <typename... Values>
class MyTuple;

template <>
class MyTuple<>
{
};

template <typename Head, typename... Tails>
class MyTuple<Head, Tails...> : private MyTuple<Tails...>
{
    using inherited = MyTuple<Tails...>;

protected:
    Head m_head;

public:
    MyTuple() {}
    MyTuple(Head head, Tails... tails) : m_head(head), inherited(tails...) {}
    auto head() const -> decltype(m_head) { return m_head; }
    const inherited &tail() const { return *this; }
};

template <typename MyTuple, std::size_t N>
struct PRINT_MY_TUPLE
{
    static void print(std::ostream &out, const MyTuple &t)
    {
        out << t.head() << ", ";
        PRINT_MY_TUPLE<MyTuple, N - 1>::print(out, t.tail());
    }
};

template <typename MyTuple>
struct PRINT_MY_TUPLE<MyTuple, 1>
{
    static void print(std::ostream &out, const MyTuple &t)
    {
        out << t.head() << "]\n";
    }
};

template <typename... args>
std::ostream &operator<<(std::ostream &out, const MyTuple<args...> &t)
{
    out << "[";
    PRINT_MY_TUPLE<decltype(t), sizeof...(args)>::print(out, t);
    //print<decltype(t), sizeof...(args)>(out, t);
    return out;
}

#endif

int main()
{
#if 0

    print(1, 3.14, "hello world", std::bitset<16>(234));

    std::cout << std::max({1, 2, 3, 4, 5}) << std::endl;
    std::cout << std::min({"hello", "world", "cplusplus"}) << std::endl;

    auto t = std::make_tuple(1, 3.14, "hello world", std::bitset<16>(234));
    std::cout << t << std::endl;

#elif 1

    const MyTuple<int, float, const char *> mytuple(1, 3.14, "hello world");
    std::cout << "tuple head: " << mytuple.head() << "\t tuple tails: " << mytuple.tail() << std::endl;
    //std::cout << "tuple head: " << tuple.head();

#endif

    return 0;
}