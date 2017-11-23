#include <map>
#include <set>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

void find_cout(multimap<string, string> &writer, const string &auther);

void find_cout(multimap<string, string> &writer,const string &auther) {
	auto result = writer.find(auther);
	if (result != writer.end())
		cout << result->first << "  " << result->second << endl;;
}

int main() {
	multimap<string, string> writer = { {"1","22"}, {"1","11"},{"1","33"}, {"5","2"}, {"5","3"}, {"7","8"}, {"9","10"}, {"7","11"}, {"7","11"}, {"6","66"}, {"6","33"} };
	for (auto beg = writer.begin(); beg != writer.end(); beg++)
		find_cout(writer, beg->first);
	system("pause");
	return 0;
}