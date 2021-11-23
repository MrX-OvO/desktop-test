#include <iostream>
#include <string>
#include <sstream>

template <typename T>
std::string debug_rep(const T &t)
{
    std::cout << "0 call std::string debug_rep(const T &)\n";
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T>
std::string debug_rep(T *p)
{
    std::cout << "1 call std::string debug_rep(T *p))\n";
    std::ostringstream ret;
    ret << "pointer: " << p;
    if (p)
        ret << " " << debug_rep(*p);
    else
        ret << " null pointer";
    return ret.str();
}

std::string debug_rep(const std::string &s)
{
    std::cout << "2 call std::string debug_rep(const std::string &)\n";
    return "\"" + s + "\"";
}

std::string debug_rep(char *p)
{
    std::cout << "3 call std::string debug_rep(char *p)\n";
    return debug_rep(std::string(p));
}

std::string debug_rep(const char *p)
{
    std::cout << "4 call std::string debug_rep(const char *p)\n";
    return debug_rep(std::string(p));
}

template <typename... Args>
void g(const Args &...args)
{
    std::cout << sizeof...(Args) << std::endl;
    std::cout << sizeof...(args) << std::endl;
}

template <typename T>
std::ostream &print(std::ostream &os, const T &t)
{
    std::cout << "0 call std::ostream &print(std::ostream &, const T &)\n";
    return os << t;
}

template <typename T, typename... Args>
std::ostream &print(std::ostream &os, const T &t, const Args &...args)
{
    std::cout << "1 call std::ostream &print(std::ostream &, const T &, const Args &...)\n";
    os << t << ", ";
    return print(os, args...);
}

template <typename... Args>
std::ostream &erroeMsg(std::ostream &os, const Args &...args)
{
    std::cout << "0 call std::ostream &erroeMsg(std::ostream &, const Args &...)\n";
    return print(os, debug_rep(args)...);
}

int main(int argc, char const *argv[])
{
    int i = 0;
    double d = 1.1;
    std::string s = "hello world";
    g(i, d, s);
    std::cout << "=======================\n";
    print(std::cout, i, d, s);
    std::cout << "\n=======================\n";
    erroeMsg(std::cout, &s, i, d, s);
    std::cout << std::endl;

    return 0;
}
