/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-01 15:53:41
 * @LastEditTime : 2021-08-01 22:33:44
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/teststl/test02.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
#include <ctime>

#include <cstdlib>

constexpr size_t ARRAY_SIZE = 1000;

long get_a_target_long()
{
    long target = 0;
    std::cout << "请输入一个数字， 范围 0~" << RAND_MAX << std::endl;
    std::cin >> target;
    return target;
}

std::string get_a_target_string()
{
    long target = 0;
    constexpr size_t bufSize = 11;
    char buf[bufSize];
    std::cout << "请输入一个数字， 范围 0~" << RAND_MAX << std::endl;
    std::cin >> target;
    snprintf(buf, bufSize, "%d\n", target);
    return std::string(buf);
}

int compareLongs(const void *a, const void *b)
{
    const long *l1 = static_cast<const long *>(a);
    const long *l2 = static_cast<const long *>(b);
    return (*l1 - *l2);
}

int compareStrings(const void *a, const void *b)
{
    const char *s1 = static_cast<const char *>(a);
    const char *s2 = static_cast<const char *>(b);
    return std::strcmp(s1, s2);
}

void test_array()
{
    std::cout << "test array...\n";

    clock_t seed;
    std::srand(static_cast<size_t>(std::time(&seed)));

    std::array<int, ARRAY_SIZE> arr;
    clock_t start, end;
    double duration;
    start = clock();
    for (size_t i = 0; i < ARRAY_SIZE; ++i)
        arr[i] = rand() % ARRAY_SIZE;
    end = clock();
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
    std::cout << "asignment spent " << duration << "ms\n";
    std::cout << "array.size() = " << arr.size() << std::endl;
    std::cout << "array.front() = " << arr.front() << std::endl;
    std::cout << "array.back() = " << arr.back() << std::endl;
    std::cout << "array.data() = " << arr.data() << std::endl;

    long target = get_a_target_long();

    start = clock();
    std::qsort(arr.data(), ARRAY_SIZE, sizeof(long), compareLongs);
    long *pItem = static_cast<long *>(std::bsearch(&target, arr.data(), ARRAY_SIZE, sizeof(long), compareLongs));
    end = clock();
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
    std::cout << "qsort() + bsearch() spent " << duration << "ms\n";

    if (pItem != nullptr)
        std::cout << "found, " << *pItem << std::endl;
    else
        std::cout << "not found\n";
}

int main(int argc, char const *argv[])
{
    test_array();

    return 0;
}
