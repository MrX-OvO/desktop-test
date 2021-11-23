#include <iostream>
#include <vector>
#include <string>

struct Base1
{
    void print(int i) const { std::cout << "call void Base1::print(int i) const, i = " << i << std::endl; }

protected:
    int ival;
    double dval;
    char cval;

private:
    int *id;
};

struct Base2
{
    void print(double d) const { std::cout << "call void Base2::print(double d) const, d = " << std::showpoint << d << std::noshowpoint << std::endl; }

protected:
    double fval;

private:
    double dval;
};

struct Derived : public Base1
{
    void print(const std::string &s) const { std::cout << "call void Derived::print(const std::string &s) const, s = " << s << std::endl; }

protected:
    std::string sval;
    double dval;
};

struct MI : public Derived, public Base2
{
    void print(const std::vector<double> &dvec)
    {
        std::cout << "call void MI::print(const std::vector<double> &dvec), dvec:\n";
        for (auto iter = dvec.begin(); iter != dvec.end();)
            std::cout << *iter++ << (iter == dvec.end() ? "\n" : ", ");
    }

    void foo(double);

protected:
    int *ival;
    std::vector<double> dvec;
};

int ival;
double dval;
void MI::foo(double cval)
{
    int dval;
    dval = Base1::dval + Derived::dval;
    Base2::fval = *--dvec.end();
    Derived::sval[0] = Base1::cval;
}

int main(int argc, char const *argv[])
{
    MI mi;
    mi.Base1::print(42);
    mi.Derived::print("42");
    mi.Base2::print(42);
    mi.foo(0);

    return 0;
}
