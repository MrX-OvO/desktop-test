#ifndef _ANDQUERY_H_
#define _ANDQUERY_H_
#include "BinaryQuery.h"
#include "Query.h"
class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query &, const Query &);

private:
    AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") {}
    QueryResult eval(const TextQuery &) const;
};
#endif // !_ANDQUERY_H_
