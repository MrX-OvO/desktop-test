#include "picture.h"

using namespace chapter9_space;

std::string init[] = {"Paris", "in the", "Spring"};

int main(int argc, char const *argv[])
{
    Picture p(init, 3);
    std::cout << "Picture p:\n"
              << p << std::endl;

    Picture q = frame(p);
    std::cout << "Picture q:\n"
              << q << std::endl;

    Picture r = p | q;
    std::cout << "Picture r:\n"
              << r << std::endl;

    Picture s = p & q;
    std::cout << "Picture s:\n"
              << s << std::endl;

    std::cout << "Picture frame(q & (p | q)):\n"
              << frame(q & (p | q)) << std::endl;

    return 0;
}
