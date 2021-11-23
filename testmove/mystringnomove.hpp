/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-07-30 23:30:42
 * @LastEditTime : 2021-07-31 18:11:00
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testmove/mystringnomove.hpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#ifndef _MYSTRINGNOMOVE_
#define _MYSTRINGNOMOVE_

class mystringnomove
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
    mystringnomove();
    mystringnomove(const char *p);
    mystringnomove(const mystringnomove &str);
    mystringnomove &operator=(const mystringnomove &str);
    bool operator<(const mystringnomove &str) const;
    bool operator==(const mystringnomove &str) const;
    char *get() const;
    static std::size_t getDCtor();
    static std::size_t getCtor();
    static std::size_t getCCtor();
    static std::size_t getCAsgn();
    static std::size_t getMCtor();
    static std::size_t getMAsgn();
    static std::size_t getDtor();
    virtual ~mystringnomove();
};
#endif // !_MYSTRINGNOMOVE_
