#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class HasPtr {
public:
	HasPtr(const std::string &s=std::string()):ps(new std::string(s)),i(0),use(new std::size_t(1)){ std::cout << "����" << std::endl; }  //���캯��,�����µ�string�ͼ�������������������ʼ��Ϊ1
	//�������캯�����������������ݳ�Ա��������������
	HasPtr(const HasPtr & rhs) :ps(rhs.ps), i(rhs.i), use(rhs.use) { ++*use; std::cout << "��������" << std::endl;}
	//�������������
	HasPtr& operator=(const HasPtr &rhs);       
	bool operator<(const HasPtr &rhs);
	~HasPtr();
	friend void swap(HasPtr &lhs, HasPtr &rhs);    //Ϊ�˷������ڳ�Ա������Ϊfriend

private:
	std::string *ps;
	int i;
	std::size_t *use;    //���ü���
};

HasPtr& HasPtr::operator=(const HasPtr &rhs)     //������ֵ������������Ҳ�������ü������ݼ����������ü�������Ҫʱ�ͷ�ʹ�õ��ڴ�
{
	++*rhs.use;       //�ȵ����Ҳ�������ü����������Ը�ֵ���
	if (--*use == 0)  //�ݼ����������ü�������Ϊ0���ͷ��ڴ�
	{
		delete ps;    //�ͷű��������ĳ�Ա
		delete use;
	}
	ps = rhs.ps;       //���������ÿ����Ա���и�ֵ
	i = rhs.i;
	use = rhs.use;
	return *this;      //���ش˶���
}

bool HasPtr::operator<(const HasPtr & rhs)
{
	return i < rhs.i;
	// TODO: �ڴ˴����� return ���
}

HasPtr::~HasPtr()  //��������
{
	if (--*use == 0)   //������ʱ��ݼ����ü��������Ϊ0
	{
		delete ps;    //�ͷ�string�ڴ�
		delete use;   //�ͷ����ü����ڴ�
	}
	std::cout << "using ~HasStr()" << std::endl;
}

inline void swap(HasPtr &lhs, HasPtr &rhs)    //����swap��Ŀ�����Ż����룬��˶���Ϊinline
{
	using std::swap;               //����ʹ�ñ�׼��swap����std::swap,��Ϊstd::swap���ȼ����� �������� �����swap�汾
	std::cout << "using HasStr::swap()" << std::endl;
	swap(lhs.ps, rhs.ps);   //����ָ��
	swap(lhs.i, rhs.i);     //����int��Ա
}


//int main()
//{
//	{
//		std::string s = "want";
//		std::string k = "swap";
//		HasPtr hs(s), hk(k);
//		swap(hs, hk);
//		HasPtr *ps = new HasPtr(hs);
//		
//
//		std::vector<HasPtr> vc;
//		vc.push_back(hs);
//		vc.push_back(hk);
//		vc.push_back(*ps);
//		std::sort(vc.begin(), vc.end());
//	}
//	system("pause");
//	return 0;
//}