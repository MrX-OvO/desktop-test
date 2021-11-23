namespace test01
{
    int sum(int *p, int n)
    {
        int result = 0;
        for (int i = 0; i < n; ++i)
            result += p[i];
        return result;
    }
} // namespace test01

namespace test02
{
    class Int_iterator
    {
    public:
        Int_iterator(int *p, int c) : data(p), len(c) {}
        Int_iterator(const Int_iterator &) = default;
        Int_iterator &operator=(const Int_iterator &) = default;
        ~Int_iterator() = default;

        bool valid() const { return len > 0; }
        int next()
        {
            --len;
            return *data++;
        }

    private:
        int *data;
        int len;
    };

    int sum(Int_iterator it)
    {
        int result = 0;
        while (it.valid())
            result += it.next();
        return result;
    }

    int sum(int *p, int n) { return sum(Int_iterator(p, n)); }
} // namespace test02

namespace test03
{
    template <typename T>
    class Iterator
    {
    public:
        Iterator(T *p, int c) : data(p), len(c) {}
        Iterator(const Iterator &) = default;
        Iterator &operator=(const Iterator &) = default;
        ~Iterator() = default;

        bool valid() const { return len > 0; }
        T next()
        {
            --len;
            return *data++;
        }

    private:
        T *data;
        int len;
    };

    template <typename T, typename It>
    void sum(T &result, It it)
    {
        result = 0;
        while (it.valid())
            result += it.next();
    }

    template <typename T>
    T sum(T *p, int n)
    {
        T result = 0;
        sum(result, Iterator<T>(p, n));
        return result;
    }
} // namespace test03

namespace test04
{
    template <typename T>
    class Iterator
    {
    public:
        virtual ~Iterator() {}
        virtual bool valid() const = 0;
        virtual T next() = 0;
    };

    template <typename T>
    class Array_iterator : public Iterator<T>
    {
    public:
        Array_iterator(T *p, int c) : data(p), len(c) {}
        Array_iterator(const Array_iterator &) = default;
        Array_iterator &operator=(const Array_iterator &) = default;
        ~Array_iterator() = default;

        bool valid() const { return len > 0; }
        T next()
        {
            --len;
            return *data++;
        }

    private:
        T *data;
        int len;
    };

    template <typename T>
    T sum(Iterator<T> &it)
    {
        T result = 0;
        while (it.valid())
            result += it.next();
        return result;
    }

    template <typename T, typename It>
    void sum(T &result, It it)
    {
        result = 0;
        while (it.valid())
            result += it.next();
    }

    template <typename T>
    T sum(T *p, int n)
    {
        T result = 0;
        sum(result, Array_iterator<T>(p, n));
        return result;
    }
} // namespace test04

#include <iostream>

namespace test05
{
    template <typename T>
    class Reader
    {
    public:
        Reader(std::istream &is) : i(is) { advance(); }
        Reader(const Reader &) = default;
        Reader &operator=(const Reader &) = default;
        ~Reader() = default;

        bool valid() const { return status; }
        T next()
        {
            T result = data;
            advance();
            return result;
        }

    private:
        std::istream &i;
        bool status;
        T data;

    private:
        void advance()
        {
            i >> data;
            status = i.good();
        }
    };

    template <typename T, typename It>
    void sum(T &result, It it)
    {
        result = 0;
        while (it.valid())
            result += it.next();
    }

    template <typename T>
    T sum(std::istream &is)
    {
        T result = 0;
        sum(result, Reader<T>(is));
        return result;
    }
} // namespace test05

int main(int argc, char const *argv[])
{
    std::cout << "=========== namespace test01 ===========\n";
    int test01[10];
    for (size_t i = 0; i < 10; ++i)
        test01[i] = i;
    std::cout << "test01 = [";
    for (size_t i = 0; i < 10; ++i)
        std::cout << test01[i] << (i < 9 ? ", " : "]\n");
    std::cout << "test01::sum(test01, 10) = " << test01::sum(test01, 10) << std::endl;
    std::cout << "=========== namespace test01 ===========\n";

    std::cout << "=========== namespace test02 ===========\n";
    int test02[10];
    for (size_t i = 0; i < 10; ++i)
        test02[i] = i;
    std::cout << "test02 = [";
    for (size_t i = 0; i < 10; ++i)
        std::cout << test02[i] << (i < 9 ? ", " : "]\n");
    std::cout << "test02::sum(test02, 10) = " << test02::sum(test02, 10) << std::endl;
    std::cout << "=========== namespace test02 ===========\n";

    std::cout << "=========== namespace test03 ===========\n";
    double test03[10];
    for (size_t i = 0; i < 10; ++i)
        test03[i] = i * 1.002;
    std::cout << "test03 = [";
    for (size_t i = 0; i < 10; ++i)
        std::cout << test03[i] << (i < 9 ? ", " : "]\n");
    std::cout << "test03::sum(test03, 10) = " << test03::sum(test03, 10) << std::endl;
    std::cout << "=========== namespace test03 ===========\n";

    std::cout << "=========== namespace test04 ===========\n";
    float test04[10];
    for (size_t i = 0; i < 10; ++i)
        test04[i] = i * 1.002f;
    std::cout << "test04 = [";
    for (size_t i = 0; i < 10; ++i)
        std::cout << test04[i] << (i < 9 ? ", " : "]\n");
    std::cout << "test04::sum(test04, 10) = " << test04::sum(test04, 10) << std::endl;
    std::cout << "=========== namespace test04 ===========\n";

    std::cout << "=========== namespace test05 ===========\n";
    std::cout << "enter numbers:\n";
    int r = test05::sum<int>(std::cin);
    std::cout << "test05::sum<int>(std::cin) = " << r << std::endl;
    std::cout << "=========== namespace test05 ===========\n";

    return 0;
}
