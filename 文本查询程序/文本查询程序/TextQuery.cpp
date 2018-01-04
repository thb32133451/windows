#include <fstream>
#include "TextQuery.h"

QueryResult TextQuery::query(const std::string &s) const
{
	auto result = word_lineSet.find(s);                   //��ѯ���
	static std::shared_ptr<std::set<size_type>> no_data(new std::set<size_type>);
	if (result != word_lineSet.end())
	{                     //���ڵ���s
		QueryResult t_yes(s, input_file, result->second);
		return t_yes;
	}
	else {                                            
		QueryResult t_no(s, input_file, no_data);
		return t_no;
	}

}

//TextQuery::TextQuery(std::ifstream &infile):input_file(new strBlob)              //����һ��ifstream�Ĺ��캯��
//{
//	std::string Line;                                      //�洢���ı�
//	size_type lineNumber = 1;                              //�к�
//	while (std::getline(infile, Line)) {                   //getlineλ��ͷ�ļ�fstream
//		input_file->push_back(Line);                       //����������ӵ�vector<string>��
//		std::stringstream stream(Line);                    //���ı�Line�󶨵�stringstream
//		std::string word;                                  //��stream��ȡ�ĵ���
//		while (stream >> word) {
//			auto &check = word_lineSet[word];         //check�ǹؼ���Ϊword��Ԫ�ض�Ӧ��shared_ptr<set<size_t>>��check����������
//			if (!check)                                  //��һ�������������ʱ����ָ��Ϊ��
//				check.reset(new std::set<size_type>);
//			check->insert(lineNumber);
//		}
//		++lineNumber;                                      //����
//	}
//}


TextQuery::TextQuery(std::ifstream &infile) :input_file(new strBlob)              //�����Ծ��Ӵ����Ϊ��ѯ��λ�İ汾
{
	std::string sentence;                                      //�洢���ı�
	size_type sentenceNumber = 1;                              //��ı��
	std::istream_iterator<char> str_it(infile);
	std::istream_iterator<char> str_end;
	auto it = str_it;
	while (str_it!=str_end) {                
		sentence.push_back(*str_it++);
		if (*(sentence.cend() - 1) == char('.')) {
			input_file->push_back(sentence);                       //����������ӵ�vector<string>��

			std::stringstream stream(sentence);                    //���ı�sentence�󶨵�stringstream
			std::string word;                                  //��stream��ȡ�ĵ���
			while (stream >> word) {
				auto &check = word_lineSet[word];         //check�ǹؼ���Ϊword��Ԫ�ض�Ӧ��shared_ptr<set<size_t>>��check����������
				if (!check)                                  //��һ�������������ʱ����ָ��Ϊ��
					check.reset(new std::set<size_type>);
				check->insert(sentenceNumber);
			}
			sentence=std::string();
			++sentenceNumber;                                      //����
		}
	}
}

std::ostream & operator<<(std::ostream & os, const QueryResult & result)
{
	if (result.file!=nullptr)                                                   //���ҽ����Ϊ��
	{
		os << "( " << result.word << " )" << " occurs " << result.line_number->size() << " times:" << std::endl;       //������ִ���=line_number��Ա��ָset��size����
		auto beg_file = result.file->begin();                                                          //����ָ��file��ָ���vector<string>���׵�����
		for (auto beg = result.line_number->begin(); beg != result.line_number->end(); beg++)
			os << "(line " << *beg << ") " << *(beg_file + (*beg) - 1) << std::endl;                         //������������������ı�
	}
	else                     //δ�ҵ���Ӧ����
		os << "can not find " << result.word << std::endl;
	return os;
	// TODO: �ڴ˴����� return ���
}
