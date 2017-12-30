#include "Query.h"
#include <algorithm>
#include <iterator>

QueryResult OrQuery::eval(const TextQuery &s) const
{
	//通过对Query成员lhs和rhs的虚调用，对他们分别调用eval成员返回每个运算对象的QueryResult
	auto left = lhs.eval(s), right = rhs.eval(s);
	//将左侧运算对象的行号拷贝到set中
	auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
	//拷贝右侧运算对象的行号
	ret_lines->insert(right.begin(), right.end());
	//返回表示lhs和rhs并集的QueryResult
	return QueryResult(rep(),left.get_file(),ret_lines);
}

QueryResult AndQuery::eval(const TextQuery &s) const
{
	auto left = lhs.eval(s), right = lhs.eval(s);
	auto ret_lines = std::make_shared<std::set<line_no>>();
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
	return QueryResult(rep(),left.get_file(),ret_lines);
}

QueryResult NotQuery::eval(const TextQuery & r) const
{
	auto result = query.eval(r);
	auto ret_lines = std::make_shared<std::set<line_no>>();
	auto beg = result.begin(), end = result.end();
	auto size = result.get_file()->size();
	for (std::size_t n = 0; n != size; ++n) {
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}
	return QueryResult(rep(),result.get_file(),ret_lines);
}
