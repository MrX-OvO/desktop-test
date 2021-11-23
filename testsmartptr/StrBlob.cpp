/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 15:30:06
 * @LastEditTime : 2021-08-08 16:07:57
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testsmartptr/StrBlob.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "StrBlob.h"

StrBlob::StrBlob(const StrBlob &strBlob)
{
    auto newdata = *strBlob.data;
    // data = std::make_sharedstd::vector<std::string>(newdata);
}

StrBlob::StrBlob(StrBlob &&strBlob) noexcept
{
}

StrBlob &StrBlob::operator=(const StrBlob &) &
{
}

StrBlob &StrBlob::operator=(StrBlob &&) &noexcept
{
}

StrBlob &StrBlob::operator=(std::initializer_list<std::string>) &
{
}

void StrBlob::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

std::string &StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

const std::string &StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string &StrBlob::back()
{
    check(0, "front on empty StrBlob");
    return data->back();
}

const std::string &StrBlob::back() const
{
    check(0, "front on empty StrBlob");
    return data->back();
}
