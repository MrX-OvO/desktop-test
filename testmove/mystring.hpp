/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-07-30 23:22:11
 * @LastEditTime : 2021-07-31 17:35:52
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testmove/mystring.hpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#ifndef _MYSTRING_
#define _MYSTRING_

class mystring
{
private:
    static std::size_t dctor; // 默认构造函数调用次数
    static std::size_t ctor;  // 构造函数调用次数
    static std::size_t cctor; // 拷贝构造函数调用次数
    static std::size_t casgn; // 拷贝赋值调用次数
    static std::size_t mctor; // 移动构造函数调用次数
    static std::size_t masgn; // 移动赋值调用次数
    static std::size_t dtor;  // 析够函数调用次数

    char *_data;
    std::size_t _len;

private:
    void _init_data(const char *s);

public:
    mystring();
    mystring(const char *p);
    mystring(const mystring &str);
    mystring(mystring &&str) noexcept; // 参数不能是const
    mystring &operator=(const mystring &str);
    mystring &operator=(mystring &&str) noexcept; // 参数不能是const
    bool operator<(const mystring &str) const;
    bool operator==(const mystring &str) const;
    char *get() const;
    static std::size_t getDCtor();
    static std::size_t getCtor();
    static std::size_t getCCtor();
    static std::size_t getCAsgn();
    static std::size_t getMCtor();
    static std::size_t getMAsgn();
    static std::size_t getDtor();
    virtual ~mystring();
};
#endif // !_MYSTRING_