#ifndef _VEC_H
#define _VEC_H

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>   //allocator��������ͷ�ļ�
#include <utility>  //std::move��׼�⺯������ͷ�ļ�

template <typename T> class Vec {
public:
	typedef unsigned int size_type;

	Vec()          //allocator��Աʹ��Ĭ�ϳ�ʼ��
		:first(nullptr), first_free(nullptr), last(nullptr) {}       //������Աʹ�ÿ�ָ���ʼ��
	Vec(const Vec &hs);        //�������캯��
	Vec& operator=(const Vec &rhs);    //�������������
	~Vec();                       //��������
	void push_back(const T &s);             //����Ԫ��
	size_t size() const { return first_free - first; }      //����ʵ����ʹ�ÿռ�������ٸ�Ԫ��
	size_t capacity() const { return last - first; }        //�����ѷ���ռ��������Ԫ������
															//begin()��end() ����const�޶����Դ���const Vec����
	T *begin() const { return first; }
	T *end() const { return first_free; }

	//�κ���ҵ
	void reserve(size_t &n);        //��������������n��Ԫ�ص��ڴ�ռ�
	void resize(size_t &n);                                  //������С
	void resize(size_t n, const T &s);             //resize()����һ���汾
															 //��׼���������resize()�ķ��� ,�����Ƕ���void resize(size_t n, const T &s = T())
	//����initializer<string>��Ϊ�����Ĺ��캯��
	Vec(std::initializer_list<T> slst);

	//�ƶ����캯�����ƶ���ֵ�����
	Vec(Vec &&s) noexcept;   //noexpect��ʾ���׳��κ��쳣
	Vec& operator=(Vec &&s) noexcept;
	T& operator[](size_type n) const;
private:
	static std::allocator<T> alloc;    //���ڷ���Ԫ�صľ�̬allocator���Ա,��̬��Ա������������Ӧ.cpp�ļ��У����������Ϊ���������
	//�����Ԫ�صĺ�����ʹ��
	void check_n_alloc()
	{
		if (size() == capacity()) reallocate();
	}
	//���������캯������ֵ���������������ʹ�õĹ��ߺ���
	std::pair<T *, T *> alloc_n_copy(const T*, const T *);
	void free();                    //����Ԫ�ز��ͷ��ڴ�
	void reallocate();              //��ø����ڴ沢��������Ԫ��
	T *first;              //ָ��������Ԫ��
	T *first_free;         //ָ�������һ������Ԫ��
	T *last;               //ָ�������һ��β��Ԫ��
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
	// TODO: �ڴ˴����� return ���
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
	// TODO: �ڴ˴����� return ���
}

template<typename T>
inline T & Vec<T>::operator[](size_type n) const
{
	return *(first + n);
	// TODO: �ڴ˴����� return ���
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
	if (first)            //����Ƿ���Ԫ�ش���
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
