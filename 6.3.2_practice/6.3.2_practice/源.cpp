#include<iostream>
#include<vector>
void print(std::vector<int>::iterator beg, std::vector<int>::iterator end) {
	if (beg != end) {
		std::cout << *beg << std::endl;
		print(++beg, end);
	}
}

int main() {
	using namespace std;
	vector<int> ia = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
	auto beg = ia.begin(), end = ia.end();
	void (*func)(std::vector<int>::iterator beg, std::vector<int>::iterator end) = print ;
	func(beg, end);
	cin.get();
}