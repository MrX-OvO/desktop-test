#include <iostream>
#include <type_traits>
#include <utility>

template <typename T1, typename T2, typename T3>
T1 sum(T2 a, T3 b) { return a + b; }

template <typename T>
T *f(const T &t)
{
    using type = typename std::remove_reference<T>::type;
    T *pt = new type(t * t + t);
    return pt;
}

template <typename T>
void f1(T &) {}

template <typename T>
void f2(const T &) {}

template <typename T>
void f3(T &&val)
{
    T t = val;
    t = *f(t);
    if (t == val)
        std::cout << "reference...\nt = val = " << t << std::endl;
    else
        std::cout << "copy...\nt = " << t << ", val = " << val << std::endl;
}

template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2)
{
    f(t2, t1);
}

void func1(int v1, int &v2) { std::cout << v1 << " " << ++v2 << std::endl; }

template <typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

void func2(int &&v1, int &v2) { std::cout << v1 << " " << ++v2 << std::endl; }

int main(int argc, char const *argv[])
{
    char c = 'A';
    short s = 3;
    int i = 1;
    int j = 2;
    float f = 1.234567F;
    double d = 2.56789;
    long l = 3L;
    long long ll = 33LL;

    std::cout << sum<double>(f, i) << std::endl;

    f1(i);
    f1(j);
    // f1(5);

    f2(i);
    f2(j);
    f2(5);

    f3(i);
    f3(5);

    int m = 5, n = 5;
    func1(42, m);
    flip1(func1, n, 42);

    int a = 5, b = 5;
    func2(42, a);
    flip2(func2, b, 42);

    return 0;
}
