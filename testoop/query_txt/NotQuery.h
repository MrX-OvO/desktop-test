#ifndef _NOTQUERY_H_
#define _NOTQUERY_H_
#include "Query.h"
class NotQuery : public Query_base
{
    friend Query operator~(const Query &);

private:
    Query query;

private:
    NotQuery(const Query &q) : query(q) {}
    QueryResult eval(const TextQuery &) const override;
    std::string rep() const override { return "~(" + query.rep() + ")"; }
};
#endif // !_NOTQUERY_H_