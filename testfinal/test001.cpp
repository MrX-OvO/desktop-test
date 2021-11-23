#include <iostream>
#include <utility>
#include <typeinfo>

class Base
{
    friend bool operator==(const Base &, const Base &);

public:
    Base() { std::cout << "call default constructor of Base...\n"; }
    Base(int i) : ival(i) { std::cout << "call constructor of Base...\n"; }
    Base(const Base &base) : ival(base.ival) { std::cout << "call copy constructor of Base...\n"; }
    Base(Base &&base) noexcept : ival(base.ival)
    {
        base.ival = 0;
        std::cout << "call move constructor of Base...\n";
    }
    Base &operator=(const Base &rhs)
    {
        if (this != &rhs)
            ival = rhs.ival;
        return *this;
    }
    Base &operator=(Base &&rhs) noexcept
    {
        if (this != &rhs)
        {
            ival = rhs.ival;
            rhs.ival = 0;
        }
        return *this;
    }
    virtual ~Base() { std::cout << "call destructor of Base...\n"; }
    int getIval() { return ival; }
    const int getIval() const { return ival; }
    void setIval(int i) { ival = i; }

protected:
    virtual bool equal(const Base &rhs) const { return ival == rhs.ival; }

private:
    int ival;
};

bool operator==(const Base &lhs, const Base &rhs) { return typeid(lhs) == typeid(rhs) && lhs.equal(rhs); }

class Derived : public Base
{
public:
    Derived() { std::cout << "call default constructor of Derived...\n"; }
    Derived(double d, int i = 0) : dval(d), Base(i) { std::cout << "call constructor of Derived...\n"; }
    Derived(const Derived &derived) : dval(derived.dval), Base(derived) { std::cout << "call copy constructor of Derived...\n"; }
    Derived(Derived &&derived) noexcept : dval(derived.dval), Base(derived)
    {
        derived.dval = 0.0;
        std::cout << "call move constructor of Derived...\n";
    }
    Derived &operator=(const Derived &rhs)
    {
        if (this != &rhs)
        {
            this->setIval(rhs.getIval());
            dval = rhs.dval;
        }
        return *this;
    }
    Derived &operator=(Derived &&rhs) noexcept
    {
        if (this != &rhs)
        {
            this->setIval(rhs.getIval());
            dval = rhs.dval;
            rhs.setIval(0);
            rhs.dval = 0.0;
        }
        return *this;
    }
    ~Derived() { std::cout << "call destructor of Derived...\n"; }
    int getDval() { return dval; }
    const int getDval() const { return dval; }
    void setDval(double d) { dval = d; }

protected:
    bool equal(const Base &rhs) const override
    {
        auto r = dynamic_cast<const Derived &>(rhs);
        return dval == r.dval;
    }

private:
    double dval;
};

int main(int argc, char const *argv[])
{
    Base b1, b2, b3(2);
    Derived d1(2), d2(2, 0), d3(5, 4);
    std::cout << "typeid(b1).name() = " << typeid(b1).name() << ", typeid(b2).name() = " << typeid(b2).name() << std::endl;
    std::cout << (b1 == b2 ? "b1 == b2\n" : "b1 != b2\n");
    std::cout << "typeid(d1).name() = " << typeid(d1).name()
              << ", typeid(d2).name() = " << typeid(d2).name()
              << ", typeid(d3).name() = " << typeid(d3).name()
              << std::endl;
    std::cout << (d1 == d2 ? "d1 == d2\n" : "d1 != d2\n");
    std::cout << (b3 == d1 ? "b3 == d1\n" : "b3 != d1\n");

    return 0;
}
