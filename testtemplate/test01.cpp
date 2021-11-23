#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <initializer_list>
#include <memory>

template <typename T>
class BlobPtr;

template <typename T>
class Blob
{
    friend class BlobPtr<T>;

public:
    using size_type = typename std::vector<T>::size_type;

    Blob() : data(std::make_shared<std::vector<T>>()) {}

    template <typename It>
    Blob(It b, It e) : data(std::make_shared<std::vector<T>>(b, e)) {}

    Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) {}
    Blob(const Blob &blob) : data(blob.data) {}
    Blob(Blob &&blob) noexcept : data(std::move(blob.data)) {}
    Blob &operator=(const Blob &) &;
    Blob &operator=(Blob &&) &noexcept;
    Blob &operator=(std::initializer_list<T> il) &;
    ~Blob() = default;

    size_type size() { return data->size(); }
    const size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const T &v) { data->push_back(v); };
    void push_back(const T &v) const { data->push_back(v); };
    void push_back(T &&v) { data->push_back(std::move(v)); };
    void push_back(T &&v) const { data->push_back(std::move(v)); };
    void pop_back();
    void pop_back() const;
    T &back();
    const T &back() const;
    T &front();
    const T &front() const;
    T &operator[](size_type i) { return data->at(i); }
    const T &operator[](size_type i) const { return data->at(i); }
    BlobPtr<T> begin() { return BlobPtr(*this); }
    const BlobPtr<T> begin() const { return BlobPtr(*this); }
    BlobPtr<T> end() { return BlobPtr(*this, data->size()); }
    const BlobPtr<T> end() const { return BlobPtr(*this, data->size()); }

private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;
};

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T>
Blob<T> &Blob<T>::operator=(const Blob &rhs) &
{
    if (this != &rhs)
    {
        delete data;
        data = rhs.data;
    }
    return *this;
}

template <typename T>
Blob<T> &Blob<T>::operator=(Blob &&rhs) &noexcept
{
    if (this != &rhs)
    {
        delete data;
        data = std::move(rhs.data);
    }
    return *this;
}

template <typename T>
Blob<T> &Blob<T>::operator=(std::initializer_list<T> il) &
{
    delete data;
    data = std::make_shared<std::vector<T>>(il);
    return *this;
}

template <typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty BLob");
    return data->pop_back();
}

template <typename T>
void Blob<T>::pop_back() const
{
    check(0, "pop_back on empty BLob");
    return data->pop_back();
}

template <typename T>
T &Blob<T>::back()
{
    check(0, "back on empty BLob");
    return data->back();
}

template <typename T>
const T &Blob<T>::back() const
{
    check(0, "back on empty BLob");
    return data->back();
}

template <typename T>
T &Blob<T>::front()
{
    check(0, "front on empty BLob");
    return data->front();
}

template <typename T>
const T &Blob<T>::front() const
{
    check(0, "front on empty BLob");
    return data->front();
}

template <typename T>
class BlobPtr
{
public:
    BlobPtr() = default;
    BlobPtr(Blob<T> &blob, size_t sz = 0) : wptr(blob.data), curr(sz) {}
    ~BlobPtr() = default;

    T &operator*() const;
    T *operator->() const { return &this->operator*(); }
    BlobPtr &operator++();
    BlobPtr &operator++(int);
    BlobPtr &operator--();
    BlobPtr &operator--(int);

private:
    std::weak_ptr<std::vector<T>> wptr;
    size_t curr;

private:
    std::shared_ptr<std::vector<T>> check(size_t, const std::string &) const;
};

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound BlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

template <typename T>
T &BlobPtr<T>::operator*() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator++()
{
    check(curr, "increment past end of BlobPtr");
    ++curr;
    return *this;
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator++(int)
{
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator--()
{
    --curr;
    check(curr, "decrement past begin of BlobPtr");
    return *this;
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator--(int)
{
    BlobPtr ret = *this;
    --*this;
    return ret;
}

int main(int argc, char const *argv[])
{
    Blob<int> squares = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < squares.size(); ++i)
    {
        std::cout << "before squares[" << i << "] = " << squares[i] << " ";
        squares[i] = i * i;
        std::cout << "after squares[" << i << "] = " << squares[i] << ((i % (squares.size() / 5) == 1 || i == squares.size() - 1) ? "\n" : "; ");
    }

    std::vector<double> vec = {3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9};
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::setiosflags(std::ios::fixed);
        std::cout << (i == 0 ? "\vec[" : "vec[") << i << "] = " << std::setprecision(1) << vec[i] << (i == vec.size() - 1 ? "\n" : " ");
    }
    Blob<int> copy_vec(vec.cbegin(), vec.cend());
    for (size_t i = 0; i < copy_vec.size(); ++i)
    {
        std::setiosflags(std::ios::fixed);
        std::cout << (i == 0 ? "\ncopy_vec[" : "copy_vec[") << i << "] = " << std::setprecision(1) << copy_vec[i] << (i == copy_vec.size() - 1 ? "\n" : " ");
    }

    std::shared_ptr<std::vector<double>> sptr(std::make_shared<std::vector<double>>(vec));
    std::cout << setiosflags(std::ios::fixed) << std::setprecision(1) << sptr->at(1) << std::endl;

    return 0;
}
