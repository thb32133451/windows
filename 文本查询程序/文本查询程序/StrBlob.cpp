#include "StrBlob.h"

strBlob::strBlob() :data(std::make_shared<std::vector<std::string>>()) {}

strBlob::strBlob(std::initializer_list<std::string> i1):data(std::make_shared<std::vector<std::string>>(i1)){}

void strBlob::pop_back()
{
	check(0, "pop_back on empty strBlob");
	data->pop_back();
}

void strBlob::check(size_type i, const std::string & msg) const
{
	if (i >= data->size())
		throw std::out_of_range(msg);
}

std::string &strBlob::do_front() const
{
	check(0, "front on empty strBlob");
	return data->front();
}

std::string &strBlob::do_back() const
{
	check(0, "back on empty strBlob");
	return data->back();
}
