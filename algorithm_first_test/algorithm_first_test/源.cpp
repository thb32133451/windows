#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <numeric>
#include <iterator>
using namespace std;
void elimDups(vector<int> &vec);
void elimDups(vector<int> &vec) {
	sort(vec.begin(), vec.end());
	auto end_unique = unique(vec.begin(), vec.end());
	vec.erase(end_unique, vec.end());
}

int main() {
	vector<int> vi = { 1,2,1,2,1,2,1,2,1,2,4,5,4,5,7,8,9,6,3,6,5,4,7,41,2,6,456,1351,56,4,321,51,1,1,5,2,7,546,1,5,63,16,4,135,15,2,321,31,88,55,5,1,1,1,1,1,1,1,1,1 };
	string s;
	list<int> li;
	int num = 1;
	for (auto i : vi)
		s.push_back(i);
	for (auto beg = vi.begin(); beg != vi.end(); beg++) {
		beg = find(beg, vi.end(), num);
		if (beg != vi.end())
			li.push_back(*beg);
	}
	for (auto i : li)
		cout << i << " ";
	cout << endl <<vi.size()<<" "<< li.size() << "  " << count(vi.begin(), vi.end(), num) << endl;
	cout << "ºÍ" << accumulate(vi.cbegin(), vi.cend(), 0) << endl;

	/*fill_n(vi.begin(), vi.size(), 0);
	for (auto i : vi)
		cout << i << " ";*/

	/*cout << endl;
	vector<int> vec;
	list<int> lst;
	int i;
	while (cin >> i)
		lst.push_back(i);
	copy(lst.cbegin(),lst.cend(), back_inserter(vec));
	for (auto i : vec)
		cout << i << " ";*/

	cout<< endl;
	elimDups(vi);
	for (auto i : vi)
		cout << i << " ";
	cout << endl << vi.size();
	system("pause");
	return 0;
}
