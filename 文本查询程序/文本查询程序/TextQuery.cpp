#include <fstream>
#include "TextQuery.h"

QueryResult TextQuery::query(const std::string &s) const
{
	auto result = word_lineSet.find(s);                   //查询结果
	static std::shared_ptr<std::set<size_type>> no_data(new std::set<size_type>);
	if (result != word_lineSet.end())
	{                     //存在单词s
		QueryResult t_yes(s, input_file, result->second);
		return t_yes;
	}
	else {                                            
		QueryResult t_no(s, input_file, no_data);
		return t_no;
	}

}

//TextQuery::TextQuery(std::ifstream &infile):input_file(new strBlob)              //接受一个ifstream的构造函数
//{
//	std::string Line;                                      //存储行文本
//	size_type lineNumber = 1;                              //行号
//	while (std::getline(infile, Line)) {                   //getline位于头文件fstream
//		input_file->push_back(Line);                       //将行输入添加到vector<string>中
//		std::stringstream stream(Line);                    //行文本Line绑定到stringstream
//		std::string word;                                  //从stream读取的单词
//		while (stream >> word) {
//			auto &check = word_lineSet[word];         //check是关键字为word的元素对应的shared_ptr<set<size_t>>，check必须是引用
//			if (!check)                                  //第一次遇到这个单词时，此指针为空
//				check.reset(new std::set<size_type>);
//			check->insert(lineNumber);
//		}
//		++lineNumber;                                      //换行
//	}
//}


TextQuery::TextQuery(std::ifstream &infile) :input_file(new strBlob)              //建立以句子代替句为查询单位的版本
{
	std::string sentence;                                      //存储句文本
	size_type sentenceNumber = 1;                              //句的编号
	std::istream_iterator<char> str_it(infile);
	std::istream_iterator<char> str_end;
	auto it = str_it;
	while (str_it!=str_end) {                
		sentence.push_back(*str_it++);
		if (*(sentence.cend() - 1) == char('.')) {
			input_file->push_back(sentence);                       //将句输入添加到vector<string>中

			std::stringstream stream(sentence);                    //句文本sentence绑定到stringstream
			std::string word;                                  //从stream读取的单词
			while (stream >> word) {
				auto &check = word_lineSet[word];         //check是关键字为word的元素对应的shared_ptr<set<size_t>>，check必须是引用
				if (!check)                                  //第一次遇到这个单词时，此指针为空
					check.reset(new std::set<size_type>);
				check->insert(sentenceNumber);
			}
			sentence=std::string();
			++sentenceNumber;                                      //换句
		}
	}
}

std::ostream & operator<<(std::ostream & os, const QueryResult & result)
{
	if (result.file!=nullptr)                                                   //查找结果不为空
	{
		os << "( " << result.word << " )" << " occurs " << result.line_number->size() << " times:" << std::endl;       //输出出现次数=line_number成员所指set的size（）
		auto beg_file = result.file->begin();                                                          //智能指针file所指向的vector<string>的首迭代器
		for (auto beg = result.line_number->begin(); beg != result.line_number->end(); beg++)
			os << "(line " << *beg << ") " << *(beg_file + (*beg) - 1) << std::endl;                         //输出单词所在行完整文本
	}
	else                     //未找到对应单词
		os << "can not find " << result.word << std::endl;
	return os;
	// TODO: 在此处插入 return 语句
}
