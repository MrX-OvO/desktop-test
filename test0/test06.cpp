#include <iostream>
#include <map>
#include <memory>
#include <typeinfo>
class A
{
public:
    static void f1(unsigned i)
    {
        static std::shared_ptr<myMap> ret(f(i));
        std::cout << typeid(ret).name();
        for (auto iter = ret->cbegin(); iter != ret->cend(); ++iter)
            std::cout << " {" << iter->first << ", " << iter->second << "}";
    }

private:
    using myMap = std::map<int, int>;
    static myMap *f(unsigned i)
    {
        myMap *ret = new myMap;
        (*ret)[i] = i;
        return ret;
    }
};

int main(int argc, char const *argv[])
{

    for (size_t i = 0, j = i + 1; i < 9 && j < 10; ++i, ++j)
    {
        std::cout << "i = " << i << ", A::f1(" << i << ") ";
        A::f1(i);
        std::cout << ", j = " << j << ", A::f1(" << j << ") ";
        A::f1(j);
        std::cout << std::endl;
    }
    A::f1(15);

    return 0;
}
