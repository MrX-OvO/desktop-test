/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 15:32:18
 * @LastEditTime : 2021-08-08 16:14:06
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testsmartptr/StrBlobPtr.h
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#ifndef _STRBLOBPTR_H_
#define _STRBLOBPTR_H_
#include "StrBlob.h"
class StrBlobPtr
{
public:
    StrBlobPtr() : curr(0){};
    StrBlobPtr(StrBlob &strblob, size_t sz = 0) : wptr(strblob.data), curr(sz){};
    ~StrBlobPtr() = default;
    std::string &deref() const;
    StrBlobPtr &incr();

private:
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr;

private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t i, const std::string &msg) const;
};
#endif // !_STRBLOBPTR_H_
