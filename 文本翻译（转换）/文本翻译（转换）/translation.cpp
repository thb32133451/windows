#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <fstream>
#include <algorithm>
#include <istream>
#include <sstream>
using namespace std;

void word_translation(ifstream &map_file, ifstream &input);
map<string, string> build_map(ifstream & map_file);
const string transform(const string &s,const map<string, string> &trans_map);

map<string, string> build_map(ifstream & map_file) {     //ȱ�ݣ�ʹ���±������ʵ��mapԪ����ӣ�������һ���ؼ�����ת�������ļ��ж��ʹ�õ����
														 //��ʱ���ùؼ���ת������Ϊ�ؼ������һ�γ���ʱ��Ӧ��ת������
	map<string, string> trans_map;                 //����ת�������map
	string key;                                    //�ؼ��֣���Ҫת����ֵ
	string value;								   //ת�����ֵ	
	while (map_file >> key && getline(map_file, value)) {   //��ȡ��һ�����ʴ���key�У�ʣ�����ݴ���value��
		if (value.size() > 1)
			trans_map[key] = value.substr(1);      //substr(1)���������м�Ŀո�
		else									   
			throw runtime_error("no value for " + key);
	}
	return trans_map;
}

const string transform(const string &s,const map<string, string> &trans_map){
	auto result = trans_map.find(s);
	if (result != trans_map.end())
		return result->second;
	else
		return s;
}

void word_translation(ifstream &map_file, ifstream &input) {
	auto trans_map = build_map(map_file);  //����ת������
	string str;							   //���������е�ÿһ��
	while (getline(input, str)) {
		istringstream stream(str);         //istringstreamλ��sstreamͷ�ļ�
		string word;
		bool firstword = true;             //�����Ƿ��ӡ�ո�
		while (stream >> word) {
			if (firstword)
				firstword = false;
			else
				cout << " ";
			//transform�������ĵ�һ����������ת��֮�����ʽ
			cout << transform(word, trans_map);   //��ӡ���
		}
		cout << endl;                      //���һ�е�ת��
	}
}

int main(int argc,char *argv[]) {
	ifstream map_file(argv[1]);
	ifstream input(argv[2]);
	if (map_file) {
		if (input) 
			word_translation(map_file, input);         //δ��������ļ����ݺϷ��ԣ�����׳�Բ�
		else
			cerr << "Could not open file: " + string(argv[2]);
	}
	else
		cerr << "Could not open file: " + string(argv[1]);
	return 0;
}
