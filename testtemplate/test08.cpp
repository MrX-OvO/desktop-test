#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

template <typename T>
void print(const std::vector<T> &vec, const char *name, unsigned n)
{
    std::cout << name << ", size() = " << n << std::endl;
    for (auto iter = vec.cbegin(); iter != vec.cend();)
        std::cout << *iter++ << (iter == vec.cend() ? "\n" : ", ");
    std::cout << std::endl;
}

template <typename T>
void initVec(std::vector<T> &vec, unsigned N)
{
    std::cout << "calling void initVec(std::vector<T> &, unsigned) \n";
    srand((unsigned)time(NULL));
    sleep(1);
    for (size_t i = 0; i < N; ++i)
    {
        auto value = rand() % 10 + 0.2;
        vec.emplace_back(static_cast<T>(value));
    }
}

template <>
void initVec(std::vector<std::string> &vec, unsigned N)
{
    std::cout << "calling void initVec(std::vector<std::string> &, unsigned) \n";
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < N; ++i)
    {
        auto s = std::to_string(rand() % 10);
        vec.emplace_back(s);
    }
}

template <typename T>
std::pair<std::ptrdiff_t, const char *> my_count(const std::vector<T> &vec, const T &t)
{
    return std::make_pair(std::count(vec.cbegin(), vec.cend(), t),
                          "calling std::pair<std::ptrdiff_t, const char *> my_count(const std::vector<T> &, const T &)");
}

template <>
std::pair<std::ptrdiff_t, const char *> my_count(const std::vector<const char *> &vec, const char *const &t)
{
    return std::make_pair(std::count(vec.cbegin(), vec.cend(), t),
                          "calling std::pair<std::ptrdiff_t, const char *> my_count(const std::vector<const char *> &, const char *const &)");
}

int main(int argc, char const *argv[])
{
    std::vector<double> dvec;
    std::vector<int> ivec;
    std::vector<std::string> svec;
    std::vector<const char *> ccvec{"hi", "world", "cpp", "hi"};
    unsigned N = 30;

    initVec(dvec, N);
    print(dvec, "dvec", dvec.size());

    initVec(ivec, N);
    print(ivec, "ivec", ivec.size());

    initVec(svec, N);
    print(svec, "svec", svec.size());

    print(ccvec, "ccvec", ccvec.size());

    auto retPair = my_count(dvec, dvec[0]);
    std::cout << retPair.second << "\nelement dvec[0] appears " << retPair.first << (retPair.first > 1 ? " times\n\n" : " time\n\n");
    retPair = my_count(ivec, ivec[0]);
    std::cout << retPair.second << "\nelement dvec[0] appears " << retPair.first << (retPair.first > 1 ? " times\n\n" : " time\n\n");
    retPair = my_count(svec, svec[0]);
    std::cout << retPair.second << "\nelement dvec[0] appears " << retPair.first << (retPair.first > 1 ? " times\n\n" : " time\n\n");
    retPair = my_count(ccvec, ccvec[0]);
    std::cout << retPair.second << "\nelement dvec[0] appears " << retPair.first << (retPair.first > 1 ? " times\n\n" : " time\n\n");

    return 0;
}
