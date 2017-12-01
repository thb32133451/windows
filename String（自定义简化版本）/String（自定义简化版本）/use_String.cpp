#include <vector>
#include "String.h"
using namespace std;

int main() {
	String s("const");
	String a;
	a = s;
	vector<String> vec;
	vec.push_back(s);
	vec.push_back(s);
	vec.push_back(s);
	vec.push_back(s); 
	/*vec.push_back(s);*/
	vec.push_back(String("vector"));
	system("pause");
	return 0;
}