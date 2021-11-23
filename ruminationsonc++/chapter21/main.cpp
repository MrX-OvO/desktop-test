#include <iostream>

namespace test01
{
    void f(int &i) { ++i; }

#if 0
void apply(void f(int &), int *p, int n)
{
    for (int i = 0; i < n; ++i)
        f(p[i]);
}

#elif 1
    void apply(void (*pf)(int &), int *p, int n)
    {
        for (int i = 0; i < n; ++i)
            f(p[i]);
    }
#endif
} // namespace test01

namespace test02
{
    int f(int i) { return i >> 1; }
    int g(int j) { return j * j; }

    using pFunc = int (*)(int);

    class Intcomp
    {
    public:
        Intcomp(pFunc f0, pFunc g0) : pf(f0), pg(g0) {}

        int operator()(int n) const { return pf(pg(n)); }

    private:
        pFunc pf, pg;
    };
} // namespace test02

namespace test03
{
    template <typename F, typename G, typename X, typename Y>
    class Comp
    {
    public:
        Comp(F f0, G g0) : f(f0), g(g0) {}

        Y operator()(X x) const { return f(g(x)); }

    private:
        F f;
        G g;
    };
} // namespace test03

namespace test04
{
    template <typename X, typename Y>
    class Comp_base
    {
    public:
        virtual Y operator()(X) const = 0;
        virtual Comp_base *clone() const = 0;
        virtual ~Comp_base() {}
    };

    template <typename F, typename G, typename X, typename Y>
    class Comp : public Comp_base<X, Y>
    {
    public:
        Comp(F f0, G g0) : f(f0), g(g0) {}

        Y operator()(X x) const { return f(g(x)); }

        Comp_base<X, Y> *clone() const override { return new Comp(*this); }

    private:
        F f;
        G g;
    };

    template <typename X, typename Y>
    class Composition
    {
    public:
        template <typename F, typename G>
        Composition(F f, G g) : p(new Comp<F, G, X, Y>(f, g)) {}

        Composition(const Composition &c) : p(c.p->clone()) {}

        Composition &operator=(const Composition &rhs)
        {
            if (this != &rhs)
            {
                delete p;
                p = rhs.p->clone();
            }
            return *this;
        }

        ~Composition() { delete p; }

        Y operator()(X x) const { return (*p)(x); } // p->operator()(x)

    private:
        Comp_base<X, Y> *p;
    };
} // namespace test04

void printArr(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << (i < n - 1 ? ", " : "\n");
}

int main(int argc, char const *argv[])
{
    int arr[] = {1, 2, 3, 4, 5};
    printArr(arr, 5);
    test01::apply(test01::f, arr, 5);
    printArr(arr, 5);

    test02::Intcomp fg(test02::f, test02::g);
    std::cout << "fg(5) = " << fg(5) << std::endl; // 5*5>>1

    using pFunc = int (*)(int);
    test03::Comp<decltype(fg), pFunc, int, int> fgg(fg, test02::g); // (5*5)*(5*5)>>1
    std::cout << "fgg(5) = " << fgg(5) << std::endl;

    test04::Composition<int, int> fgf(fg, test02::f);
    std::cout << "fgf(5) = " << fgf(5) << std::endl; // (5>>1)*(5>>1)>>1

    return 0;
}
