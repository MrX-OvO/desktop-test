/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 19:30:58
 * @LastEditTime : 2021-08-08 21:41:54
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testnewdelete/TextQuery.h
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#ifndef _TEXTQUERY_H_
#define _TEXTQUERY_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>
class QueryResult;
class TextQuery
{
    using line_no = std::vector<std::string>::size_type;

private:
    std::shared_ptr<std::vector<std::string>> file;                              // 保存输入文件
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wordLineNumMapper; // 关联每个单词和它出现的行号 key：单词，value：行号(set)
private:
    std::string eraseToken(std::string &);

public:
    TextQuery(std::ifstream &);
    ~TextQuery() = default;
    QueryResult query(const std::string &) const;
};
#endif // !_TEXTQUERY_H_