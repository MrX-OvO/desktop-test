#ifndef _ORQUERY_H_
#define _ORQUERY_H_
#include "BinaryQuery.h"
#include "Query.h"
class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query &, const Query &);

private:
    OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|") {}
    QueryResult eval(const TextQuery &) const override;
};
#endif // !_ORQUERY_H_
