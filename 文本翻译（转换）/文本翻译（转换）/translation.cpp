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

map<string, string> build_map(ifstream & map_file) {     //缺陷：使用下标运算符实现map元素添加，忽略了一个关键字在转换规则文件中多次使用的情况
														 //这时，该关键字转换规则为关键字最后一次出现时对应的转换规则
	map<string, string> trans_map;                 //保存转换规则的map
	string key;                                    //关键字，即要转换的值
	string value;								   //转换后的值	
	while (map_file >> key && getline(map_file, value)) {   //读取第一个单词存入key中，剩余内容存入value中
		if (value.size() > 1)
			trans_map[key] = value.substr(1);      //substr(1)用于跳过中间的空格
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
	auto trans_map = build_map(map_file);  //保存转换规则
	string str;							   //保存输入中的每一行
	while (getline(input, str)) {
		istringstream stream(str);         //istringstream位于sstream头文件
		string word;
		bool firstword = true;             //控制是否打印空格
		while (stream >> word) {
			if (firstword)
				firstword = false;
			else
				cout << " ";
			//transform返回他的第一个参数或其转换之后的形式
			cout << transform(word, trans_map);   //打印输出
		}
		cout << endl;                      //完成一行的转换
	}
}

int main(int argc,char *argv[]) {
	ifstream map_file(argv[1]);
	ifstream input(argv[2]);
	if (map_file) {
		if (input) 
			word_translation(map_file, input);         //未检查输入文件内容合法性，程序健壮性差
		else
			cerr << "Could not open file: " + string(argv[2]);
	}
	else
		cerr << "Could not open file: " + string(argv[1]);
	return 0;
}
