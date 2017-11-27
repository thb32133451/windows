#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <new>
using namespace std;

//vector<int> *new_vector_int();                                          //使用new的版本
//vector<int> *input(vector<int> *vec);
//void print(vector<int> *vec);
//
//vector<int> *new_vector_int() {
//	return new vector<int>;
//}
//
//vector<int> *input(vector<int> *vec) {
//	int i;
//	while (cin >> i)
//		vec->push_back(i);
//	return vec;
//}
//
//void print(vector<int> *vec) {
//	for (auto i : *(vec))
//		cout << i << endl;
//	delete vec;
//	vec = nullptr;
//}
//
//int main() {
//	print(input(new_vector_int()));
//	
//	system("pause");
//	return 0;
//}

shared_ptr<vector<int>> new_shared_ptr_vector_int();                      //使用shared_ptr
shared_ptr<vector<int>> input(shared_ptr<vector<int>> vec);
void print(shared_ptr<vector<int>> vec);

shared_ptr<vector<int>> new_shared_ptr_vector_int() {
	return make_shared<vector<int>>();
}

shared_ptr<vector<int>> input(shared_ptr<vector<int>> vec) {
	int i;
	while (cin >> i)
		vec->push_back(i);
	return vec;
}

void print(shared_ptr<vector<int>> vec) {
	for (auto i : *(vec))
		cout << i << endl;
}

void process(shared_ptr<int> ptr);
void process(shared_ptr<int> ptr) {
	cout << *ptr << endl;
}

int main() {
	//print(input(new_shared_ptr_vector_int()));

	/*shared_ptr<int> p(new int(42));
	process(shared_ptr<int>(p));
	cout << *p << endl;*/

	auto sp = make_shared<int>();
	auto p = sp.get();
	

	system("pause");
	return 0;
}