class Base
{
private:
    int i;

protected:
    int j;

public:
    int k;
};

class Derived : protected Base
{

    //using Base::i;
protected:
    using Base::j;

public:
    using Base::k;
};

int main(int argc, char const *argv[])
{
    Derived d;
    //d.i;
    d.k;
    //d.j;

    return 0;
}
