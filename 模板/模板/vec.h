#ifndef _VEC_H
#define _VEC_H

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>   //allocator定义所在头文件
#include <utility>  //std::move标准库函数所在头文件

template <typename T> class Vec {
public:
	typedef unsigned int size_type;

	Vec()          //allocator成员使用默认初始化
		:first(nullptr), first_free(nullptr), last(nullptr) {}       //其他成员使用空指针初始化
	Vec(const Vec &hs);        //拷贝构造函数
	Vec& operator=(const Vec &rhs);    //拷贝复制运算符
	~Vec();                       //析构函数
	void push_back(const T &s);             //拷贝元素
	size_t size() const { return first_free - first; }      //返回实际已使用空间包含多少个元素
	size_t capacity() const { return last - first; }        //返回已分配空间最大容纳元素数量
															//begin()和end() 加上const限定符以处理const Vec类型
	T *begin() const { return first; }
	T *end() const { return first_free; }

	//课后作业
	void reserve(size_t &n);        //分配至少能容纳n个元素的内存空间
	void resize(size_t &n);                                  //调整大小
	void resize(size_t n, const T &s);             //resize()的另一个版本
															 //标准库采用重载resize()的方法 ,而不是定义void resize(size_t n, const T &s = T())
	//接受initializer<string>作为参数的构造函数
	Vec(std::initializer_list<T> slst);

	//移动构造函数与移动赋值运算符
	Vec(Vec &&s) noexcept;   //noexpect表示不抛出任何异常
	Vec& operator=(Vec &&s) noexcept;
	T& operator[](size_type n) const;
private:
	static std::allocator<T> alloc;    //用于分配元素的静态allocator类成员,静态成员必须声明到对应.cpp文件中，否则会引起为定义的引用
	//被添加元素的函数所使用
	void check_n_alloc()
	{
		if (size() == capacity()) reallocate();
	}
	//被拷贝构造函数，赋值运算符和析构函数使用的工具函数
	std::pair<T *, T *> alloc_n_copy(const T*, const T *);
	void free();                    //销毁元素并释放内存
	void reallocate();              //获得更多内存并拷贝已有元素
	T *first;              //指向数组首元素
	T *first_free;         //指向数组第一个空闲元素
	T *last;               //指向数组第一个尾后元素
};

#endif // !_VEC_H

template <typename T> std::allocator<T> Vec<T>::alloc;

template <typename T>
inline Vec<T>::Vec(const Vec & hs)
{
	auto newdata = alloc_n_copy(hs.begin(), hs.end());
	first = newdata.first;
	first_free = last = newdata.second;
}

template <typename T>
inline Vec<T> & Vec<T>::operator=(const Vec & rhs)
{
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	first = newdata.first;
	first_free = last = newdata.second;
	return *this;
	// TODO: 在此处插入 return 语句
}

template <typename T>
inline Vec<T>::~Vec()
{
	free();
}

template <typename T>
inline void Vec<T>::push_back(const T & s)
{
	check_n_alloc();
	alloc.construct(first_free++, s);
}

template <typename T>
inline void Vec<T>::reserve(size_t & n)
{
	if (capacity() < n)
	{
		auto newdata = alloc.allocate(n);
		auto f_free = std::uninitialized_copy(first, first_free, newdata);
		free();
		first = newdata;
		first_free = f_free;
		last = newdata + n;
	}
}

template <typename T>
inline void Vec<T>::resize(size_t & n)
{
	if (capacity() < n)
		reserve(n);
	else if (capaticy() == n);
	else {
		auto dest = last;
		for (; dest != first + n;)
			alloc.destroy(--dest);
		first_free = dest;
	}
}

template <typename T>
inline Vec<T>::Vec(std::initializer_list<T> slst)
{
	auto newdata = alloc_n_copy(slst.begin(), slst.end());
	free();
	first = newdata.first;
	first_free = last = newdata.second;
}

template <typename T>
inline Vec<T>::Vec(Vec && s) noexcept
	:first(s.first),first_free(s.first_free),last(s.last)
{
	s.first = s.first_free = s.last = nullptr;
}

template <typename T>
inline Vec<T> & Vec<T>::operator=(Vec && s) noexcept
{
	if (first != s.first) {
		free();
		first = s.first;
		first_free = s.first_free;
		last = s.last;

		s.first = s.first_free = s.last = nullptr;
	}
	return *this;
	// TODO: 在此处插入 return 语句
}

template<typename T>
inline T & Vec<T>::operator[](size_type n) const
{
	return *(first + n);
	// TODO: 在此处插入 return 语句
}

template <typename T>
inline std::pair<T*, T*> Vec<T>::alloc_n_copy(const T *beg, const T *end)
{
	auto data = alloc.allocate(end - beg);
	return{ data,std::uninitialized_copy(beg,end,data) };
}

template <typename T>
inline void Vec<T>::free()
{
	if (first)            //检查是否有元素存在
		std::for_each(first, first_free, [this](T& t) {alloc.destroy(&t); });
	alloc.deallocate(first, last - first);
}
template <typename T>
inline void Vec<T>::reallocate()
{
	auto newsize = size() ? size() * 2 : 1;
	auto newdata = alloc.allocate(newsize);
	auto s = newdata;
	auto fst = first;
	for (size_t i = 0; i != size(); i++)
		alloc.construct(s++, std::move(*fst++));
	free();
	first = newdata;
	first_free = s;
	last = newdata + newsize;
}
