#include <iostream>
class UPInt
{
public:
    UPInt(int ival = 0) : i(ival) {}
    ~UPInt() = default;
    UPInt &operator++()
    {
        i += 1;
        return *this;
    }
    UPInt operator++(int)
    {
        UPInt oldValue = *this;
        ++(*this);
        return oldValue;
    }
    int getInt() const { return i; }

private:
    int i;
};

int main(int argc, char const *argv[])
{
    UPInt i;
    std::cout << i.getInt() << std::endl;
    i++ ++;
    std::cout << i.getInt() << std::endl;
    ++++i;
    std::cout << i.getInt() << std::endl;

    return 0;
}
