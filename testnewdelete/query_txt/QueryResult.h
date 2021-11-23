/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 20:12:17
 * @LastEditTime : 2021-08-08 21:06:47
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testnewdelete/QueryResult.h
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>
#ifndef _QUERYRESULT_H_
#define _QUERYRESULT_H_
class QueryResult
{
    using line_no = std::vector<std::string>::size_type;
    friend std::ostream &print(std::ostream &, const QueryResult &);

private:
    std::string word;                               // 查询单词
    std::shared_ptr<std::set<line_no>> lines;       // 出现的行号
    std::shared_ptr<std::vector<std::string>> file; // 输入文件

public:
    QueryResult(std::string w, std::shared_ptr<std::set<line_no>> ls, std::shared_ptr<std::vector<std::string>> f)
        : word(w), lines(ls), file(f) {}
    ~QueryResult() = default;
};
#endif // !_QUERYRESULT_H_