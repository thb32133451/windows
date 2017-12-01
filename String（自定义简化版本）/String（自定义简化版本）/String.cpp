#include "String.h"
std::allocator<char> String::alloc;

String::String(const String & s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	first = newdata.first;
	first_free = last = newdata.second;
	std::cout << "拷贝构造" << std::endl;
}

String::String(const char * ptr)         //接受c风格字符串的构造函数
{
	auto end = ptr;
	for (;;) {
		if (*end++ == '\0')
			break;
	}
	auto newdata = alloc_n_copy(ptr, end);
	first = newdata.first;
	first_free = last = newdata.second;
	
}

String & String::operator=(const String & s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	free();
	first = newdata.first;
	first_free = last = newdata.second;
	std::cout << "拷贝赋值" << std::endl;
	return *this;
	// TODO: 在此处插入 return 语句
}

void String::push_back(const char * s)
{
	check_n_alloc();
	alloc.construct(first_free++, *s);
}

void String::reallocate()
{
	auto newsize = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newsize);
	auto fst_free = newdata;
	auto fst = first;
	for (size_t i = 0; i != newsize; ++i)
		alloc.construct(fst_free++, std::move(*fst++));     //使用std::move进行移动构造
	free();
	first = newdata; first_free = fst_free;
	last = newdata + newsize;
}

void String::free()
{
	if (first) {        //检查String是否为空
		for (auto i = first_free; i != first;)
			alloc.destroy(--i);
		alloc.deallocate(first, last - first);
	}
}

std::pair<char*, char*> String::alloc_n_copy(const char *beg, const char *end)
{
	auto newdata=alloc.allocate(end - beg);
	return std::pair<char*, char*>(newdata,std::uninitialized_copy(beg,end,newdata));
}
