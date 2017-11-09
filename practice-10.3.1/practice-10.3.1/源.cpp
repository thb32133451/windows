#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

class Sales_data {
private:
	string name;
	int isbn;
public:
	Sales_data(string s,int n):name(s),isbn(n){}
	Sales_data():name("no name"),isbn(0){}
	int getIsbn() const { return isbn;}
};


void elimDups(vector<string> &vec);
bool isShorter(const string &s1,const string &s2);
bool compareIsbn(Sales_data & s1, Sales_data & s2);
bool isShorterthan5(const string &s);

bool isShorterthan5(const string &s) {
	return s.size() < 5;
}

void elimDups(vector<string>& vec)
{
	sort(vec.begin(), vec.end());                         //按字典顺序排序
	auto end_unique = unique(vec.begin(), vec.end());       //重排输入范围，使每个单词只出现一次，返回指向最后一个不重复单词之后位置的迭代器
	vec.erase(end_unique, vec.end());                       //删除重复单词
}

bool isShorter(const string &s1,const string &s2)
{
	return s1.size() < s2.size();
}

bool compareIsbn(Sales_data & s1, Sales_data & s2) 
{
	return s1.getIsbn()<s2.getIsbn();
}

int main() {
	vector<string> str;
	string s;
	while (cin >> s && s != "q")
		str.push_back(s);

	/*elimDups(str);
	stable_sort(str.begin(),str.end(), isShorter);  
	//使用lambda表达式
	//stable_sort(str.begin(),str.end(),[](const string &s1,const string &s2){return s1.size()<s2.size();});
	for (const auto &i : str)
		cout << i << " ";*/

	auto last_5_words = partition(str.begin(), str.end(), isShorterthan5);
	for (; last_5_words !=str.end(); last_5_words++)
		cout << *last_5_words << endl;

	system("pause");
	return 0;
}

//int main() {
//	vector<Sales_data> vec;
//	string s;
//	int n;
//	while (cin >> s >> n && s != "q")
//		vec.emplace_back(s, n);
//	sort(vec.begin(), vec.end(), compareIsbn);
//	for (const auto &i : vec)
//		cout << i.getIsbn() << " ";
//	system("pause");
//	return 0;
//}