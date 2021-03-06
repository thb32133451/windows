#ifndef _TEXTQUERY_H
#define _TEXTQUERY_H

#include <map>
#include <set>
#include <sstream>
#include <iterator>
#include "StrBlob.h"
using size_type = std::vector<std::string>::size_type;

class QueryResult {                                     //保存TextQuery.query()的查询结果
public:
	QueryResult(std::string s, std::shared_ptr<strBlob> svec, std::shared_ptr<std::set<size_type>> sset) :word(s), file(svec), line_number(sset) {}      //找到指定string时的构造函数
	friend std::ostream& operator<<(std::ostream &os, const QueryResult &result);              //打印查询结果的友元函数

	std::set<size_type>::const_iterator begin() const { return line_number->cbegin(); }
	std::set<size_type>::const_iterator end() const { return line_number->cend(); }
	const std::shared_ptr<strBlob> get_file() const { return file; }

	std::set<size_type>::iterator begin() { return line_number->begin(); }
	std::set<size_type>::iterator end() { return line_number->end(); }
	std::shared_ptr<strBlob> get_file() { return file; }

private:
	std::string word;                                   //要查询的单词
	std::shared_ptr<strBlob> file;     //输入的文件
	std::shared_ptr<std::set<size_type>> line_number;        //单词出现的行号

};




class TextQuery {                                       //保存输入文件,并建立单词与行号之间的关联map
public:
	QueryResult query(const std::string &s) const;                   //查询单词s，返回QueryResult查询结果
	TextQuery() {};
	explicit TextQuery(std::ifstream &infile);
	
private:
	std::shared_ptr<strBlob> input_file;                           //使用StrBlob类保存输入的每一行文本
	std::map<std::string, std::shared_ptr<std::set<size_type>>> word_lineSet;     //保存单词出现的行号
};

#endif // _TEXTQUERY_H
