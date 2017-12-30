#ifndef _BASKET_H
#define _BASKET_H

#include <vector>
#include <memory>
#include <set>
#include <iostream>
#include "Quote.h"

class Basket {           //��������
public:
	//ʹ�úϳɵ�Ĭ�Ϲ��캯���뿽�����Ƴ�Ա
	void add_items(const Quote &sale) { items.insert(std::shared_ptr<Quote>(sale.clone())); }
	void add_items(Quote &&sale) { items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); }
	//��ӡÿ������ܼۼ���������������ļ۸�
	double total_receipt(std::ostream &)const;
private:
	static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs) { return lhs->isbn() < rhs->isbn(); }
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{ compare };
	
};

#endif // !_BASKET_H
