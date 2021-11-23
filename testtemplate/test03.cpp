#include <iostream>
#include <memory>

class DebugDelete
{
public:
    DebugDelete(std::ostream &s = std::cerr) : os(s) {}

    template <typename T>
    void operator()(T *p) const;

private:
    std::ostream &os;
};

template <typename T>
void DebugDelete::operator()(T *p) const
{
    os << "deleting unique_ptr...\n";
    delete p;
    p = nullptr;
}

int main(int argc, char const *argv[])
{
    int *p = new int;
    DebugDelete d;
    d(p);

    DebugDelete()(new double);
    std::unique_ptr<int, DebugDelete> uptr(new int, DebugDelete());

    return 0;
}
