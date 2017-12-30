#ifndef _QUOTE_H
#define _QUOTE_H

#include <string>
#include <iostream>



class Quote {
public:
	Quote() = default;
	Quote(const std::string & book, double sales_price):bookNo(book), price(sales_price) {}
	std::string isbn() const { return bookNo; }
	//���ظ��������鼮�������ܽ��
	//���������ฺ���д��ʹ�ò�ͬ���ۿۼ����㷨
	virtual double net_price(std::size_t n) const { return n*price; }             
	virtual ~Quote() = default;             //�������������ж�̬��
	virtual void debug(std::ostream &os)const { os << "bookNo: " << isbn() << " ,price: " << price << "   "; }
	bool operator!=(const Quote & rhs)const { if (this->isbn() != rhs.isbn()) return true; else return false; }

	Quote(const Quote &rhs) :bookNo(rhs.bookNo), price(rhs.price) { std::cout << "Quote�Ŀ�������" << std::endl; }
	Quote(Quote &&rhs) noexcept : bookNo(std::move(rhs.bookNo)), price(std::move(rhs.price)) { std::cout << "Quote���ƶ�����" << std::endl; }
	Quote & operator=(const Quote &rhs) { 
		if (*this != rhs)         //�����Ը�ֵ
		{
			bookNo = rhs.bookNo;
			price = rhs.price;
		}
		std::cout << "Quote�Ŀ�����ֵ" << std::endl;
		return *this;
	}
	
	Quote & operator=(Quote &&rhs) {
		if (*this != rhs) {
			bookNo = std::move(rhs.bookNo);
			price = std::move(rhs.price);
		}
		std::cout << "Quote���ƶ���ֵ" << std::endl;
		return *this;
	}

	//���ص�ǰ�����һ�ݶ�̬����Ŀ���
	virtual Quote* clone() const & { return new Quote(*this); }
	virtual Quote* clone() && {return new Quote(std::move(*this)); }
private:
	std::string bookNo;       //�鼮��isbn���
protected:
	double price = 0.0;       //��ͨ������״̬�µļ۸�
};

class Disc_quote :public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string & book, double sales_price, std::size_t min_size, double sales_discount) :
		       Quote(book, sales_price), min_qty(min_size), discount(sales_discount) {};
	double net_price(std::size_t n) const = 0;      //=0��ʾ����һ�����麯����û�������κ�����
protected:
	std::size_t min_qty = 0;
	double discount = 0.0;
};

//class Bulk_quote :public Quote {           //����ʹ��public�ؼ��ּ̳�Quote���Bulk_quote��
//public:
//	Bulk_quote() = default;
//	Bulk_quote(const std::string & book, double sales_price, std::size_t min_size, double sales_discount):
//		Quote(book, sales_price), min_qty(min_size), discount(sales_discount) {};
//	double net_price(std::size_t n) const override;
//	void debug(std::ostream &os)const override{ os << "bookNo: " << isbn() << " ,price: " << price <<" ,min_qty: "<<min_qty<<" ,discount: "<<discount<<"   "; }
//private:
//	std::size_t min_qty = 0;     //�����ۿ���������С������
//	double discount = 0.0;       //�ۿ۶�
//};

class Bulk_quote :public Disc_quote {               //���¶���̳�Disc_quote��Bulk_quote��
public:
	Bulk_quote() = default;
	using Disc_quote::Disc_quote;      //�̳�Disc_quote�Ĺ��캯��
	/*Bulk_quote(const std::string & book, double sales_price, std::size_t min_size, double sales_discount) :
		Disc_quote(book, sales_price, min_size, sales_discount) {};*/
	double net_price(std::size_t n) const override;           //���ǻ����еĺ����汾��ʵ���µ��ۿ۲���
	void debug(std::ostream &os)const override { os << "bookNo: " << isbn() << " ,price: " << price << " ,min_qty: " << min_qty << " ,discount: " << discount << "   "; }

	Bulk_quote(const Bulk_quote &rhs) :Disc_quote(rhs.isbn(),rhs.price,rhs.min_qty,rhs.discount) { std::cout << "Bulk_quote�Ŀ�������" << std::endl; }
	Bulk_quote(Bulk_quote &&rhs) noexcept : Disc_quote(rhs.isbn(), std::move(rhs.price), std::move(rhs.min_qty), std::move(rhs.discount)) { std::cout << "Bulk_quote���ƶ�����" << std::endl; }
	Bulk_quote & operator=(const Bulk_quote &rhs) {
		if (*this != rhs)         //�����Ը�ֵ
		{
			Quote::operator=(rhs);
			min_qty = rhs.min_qty; 
			discount = rhs.discount;
		}
		std::cout << "Bulk_quote�Ŀ�����ֵ" << std::endl;
		return *this;
	}

	Bulk_quote & operator=(Bulk_quote &&rhs) {
		if (*this != rhs) {
			Quote::operator=(rhs);
			min_qty = std::move(rhs.min_qty);
			discount = std::move(rhs.discount);
		}
		std::cout << "Bulk_quote���ƶ���ֵ" << std::endl;
		return *this;
	}

	//���ص�ǰ�����һ�ݶ�̬����Ŀ���
	Bulk_quote* clone() const & { return new Bulk_quote(*this); }
	Bulk_quote* clone() && {return new Bulk_quote(std::move(*this)); }
	
};

double print_total(std::ostream &os, const Quote &item, std::size_t n);

#endif // !_QUOTE_H
