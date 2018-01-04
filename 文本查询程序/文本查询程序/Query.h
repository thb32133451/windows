#ifndef _QUERY_H
#define _QUERY_H

#include "TextQuery.h"


//һ����ѯ����ĳ�����࣬����Ĳ�ѯ���ʹ������������г�Ա����private��
class Query_Base {
	friend class Query;
protected:
	using line_no= std::vector<std::string>::size_type;
	virtual ~Query_Base() = default;
private:
	//������Ա�������Ǵ��麯����������һ���������
	virtual QueryResult eval(const TextQuery&) const = 0;       //�����뵱ǰQueryƥ���QueryResult
	virtual std::string rep() const = 0;                        //��ʾ��ѯ��string
	
	virtual Query_Base* clone() const & = 0;                       //����һ��ָ���Լ��Ŀ�����ָ��                          
	virtual Query_Base* clone() && = 0;
};



class Query {          //����QueryBase�̳���ϵ�Ľӿ���
	friend Query operator&(const Query &lhs, const Query &rhs);
	friend Query operator~(const Query &rhs);
	friend Query operator|(const Query &lhs, const Query &rhs);
	friend std::ostream & operator<<(std::ostream &os, const Query &query);
public:
	Query(const std::string &s);
	//�ӿں��������ö�Ӧ��Query_Base����
	QueryResult eval(const TextQuery &r) const { return q->eval(r); }
	std::string rep() const { return q->rep(); }

	Query(const Query& query) :q(query.q->clone()) {};
	Query(Query&& query) :q(std::move(query.q)->clone()) {};
	Query& operator=(const Query& rhs) { q = rhs.q->clone(); }
	Query& operator=(Query&& rhs) { q = std::move(rhs.q)->clone(); }
	~Query()
	{
		delete q;
	}
private:
	Query_Base* q;
	Query(Query_Base* ptr) :q(ptr) {}
};
inline std::ostream & operator<<(std::ostream &os, const Query &query) {
	return os << query.rep();
}





class WordQuery :public Query_Base {
	std::string words;    //Ҫ���ҵĵ���

	friend class Query;   //Query����õ�WordQuery�Ĺ��캯�����������Ϊ��Ԫ

	WordQuery(const std::string &s) :words(s) {}

	//���¶���̳ж����Ĵ��麯��
	QueryResult eval(const TextQuery &r)const { return r.query(words); }
	std::string rep() const{ return words; }

	Query_Base* clone() const & { return new WordQuery(*this); }
	Query_Base* clone() && { return new WordQuery(std::move(*this)); }
};
inline Query::Query(const std::string &s) :q(new WordQuery(s)) {};       //Query�Ĺ��캯��



class NotQuery :public Query_Base {
	friend Query operator~(const Query &rhs);
	NotQuery(const Query &q) :query(q) {}
	Query query;

	//���¶���̳ж����Ĵ��麯��
	QueryResult eval(const TextQuery &r)const;
	std::string rep() const { return "~(" + query.rep() + ")"; }

	Query_Base* clone() const & { return new NotQuery(*this); }
	Query_Base* clone() && { return new NotQuery(std::move(*this)); }
};
inline Query operator~(const Query &rhs) {
	Query_Base* re = new NotQuery(rhs);
	return re;
}




class BinaryQuery :public Query_Base {        //������������������Ĳ�ѯ�������������
protected:
	Query lhs, rhs;          //����������Ҳ����
	std::string opSym;       //�����������

	BinaryQuery(const Query &l, const Query &r, std::string s) :lhs(l), rhs(r), opSym(s) {}
	//�����࣬������eval
	std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
};





class AndQuery :public BinaryQuery {
	friend Query operator&(const Query &, const Query&);
	AndQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "&") {}
	//������࣬AndQuery�̳���rep���Ҷ������������麯��
	QueryResult eval(const TextQuery&) const;

	Query_Base* clone() const & { return new AndQuery(*this); }
	Query_Base* clone() && { return new AndQuery(std::move(*this)); }
};
inline Query operator&(const Query &lhs, const Query &rhs) {
	Query_Base* re = new AndQuery(lhs, rhs);
	return re;
}





class OrQuery :public BinaryQuery {
	friend Query operator|(const Query &, const Query&);
	OrQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "|") {}
	//������࣬OrQuery�̳���rep���Ҷ������������麯��
	QueryResult eval(const TextQuery&) const;

	Query_Base* clone() const & { return new OrQuery(*this); }
	Query_Base* clone() && { return new OrQuery(std::move(*this)); }
};
inline Query operator|(const Query &lhs, const Query &rhs) {
	Query_Base* re = new OrQuery(lhs, rhs);
	return re;
}







#endif // !_QUERY_H
