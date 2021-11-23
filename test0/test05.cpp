#include <iostream>

void f()
{
    int i;
    static int j;
}

int main(int argc, char const *argv[])
{
    int i;
    static int j;
    double d;
    std::cout << "i = " << i << ", j = " << j << ", d = " << d << std::endl;

    int a[] = {1, 2, 3, 4};

    return 0;
}
