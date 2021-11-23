#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <ctime>

int main(int argc, char const *argv[])
{
    std::default_random_engine e(time(0));
    std::normal_distribution<> n(4, 0.5);
    std::vector<unsigned> vals(9);
    for (size_t i = 0; i != 100; ++i)
    {
        unsigned v = lround(n(e));
        if (v < vals.size())
            ++vals[v];
    }
    for (size_t i = 0; i < vals.size(); ++i)
        std::cout << i << ": " << std::string(vals[i], '*') << std::endl;

    return 0;
}
