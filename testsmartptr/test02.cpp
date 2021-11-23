/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-06 14:45:44
 * @LastEditTime : 2021-08-06 15:16:15
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testsmartptr/test02.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <memory>
#include <vector>
#include <string>

class StrBlob
{
public:
    using size_type = std::vector<std::string>::size_type;
    StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
    StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}
    ~StrBlob() {}
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string &str) { data->push_back(str); }
    void pop_back();
    std::string &front();
    std::string &front() const;
    std::string &back();
    std::string &back() const;

private:
    std::shared_ptr<std::vector<std::string>> data;

private:
    void check(size_type i, const std::string &msg) const;
};

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

std::string &StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string &StrBlob::back()
{
    check(0, "front on empty StrBlob");
    return data->back();
}

std::string &StrBlob::back() const
{
    check(0, "front on empty StrBlob");
    return data->back();
}

int main(int argc, char const *argv[])
{
    StrBlob b1;
    {
        StrBlob b2({"a", "an", "the"});
        b1 = b2;
        b2.push_back("about");
        std::cout << "b2.size() = " << b2.size() << std::endl;
    }
    std::cout << "b1.size() = " << b1.size() << std::endl;

    return 0;
}
