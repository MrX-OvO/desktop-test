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
#ifndef _QUERYRESULT_H_
#define _QUERYRESULT_H_
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>
class QueryResult
{
    using line_no = std::vector<std::string>::size_type;
    using iter = std::set<line_no>::iterator;
    friend std::ostream &print(const QueryResult &, std::ostream &);

private:
    std::string word;                               // 查询单词
    std::shared_ptr<std::set<line_no>> lines;       // 出现的行号(set)
    std::shared_ptr<std::vector<std::string>> file; // 输入文件

public:
    QueryResult(std::string w, std::shared_ptr<std::set<line_no>> ls, std::shared_ptr<std::vector<std::string>> f)
        : word(w), lines(ls), file(f) {}
    ~QueryResult() = default;
    iter begin() const { return lines->begin(); }
    iter end() const { return lines->end(); }
    decltype(file) get_file() const { return file; }
};
#endif // !_QUERYRESULT_H_