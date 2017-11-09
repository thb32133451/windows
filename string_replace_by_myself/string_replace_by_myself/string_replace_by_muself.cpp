#include <iostream>
#include <vector>
#include <string>


using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;

void rewrite(string& _s, string oldVal, string newVal);

int main() {
	string str = "zxcvbnmasdfghjklqwertyuiopzxcvbnmasdfghjklqwertyuiop";
	string oldval = "io", newval = "888888";
	rewrite(str, oldval, newval);
	cout << str;
	std::cin.get();
}

void rewrite(string& _s, string oldVal, string newVal) {
	
	/*for (size_t i = 0; i != _s.size() - oldVal.size() + 1; ++i) {             //use об╠Й & replace
		if (_s[i] == oldVal[0]) {
			if (_s.substr(i, oldVal.size()) == oldVal)
				_s.replace(i, oldVal.size(), newVal);
		}
	}*/

	       //use iterator & insert & erase
	bool isFind = true;
	string::iterator _s_beg = _s.begin();
	const string::iterator old_beg = oldVal.begin();
	for (; _s_beg != _s.end()-oldVal.size();++_s_beg) {
		for (unsigned int i = 0; i != oldVal.size(); ++i) {
			if (*(_s_beg + i) == *(old_beg + i) )
				continue;
			else{
				isFind = false;
				break;}}
		if (isFind == true) {
			_s.erase(_s_beg, _s_beg + oldVal.size());
			_s_beg=_s.insert(_s_beg, newVal.begin(), newVal.end())+newVal.size();}	
		else
			isFind = true;
	}
}