#include <algorithm>
#include <iterator>
#include "AndQuery.h"

inline Query operator&(const Query &lhs, const Query &rhs) { return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs)); }

QueryResult AndQuery::eval(const TextQuery &t) const
{
    auto left = lhs.eval(t), right = rhs.eval(t);
    auto ret_lines = std::make_shared<std::set<line_no>>();
    std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                          std::inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}
