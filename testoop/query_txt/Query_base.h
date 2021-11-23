#ifndef _QUERY_BASE_H_
#define _QUERY_BASE_H_
#include "TextQuery.h"
#include "QueryResult.h"
class Query;
class Query_base
{
    friend class Query;

private:
    virtual QueryResult eval(const TextQuery &) const = 0; // 求查询结果
    virtual std::string rep() const = 0;                   //生产查询的string版本

protected:
    using line_no = size_t;
    virtual ~Query_base() = default;
};
#endif // !_QUERY_BASE_H_