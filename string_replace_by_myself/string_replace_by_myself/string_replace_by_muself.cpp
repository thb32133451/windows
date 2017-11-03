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
	string oldval = "zxc", newval = "00000000000000";
	rewrite(str, oldval, newval);
	cout << str;
	std::cin.get();
}

void rewrite(string& _s, string oldVal, string newVal) {
	for (size_t i = 0; i != _s.size() - oldVal.size() + 1; ++i) {
		if (_s[i] == oldVal[0]) {
			if (_s.substr(i, oldVal.size()) == oldVal)
				_s.replace(i, oldVal.size(), newVal);
		}
	}
}