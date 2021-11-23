#include <iostream>
#include <cstring>
#include <cassert>

template <typename In, typename Out>
Out copy(In start, In end, Out dest)
{
    while (start != end)
        *dest++ = *start++;
    return dest;
}

template <typename T>
class Constant_iterator
{
    template <typename U>
    friend bool operator==(const Constant_iterator<U> &, const Constant_iterator<U> &);
    template <typename U>
    friend bool operator!=(const Constant_iterator<U> &, const Constant_iterator<U> &);
    template <typename U>
    friend Constant_iterator<U> operator+(const Constant_iterator<U> &, int);
    template <typename U>
    friend Constant_iterator<U> operator+(int, const Constant_iterator<U> &);

public:
    Constant_iterator() = default;
    Constant_iterator(const T &t) : data(t), count(1) {}
    ~Constant_iterator() = default;

    T operator*() const { return data; }
    Constant_iterator &operator++();
    Constant_iterator operator++(int);

private:
    T data;
    unsigned count;
};

template <typename T>
Constant_iterator<T> &Constant_iterator<T>::operator++()
{
    ++count;
    return *this;
}

template <typename T>
Constant_iterator<T> Constant_iterator<T>::operator++(int)
{
    Constant_iterator old = *this;
    ++*this;
    return old;
}

template <typename T>
bool operator==(const Constant_iterator<T> &c1, const Constant_iterator<T> &c2) { return c1.count == c2.count && c1.data == c2.data; }

template <typename T>
bool operator!=(const Constant_iterator<T> &c1, const Constant_iterator<T> &c2) { return !(c1 == c2); }

template <typename T>
Constant_iterator<T> operator+(const Constant_iterator<T> &c, int n)
{
    Constant_iterator<T> r = c;
    r.count += n;
    return r;
}

template <typename T>
Constant_iterator<T> operator+(int n, const Constant_iterator<T> &c) { return c + n; }

template <typename T>
class ostream_iterator
{
public:
    ostream_iterator(std::ostream &o, const char *s) : os(&o), str(s) {}
    ostream_iterator &operator=(const T &t)
    {
        *os << t << str;
        return *this;
    }

    ostream_iterator &operator++() { return *this; }
    ostream_iterator operator++(int) { return *this; }
    ostream_iterator &operator*() { return *this; }

private:
    std::ostream *os;
    const char *str;
};

template <typename T>
class istream_iterator
{
    template <typename U>
    friend bool operator==(istream_iterator<U> &, istream_iterator<U> &);
    template <typename U>
    friend bool operator!=(istream_iterator<U> &, istream_iterator<U> &);

public:
    istream_iterator() : is(nullptr), full(false), eof(true) {}
    istream_iterator(std::istream &i) : is(&i), full(false), eof(false) {}

    istream_iterator &operator++();
    istream_iterator operator++(int);
    T operator*();

private:
    T buffer;
    std::istream *is;
    bool full;
    bool eof;

private:
    void fill();
};

template <typename T>
void istream_iterator<T>::fill()
{
    if (!full && !eof)
    {
        if (*is >> buffer)
            full = true;
        else
            eof = true;
    }
}

template <typename T>
istream_iterator<T> &istream_iterator<T>::operator++()
{
    full = false;
    return *this;
}

template <typename T>
istream_iterator<T> istream_iterator<T>::operator++(int)
{
    istream_iterator old = *this;
    ++*this;
    return old;
}

template <typename T>
T istream_iterator<T>::operator*()
{
    fill();
    assert(full);
    return buffer;
}

template <typename T>
bool operator==(istream_iterator<T> &i1, istream_iterator<T> &i2)
{
    if (i1.eof && i2.eof)
        return true;
    if (!i1.eof && !i2.eof)
        return &i1 == &i2;
    i1.fill();
    i2.fill();
    return i1.eof == i2.eof;
}

template <typename T>
bool operator!=(istream_iterator<T> &i1, istream_iterator<T> &i2) { return !(i1 == i2); }

int main(int argc, char const *argv[])
{
    char hello[] = "Hello ";
    char world[] = "World";
    char message[15];
    char *p = message;
    p = copy(hello, hello + strlen(hello), p);
    p = copy(world, world + strlen(world), p);
    *p = '\0';
    std::cout << message << std::endl;

    double d[10];
    Constant_iterator<double> c(0.2);
    copy(c, c + 10, d);
    for (size_t i = 0; i < 10; ++i)
        std::cout << d[i] << (i < 9 ? ", " : "\n");

    ostream_iterator<double> oi(std::cout, "; ");
    copy(c, c + 10, oi);
    std::cout << std::endl;

    ostream_iterator<int> output(std::cout, ",,\n");
    istream_iterator<int> input(std::cin);
    istream_iterator<int> eof;
    copy(input, eof, output);

    return 0;
}
