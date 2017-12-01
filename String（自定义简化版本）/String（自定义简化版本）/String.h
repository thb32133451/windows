#ifndef _STRING_H
#define _STRING_H

#include <memory>
#include <iostream>
#include <allocators>

class String {
public:
	String():first(nullptr),first_free(nullptr),last(nullptr){}      //默认初始化为空
	String(const String& s);
	String(const char* ptr);
	~String()
	{
		free();
	}
	String& operator=(const String& s);
	char* begin() const { return first; }
	char* end() const { return first_free; }
	size_t size() const { return first_free - first; }
	size_t capacity() const { return last - first; }
	void push_back(const char* s);
	void reallocate();
private:
	static std::allocator<char> alloc;        //静态allocator成员，用于分配内存
	char* first;
	char* first_free;
	char* last;
	void free();             //销毁对象并释放内存
	void check_n_alloc() { if (capacity() == size()) reallocate(); }
	std::pair<char*, char*> alloc_n_copy(const char*, const char*);
};

#endif // !_STRING_H

