#include <iostream>
#include <iterator>
#include <vector>
int main(){
	using namespace std;
	int copy[10];
	vector<int> cut;
	for (int i = 0; i != 10; ++i) {
		cut.push_back(i);
	}
	cout << cut.size() << endl;;
	for (auto i : cut)
		cout << i<<"  ";
	cout << endl;
	for (int i = 0; i != cut.size(); ++i) {
		copy[i] = cut[i];
	}
	for (auto i : copy)
		cout << i<<"  ";
	std::cin.get();
	return 0;
}