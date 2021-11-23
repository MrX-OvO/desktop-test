#include "NotQuery.h"

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery &t) const
{
    auto result = query.eval(t);
    auto ret_lines = std::make_shared<std::set<line_no>>();
    auto begin = result.begin(), end = result.end();
    auto sz = result.get_file()->size();
    for (size_t i = 0; i < sz; ++i)
    {
        if (begin == end || *begin != i)
            ret_lines->insert(i);
        else if (begin != end)
            ++begin;
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}