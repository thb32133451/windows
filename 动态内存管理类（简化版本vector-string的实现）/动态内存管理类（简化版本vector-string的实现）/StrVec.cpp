#include "StrVec.h"

StrVec::StrVec(const StrVec &hs)
{
	auto newdata = alloc_n_copy(hs.begin(), hs.end());   //分配空间并拷贝
	//由于分配的空间恰好等于要拷贝的元素数目，因此first_free=last
	first = newdata.first;
	first_free = last = newdata.second;
}

StrVec & StrVec::operator=(const StrVec & rhs)
{
	//在释放已有元素之前使用alloc_n_copy，能够适应自赋值情况
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	first = newdata.first;
	last = first_free = newdata.second;
	return *this;
	// TODO: 在此处插入 return 语句
}

StrVec::~StrVec()
{
	free();
}

void StrVec::push_back(const std::string & s)
{
	check_n_alloc();     //确保有空间容纳新元素
	//在first_free指向的元素中构造新元素
	alloc.construct(first_free++, s);
}

void StrVec::reserve(size_t & n)    //至少分配能容纳n个元素的空间
{
	if (capacity() < n)        //如果已分配空间大于n，则本函数不做任何事情
	{
		auto newsize = capacity();
		do {                              //确定新空间大小
			newsize *= 2;
		} while (newsize < n);

		auto newdata = alloc.allocate(newsize);    //分配新空间
		std::uninitialized_copy(first, first_free, newdata);       //从旧空间中将元素构造至新空间
		//更新数据结构
		first_free = newdata + (first_free - first);               //先更新first_free以避免指针错误
		first = newdata;
		last = first + newsize;
	}
}

void StrVec::resize(size_t &n)       //单参数版本
{
	if (capacity() < n) {  //n大于现有空间
		reserve(n);        //重新分配空间
	}
	else if (capacity() == n);   //不做任何操作
	else                   //n小于现有空间
	{
		auto dest = last;
		for (; dest != first + n;)
			alloc.destroy(--dest);             //销毁对象
		//更新数据结构
		first_free = dest;
	}
}

void StrVec::resize(size_t n, const std::string & s)   //双参数版本
{

	if (capacity() < n) {  //n大于现有空间
		reserve(n);        //重新分配空间并移动旧空间元素
		for (auto i = first_free; i != last;)
			alloc.construct(i++, s);    //用s逐个构造first_free之后的对象
	}
	else if (capacity() == n);   //不做任何操作
	else                   //n小于现有空间
	{
		auto dest = last;
		for (; dest != first + n;)
			alloc.destroy(--dest);             //销毁对象
		//更新数据结构
		first_free = dest;
	}
}

std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string *beg, const std::string *end)
//分配足够的内存以保存给定范围中的元素，并将这些元素拷贝到分配的空间中
//返回的pair的两个指针分别指向分配空间开始的位置和拷贝的尾后的位置
{
	auto data = alloc.allocate(end - beg);              //分配空间
	return { data, std::uninitialized_copy(beg, end, data) };      //使用uninitialized_copy()拷贝元素
}

void StrVec::free()
{
	if (first) {          //检查first是否为nullptr，如果是，不执行下面的函数体
		//逆序销旧元素
		for (auto des = first_free - 1; des != first; --des) {
			alloc.destroy(des);     
		}
		//释放内存
		alloc.deallocate(first, last - first);
	}
}

void StrVec::reallocate()
// 1 为一个新的、更大的string数组分配内存
// 2 在新空间的前一部分构造对象，保存现有元素
// 3 销毁原内存空间的元素，释放内存
{
	//即将分配空间的大小
	auto newcapacity = size() ? 2 * size() : 1;
	//分配新内存
	auto newdata = alloc.allocate(newcapacity);
	//将数据从旧内存移动到新内存
	auto dest = newdata;     //指向新数组中下一个空闲元素
	auto fst = first;        //指向旧数组中下一个元素
	for (size_t i = 0; i != size(); i++)
		alloc.construct(dest++, std::move(*fst++));
	free();                  //完成之后释放旧内存空间
	//更新数据结构，执行新元素
	first = newdata;
	first_free = dest;
	last = first + newcapacity;
}
