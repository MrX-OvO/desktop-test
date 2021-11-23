#ifndef _POINTER
#define _POINTER

namespace chapter12_space
{
    template <typename T>
    class Array;
    template <typename T>
    class pointer
    {
    public:
        pointer() : pa(nullptr), sub(0) {}
        pointer(Array<T> &a, unsigned n = 0) : pa(&a), sub(n) {}

        T operator*() const
        {
            if (pa == nullptr)
                throw "* of unbound Pointer";
            return (*pa)[sub];
        }

        void update(const T &t)
        {
            if (pa == nullptr)
                throw "* of unbound Pointer";
            (*pa)[sub] = t;
        }

    private:
        Array<T> *pa;
        unsigned sub;
    };
} //namespace
#endif // !_POINTER
