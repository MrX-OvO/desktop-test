namespace array_space
{
    template <typename T>
    class Array;
    template <typename T>
    class Ptr_to_const;
    template <typename T>
    class Pointer;
    template <typename T>
    class Array_data
    {
        friend class Array<T>;
        friend class Ptr_to_const<T>;
        friend class Pointer<T>;

        Array_data(unsigned sz = 0) : data(new T[sz]), size(sz), use(1) {}
        Array_data(T *arr, unsigned sz = 0) : data(new T[sz]), size(sz), use(1) { copy(arr, sz); }
        Array_data(const Array_data &) = delete;
        Array_data &operator=(const Array_data &) = delete;
        ~Array_data() { delete[] data; }

        const T &operator[](unsigned n) const
        {
            if (n >= size || data == nullptr)
                throw "Array subscript out of range";
            return data[n];
        }

        T &operator[](unsigned n)
        {
            if (n >= size || data == nullptr)
                throw "Array subscript out of range";
            return data[n];
        }

        void copy(T *arr, unsigned n)
        {
            for (unsigned i = 0; i < n; ++i)
                data[i] = arr[i];
        }

        void resize(unsigned n)
        {
            if (n == size)
                return;
            T *oldData = data;
            data = new T[n];
            copy(oldData, size > n ? n : size);
            delete[] oldData;
            size = n;
        }

        void grow(unsigned new_sz)
        {
            unsigned sz = size;
            if (sz == 0)
                sz = 1;
            while (sz <= new_sz)
                sz |= (sz >> 1); // 约1.5倍
            resize(sz);
        }

        void clone(const Array_data &a, unsigned n)
        {
            delete[] data;
            size = a.size;
            data = new T[size];
            copy(a.data, a.size);
        }

        T *data;
        unsigned size;
        unsigned use;
    };

    template <typename T>
    class Array
    {
        friend class Ptr_to_const<T>;

    public:
        Array(unsigned sz) : data(new Array_data<T>(sz)) {}
        Array(T *arr, unsigned sz) : data(new Array_data<T>(arr, sz)) {}
        Array(const Array &a) : data(new Array_data<T>(a.data->size)) { data->copy(a.data->data, a.data->size); }
        Array &operator=(const Array &rhs)
        {
            if (this != &rhs)
                data->clone(*rhs.data, rhs.data->size);
            return *this;
        }
        ~Array()
        {
            if (--data->use == 0)
                delete data;
        }

        const T &operator[](unsigned n) const
        {
            return (*data)[n];
        }

        T &operator[](unsigned n)
        {
            return (*data)[n];
        }

        void resize(unsigned n)
        {
            data->resize(n);
        }

        void reserve(unsigned new_sz)
        {
            if (new_sz >= data->size)
                data->grow(new_sz);
        }

    private:
        Array_data<T> *data;
    };

    template <typename T>
    class Ptr_to_const
    {
        template <typename U>
        friend int operator-(const Ptr_to_const<U> &, const Ptr_to_const<U> &);
        template <typename U>
        friend bool operator==(const Ptr_to_const<U> &, const Ptr_to_const<U> &);
        template <typename U>
        friend bool operator<(const Ptr_to_const<U> &, const Ptr_to_const<U> &);

    public:
        Ptr_to_const() : pa(nullptr), sub(0) {}
        Ptr_to_const(const Array<T> &a, unsigned n = 0) : pa(a.data), sub(n) { ++pa->use; }
        Ptr_to_const(const Ptr_to_const<T> &p) : pa(p.pa), sub(p.sub)
        {
            if (pa)
                ++pa->use;
        }
        Ptr_to_const &operator=(const Ptr_to_const<T> rhs)
        {
            if (rhs.pa)
                ++rhs.pa->use;
            if (pa && --pa->use == 0)
                delete pa;
            pa = rhs.pa;
            sub = rhs.sub;
            return *this;
        }
        ~Ptr_to_const()
        {
            if (pa && --pa->use == 0)
                delete pa;
        }

        const T &operator*() const
        {
            if (pa == nullptr)
                throw "* of unbound Pointer";
            return (*pa)[sub];
        }

        Ptr_to_const &operator++()
        {
            ++sub;
            return *this;
        }

        Ptr_to_const operator++(int)
        {
            Ptr_to_const ret = *this;
            ++*this;
            return ret;
        }

        Ptr_to_const &operator--()
        {
            --sub;
            return *this;
        }

        Ptr_to_const operator--(int)
        {
            Ptr_to_const ret = *this;
            --*this;
            return ret;
        }

        Ptr_to_const &operator+=(int n)
        {
            sub += n;
            return *this;
        }

        Ptr_to_const &operator-=(int n)
        {
            sub -= n;
            return *this;
        }

    protected:
        Array_data<T> *pa;
        unsigned sub;
    };

    template <typename T>
    int operator-(const Ptr_to_const<T> &op1, const Ptr_to_const<T> &op2) { return static_cast<int>(op1.sub) - static_cast<int>(op2.sub); }

    template <typename T>
    Ptr_to_const<T> operator+(const Ptr_to_const<T> &p, int n)
    {
        Ptr_to_const<T> ret = p;
        return p += n;
    }

    template <typename T>
    Ptr_to_const<T> operator+(int n, const Ptr_to_const<T> &p) { return p + n; }

    template <typename T>
    Ptr_to_const<T> operator-(const Ptr_to_const<T> &p, int n)
    {
        Ptr_to_const<T> ret = p;
        return p -= n;
    }

    template <typename T>
    bool operator==(const Ptr_to_const<T> &op1, const Ptr_to_const<T> &op2)
    {
        if (op1.pa != op2.pa)
            return false;
        return true;
    }

    template <typename T>
    bool operator<(const Ptr_to_const<T> &op1, const Ptr_to_const<T> &op2)
    {
        if (op1.pa != op2.pa)
            throw "< on different Arrays";
        return op1.sub < op2.sub;
    }

    template <typename T>
    class Pointer : Ptr_to_const<T>
    {
    public:
        Pointer() {}
        Pointer(Array<T> &a, unsigned n = 0) : Ptr_to_const<T>(a, n) {}

        T &operator*() const
        {
            if (this->pa == nullptr)
                throw "* of unbound Pointer";
            return (*(this->pa))[this->sub];
        }

        Pointer &operator++()
        {
            ++this->sub;
            return *this;
        }

        Pointer operator++(int)
        {
            Pointer ret = *this;
            ++*this;
            return ret;
        }

        Pointer &operator--()
        {
            --this->sub;
            return *this;
        }

        Pointer operator--(int)
        {
            Pointer ret = *this;
            --*this;
            return ret;
        }

        Pointer &operator+=(int n)
        {
            this->sub += n;
            return *this;
        }

        Pointer &operator-=(int n)
        {
            this->sub -= n;
            return *this;
        }
    };

    template <typename T>
    Pointer<T> operator+(const Pointer<T> &p, int n)
    {
        Pointer<T> ret = p;
        return p += n;
    }

    template <typename T>
    Pointer<T> operator+(int n, const Pointer<T> &p) { return p + n; }

    template <typename T>
    Pointer<T> operator-(const Pointer<T> &p, int n)
    {
        Pointer<T> ret = p;
        return p -= n;
    }
} // namespace

#include <iostream>
#include <iomanip>

int main(int argc, char const *argv[])
{
    using namespace array_space;
    Array<int> *pa = new Array<int>(10);
    for (int i = 0; i < 10; ++i)
        (*pa)[i] = i;
    for (int i = 0; i < 2; ++i)
    {
        if (i == 0)
        {
            std::cout << std::setw(9) << "i ";
            for (int j = 0; j < 10; ++j)
                std::cout << j << (j < 9 ? ", " : "\n");
        }
        else
        {
            std::cout << "(*pa)[i] ";
            for (int j = 0; j < 10; ++j)
                std::cout << (*pa)[j] << (j < 9 ? ", " : "\n");
        }
    }

    Pointer<int> p(*pa, 5);
    std::cout << "before delete pa, *p = " << *p << std::endl;
    delete pa;
    *p = 42;
    std::cout << "after delete pa, *p = " << *p << std::endl;

    return 0;
}
