/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-07-30 21:54:49
 * @LastEditTime : 2021-07-31 18:13:41
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testmove/mystringnomove.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include "myheader.hpp"
#include "mystringnomove.hpp"

// 静态数据初始化为0
std::size_t mystringnomove::dctor = 0;
std::size_t mystringnomove::ctor = 0;
std::size_t mystringnomove::cctor = 0;
std::size_t mystringnomove::casgn = 0;
std::size_t mystringnomove::mctor = 0;
std::size_t mystringnomove::masgn = 0;
std::size_t mystringnomove::dtor = 0;

void mystringnomove::_init_data(const char *s)
{
    _data = new char[_len + 1];
    memcpy(_data, s, _len);
    _data[_len] = '\0';
}
mystringnomove::mystringnomove() : _data(nullptr), _len(0) { ++dctor; };

mystringnomove::mystringnomove(const char *p) : _len(strlen(p))
{
    ++ctor;
    _init_data(p);
}

mystringnomove::mystringnomove(const mystringnomove &str) : _len(str._len)
{
    ++casgn;
    _init_data(str._data);
}

mystringnomove &mystringnomove::operator=(const mystringnomove &str)
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
bool mystringnomove::operator<(const mystringnomove &str) const { return strcmp(_data, str._data) < 0 ? true : false; };

bool mystringnomove::operator==(const mystringnomove &str) const { return strcmp(_data, str._data) == 0 ? true : false; };

char *mystringnomove::get() const { return _data; }

std::size_t mystringnomove::getDCtor() { return dctor; }

std::size_t mystringnomove::getCtor() { return ctor; }

std::size_t mystringnomove::getCCtor() { return cctor; }

std::size_t mystringnomove::getCAsgn() { return casgn; }

std::size_t mystringnomove::getMCtor() { return mctor; }

std::size_t mystringnomove::getMAsgn() { return masgn; }

std::size_t mystringnomove::getDtor() { return dtor; }

mystringnomove::~mystringnomove()
{
    ++dtor;
    if (_data)
        delete _data;
}

namespace std
{
    template <>
    struct hash<mystringnomove>
    {
        size_t operator()(const mystringnomove &str) const noexcept { return hash<string>()(string(str.get())); }
    };
};