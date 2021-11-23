#include <iostream>
#include <random>
#include <cstdlib>

int main(int argc, char const *argv[])
{
    std::default_random_engine e;
    for (size_t i = 0; i < 10; ++i)
        std::cout << e() << " ";
    std::cout << "\ne1.min() = " << e.min() << ", e1.max() = " << e.max() << std::endl;

    std::uniform_int_distribution<unsigned> u1(0, 9);
    for (size_t i = 0; i < 10; ++i)
        std::cout << u1(e) << " ";
    std::cout << "\ne.min() = " << e.min() << ", e.max() = " << e.max() << std::endl;

    std::cout << "RAND_MAX = " << RAND_MAX << std::endl;

    std::uniform_real_distribution<double> u2(0, 1);
    for (size_t i = 0; i < 10; ++i)
        std::cout << u2(e) << " ";
    std::cout << "\ne.min() = " << e.min() << ", e.max() = " << e.max() << std::endl;

    return 0;
}
