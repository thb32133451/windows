#ifndef _QUERY_H
#define _QUERY_H

#include "TextQuery.h"


//一个查询结果的抽象基类，具体的查询类型从中派生，所有成员都是private的
class Query_Base {
	friend class Query;
protected:
	using line_no= std::vector<std::string>::size_type;
	virtual ~Query_Base() = default;
private:
	//两个成员函数都是纯虚函数，本类是一个抽象基类
	virtual QueryResult eval(const TextQuery&) const = 0;       //返回与当前Query匹配的QueryResult
	virtual std::string rep() const = 0;                        //表示查询的string

};



class Query {          //管理QueryBase继承体系的接口类
	friend Query operator&(const Query &lhs, const Query &rhs);
	friend Query operator~(const Query &rhs);
	friend Query operator|(const Query &lhs, const Query &rhs);
	friend std::ostream & operator<<(std::ostream &os, const Query &query);
public:
	Query(const std::string &s);
	//接口函数：调用对应的Query_Base操作
	QueryResult eval(const TextQuery &r) const { return q->eval(r); }
	std::string rep() const { return q->rep(); }
	
private:
	std::shared_ptr<Query_Base> q;
	Query(std::shared_ptr<Query_Base> ptr) :q(ptr) {}
};
inline std::ostream & operator<<(std::ostream &os, const Query &query) {
	return os << query.rep();
}





class WordQuery :public Query_Base {
	std::string words;    //要查找的单词

	friend class Query;   //Query类会用到WordQuery的构造函数，因此声明为友元

	WordQuery(const std::string &s) :words(s) {}

	//重新定义继承而来的纯虚函数
	QueryResult eval(const TextQuery &r)const { return r.query(words); }
	std::string rep() const{ return words; }
};
inline Query::Query(const std::string &s) :q(new WordQuery(s)) {};       //Query的构造函数



class NotQuery :public Query_Base {
	friend Query operator~(const Query &rhs);
	NotQuery(const Query &q) :query(q) {}
	Query query;

	//重新定义继承而来的纯虚函数
	QueryResult eval(const TextQuery &r)const;
	std::string rep() const { return "~(" + query.rep() + ")"; }
};
inline Query operator~(const Query &rhs) {
	return std::shared_ptr<Query_Base>(new NotQuery(rhs));
}




class BinaryQuery :public Query_Base {        //保存操作两个运算对象的查询类型所需的数据
protected:
	Query lhs, rhs;          //运算符左侧和右侧对象
	std::string opSym;       //运算符的名字

	BinaryQuery(const Query &l, const Query &r, std::string s) :lhs(l), rhs(r), opSym(s) {}
	//抽象类，不定义eval
	std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
};





class AndQuery :public BinaryQuery {
	friend Query operator&(const Query &, const Query&);
	AndQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "&") {}
	//具体的类，AndQuery继承了rep并且定义了其他纯虚函数
	QueryResult eval(const TextQuery&) const;
};
inline Query operator&(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_Base>(new AndQuery(lhs, rhs));
}





class OrQuery :public BinaryQuery {
	friend Query operator|(const Query &, const Query&);
	OrQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "|") {}
	//具体的类，OrQuery继承了rep并且定义了其他纯虚函数
	QueryResult eval(const TextQuery&) const;
};
inline Query operator|(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_Base>(new OrQuery(lhs, rhs));
}







#endif // !_QUERY_H
