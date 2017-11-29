#ifndef _TEXTQUERY_H
#define _TEXTQUERY_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <sstream>
#include "StrBlob.h"
using size_type = std::vector<std::string>::size_type;

class QueryResult {                                     //����TextQuery.query()�Ĳ�ѯ���
public:
	QueryResult(std::string s, std::shared_ptr<strBlob> svec, std::shared_ptr<std::set<size_type>> sset) :word(s), file(svec), line_number(sset) {}      //�ҵ�ָ��stringʱ�Ĺ��캯��
	friend std::ostream& print(std::ostream &os, const QueryResult &result);              //��ӡ��ѯ�������Ԫ����

	std::set<size_type>::iterator begin() { return line_number->begin(); }         //��ȡָ����ѯ���ص��кŵ�set���׵�����
	std::set<size_type>::iterator end() { return line_number->end(); }             //��ȡָ����ѯ���ص��кŵ�set��β�������
	std::shared_ptr<strBlob> get_file()const { return file; }                     //��ȡ����������ļ�
private:
	std::string word;                                   //Ҫ��ѯ�ĵ���
	std::shared_ptr<strBlob> file;     //������ļ�
	std::shared_ptr<std::set<size_type>> line_number;        //���ʳ��ֵ��к�

};




class TextQuery {                                       //���������ļ�,�������������к�֮��Ĺ���map
public:
	QueryResult query(const std::string &s) const;                   //��ѯ����s������QueryResult��ѯ���
	TextQuery() {};
	explicit TextQuery(std::ifstream &infile);
	
private:
	std::shared_ptr<strBlob> input_file;                           //ʹ��StrBlob�ౣ�������ÿһ���ı�
	std::map<std::string, std::shared_ptr<std::set<size_type>>> word_lineSet;     //���浥�ʳ��ֵ��к�
};

#endif // _TEXTQUERY_H
