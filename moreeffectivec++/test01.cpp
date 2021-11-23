#include <iostream>

struct Base
{
    int ival;
    Base() = delete;
    Base(int i) : ival(i) {}
    ~Base() = default;
};

int main(int argc, char const *argv[])
{
    // Base baseArr[10]; // 无法引用"Base"的默认构造函数 -- 它是已删除的函数
    // Base *pbaseArr = new Base[10]; // 无法引用"Base"的默认构造函数 -- 它是已删除的函数
    Base baseArr[] = {Base(0), Base(1), Base(2), Base(3), Base(4)};
    using pbaseArr = Base *;
    pbaseArr baseArr1[5];
    pbaseArr *pbaseArr1 = new pbaseArr[10];
    for (size_t i = 0; i < 5; ++i)
        pbaseArr1[i] = new Base(i);
    delete[] pbaseArr1;

    void *rawMem = operator new[](5 * sizeof(Base));
    Base *pbase = static_cast<Base *>(rawMem);
    for (size_t i = 0; i < 5; ++i)
        new (&pbase[i]) Base(i);
    for (size_t i = 4; i >= 0; --i)
        pbase[i].~Base();
    operator delete[](rawMem);

    return 0;
}
