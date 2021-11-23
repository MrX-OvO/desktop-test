#ifndef _WORDQUERY_H_
#define _WORDQUERY_H_
#include "Query_base.h"
#include "QueryResult.h"
#include "TextQuery.h"
class Query;
class WordQuery : public Query_base
{
    friend class Query;

private:
    std::string query_word;

private:
    WordQuery(const std::string &s) : query_word(s) {}
    QueryResult eval(const TextQuery &t) const override { return t.query(query_word); }
    std::string rep() const override { return query_word; }
};
#endif // !_WORDQUERY_H_