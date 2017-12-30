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
	
private:
	std::shared_ptr<Query_Base> q;
	Query(std::shared_ptr<Query_Base> ptr) :q(ptr) {}
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
};
inline Query::Query(const std::string &s) :q(new WordQuery(s)) {};       //Query�Ĺ��캯��



class NotQuery :public Query_Base {
	friend Query operator~(const Query &rhs);
	NotQuery(const Query &q) :query(q) {}
	Query query;

	//���¶���̳ж����Ĵ��麯��
	QueryResult eval(const TextQuery &r)const;
	std::string rep() const { return "~(" + query.rep() + ")"; }
};
inline Query operator~(const Query &rhs) {
	return std::shared_ptr<Query_Base>(new NotQuery(rhs));
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
};
inline Query operator&(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_Base>(new AndQuery(lhs, rhs));
}





class OrQuery :public BinaryQuery {
	friend Query operator|(const Query &, const Query&);
	OrQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "|") {}
	//������࣬OrQuery�̳���rep���Ҷ������������麯��
	QueryResult eval(const TextQuery&) const;
};
inline Query operator|(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_Base>(new OrQuery(lhs, rhs));
}







#endif // !_QUERY_H
