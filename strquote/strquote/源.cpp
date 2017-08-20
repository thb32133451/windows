#include <iostream>
#include <string>
using namespace std;

string version1(const string & s1, const string & s2);
const string & version2(const string & s1, const string & s2);


int main() {

	string result;
	string copy = "Enrer a string.";

	result = version1(copy, "###");
	cout << result << endl;
	result = version2(copy, "###");
	cout << result << endl;
	cin.get();
	return 0;
}

string version1(const string & s1, const string & s2) {
	string temp;

	temp = s2 + s1 + s2;
	return temp;
}

const string & version2(const string & s1, const string & s2) {
	string temp;

	temp = s2 + s1 + s2;
	return temp;
}
