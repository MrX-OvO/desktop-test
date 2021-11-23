/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 15:39:38
 * @LastEditTime : 2021-08-08 15:54:52
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testsmartptr/StrBlolPtr.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "StrBlobPtr.h"

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

std::string &StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr &StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}
