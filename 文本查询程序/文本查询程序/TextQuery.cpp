#include "TextQuery.h"
#include <iostream>
#include <fstream>

QueryResult TextQuery::query(const std::string s) const
{
	auto result = word_lineSet.find(s);                   //��ѯ���
	if (result != word_lineSet.end())
	{                     //���ڵ���s
		QueryResult t_yes(s, input_file, result->second);
		return t_yes;
	}
	else {                                            //��δ�ҵ�����s������ֻ��s�����QueryResult��������ԱΪ��
		QueryResult t_no(s);
		return t_no;
	}

}

TextQuery::TextQuery(std::ifstream &infile):input_file(new std::vector<std::string>)              //����һ��ifstream�Ĺ��캯��
{
	std::string Line;                                      //�洢���ı�
	std::size_t lineNumber = 1;                            //�к�
	while (std::getline(infile, Line)) {                   //getlineλ��ͷ�ļ�fstream
		input_file->push_back(Line);                       //����������ӵ�vector<string>��
		std::stringstream stream(Line);                    //���ı�Line�󶨵�stringstream
		std::string word;                                  //��stream��ȡ�ĵ���
		while (stream >> word) {
			auto &check = word_lineSet[word];         //check�ǹؼ���Ϊword��Ԫ�ض�Ӧ��shared_ptr<set<size_t>>
			if (!check)                                  //��һ�������������ʱ����ָ��Ϊ��
				check.reset(new std::set<std::size_t>);
			check->insert(lineNumber);
		}
		++lineNumber;                                      //����
	}
}

std::ostream & print(std::ostream & os, QueryResult & result)
{
	if (result.file!=nullptr)                                                   //���ҽ����Ϊ��
	{
		os << result.word << " occurs " << result.line_number->size() << " times:" << std::endl;       //������ִ���=line_number��Ա��ָset��size����
		auto beg_file = result.file->begin();                                                          //����ָ��file��ָ���vector<string>���׵�����
		for (auto beg = result.line_number->begin(); beg != result.line_number->end(); beg++)
			os << "(line " << *beg << ") " << *(beg_file + (*beg) - 1) << std::endl;                         //������������������ı�
	}
	else                     //δ�ҵ���Ӧ����
		os << "can not find " << result.word << std::endl;
	return os;
	// TODO: �ڴ˴����� return ���
}
