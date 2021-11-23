#ifndef _ARRAY
#define _ARRAY

namespace chapter12_space
{
    template <typename T>
    class Array
    {
    public:
        Array() : data(nullptr), size(0) {}
        Array(unsigned sz) : data(new T[sz]), size(sz) {}
        Array(const Array &) = delete;
        Array &operator=(const Array &) = delete;
        ~Array() { delete[] data; }

        const T operator[](unsigned n) const
        {
            if (n >= size || data == nullptr)
                throw "Array subscript out of range";
            return data[n];
        }

        T operator[](unsigned n)
        {
            if (n >= size || data == nullptr)
                throw "Array subscript out of range";
            return data[n];
        }

        operator const T *() const { return data; }

        operator T *() { return data; }

        void update(unsigned n, const T &t)
        {
            if (n >= size || data == nullptr)
                throw "Array subscript out of range";
            data[n] = t;
        }

    private:
        T *data;
        unsigned size;
    };
} // namespace

#endif // !_ARRAY
