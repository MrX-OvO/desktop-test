/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-09 17:31:01
 * @LastEditTime : 2021-08-09 23:21:08
 * @LastEditors  : MrX-OvO
 * @Description  : implement a string vector
 * @FilePath     : /test/testclassdesign/test06.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <string>
#include <memory>
#include <utility>

class StrVec
{
    using elemtype = std::string *;

private:
    static std::allocator<std::string> alloc; // 分配元素
    elemtype elements;                        // 指向数组首元素的指针
    elemtype first_free;                      // 指向数组第一个空闲元素的指针
    elemtype cap;                             // 指向数组尾后位置的指针

private:
    void check_n_alloc();                                                                           // 检查是否有足够空间容纳新元素
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *); // 分配内存并拷贝一个给定范围中的元素
    void free();                                                                                    // 销毁元素并释放内存
    void reallocate();                                                                              // 获得更多内存并拷贝已有元素

public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const std::string &);
    StrVec(const StrVec &);
    StrVec(std::initializer_list<std::string>);
    StrVec(StrVec &&) noexcept;
    ~StrVec() { free(); }
    StrVec &operator=(const StrVec &);
    StrVec &operator=(std::initializer_list<std::string>);
    StrVec &operator=(StrVec &&) noexcept;
    std::string &operator[](size_t n) { return elements[n]; }
    const std::string &operator[](size_t n) const { return elements[n]; }
    void push_back(const std::string &);
    void push_back(std::string &&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return cap; }
};

std::allocator<std::string> StrVec::alloc;

void StrVec::check_n_alloc()
{
    if (size() == capacity())
        reallocate();
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    if (elements)
    {
        for (auto p = first_free; p != elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

void StrVec::reallocate()
{
    auto newcanpacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcanpacity);
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(begin()), first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newcanpacity;
}

StrVec::StrVec(const std::string &str)
{
    auto b = &*str.begin();
    auto bstr = std::string(b);
    elements = static_cast<elemtype>(&bstr);
    auto f = &*str.end();
    auto fstr = std::string(b);
    first_free = static_cast<elemtype>(&fstr);
    cap = static_cast<elemtype>(&fstr);
}

StrVec::StrVec(std::initializer_list<std::string> il)
{
    elements = const_cast<elemtype>(il.begin());
    first_free = const_cast<elemtype>(il.end());
    cap = const_cast<elemtype>(il.end());
}

StrVec::StrVec(const StrVec &strVec)
{
    auto newdata = alloc_n_copy(strVec.begin(), strVec.end());
    elements = newdata.first;
    first_free = newdata.second;
    cap = newdata.second;
}

StrVec::StrVec(StrVec &&strVec) noexcept
    : elements(strVec.elements), first_free(strVec.first_free), cap(strVec.cap)
{
    strVec.elements = nullptr;
    strVec.first_free = nullptr;
    strVec.cap = nullptr;
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
    if (this != &rhs)
    {
        auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
        free();
        elements = newdata.first;
        first_free = newdata.second;
        cap = newdata.second;
    }
    return *this;
}

StrVec &StrVec::operator=(std::initializer_list<std::string> il)
{
    auto newdata = alloc_n_copy(il.begin(), il.end());
    free();
    elements = newdata.first;
    first_free = newdata.second;
    cap = newdata.second;
    return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
    if (this != &rhs)
    {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = nullptr;
        rhs.first_free = nullptr;
        rhs.cap = nullptr;
    }
    return *this;
}

void StrVec::push_back(const std::string &s)
{
    check_n_alloc();
    alloc.construct(first_free++, s);
}

void StrVec::push_back(std::string &&s)
{
    check_n_alloc();
    alloc.construct(first_free++, std::move(s));
}

std::ostream &operator<<(std::ostream &os, const StrVec &strVec)
{
    for (auto iter = strVec.begin(); iter != strVec.end();)
        os << *iter++;
    return os;
}

int main(int argc, char const *argv[])
{
    std::string s("StrVec");
    StrVec strVec;
    strVec.push_back(s);
    std::cout << strVec << std::endl;

    StrVec strVec1 = {"initializer_list"};
    std::cout << strVec1 << std::endl;

    return 0;
}
