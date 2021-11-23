/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 20:44:24
 * @LastEditTime : 2021-08-08 21:08:46
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testnewdelete/testmain.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <fstream>
#include "TextQuery.h"
#include "QueryResult.h"

void runQueries(std::ifstream &infile);

int main(int argc, char const *argv[])
{
    std::string infilePath = "./The Old Man and the Sea.txt";
    std::ifstream infile(infilePath);
    runQueries(infile);

    return 0;
}

void runQueries(std::ifstream &infile)
{
    TextQuery tq(infile);
    while (true)
    {
        std::cout << "enter word to look for, or q to quit: ";
        std::string word;
        if (!(std::cin >> word) || "q" == word)
            break;
        print(std::cout, tq.query(word)) << std::endl;
    }
}
