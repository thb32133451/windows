#include "Quote.h"

double Bulk_quote::net_price(std::size_t n) const
{
	if (n > min_qty)
		return n * (1 - discount) * price;
	else
		return n * price;
}

double print_total(std::ostream &os, const Quote &item, std::size_t n) {
	auto final_price = item.net_price(n);
	os << "The book " << item.isbn() << " need " << final_price << "." << std::endl;
	return final_price;
}