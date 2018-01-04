#ifndef _BLOB_H
#define _BLOB_H

#include <memory>
#include <vector>
#include <string>
#include <initializer_list>

template <typename> class Blob;            //������Ԫʱ����Ҫ�õ�ǰ������
template <typename> class BlobPtr;
template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);


template <typename T> class Blob {
public:
	//����ģ�����<T>�Խ�����Ȩ��ֻ��������ͬ����ʵ������BlobPtr��operator==���Խ���һ��һ���Ѻù�ϵ
	friend class BlobPtr<T>;     //��Ҫ����ģ�����
	friend bool operator==(const Blob<T>&, const Blob<T>&);

	typedef T value_type;
	typedef typename std::vector<T >::size_type size_type;

	Blob();
	Blob(std::initializer_list<T> i1);

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty();}

	void push_back(const T& t) { data->push_back(T); }
	void push_back(T&& t) { data->push_back(std::move(T)); }
	void pop_back();

	T& back();
	T& operator[](sizetype i);
	//�κ���ҵ�������±��������back��Ա
	const T& back() const;
	const T& operator[](size_type i) const;
private:
	std::shared_ptr<std::vector<T>> data;
	void check(size_type i, const std::string &msg) const;
};






template <typenamae T> class BlobPtr {
public:
	BlobPtr() :curr(0) {}
	BlobPtr(Blob<T> &a, std::size_t sz = 0) :wptr(a.data), curr(sz) {}
	T& operator*()const {
		auto p = check(curr, "dereference past end.");
		return (*p)[curr];
	}
	BlobPtr& operator++();
	BlobPtr& operator--();
private:
	std::shared_ptr<std::vector<T>> check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<T>> wptr;         //����һ��weak_ptr����ʾ�ײ�vector���ܱ�����
	std::size_t curr;     //�����еĵ�ǰλ��
};



#endif // !_BLOB_H

template<typename T>
inline Blob<T>::Blob() :data(std::make_shared<std::vector<T>>()) {}

template<typename T>
inline Blob<T>::Blob(std::initializer_list<T> i1) : data(std::make_shared<std::vector<T>>(i1)) {}

template<typename T>
inline void Blob<T>::pop_back()
{
	check(0, "pop_back on empty Blob.");
	data->pop_back();
}

template<typename T>
inline T & Blob<T>::back()
{
	check(0, "back on empty Blob.");
	return data->back();
	// TODO: �ڴ˴����� return ���
}

template<typename T>
inline T & Blob<T>::operator[](sizetype i)
{
	check(i, "subscript out of range");
	return(*data)[i];
	// TODO: �ڴ˴����� return ���
}

template <typename T>
inline const t& Blob<T>::back() const {
	check(0, "back on empty Blob");
	return data->back();
}

template <typename T>
inline const T& Blob<T>::operator[](size_type i) const {
	check(i, "subscript out of range");
	return (*data)[i];
}

template<typename T>
inline void Blob<T>::check(size_type i, const std::string & msg) const
{
	if (i >= data->size())
		throw std::out_of_range(msg);
}

template<typenamae T>
inline BlobPtr & BlobPtr<T>::operator++()
{
	//�˴������飬ǰ�õ����������������Ƿ�Ϸ�
	BlobPtr ret = *this;
	++*this;
	return ret;
	// TODO: �ڴ˴����� return ���
}

template<typenamae T>
inline BlobPtr & BlobPtr<T>::operator--()
{
	BlobPtr ret = *this;
	--*this;
	return ret;
	// TODO: �ڴ˴����� return ���
}
