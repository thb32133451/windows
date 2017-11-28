#ifndef _TEXTQUERY_H
#define _TEXTQUERY_H
 
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <sstream>
 
class QueryResult {                                     //保存TextQuery.query()的查询结果
public:
 	QueryResult() {}
 	QueryResult(std::string s) :word(s), file(nullptr), line_number(nullptr) {}
 	QueryResult(std::string s, std::shared_ptr<std::vector<std::string>> svec, std::shared_ptr<std::set<std::size_t>> sset) :word(s), file(svec), line_number(sset) {}
 	friend std::ostream &print(std::ostream &os, QueryResult &result);
private:
 	std::string word;                                   //要查询的单词
 	std::shared_ptr<std::vector<std::string>> file;     //输入的文件
 	std::shared_ptr<std::set<std::size_t>> line_number;        //单词出现的行号
 
};
 
 
 
 
class TextQuery {                                       //保存输入文件,并建立单词与行号之间的关联map
public:
	QueryResult query(const std::string s) const;                   //查询单词s，返回QueryResult查询结果
 	TextQuery() {};
 	explicit TextQuery(std::ifstream &infile);
 	
private:
 	std::shared_ptr<std::vector<std::string>> input_file;                           //保存输入的每一行文本
 	std::map<std::string, std::shared_ptr<std::set<std::size_t>>> word_lineSet;     //保存单词出现的行号
};
 
#endif // _TEXTQUERY_H 