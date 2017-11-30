#ifndef _STRBLOB_H
#define _STRBLOB_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <initializer_list>

class strBlob {
public:
	typedef std::vector<std::string>::size_type size_type;
	strBlob();
	strBlob(std::initializer_list<std::string> i1);
	size_type size() const { return data->size(); }
	bool empty()const { return data->empty(); }

	//��Ӻ�ɾ��Ԫ��
	void push_back(const std::string &s) { data->push_back(s); }
	void pop_back();

	//Ԫ�ط���
	std::string &front() { return do_front(); }
	std::string &back() { return do_back(); }
	const std::string front() const { return do_front(); }  //front & back���ذ汾�����Խ���const strBlob����Ĳ�������
	const std::string back() const { return do_back(); }
	std::vector<std::string>::iterator begin() { return data->begin(); }
	std::vector<std::string>::iterator end() { return data->end(); }
private:
	std::shared_ptr < std::vector < std::string>> data;
	//���data[i]���Ϸ����׳�һ���쳣
	void check(size_type i, const std::string &msg) const;
	std::string &do_front()const;
	std::string &do_back()const;
};

#endif //_STRBLOB_H
