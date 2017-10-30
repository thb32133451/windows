#ifndef _SALES_DATA
#define _SALES_DATA
#include <string>
using std::endl;
class Sales_data {
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::istream &read(std::istream &, Sales_data &);
	friend std::ostream &print(std::ostream &, const Sales_data &);
private:
	double avg_price()const { return units_sold ? revenue / units_sold : 0; }
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
public:
	Sales_data() :Sales_data("", 0, 0) { std::cout << "using default"<<endl; }
	Sales_data(const std::string &s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(n*p) { std::cout << "using three"<<endl; }
	Sales_data(const std::string &s) :Sales_data(s, 0, 0) { std::cout << "using one string"<<endl; }
	Sales_data(std::istream&is):Sales_data(){ read(is, *this); std::cout << "using one istream"<<endl; }
	
	std::string isbn()const { return bookNo; }
	Sales_data &combine(const Sales_data&);
};

Sales_data add(const Sales_data&, const Sales_data&);
std::istream &read(std::istream &, Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);
#endif