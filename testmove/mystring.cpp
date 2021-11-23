/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-07-30 21:54:49
 * @LastEditTime : 2021-07-31 18:25:39
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testmove/mystring.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include "myheader.hpp"
#include "mystring.hpp"

// 静态数据初始化为0
std::size_t mystring::dctor = 0;
std::size_t mystring::ctor = 0;
std::size_t mystring::cctor = 0;
std::size_t mystring::casgn = 0;
std::size_t mystring::mctor = 0;
std::size_t mystring::masgn = 0;
std::size_t mystring::dtor = 0;

void mystring::_init_data(const char *s)
{
    _data = new char[_len + 1];
    memcpy(_data, s, _len);
    _data[_len] = '\0';
}

mystring::mystring() : _data(nullptr), _len(0) { ++dctor; };

mystring::mystring(const char *p) : _len(strlen(p))
{
    ++ctor;
    _init_data(p);
}

mystring::mystring(const mystring &str) : _len(str._len)
{
    ++casgn;
    _init_data(str._data);
}

mystring::mystring(mystring &&str) noexcept
    : _len(str._len), _data(str._data)
{
    ++mctor;
    str._len = 0;
    str._data = nullptr;
}

mystring &mystring::operator=(const mystring &str)
{
    ++casgn;
    if (this != &str)
    {
        if (_data)
            delete _data;
        _len = str._len;
        _init_data(str._data);
    }
    return *this;
}

mystring &mystring::operator=(mystring &&str) noexcept
{
    ++masgn;
    if (this != &str)
    {
        if (_data)
            delete _data;
        _len = str._len;
        _data = str._data;
        str._len = 0;
        str._data = nullptr;
    }
    return *this;
}
bool mystring::operator<(const mystring &str) const { return strcmp(_data, str._data) < 0 ? true : false; };

bool mystring::operator==(const mystring &str) const { return strcmp(_data, str._data) == 0 ? true : false; };

char *mystring::get() const { return _data; }

std::size_t mystring::getDCtor() { return dctor; }

std::size_t mystring::getCtor() { return ctor; }

std::size_t mystring::getCCtor() { return cctor; }

std::size_t mystring::getCAsgn() { return casgn; }

std::size_t mystring::getMCtor() { return mctor; }

std::size_t mystring::getMAsgn() { return masgn; }

std::size_t mystring::getDtor() { return dtor; }

mystring::~mystring()
{
    ++dtor;
    if (_data)
        delete _data;
}

namespace std
{
    template <>
    struct hash<mystring>
    {
        size_t operator()(const mystring &str) const noexcept { return hash<string>()(string(str.get())); }
    };
};