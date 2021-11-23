#include "Rational.h"

namespace rational_sp
{
    // 最大公约数、最小公倍数
    int gcd(int i, int j)
    {
        if (i < 0)
            i = -i;
        if (j < 0)
            j = -j;
        while (i != j)
        {
            if (i > j)
                i -= j;
            else
                j -= i;
        }
        return i;
    }

    int lcm(int i, int j)
    {
        return i * j * gcd(i, j);
    }

    bool Rational::invalidRational(int i) const { return i == 0; } // 检查分母是否为0

    bool Rational::invalidIndex(int i) const { return i > 1 || i < 0; } // 检查下标运算符是否越界

    void Rational::handleND(int &n, int &d) // 处理初始化Rational的参数
    {
        int temp_n = n, temp_d = d;
        if (temp_n < 0)
            temp_n = -temp_n;
        if (temp_d < 0)
            temp_d = -temp_d;
        int cd = gcd(temp_n, temp_d);
        if (cd > 1)
        {
            n /= cd;
            d /= cd;
        }
        if (n < 0 && d < 0)
        {
            n = -n;
            d = -d;
        }
    }

    Rational::Rational(int n = 0, int d = 1)
    {
        if (invalidRational(d))
        {
            numerator = 0;
            denominator = 1;
            std::cerr << "\nConstructing rational invalidly, for denominator is 0...\n";
        }
        else
        {
            if (n != 0)
                handleND(n, d);
            numerator = n;
            denominator = d;
        }
    }

    Rational::Rational(const Rational &r) : numerator(r.numerator), denominator(r.denominator) {}

    Rational::Rational(Rational &&r) noexcept : numerator(r.numerator), denominator(r.denominator)
    {
        r.numerator = 0;
        r.denominator = 1;
    }

    Rational::Rational(std::initializer_list<int> il)
    {
        if (il.size() == 0)
        {
            numerator = 0;
            denominator = 1;
        }
        else if (il.size() == 1)
        {
            numerator = *il.begin();
            denominator = 1;
        }
        else if (il.size() == 2)
        {
            auto iter = il.begin();
            auto n = *iter;
            auto d = *++iter;
            handleND(n, d);
            numerator = n;
            denominator = d;
        }
        else
        {
            auto iter = il.begin();
            auto n = *iter;
            auto d = *++iter;
            handleND(n, d);
            numerator = n;
            denominator = d;
            std::cout << "\nToo many elements in initializer_list, first and second element used...\n";
        }
    }

    Rational &Rational::operator=(const Rational &rhs) &
    {
        if (this != &rhs)
        {
            numerator = rhs.numerator;
            denominator = rhs.denominator;
        }
        return *this;
    }

    Rational &Rational::operator=(Rational &&rhs) &noexcept
    {
        if (this != &rhs)
        {
            numerator = rhs.numerator;
            denominator = rhs.denominator;
            rhs.numerator = 0;
            rhs.denominator = 1;
        }
        return *this;
    }

    Rational &Rational::operator=(std::initializer_list<int> il) &
    {
        if (il.size() == 0)
        {
            numerator = 0;
            denominator = 1;
        }
        else if (il.size() == 1)
        {
            numerator = *il.begin();
            denominator = 1;
        }
        else if (il.size() == 2)
        {
            auto iter = il.begin();
            numerator = *iter;
            ++iter;
            denominator = *iter;
        }
        else
        {
            auto iter = il.begin();
            numerator = *iter;
            ++iter;
            denominator = *iter;
            std::cout << "\nToo many elements in initializer_list, first and second element used...\n";
        }
        return *this;
    }

    Rational::~Rational() = default;

    //重载复合赋值运算符 (用复合赋值运算符实现算术运算符)
    Rational &Rational::operator+=(const Rational &rhs) &
    {
        if (rhs.isZero())
            return *this;
        if (isTheSameDenominator(rhs))
        {
            int n = getNumerator() + rhs.getNumerator();
            setNumerator(n);
        }
        else
        {
            int d = lcm(getDenominator(), rhs.getDenominator());
            int n = d / getDenominator() * getNumerator() + d / rhs.getDenominator() * rhs.getNumerator();
            setNumerator(n);
            setDenominator(d);
        }
        return *this;
    }

    Rational &Rational::operator-=(const Rational &rhs) &
    {
        if (rhs.isZero())
            return *this;
        if (isTheSameDenominator(rhs))
        {
            int n = getNumerator() - rhs.getNumerator();
            setNumerator(n);
        }
        else
        {
            int d = lcm(getDenominator(), rhs.getDenominator());
            int n = d / getDenominator() * getNumerator() - d / rhs.getDenominator() * rhs.getNumerator();
            setNumerator(n);
            setDenominator(d);
        }
        return *this;
    }

    Rational &Rational::operator*=(const Rational &rhs) &
    {
        int n = getNumerator() * rhs.getNumerator();
        int d = getDenominator() * rhs.getDenominator();
        handleND(n, d);
        setNumerator(n);
        setDenominator(d);
        return *this;
    }

    Rational &Rational::operator/=(const Rational &rhs) &
    {
        int n = getNumerator() * rhs.getDenominator();
        int d = getDenominator() * rhs.getNumerator();
        handleND(n, d);
        setNumerator(n);
        setDenominator(d);
        return *this;
    }

    //重载递增递减运算符 （用前置版本实现后置版本)
    Rational &Rational::operator++() &
    {
        numerator += denominator;
        return *this;
    }

    Rational Rational::operator++(int)
    {
        Rational ret = *this;
        ++*this;
        return ret;
    }

    Rational &Rational::operator--() &
    {
        numerator -= denominator;
        return *this;
    }

    Rational Rational::operator--(int)
    {
        Rational ret = *this;
        --*this;
        return ret;
    }

    // 重载下标运算符
    const int &Rational::operator[](int i) const
    {
        if (invalidIndex(i))
        {
            std::cout << "\nInvalid index, return numerator...\n";
            return numerator;
        }
        else if (i == 0)
            return numerator;
        else
            return denominator;
    }

    int &Rational::operator[](int i) { return const_cast<int &>(static_cast<const Rational &>(*this)[i]); }

    // 重载移位赋值运算符
    Rational &Rational::operator<<=(unsigned n) &
    {
        numerator <<= n;
        handleND(numerator, denominator);
        return *this;
    }

    Rational &Rational::operator>>=(unsigned n) &
    {
        denominator <<= n;
        handleND(numerator, denominator);
        return *this;
    }

    // 重载位赋值运算符
    Rational &Rational::operator&=(const Rational &rhs) &
    {
        if (rhs.isZero())
        {
            numerator = 0;
            denominator = 1;
        }
        if (isTheSameDenominator(rhs))
        {
            int n = getNumerator() & rhs.getNumerator();
            setNumerator(n);
        }
        else
        {
            int d = lcm(getDenominator(), rhs.getDenominator());
            int nl = d / getDenominator() * getNumerator();
            int nr = d / rhs.getDenominator() * rhs.getNumerator();
            int n = nl & nr;
            setNumerator(n);
            setDenominator(d);
        }
        return *this;
    }

    Rational &Rational::operator|=(const Rational &rhs) &
    {
        if (rhs.isZero())
            return *this;
        if (isTheSameDenominator(rhs))
        {
            int n = getNumerator() | rhs.getNumerator();
            setNumerator(n);
        }
        else
        {
            int d = lcm(getDenominator(), rhs.getDenominator());
            int nl = d / getDenominator() * getNumerator();
            int nr = d / rhs.getDenominator() * rhs.getNumerator();
            int n = nl | nr;
            setNumerator(n);
            setDenominator(d);
        }
        return *this;
    }

    Rational &Rational::operator^=(const Rational &rhs) &
    {
        if (*this == rhs)
        {
            numerator = 0;
            denominator = 1;
        }
        else
        {
            numerator = 1;
            denominator = 1;
        }
        return *this;
    }

    // 重载函数调用运算符
    Rational Rational::operator()(int n = 0, int d = 1) const { return Rational(n, d); }

    // 重载类型转换运算符
    Rational::operator double() const { return static_cast<double>(numerator) / denominator; }

    //设置分子、分母
    void Rational::setNumerator(int n) { numerator = n; }

    void Rational::setDenominator(int d)
    {
        if (invalidRational(d))
            std::cerr << "\nSetting denominator invalidly, for denominator is 0...\n";
        else
            denominator = d;
    }

    //获取分子、分母
    int Rational::getNumerator() const { return numerator; }

    int Rational::getDenominator() const { return denominator; }

    // 是否同分子、同分母
    bool Rational::isTheSameNumerator(const Rational &r) const { return numerator == r.numerator; }

    bool Rational::isTheSameDenominator(const Rational &r) const { return denominator == r.denominator; }

    // 判断是否为正数
    bool Rational::isPositive() const { return numerator * denominator > 0; }

    // 判断是否为负数
    bool Rational::isNegative() const { return numerator * denominator < 0; }

    // 判断是否为0
    bool Rational::isZero() const { return numerator == 0; }

    // 重载算术运算符
    Rational operator+(const Rational &r) { return Rational(r); }

    Rational operator-(const Rational &r)
    {
        if (r.getDenominator() > 0)
            return Rational(-r.getNumerator(), r.getDenominator());
        else
            return Rational(r.getNumerator(), -r.getDenominator());
    }

    Rational operator+(const Rational &lhs, const Rational &rhs)
    {
        Rational ret = lhs;
        ret += rhs;
        return ret;
    }

    Rational operator-(const Rational &lhs, const Rational &rhs)
    {
        Rational ret = lhs;
        ret -= rhs;
        return ret;
    }

    Rational operator*(const Rational &lhs, const Rational &rhs)
    {
        Rational ret = lhs;
        ret *= rhs;
        return ret;
    }

    Rational operator/(const Rational &lhs, const Rational &rhs)
    {
        Rational ret = lhs;
        ret /= rhs;
        return ret;
    }

    // 重载关系运算符
    bool operator<(const Rational &lhs, const Rational &rhs) { return (lhs - rhs).isNegative(); }

    bool operator>(const Rational &lhs, const Rational &rhs) { return (lhs - rhs).isPositive(); }

    bool operator<=(const Rational &lhs, const Rational &rhs) { return !(lhs > rhs); }

    bool operator>=(const Rational &lhs, const Rational &rhs) { return !(lhs < rhs); }

    bool operator==(const Rational &lhs, const Rational &rhs) { return (lhs - rhs).isZero(); }

    bool operator!=(const Rational &lhs, const Rational &rhs) { return !(lhs == rhs); }

    // 重载输入输出运算符
    std::istream &operator>>(std::istream &is, Rational &r)
    {
        int n, d;
        is >> n >> d;
        if (is)
        {
            r.setNumerator(n);
            r.setDenominator(d);
        }
        else
            r = Rational();
        return is;
    }

    std::ostream &operator<<(std::ostream &os, const Rational &r)
    {
        os << "rational: " << r.getNumerator() << "/" << r.getDenominator();
        return os;
    }

    // 重载移位运算符
    Rational operator<<(Rational r, unsigned n)
    {
        r <<= n;
        return r;
    }
    Rational operator>>(Rational r, unsigned n)
    {
        r >>= n;
        return r;
    }

    // 重载逻辑运算符
    bool operator&&(const Rational &lhs, const Rational &rhs)
    {
        if (lhs.isZero() || rhs.isZero())
            return false;
        else
            return true;
    }

    bool operator||(const Rational &lhs, const Rational &rhs)
    {
        if (lhs.isZero() && rhs.isZero())
            return false;
        else
            return true;
    }

    bool operator!(const Rational &r)
    {
        if (r.isZero())
            return true;
        else
            return false;
    }

    // 重载位运算符
    Rational operator&(const Rational &lhs, const Rational &rhs)
    {
        Rational ret = lhs;
        ret &= rhs;
        return ret;
    }

    Rational operator|(const Rational &lhs, const Rational &rhs)
    {
        Rational ret = lhs;
        ret |= rhs;
        return ret;
    }

    Rational operator^(const Rational &lhs, const Rational &rhs)
    {
        Rational ret = lhs;
        ret ^= rhs;
        return ret;
    }

    Rational operator~(const Rational &r)
    {
        Rational ret = r;
        int n = ~ret.getNumerator();
        int d = ret.getDenominator();
        int cd = gcd(n, d);
        if (cd > 1)
        {
            n /= cd;
            d /= cd;
        }
        ret.setNumerator(n);
        ret.setDenominator(d);
        return ret;
    }
}
