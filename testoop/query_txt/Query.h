#ifndef _QUERY_H_
#define _QUERY_H_
#include "Query_base.h"
#include "QueryResult.h"
#include "TextQuery.h"
#include "WordQuery.h"
class Query
{
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);

private:
    Query(std::shared_ptr<Query_base> query) : q(query) {}
    std::shared_ptr<Query_base> q;

public:
    Query(const std::string &s) : q(new WordQuery(s)) {}
    QueryResult eval(const TextQuery &t) const { return q->eval(t); }
    std::string rep() const { return q->rep(); }
};
#endif // !_QUERY_H_
