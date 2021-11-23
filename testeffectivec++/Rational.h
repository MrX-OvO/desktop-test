#ifndef _RATiONAL_H_
#define _RATiONAL_H_

#include <iostream>
#include <utility>

namespace rational_sp
{
    class Rational
    {
    public:
        Rational(int, int);
        Rational(const Rational &);
        Rational(Rational &&) noexcept;
        Rational(std::initializer_list<int>);
        Rational &operator=(const Rational &) &;
        Rational &operator=(Rational &&) &noexcept;
        Rational &operator=(std::initializer_list<int>) &;
        ~Rational();

        //重载复合赋值运算符
        Rational &operator+=(const Rational &) &;
        Rational &operator-=(const Rational &) &;
        Rational &operator*=(const Rational &) &;
        Rational &operator/=(const Rational &) &;

        //重载递增递减运算符
        Rational &operator++() &;
        Rational operator++(int);
        Rational &operator--() &;
        Rational operator--(int);

        // 重载下标运算符
        const int &operator[](int) const; // 下标 => 0：分子，1：分母
        int &operator[](int);             // 下标 => 0：分子，1：分母

        // 重载移位赋值运算符
        Rational &operator<<=(unsigned) &;
        Rational &operator>>=(unsigned) &;

        // 重载位赋值运算符
        Rational &operator&=(const Rational &) &;
        Rational &operator|=(const Rational &) &;
        Rational &operator^=(const Rational &) &;

        // 重载函数调用运算符
        Rational operator()(int, int) const;

        // 重载类型转换运算符
        operator double() const;

        //设置分子、分母
        void setNumerator(int);
        void setDenominator(int);

        //获取分子、分母
        int getNumerator() const;
        int getDenominator() const;

        // 是否同分子、同分母
        bool isTheSameNumerator(const Rational &) const;
        bool isTheSameDenominator(const Rational &) const;

        // 判断是否为正数
        bool isPositive() const;

        // 判断是否为负数
        bool isNegative() const;

        // 判断是否为0
        bool isZero() const;

    private:
        int numerator;   // 分子
        int denominator; // 分母

    private:
        bool invalidRational(int) const; // 检查分母是否为0
        bool invalidIndex(int) const;    // 检查下标运算符是否越界
        void handleND(int &, int &);     // 处理初始化Rational的参数
    };
}

#endif // !_RATHONAL_H_