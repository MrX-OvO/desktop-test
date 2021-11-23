#include <iostream>

class X
{
};
class A : virtual public X
{
};
class B : virtual public X
{
};
class C : public A, public B
{
};

#include <string>

class ZooAnimal
{
public:
    ZooAnimal();
    virtual ~ZooAnimal();
    virtual void rotate();

protected:
    int loc;
    std::string name;
};

class Bear : public ZooAnimal
{
public:
    Bear();
    ~Bear();
    void rotate() override;
    virtual void dance();

protected:
    /*     enum Dances
    {
    };
    Dances dances_known; */
    int cell_block;
};

#include <cassert>

class Point3D
{
private:
    double _x;
    double _y;
    double _z;

public:
    Point3D(double x = 0.0, double y = 0.0, double z = 0.0) : _x(x), _y(y), _z(z) {}
    Point3D(const Point3D &p) : _x(p._x), _y(p._y), _z(p._z) {}
    Point3D(Point3D &&p) noexcept : _x(std::move(p._x)), _y(std::move(p._y)), _z(std::move(p._z)) {}
    Point3D &operator=(const Point3D &rhs) &
    {
        if (this != &rhs)
        {
            _x = rhs._x;
            _y = rhs._y;
            _z = rhs._z;
        }
        return *this;
    }
    Point3D &operator=(Point3D &&rhs) &noexcept
    {
        if (this != &rhs)
        {
            _x = std::move(rhs._x);
            _y = std::move(rhs._y);
            _z = std::move(rhs._z);
        }
        return *this;
    }
    ~Point3D() = default;
    const char *access_order_zy()
    {
        assert(&_z != &_y);
        return &_z < &_y ? "_z occurs first" : "_y occurs first";
    }
};

class O
{
};
class P : public O
{
};
class Q : public P
{
};

O o;
O fooO()
{
    O local;
    O *po = new O;
    *po = local;
    delete po;
    return local;
}

int main(int argc, char const *argv[])
{
    std::cout << "size of class X: " << sizeof(X) << std::endl; // 1
    std::cout << "size of class A: " << sizeof(A) << std::endl; // 8
    std::cout << "size of class B: " << sizeof(B) << std::endl; // 8
    std::cout << "size of class C: " << sizeof(C) << std::endl; // 16

    std::cout << "size of class ZooAnimal: " << sizeof(ZooAnimal) << std::endl; // 16
    std::cout << "size of class Bear: " << sizeof(Bear) << std::endl;           // 16

    Point3D point3d;
    std::cout << point3d.access_order_zy() << std::endl;

    Q q;
    P p;
    O *o1 = &q, *o2 = &q;
    auto m = *o1;

    return 0;
}
