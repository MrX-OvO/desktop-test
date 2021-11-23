/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-02 15:50:28
 * @LastEditTime : 2021-08-02 17:05:42
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/test01.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    std::string s;
    for (size_t i = 1; i < argc; ++i)

        s += std::string(argv[i]);
    std::cout << s << std::endl;

    return 0;
}
