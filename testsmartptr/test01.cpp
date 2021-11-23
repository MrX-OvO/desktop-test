/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-06 14:23:10
 * @LastEditTime : 2021-08-06 14:26:32
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testsmartptr/test01.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <memory>

int main(int argc, char const *argv[])
{
    auto p1 = std::make_shared<int>(42);
    std::cout << "p1 = " << p1 << ", *p1 = " << *p1 << std::endl;
    return 0;
}
