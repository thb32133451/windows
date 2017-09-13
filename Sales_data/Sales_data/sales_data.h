#ifndef _SALES_DATA
#define _SALES_DATA
#include <string>
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
	Sales_data() = default;
	Sales_data(const std::string &s, unsigned n, double p) :bookNo(s),units_sold(n),revenue(n*p){}
	Sales_data(const std::string &s):bookNo(s){}
	Sales_data(std::istream&);
	std::string isbn()const { return bookNo; }
	Sales_data &combine(const Sales_data&);
};

Sales_data add(const Sales_data&, const Sales_data&);
std::istream &read(std::istream &, Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);
#endif