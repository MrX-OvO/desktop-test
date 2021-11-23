#include <iostream>
#include <string>
#include <cstring>
#include <functional>

template <typename T>
int compare(const T &t1, const T &t2)
{
    std::cout << "call int compare(const T &, const T &)\n";
    if (std::less<T>()(t1, t2))
        return -1;
    if (std::less<T>()(t2, t1))
        return 1;
    return 0;
}

template <unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
    std::cout << "call int compare(const char (&)[], const char (&)[])\n";
    return strcmp(p1, p2);
}

template <>
int compare(const char *const &p1, const char *const &p2)
{
    std::cout << "call int compare(const char *const &, const char *const &)\n";
    return strcmp(p1, p2);
}

int compare(const char *p1, const char *p2)
{
    std::cout << "call int compare(const char *, const char *)\n";
    return strcmp(p1, p2);
}

int main(int argc, char const *argv[])
{
    int i = 1, j = 2;
    std::cout << compare(i, j) << std::endl;

    const char p1[] = "hello world";
    const char p2[] = "hello word";
    std::cout << compare(p1, p2) << std::endl;

    std::cout << compare("hi", "hello") << std::endl;

    return 0;
}
