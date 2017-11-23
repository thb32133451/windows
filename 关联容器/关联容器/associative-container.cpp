#include <map>
#include <set>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std; 

int use_map(void);
int use_set(void);
void practice11_7();                  //11.2.1����ϰ3
bool compare(const int &i1, const int &i2);

int use_map(void) {                   //ͳ��ÿ�����ʳ��ֵĴ���
	map<string, size_t> word_count;   //string��size_t�Ŀ�map
	string word;
	while (cin >> word && word!="q")
		++word_count[word];
	for (const auto &i : word_count)
		cout << i.first << " occurs " << i.second << ((i.second) > 1 ? " times" : " time") << endl;
	system("pause");
	return 0;
}

int use_set(void) {                   //ͳ��ÿ�����ʳ��ֵĴ���,����set�еĵ���
	map<string, size_t> word_count;   //string��size_t�Ŀ�map
	set<string> exclude = { "the" ,"but" ,"and" ,"or" ,"an" ,"a" ,
						    "The" ,"But" ,"And" ,"Or" ,"An" ,"A" };
	string word;
	while (cin >> word && word != "q") {
		if (exclude.find(word) == exclude.end())    //ͳ�Ʋ�������exclude�еĵ���
			++word_count[word];
	}
	for (const auto &i : word_count)
		cout << i.first << " occurs " << i.second << ((i.second) > 1 ? " times" : " time") << endl;
	system("pause");
	return 0;
}

void practice11_7() {
	map<string, vector<string>> family;
	string first_name, last_name;
	while (cin >> first_name >> last_name)
		family[first_name].push_back(last_name);
}
bool compare(const int &i1, const int &i2) {
	return i1 < i2;
}
//int main() {
//	multiset<int, decltype(compare)*> bookstore(compare);
//	multiset<int, bool(*)(const int&,const int&)>::iterator beg = bookstore.begin();
//}