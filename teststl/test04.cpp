/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-04 20:24:22
 * @LastEditTime : 2021-08-04 22:59:00
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/teststl/test04.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

bool isShorter(const std::string &s1, const std::string &s2) { return s1.size() < s2.size(); }

bool isBigger(const std::string &s) { return s.size() >= 5; }

void elimDups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    auto end_unique_iter = std::unique(words.begin(), words.end());
    words.erase(end_unique_iter, words.end());
    std::cout << "\n-------------------------------------\n";
    std::cout << "elimDups(words): \n";
    for (auto &&word : words)
    {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(word.size() + 1) << word;
    }
    std::cout << "\n-------------------------------------\n";
}

void biggers(std::vector<std::string> &words, std::vector<std::string>::size_type sz)
{
    elimDups(words);
    std::stable_sort(words.begin(), words.end(), isShorter);
    auto iter = std::find_if(words.begin(), words.end(),
                             [sz](const std::string &a)
                             { return a.size() >= sz; });
    auto count = words.end() - iter;
    std::cout << count << " ";
    std::cout << [count](size_t t) -> std::string
    { return t > 1 ? "words" : "word"; }(count);
    std::cout << " of length " << sz << " or longer\n";
    std::for_each(iter, words.end(), [](const std::string &s)
                  {
                      std::cout.setf(std::ios::left);
                      std::cout << std::setw(s.size() + 1) << s;
                  });
    std::cout << std::endl;
}

void biggers(std::vector<std::string> &words)
{
    elimDups(words);
    std::stable_sort(words.begin(), words.end(), isShorter);
    auto iter = std::find_if(words.begin(), words.end(), isBigger);
    auto count = words.end() - iter;
    std::cout << count << " ";
    std::cout << [count](size_t t) -> std::string
    { return t > 1 ? "words" : "word"; }(count);
    std::cout << " of length " << 5 << " or longer\n";
    std::for_each(iter, words.end(), [](const std::string &s)
                  {
                      std::cout.setf(std::ios::left);
                      std::cout << std::setw(s.size() + 1) << s;
                  });
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> words1 = {"sort", "hello", "world", "I", "C++", "red", "sort", "red"};
    std::vector<std::string> words2 = {"sort", "hello", "world", "I", "C++", "red", "sort", "red"};
    std::vector<std::string>::size_type sz = 5;
    std::cout << "words1: \n";
    for (auto &&word : words1)
    {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(word.size() + 1) << word;
    }
    std::cout << std::endl;

    std::cout << "words2: \n";
    for (auto &&word : words2)
    {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(word.size() + 1) << word;
    }
    std::cout << "\n=====================================\n";

    std::cout << "biggers(words1): \n";
    biggers(words1);
    std::cout << std::endl;

    std::cout << "biggers(words2): \n";
    biggers(words2, sz);
    std::cout << "\n=====================================\n";

    std::sort(words1.begin(), words1.end(), isShorter);
    std::cout << "sort(words1): \n";
    for (auto &&word : words1)
    {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(word.size() + 1) << word;
    }
    std::cout << std::endl;

    std::stable_sort(words2.begin(), words2.end(), isShorter);
    std::cout << "stable_sort(words2): \n";
    for (auto &&word : words2)
    {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(word.size() + 1) << word;
    }
    std::cout << "\n=====================================\n";

    return 0;
}
