#ifndef _STRVEC_H
#define _STRVEC_H

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>   //allocator��������ͷ�ļ�
#include <utility>  //std::move��׼�⺯������ͷ�ļ�

class StrVec {

public:
	StrVec()          //allocator��Աʹ��Ĭ�ϳ�ʼ��
		:first(nullptr), first_free(nullptr), last(nullptr) {}       //������Աʹ�ÿ�ָ���ʼ��
	StrVec(const StrVec &hs);        //�������캯��
	StrVec& operator=(const StrVec &rhs);    //�������������
	~StrVec();                       //��������
	void push_back(const std::string &s);             //����Ԫ��
	size_t size() const { return first_free - first; }      //����ʵ����ʹ�ÿռ�������ٸ�Ԫ��
	size_t capacity() const { return last - first; }        //�����ѷ���ռ��������Ԫ������
	//begin()��end() ����const�޶����Դ���const StrVec����
	std::string *begin() const { return first; }            
	std::string *end() const { return first_free; }
	
	//�κ���ҵ
	void reserve(size_t &n);        //��������������n��Ԫ�ص��ڴ�ռ�
	void resize(size_t &n);                                  //������С
	void resize(size_t n, const std::string &s);             //resize()����һ���汾
	//��׼���������resize()�ķ��� ,�����Ƕ���void resize(size_t n, const std::string &s = std::string())
	//����initializer<string>��Ϊ�����Ĺ��캯��
	StrVec(std::initializer_list<std::string> slst);

	//�ƶ����캯�����ƶ���ֵ�����
	StrVec(StrVec &&s) noexcept;   //noexpect��ʾ���׳��κ��쳣
	StrVec& operator=(StrVec &&s) noexcept;
private:
	static std::allocator<std::string> alloc;    //���ڷ���Ԫ�صľ�̬allocator���Ա
	//��̬��Ա������������Ӧ.cpp�ļ��У����������Ϊ���������
	//�����Ԫ�صĺ�����ʹ��
	void check_n_alloc()
	{
		if (size() == capacity()) reallocate();
	}
	//���������캯������ֵ���������������ʹ�õĹ��ߺ���
	std::pair<std::string *, std::string *> alloc_n_copy(const std::string*, const std::string *);
	void free();                    //����Ԫ�ز��ͷ��ڴ�
	void reallocate();              //��ø����ڴ沢��������Ԫ��
	std::string *first;               //ָ��������Ԫ��
	std::string *first_free;        //ָ�������һ������Ԫ��
	std::string *last;               //ָ�������һ��β��Ԫ��
};

#endif // !_STRVEC_H
