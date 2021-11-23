/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-08 19:44:40
 * @LastEditTime : 2021-08-08 21:50:51
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testnewdelete/TextQuery.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include "TextQuery.h"
#include "QueryResult.h"

std::string TextQuery::eraseToken(std::string &str)
{
    const char *tokens[] = {"\"", "\'", ",", ".", "?"};
    //if (str.size() > 1)
    {
        auto iter = tokens;
        auto pos = str.find(*iter);
        for (int i = 0; i < 5; ++i)
        {
            while (pos)
            {
                str.erase(pos);
                pos = str.find(*iter);
            }
            ++iter;
        }
    }
    return str;
}

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
{
    std::string line;
    while (getline(is, line))
    {
        file->push_back(line);
        int no = file->size() - 1;
        std::istringstream stream(line);
        std::string word;
        while (stream >> word)
        {
            //word = eraseToken(word);
            auto &lines = wordLineNumMapper[word];
            if (!lines)
                lines.reset(new std::set<line_no>);
            lines->insert(no);
        }
    }
}

QueryResult TextQuery::query(const std::string &word) const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto iter = wordLineNumMapper.find(word);
    if (iter == wordLineNumMapper.end())
        return QueryResult(word, nodata, file);
    else
        return QueryResult(word, iter->second, file);
}