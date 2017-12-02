#include "StrVec.h"

std::allocator<std::string> StrVec::alloc;          //��ľ�̬��Ա����ʵ�ʶ�����cpp�ļ��У�����ᷢ��δ���������

StrVec::StrVec(const StrVec &hs)
{
	auto newdata = alloc_n_copy(hs.begin(), hs.end());   //����ռ䲢����
	//���ڷ���Ŀռ�ǡ�õ���Ҫ������Ԫ����Ŀ�����first_free=last
	first = newdata.first;
	first_free = last = newdata.second;
}

StrVec & StrVec::operator=(const StrVec & rhs)
{
	//���ͷ�����Ԫ��֮ǰʹ��alloc_n_copy���ܹ���Ӧ�Ը�ֵ���
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	first = newdata.first;
	last = first_free = newdata.second;
	return *this;
	// TODO: �ڴ˴����� return ���
}

StrVec::~StrVec()
{
	free();
}

void StrVec::push_back(const std::string & s)
{
	check_n_alloc();     //ȷ���пռ�������Ԫ��
	//��first_freeָ���Ԫ���й�����Ԫ��
	alloc.construct(first_free++, s);
}

void StrVec::reserve(size_t & n)    //���ٷ���������n��Ԫ�صĿռ�
{
	if (capacity() < n)        //����ѷ���ռ����n���򱾺��������κ�����
	{
		auto newsize = capacity();
		do {                              //ȷ���¿ռ��С
			newsize *= 2;
		} while (newsize < n);

		auto newdata = alloc.allocate(newsize);    //�����¿ռ�
		std::uninitialized_copy(first, first_free, newdata);       //�Ӿɿռ��н�Ԫ�ع������¿ռ�
		//�������ݽṹ
		first_free = newdata + (first_free - first);               //�ȸ���first_free�Ա���ָ�����
		first = newdata;
		last = first + newsize;
	}
}

void StrVec::resize(size_t &n)       //�������汾
{
	if (capacity() < n) {  //n�������пռ�
		reserve(n);        //���·���ռ�
	}
	else if (capacity() == n);   //�����κβ���
	else                   //nС�����пռ�
	{
		auto dest = last;
		for (; dest != first + n;)
			alloc.destroy(--dest);             //���ٶ���
		//�������ݽṹ
		first_free = dest;
	}
}

void StrVec::resize(size_t n, const std::string & s)   //˫�����汾
{

	if (capacity() < n) {  //n�������пռ�
		reserve(n);        //���·���ռ䲢�ƶ��ɿռ�Ԫ��
		for (auto i = first_free; i != last;)
			alloc.construct(i++, s);    //��s�������first_free֮��Ķ���
	}
	else if (capacity() == n);   //�����κβ���
	else                   //nС�����пռ�
	{
		auto dest = last;
		for (; dest != first + n;)
			alloc.destroy(--dest);             //���ٶ���
		//�������ݽṹ
		first_free = dest;
	}
}

StrVec::StrVec(std::initializer_list<std::string> slst)       //����initializer<string>��Ϊ�����Ĺ��캯��
{
	//initializer_list<>��Ԫ����Զ���ǳ���ֵ����˲���ֱ��ʹ�����Ŀռ䣬�����Լ�����
	//����ռ䲢����
	auto newdata = alloc_n_copy(slst.begin(), slst.end());
	//�ͷ����пռ�
	free();
	//�������ݽṹ
	first = newdata.first;
	first_free = last = newdata.second;
}

StrVec::StrVec(StrVec && s)noexcept     //noexpect����֪ͨ��׼��˺������׳��κ��쳣
	//��Ա��ʼ�����ӹ�s�е���Դ
	:first(s.first),first_free(s.first_free),last(s.last)
{
	//��s����������״̬�������������������ǰ�ȫ��
	s.first = s.first_free = s.last = nullptr;
}

StrVec & StrVec::operator=(StrVec && rhs) noexcept
{
	if (this != &rhs)       //��ֹ�Ը�ֵ
	{
		free();
		first = rhs.first;
		first_free = rhs.first_free;
		last = rhs.last;
		//��rhs���ڲ�����״̬
		rhs.first = rhs.first_free = rhs.last = nullptr;
	}
	return *this;
	// TODO: �ڴ˴����� return ���
}

std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string *beg, const std::string *end)
//�����㹻���ڴ��Ա��������Χ�е�Ԫ�أ�������ЩԪ�ؿ���������Ŀռ���
//���ص�pair������ָ��ֱ�ָ�����ռ俪ʼ��λ�úͿ�����β���λ��
{
	auto data = alloc.allocate(end - beg);              //����ռ�
	return { data, std::uninitialized_copy(beg, end, data) };      //ʹ��uninitialized_copy()����Ԫ��
}

void StrVec::free()
{
	/*
	if (first) {          //���first�Ƿ�Ϊnullptr������ǣ���ִ������ĺ�����
		//��������Ԫ��
		for (auto des = first_free - 1; des != first; --des) {
			alloc.destroy(des);     
		}
		//�ͷ��ڴ�
		alloc.deallocate(first, last - first);
	}
	*/

	//ʹ��for_each()��lambda���ʽ,�����������
	if (first) {
		std::for_each(first, first_free, [this](std::string &rhs) {alloc.destroy(&rhs); });
		alloc.deallocate(first, last - first);
	}
}

void StrVec::reallocate()
// 1 Ϊһ���µġ������string��������ڴ�
// 2 ���¿ռ��ǰһ���ֹ�����󣬱�������Ԫ��
// 3 ����ԭ�ڴ�ռ��Ԫ�أ��ͷ��ڴ�
{
	//��������ռ�Ĵ�С
	auto newcapacity = size() ? 2 * size() : 1;
	//�������ڴ�
	auto newdata = alloc.allocate(newcapacity);
	//�����ݴӾ��ڴ��ƶ������ڴ�
	auto dest = newdata;     //ָ������������һ������Ԫ��
	auto fst = first;        //ָ�����������һ��Ԫ��
	for (size_t i = 0; i != size(); i++)
		alloc.construct(dest++, std::move(*fst++));
	free();                  //���֮���ͷž��ڴ�ռ�
	//�������ݽṹ��ִ����Ԫ��
	first = newdata;
	first_free = dest;
	last = first + newcapacity;
}
