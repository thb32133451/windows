#ifndef _TEXTQUERY_H
#define _TEXTQUERY_H

#include <map>
#include <set>
#include <sstream>
#include <iterator>
#include "StrBlob.h"
using size_type = std::vector<std::string>::size_type;

class QueryResult {                                     //����TextQuery.query()�Ĳ�ѯ���
public:
	QueryResult(std::string s, std::shared_ptr<strBlob> svec, std::shared_ptr<std::set<size_type>> sset) :word(s), file(svec), line_number(sset) {}      //�ҵ�ָ��stringʱ�Ĺ��캯��
	friend std::ostream& operator<<(std::ostream &os, const QueryResult &result);              //��ӡ��ѯ�������Ԫ����

	std::set<size_type>::const_iterator begin() const { return line_number->cbegin(); }
	std::set<size_type>::const_iterator end() const { return line_number->cend(); }
	const std::shared_ptr<strBlob> get_file() const { return file; }

	std::set<size_type>::iterator begin() { return line_number->begin(); }
	std::set<size_type>::iterator end() { return line_number->end(); }
	std::shared_ptr<strBlob> get_file() { return file; }

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
