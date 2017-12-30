#ifndef _BASKET_H
#define _BASKET_H

#include <vector>
#include <memory>
#include <set>
#include <iostream>
#include "Quote.h"

class Basket {           //购物篮类
public:
	//使用合成的默认构造函数与拷贝控制成员
	void add_items(const Quote &sale) { items.insert(std::shared_ptr<Quote>(sale.clone())); }
	void add_items(Quote &&sale) { items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); }
	//打印每本书的总价及购物篮中所有书的价格
	double total_receipt(std::ostream &)const;
private:
	static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs) { return lhs->isbn() < rhs->isbn(); }
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{ compare };
	
};

#endif // !_BASKET_H
