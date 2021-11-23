/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 15:02:47
 * @LastEditTime : 2021-08-08 15:12:00
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testnewdelete/test02.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <memory>

void process(std::shared_ptr<int> ptr) { std::cout << "process:use_count() = " << ptr.use_count() << std::endl; }

int main(int argc, char const *argv[])
{
    std::shared_ptr<int> p(new int(1024));
    std::cout << "p.use_count() = " << p.use_count() << std::endl;
    process(p);

    return 0;
}
