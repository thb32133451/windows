#ifndef _QUOTE_H
#define _QUOTE_H

#include <string>
#include <iostream>



class Quote {
public:
	Quote() = default;
	Quote(const std::string & book, double sales_price):bookNo(book), price(sales_price) {}
	std::string isbn() const { return bookNo; }
	//返回给定数量书籍的销售总金额
	//并由派生类负责改写并使用不同的折扣计算算法
	virtual double net_price(std::size_t n) const { return n*price; }             
	virtual ~Quote() = default;             //对析构函数进行动态绑定
	virtual void debug(std::ostream &os)const { os << "bookNo: " << isbn() << " ,price: " << price << "   "; }
	bool operator!=(const Quote & rhs)const { if (this->isbn() != rhs.isbn()) return true; else return false; }

	Quote(const Quote &rhs) :bookNo(rhs.bookNo), price(rhs.price) { std::cout << "Quote的拷贝构造" << std::endl; }
	Quote(Quote &&rhs) noexcept : bookNo(std::move(rhs.bookNo)), price(std::move(rhs.price)) { std::cout << "Quote的移动构造" << std::endl; }
	Quote & operator=(const Quote &rhs) { 
		if (*this != rhs)         //处理自赋值
		{
			bookNo = rhs.bookNo;
			price = rhs.price;
		}
		std::cout << "Quote的拷贝赋值" << std::endl;
		return *this;
	}
	
	Quote & operator=(Quote &&rhs) {
		if (*this != rhs) {
			bookNo = std::move(rhs.bookNo);
			price = std::move(rhs.price);
		}
		std::cout << "Quote的移动赋值" << std::endl;
		return *this;
	}

	//返回当前对象的一份动态分配的拷贝
	virtual Quote* clone() const & { return new Quote(*this); }
	virtual Quote* clone() && {return new Quote(std::move(*this)); }
private:
	std::string bookNo;       //书籍的isbn编号
protected:
	double price = 0.0;       //普通不打折状态下的价格
};

class Disc_quote :public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string & book, double sales_price, std::size_t min_size, double sales_discount) :
		       Quote(book, sales_price), min_qty(min_size), discount(sales_discount) {};
	double net_price(std::size_t n) const = 0;      //=0表示这是一个纯虚函数，没有其他任何内容
protected:
	std::size_t min_qty = 0;
	double discount = 0.0;
};

//class Bulk_quote :public Quote {           //定义使用public关键字继承Quote类的Bulk_quote类
//public:
//	Bulk_quote() = default;
//	Bulk_quote(const std::string & book, double sales_price, std::size_t min_size, double sales_discount):
//		Quote(book, sales_price), min_qty(min_size), discount(sales_discount) {};
//	double net_price(std::size_t n) const override;
//	void debug(std::ostream &os)const override{ os << "bookNo: " << isbn() << " ,price: " << price <<" ,min_qty: "<<min_qty<<" ,discount: "<<discount<<"   "; }
//private:
//	std::size_t min_qty = 0;     //满足折扣条件的最小购买数
//	double discount = 0.0;       //折扣额
//};

class Bulk_quote :public Disc_quote {               //重新定义继承Disc_quote的Bulk_quote类
public:
	Bulk_quote() = default;
	using Disc_quote::Disc_quote;      //继承Disc_quote的构造函数
	/*Bulk_quote(const std::string & book, double sales_price, std::size_t min_size, double sales_discount) :
		Disc_quote(book, sales_price, min_size, sales_discount) {};*/
	double net_price(std::size_t n) const override;           //覆盖基类中的函数版本已实现新的折扣策略
	void debug(std::ostream &os)const override { os << "bookNo: " << isbn() << " ,price: " << price << " ,min_qty: " << min_qty << " ,discount: " << discount << "   "; }

	Bulk_quote(const Bulk_quote &rhs) :Disc_quote(rhs.isbn(),rhs.price,rhs.min_qty,rhs.discount) { std::cout << "Bulk_quote的拷贝构造" << std::endl; }
	Bulk_quote(Bulk_quote &&rhs) noexcept : Disc_quote(rhs.isbn(), std::move(rhs.price), std::move(rhs.min_qty), std::move(rhs.discount)) { std::cout << "Bulk_quote的移动构造" << std::endl; }
	Bulk_quote & operator=(const Bulk_quote &rhs) {
		if (*this != rhs)         //处理自赋值
		{
			Quote::operator=(rhs);
			min_qty = rhs.min_qty; 
			discount = rhs.discount;
		}
		std::cout << "Bulk_quote的拷贝赋值" << std::endl;
		return *this;
	}

	Bulk_quote & operator=(Bulk_quote &&rhs) {
		if (*this != rhs) {
			Quote::operator=(rhs);
			min_qty = std::move(rhs.min_qty);
			discount = std::move(rhs.discount);
		}
		std::cout << "Bulk_quote的移动赋值" << std::endl;
		return *this;
	}

	//返回当前对象的一份动态分配的拷贝
	Bulk_quote* clone() const & { return new Bulk_quote(*this); }
	Bulk_quote* clone() && {return new Bulk_quote(std::move(*this)); }
	
};

double print_total(std::ostream &os, const Quote &item, std::size_t n);

#endif // !_QUOTE_H
