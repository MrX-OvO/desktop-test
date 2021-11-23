/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-07-30 16:42:48
 * @LastEditTime : 2021-08-03 15:53:36
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/complex.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <vector>

template <typename T>
class complex
{
private:
    T real;
    T image;

public:
    explicit complex() : real(T()), image(T()) {}
    explicit complex(const T &r, const T &i) : real(r), image(i) {}
    complex(const complex<T> &c);
    complex &operator=(const complex<T> &c);
    T getReal() const { return real; }
    T getImage() const { return image; }
    void setReal(const T &r) { this->real = r; }
    void setImage(const T &i) { this->image = i; }
    complex operator+(const complex<T> &c);
    complex &operator+=(const complex<T> &c);
    complex operator-(const complex<T> &c);
    complex &operator-=(const complex<T> &c);
    complex operator*(const complex<T> &c);
    complex &operator*=(const complex<T> &c);
    complex<float> operator/(const complex<T> &c);
    complex<float> &operator/=(const complex<T> &c);
    std::ostream &operator<<(std::ostream &out);
    ~complex(){};
};

template <typename T>
complex<T>::complex(const complex<T> &c)
{
    if (this != &c)
    {
        this->real = c.real;
        this->image = c.image;
    }
}

template <typename T>
complex<T> &complex<T>::operator=(const complex<T> &c)
{
    if (this != &c)
    {
        this->real = c.real;
        this->image = c.image;
    }
    return *this;
}

template <typename T>
complex<T> complex<T>::operator+(const complex<T> &c) { return complex(this->real + c.real, this->image + c.image); }

template <typename T>
complex<T> &complex<T>::operator+=(const complex<T> &c)
{
    this->real += c.real;
    this->image += c.image;
    return *this;
}
template <typename T>
complex<T> complex<T>::operator-(const complex<T> &c) { return complex(this->real - c.real, this->image - c.image); }

template <typename T>
complex<T> &complex<T>::operator-=(const complex<T> &c)
{
    this->real -= c.real;
    this->image -= c.image;
    return *this;
}

template <typename T>
complex<T> complex<T>::operator*(const complex<T> &c)
{
    T real, image;
    real = this->real * c.real - this->image * c.image;
    image = this->real * c.image + this->image * c.real;
    return complex(real, image);
}

template <typename T>
complex<T> &complex<T>::operator*=(const complex<T> &c)
{
    this->real = this->real * c.real - this->image * c.image;
    this->image = this->real * c.image + this->image * c.real;
    return *this;
}

template <typename T>
complex<float> complex<T>::operator/(const complex<T> &c)
{
    float real, image;
    real = static_cast<float>(this->real * c.real + this->image * c.image) / (c.real * c.real + c.image * c.image);
    image = static_cast<float>(this->image * c.real - this->real * c.image) / (c.real * c.real + c.image * c.image);
    return complex<float>(real, image);
}

template <typename T>
complex<float> &complex<T>::operator/=(const complex<T> &c)
{
    this->real = static_cast<float>(this->real * c.real + this->image * c.image) / (c.real * c.real + c.image * c.image);
    this->image = static_cast<float>(this->image * c.real - this->real * c.image) / (c.real * c.real + c.image * c.image);

    return *(static_cast<complex<float> *>(this));
}

template <typename T>
std::ostream &complex<T>::operator<<(std::ostream &out)
{
    out << this->getReal() << (this->getImage() >= 0 ? "+" : "") << this->getImage() << "i\n";
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const complex<T> &c)
{
    out << "(" << c.getReal() << "," << c.getImage() << ")\n";
    return out;
}

int main(int argc, const char **argv)
{
    complex<int> c1;
    complex<int> c2(1, -1);
    complex<int> c3(1, 1);
    complex<float> c4(1.0, -1.0);
    complex<float> c5(1.0, 1.0);
    std::cout << "c1 =" << c1 << "c2 = " << c2 << "c3 = " << c3;

    complex<int> c = c2 + c3;
    std::cout << "c = c2 + c3 = " << c;
    c += c2;
    std::cout << "c += c2 = " << c;

    c = c2 - c3;
    std::cout << "c = c2 - c3 = " << c;
    c -= c2;
    std::cout << "c -= c2 = " << c;

    c = c2 * c3;
    std::cout << "c = c2 * c3 = " << c;
    c *= c2;
    std::cout << "c *= c2 = " << c;

    complex<float> c_ = c4 / c5;
    std::cout << "c_ = c4 / c5 = " << c_;
    c_ /= c4;
    std::cout << "c_ /= c4 = " << c_;

    return 0;
}
