#include "basket.h"

double Basket::total_receipt(std::ostream &os) const
{
	double sum = 0.0;
	for (auto beg = items.cbegin(); beg != items.cend(); beg=items.upper_bound(*beg)) {
		sum += print_total(os, **beg, items.count(*beg));
	}
	os << "Total sales " << sum << std::endl;
	return sum;
}

