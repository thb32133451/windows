#ifndef _STRVEC_H
#define _STRVEC_H

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>   //allocator定义所在头文件
#include <utility>  //std::move标准库函数所在头文件

class StrVec {

public:
	StrVec()          //allocator成员使用默认初始化
		:first(nullptr), first_free(nullptr), last(nullptr) {}       //其他成员使用空指针初始化
	StrVec(const StrVec &hs);        //拷贝构造函数
	StrVec& operator=(const StrVec &rhs);    //拷贝复制运算符
	~StrVec();                       //析构函数
	void push_back(const std::string &s);             //拷贝元素
	size_t size() const { return first_free - first; }      //返回实际已使用空间包含多少个元素
	size_t capacity() const { return last - first; }        //返回已分配空间最大容纳元素数量
	//begin()和end() 加上const限定符以处理const StrVec类型
	std::string *begin() const { return first; }            
	std::string *end() const { return first_free; }
	
	//课后作业
	void reserve(size_t &n);        //分配至少能容纳n个元素的内存空间
	void resize(size_t &n);                                  //调整大小
	void resize(size_t n, const std::string &s);             //resize()的另一个版本
	//标准库采用重载resize()的方法 ,而不是定义void resize(size_t n, const std::string &s = std::string())
	//接受initializer<string>作为参数的构造函数
	StrVec(std::initializer_list<std::string> slst);

	//移动构造函数与移动赋值运算符
	StrVec(StrVec &&s) noexcept;   //noexpect表示不抛出任何异常
	StrVec& operator=(StrVec &&s) noexcept;
private:
	static std::allocator<std::string> alloc;    //用于分配元素的静态allocator类成员
	//静态成员必须声明到对应.cpp文件中，否则会引起为定义的引用
	//被添加元素的函数所使用
	void check_n_alloc()
	{
		if (size() == capacity()) reallocate();
	}
	//被拷贝构造函数，赋值运算符和析构函数使用的工具函数
	std::pair<std::string *, std::string *> alloc_n_copy(const std::string*, const std::string *);
	void free();                    //销毁元素并释放内存
	void reallocate();              //获得更多内存并拷贝已有元素
	std::string *first;               //指向数组首元素
	std::string *first_free;        //指向数组第一个空闲元素
	std::string *last;               //指向数组第一个尾后元素
};

#endif // !_STRVEC_H
