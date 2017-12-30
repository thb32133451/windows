#include <string>
#include <iostream>
#include "basket.h"

int main() {
	Quote book1("T253017", 10.0);
	Bulk_quote book2("T20348512",10.0, 20, 0.3);
	Basket bas;
	bas.add_items(book1);
	bas.add_items(book1);
	bas.add_items(book1);
	bas.add_items(book1);
	bas.add_items(book1);
	bas.add_items(book2);
	bas.add_items(book2);
	bas.add_items(book2);
	bas.add_items(book2);
	bas.add_items(book2);
	bas.add_items(book2);
	bas.add_items(book2);
	bas.add_items(book2);
	bas.add_items(std::move(book2));
	bas.add_items(book2);
	bas.add_items(std::move(book2));
	bas.add_items(book2);
	bas.add_items(std::move(book2));
	bas.add_items(book2);
	bas.add_items(std::move(book2));
	bas.add_items(book2);
	bas.add_items(std::move(book2));
	bas.add_items(book2);
	bas.add_items(std::move(book2));
	bas.add_items(book2);
	bas.add_items(std::move(book2));
	bas.add_items(book2);
	bas.add_items(std::move(book2));
	bas.add_items(book2);
	bas.add_items(std::move(book2));
	bas.add_items(book2);
	bas.add_items(std::move(book2));
	bas.add_items(book2);
	bas.add_items(std::move(book2));
	bas.add_items(std::move(book2));

	bas.total_receipt(std::cout);
	
	system("pause");
	return 0;
}

