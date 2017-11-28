#ifndef _TEXTQUERY_H
#define _TEXTQUERY_H
 
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <sstream>
 
class QueryResult {                                     //����TextQuery.query()�Ĳ�ѯ���
public:
 	QueryResult() {}
 	QueryResult(std::string s) :word(s), file(nullptr), line_number(nullptr) {}
 	QueryResult(std::string s, std::shared_ptr<std::vector<std::string>> svec, std::shared_ptr<std::set<std::size_t>> sset) :word(s), file(svec), line_number(sset) {}
 	friend std::ostream &print(std::ostream &os, QueryResult &result);
private:
 	std::string word;                                   //Ҫ��ѯ�ĵ���
 	std::shared_ptr<std::vector<std::string>> file;     //������ļ�
 	std::shared_ptr<std::set<std::size_t>> line_number;        //���ʳ��ֵ��к�
 
};
 
 
 
 
class TextQuery {                                       //���������ļ�,�������������к�֮��Ĺ���map
public:
	QueryResult query(const std::string s) const;                   //��ѯ����s������QueryResult��ѯ���
 	TextQuery() {};
 	explicit TextQuery(std::ifstream &infile);
 	
private:
 	std::shared_ptr<std::vector<std::string>> input_file;                           //���������ÿһ���ı�
 	std::map<std::string, std::shared_ptr<std::set<std::size_t>>> word_lineSet;     //���浥�ʳ��ֵ��к�
};
 
#endif // _TEXTQUERY_H 