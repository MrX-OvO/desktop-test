#include <iostream>
#include <string>
#include <sstream>

template <typename T>
std::string debug_rep(const T &t)
{
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T>
std::string debug_rep(T *p)
{
    std::ostringstream ret;
    ret << "pointer: " << p;
    if (p)
        ret << " " << debug_rep(*p);
    else
        ret << " null pointer";
    return ret.str();
}

std::string debug_rep(const std::string &s) { return "\"" + s + "\""; }

std::string debug_rep(char *p) { return debug_rep(std::string(p)); }

std::string debug_rep(const char *p) { return debug_rep(std::string(p)); }

template <typename T>
void f(T) { std::cout << "void f(T)" << std::endl; }

template <typename T>
void f(const T *) { std::cout << "void f(const T *)" << std::endl; }

template <typename T>
void g(T) { std::cout << "void g(T)" << std::endl; }

template <typename T>
void g(T *) { std::cout << "void g(T *)" << std::endl; }

int main(int argc, char const *argv[])
{
    std::string s("hi");
    std::cout << debug_rep(s) << std::endl;
    std::cout << debug_rep(&s) << std::endl;

    std::string *sp = &s;
    std::cout << debug_rep(sp) << std::endl;
    std::cout << debug_rep(&sp) << std::endl;

    char ch[] = "hi world";
    char *p = ch;
    std::cout << debug_rep(p) << std::endl;
    std::cout << debug_rep("hello world!") << std::endl;
    std::cout << std::endl;

    int i = 1, j = 2, k = 3;
    std::cout << "i = " << i << " &i = " << &i << std::endl;
    std::cout << "j = " << j << " &j = " << &j << std::endl;
    std::cout << "k = " << k << " &k = " << &k << std::endl;

    int *pi = &i;
    int *pj = &j;
    int *pk = &k;
    std::cout << "*pi = " << *pi << " pi = " << pi << " &pi = " << &pi << std::endl;
    std::cout << "*pj = " << *pj << " pj = " << pj << " &pj = " << &pj << std::endl;
    std::cout << "*pk = " << *pk << " pk = " << pk << " &pk = " << &pk << std::endl;

    int *a[] = {pi, pj, pk};
    for (size_t i = 0; i < 3; ++i)
        std::cout << "*a[" << i << "] = " << *a[i] << " a[" << i << "] = " << a[i] << " &a[" << i << "] = " << &a[i] << std::endl;

    int b[] = {i, j, k};
    int(*c)[3];
    c = &b;
    for (size_t i = 0; i < 3; ++i)
        std::cout << "*c[" << i << "] = " << *c[i] << " c[" << i << "] = " << c[i] << " &c[" << i << "] = " << &c[i] << std::endl;

    int m = 1, *n = &m;
    const int cm = 0, *cn = &cm;
    f(42);
    f(n);
    f(cm);
    f(cn);
    g(42);
    g(n);
    g(cm);
    g(cn);

    return 0;
}
