#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "vec.h"
using std::cout;

template <typename T>
void print_f(const T& s) {
	typename T::size_type n = s.size();
	for (typename T::size_type i = 0; i != n; ++i)
		std::cout << s[i] << std::endl;
}

template <typename T, typename U>
T find(const U& val,const T& beg,const T& end) {
	for (auto it = beg; it != end; ++it) {
		if (*it == val) return it;
	}
	return end;
}

template <typename T>
void print(const T& arr) {
	for (auto i : arr) {
		std::cout << i << std::endl;
	}
}

class DebugDelete {
public:
	DebugDelete(std::ostream& o) :os(o) {}
	template <typename IT> void operator()(IT* p) { os << "deleting uniqe_ptr" << std::endl; delete p; }
private:
	std::ostream &os;
};

int main() {
	/*std::list<std::string> lst{ "sh","vec", "str", "std", "int", "double", "vector", "cin", "cout", "beg", "end" };
	std::vector<int> vec{ 1,2,3,4,5,6,7,8,9,1,10,12,13,46,79,58,46,36,41,2,31,564,12,32,74,6,25 };

	auto it = find(std::string("std"), lst.begin(), lst.end());

	if (it != lst.cend())
		cout << *it << std::endl;
	else cout << "can not find \"" << std::string("std") << "\"." << std::endl;*/
	Vec<std::string> svec = { "sh","vec", "str", "std", "int", "double", "vector", "cin", "cout", "beg", "end" };
	svec.push_back("гЂал");
	auto beg = svec.begin();
	for (; beg != svec.end(); ++beg)
		cout << *beg << std::endl;

	Vec<std::string> v;
	auto && k = std::move(svec);
	v = std::move(k);

	beg = v.begin();
	for (; beg != v.end(); ++beg)
		cout << *beg << std::endl;

	std::cout << std::endl;
	print_f(v);

	std::cin.get();
	return 0;
}