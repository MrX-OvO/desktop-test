#include <iostream>

#include "seq.h"
#include "seq_algorithm.h"

int main(int argc, char const *argv[])
{
    using namespace chapter15_space;

    Seq<int> s1, s2;
    for (size_t i = 0; i < 10; i++)
    {
        s1.insert(i);
        s2.insert(i * i);
    }
    std::cout << " s1 = ";
    while (s1)
    {
        std::cout << *s1++;
        std::cout << (s1 ? "\n" : ", ");
    }
    std::cout << " s2 = ";
    while (s2)
    {
        std::cout << *s2++;
        std::cout << (s2 ? "\n" : ", ");
    }

    Seq<int> m = merge<int>(s1, s2);
    std::cout << "merge(s1, s2) = ";
    while (m)
    {
        std::cout << *m++;
        std::cout << (m ? "\n" : ", ");
    }

    Seq<int> p, q;
    for (size_t i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
            p.insert(i * i);
        else
            p.insert(i >> 1);
    }
    std::cout << "p = ";
    while (p)
    {
        std::cout << *p++;
        std::cout << (p ? "\n" : ", ");
    }
    q = sort<int>(p);
    std::cout << "sort(p) = ";
    while (q)
    {
        std::cout << *q++;
        std::cout << (q ? "\n" : ", ");
    }

    return 0;
}
