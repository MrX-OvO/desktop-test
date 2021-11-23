/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-05 17:38:59
 * @LastEditTime : 2021-08-05 22:44:18
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/teststl/test08.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

std::map<std::string, std::string> buildMap(std::ifstream &map_file);
const std::string &transform(const std::string &s, const std::map<std::string, std::string> &m);
void word_transform(std::ifstream &map_file, std::ifstream &input);

int main(int argc, char const *argv[])
{
    std::string map_file_path = "./map_file.txt";
    std::string input_path = "./input.txt";
    std::ifstream map_file(map_file_path);
    std::ifstream input(input_path);
    word_transform(map_file, input);

    return 0;
}

std::map<std::string, std::string> buildMap(std::ifstream &map_file)
{
    std::map<std::string, std::string> trans_map;       // 保存转换规则
    std::string key;                                    // 要转换的单词（key）
    std::string value;                                  // 替换后的内容（value）
    while (map_file >> key && getline(map_file, value)) // 读取第一个单词存入key中，行中剩余内容存入value中
    {
        if (value.size() > 1)                 // 存在转换规则
            trans_map[key] = value.substr(1); // 跳过前导空格
        else
            throw std::runtime_error("no rule for " + key);
    }
    return trans_map;
}

const std::string &transform(const std::string &s, const std::map<std::string, std::string> &m)
{
    auto map_iter = m.find(s);
    if (map_iter != m.cend())    // 单词存在转换规则
        return map_iter->second; // 使用短语替换
    else
        return s;
}

void word_transform(std::ifstream &map_file, std::ifstream &input)
{
    auto trans_map = buildMap(map_file); //保存转换规则
    std::string text;                    //保存输入（文件）中的每一行
    while (getline(input, text))         //读取一行到text
    {
        std::istringstream stream(text); // 读取每个单词（或空格）
        std::string word;
        bool firstword = true; // 控制是否打印空格
        while (stream >> word)
        {
            if (firstword)
                firstword = false;
            else
                std::cout << " ";
            std::cout << transform(word, trans_map); // 转换并打印输出
        }
        std::cout << std::endl; // 完成一行的转换
    }
}
