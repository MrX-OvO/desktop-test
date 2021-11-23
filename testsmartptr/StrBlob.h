/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 15:29:52
 * @LastEditTime : 2021-08-09 14:22:32
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testsmartptr/StrBlob.h
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include "StrBlobPtr.h"
#ifndef _STRBLOB_H_
#define _STRBLOB_H_
class StrBlob
{
    using size_type = std::vector<std::string>::size_type;
    friend class StrBlobPtr;

public:
    StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
    StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}
    StrBlob(const StrBlob &);
    StrBlob(StrBlob &&) noexcept;
    StrBlob &operator=(const StrBlob &) &;
    StrBlob &operator=(StrBlob &&) &noexcept;
    StrBlob &operator=(std::initializer_list<std::string>) &;
    ~StrBlob() = default;
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string &str) { data->push_back(str); }
    void pop_back();
    std::string &front();
    const std::string &front() const;
    std::string &back();
    const std::string &back() const;
    StrBlobPtr begin() { return StrBlobPtr(*this); }
    StrBlobPtr end() { return StrBlobPtr(*this, data->size()); }

private:
    std::shared_ptr<std::vector<std::string>> data;

private:
    void check(size_type i, const std::string &msg) const;
};
#endif // !_STRBLOB_H_