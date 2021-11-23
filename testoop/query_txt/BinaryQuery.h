#ifndef _BINARYQUERY_H_
#define _BINARYQUERY_H_
#include "Query.h"
class BinaryQuery : public Query_base
{
protected:
    Query lhs, rhs;
    std::string opSym;

protected:
    BinaryQuery(const Query &l, const Query &r, std::string s) : lhs(l), rhs(r), opSym(s) {}
    std::string rep() const override { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
};
#endif // !_BINARYQUERY_H_
