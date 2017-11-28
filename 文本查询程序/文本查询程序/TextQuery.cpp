#include "TextQuery.h"
#include <iostream>
#include <fstream>

QueryResult TextQuery::query(const std::string s) const
{
	auto result = word_lineSet.find(s);                   //查询结果
	if (result != word_lineSet.end())
	{                     //存在单词s
		QueryResult t_yes(s, input_file, result->second);
		return t_yes;
	}
	else {                                            //若未找到单词s，返回只由s构造的QueryResult，其他成员为空
		QueryResult t_no(s);
		return t_no;
	}

}

TextQuery::TextQuery(std::ifstream &infile):input_file(new std::vector<std::string>)              //接受一个ifstream的构造函数
{
	std::string Line;                                      //存储行文本
	std::size_t lineNumber = 1;                            //行号
	while (std::getline(infile, Line)) {                   //getline位于头文件fstream
		input_file->push_back(Line);                       //将行输入添加到vector<string>中
		std::stringstream stream(Line);                    //行文本Line绑定到stringstream
		std::string word;                                  //从stream读取的单词
		while (stream >> word) {
			auto &check = word_lineSet[word];         //check是关键字为word的元素对应的shared_ptr<set<size_t>>
			if (!check)                                  //第一次遇到这个单词时，此指针为空
				check.reset(new std::set<std::size_t>);
			check->insert(lineNumber);
		}
		++lineNumber;                                      //换行
	}
}

std::ostream & print(std::ostream & os, QueryResult & result)
{
	if (result.file!=nullptr)                                                   //查找结果不为空
	{
		os << result.word << " occurs " << result.line_number->size() << " times:" << std::endl;       //输出出现次数=line_number成员所指set的size（）
		auto beg_file = result.file->begin();                                                          //智能指针file所指向的vector<string>的首迭代器
		for (auto beg = result.line_number->begin(); beg != result.line_number->end(); beg++)
			os << "(line " << *beg << ") " << *(beg_file + (*beg) - 1) << std::endl;                         //输出单词所在行完整文本
	}
	else                     //未找到对应单词
		os << "can not find " << result.word << std::endl;
	return os;
	// TODO: 在此处插入 return 语句
}
