#include <iostream>
#include "sales_data.h"
#include <string>
using namespace std;

int main() {
	unsigned cnt = 0;
	double price = 0.0;
	string s = "this";
	Sales_data saledata{ s,cnt,price };
	Sales_data s1{"that"};
	Sales_data s2{};
	Sales_data s3{ cin };
	cin.get();	
	cin.get();
	return 0;
}