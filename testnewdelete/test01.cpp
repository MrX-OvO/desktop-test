/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 14:03:19
 * @LastEditTime : 2021-08-08 14:50:53
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testnewdelete/test01.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <vector>
#include <memory>

std::vector<int> *f1();
std::shared_ptr<std::vector<int>> f11();

void f2(std::vector<int> *pvec);
void f2(std::shared_ptr<std::vector<int>> spvec);

void f3(std::vector<int> *pvec);
void f3(std::shared_ptr<std::vector<int>> spvec);

int main(int argc, char const *argv[])
{
    std::cout << "不使用shared_ptr\n";
    std::vector<int> *pvec = f1();
    f2(pvec);
    std::cout << "\npvec:\n";
    f3(pvec);
    std::cout << std::endl;
    delete pvec;

    std::cout << "\n使用shared_ptr\n";
    std::shared_ptr<std::vector<int>> spvec = f11();
    f2(spvec);
    std::cout << "\nspvec:\n";
    f3(spvec);
    std::cout << std::endl;

    return 0;
}

std::vector<int> *f1() { return new std::vector<int>(); }

std::shared_ptr<std::vector<int>> f11() { return std::shared_ptr<std::vector<int>>(); }

void f2(std::vector<int> *pvec)
{
    int i = 0, v = 0;
    do
    {
        if (i > 0)
            pvec->push_back(v);
        std::cout << "请输入一个正整数:\n";
        std::cin >> v;
        ++i;
    } while (v > 0 && i < 10);
}

void f2(std::shared_ptr<std::vector<int>> spvec)
{
    int i = 0, v = 0;
    do
    {
        if (i > 0)
            spvec->push_back(v);
        std::cout << "请输入一个正整数:\n";
        std::cin >> v;
        ++i;
    } while (v > 0 && i < 10);
}

void f3(std::vector<int> *pvec)
{
    for (auto iter = pvec->begin(); iter != pvec->end();)
        std::cout << *iter++ << (iter == pvec->end() ? "" : ", ");
}

void f3(std::shared_ptr<std::vector<int>> spvec)
{
    for (auto iter = spvec->begin(); iter != spvec->end();)
        std::cout << *iter++ << (iter == spvec->end() ? "" : ", ");
}