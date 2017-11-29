#include <iostream>
#include <string>



class HasPtr {
public:
	HasPtr(const std::string &s=std::string()):ps(new std::string(s)),i(0),use(new std::size_t(1)){ std::cout << "构造" << std::endl; }  //构造函数,分配新的string和计数器，并将计数器初始化为1
	//拷贝构造函数拷贝所有三个数据成员，并递增加速器
	HasPtr(const HasPtr & rhs) :ps(rhs.ps), i(rhs.i), use(rhs.use) { ++*use; std::cout << "拷贝构造" << std::endl;}
	//拷贝复制运算符
	HasPtr& operator=(const HasPtr &rhs);       
	~HasPtr();
	friend void swap(HasPtr &lhs, HasPtr &rhs);    //为了访问类内成员，定义为friend
private:
	std::string *ps;
	int i;
	std::size_t *use;    //引用计数
};

HasPtr& HasPtr::operator=(const HasPtr &rhs)     //拷贝赋值运算符，递增右侧对象引用计数，递减左侧对象引用计数，必要时释放使用的内存
{
	++*rhs.use;       //先递增右侧对象引用计数，处理自赋值情况
	if (--*use == 0)  //递减左侧对象引用计数，若为0，释放内存
	{
		delete ps;    //释放本对象分配的成员
		delete use;
	}
	ps = rhs.ps;       //对左侧对象的每个成员进行赋值
	i = rhs.i;
	use = rhs.use;
	return *this;      //返回此对象
}

HasPtr::~HasPtr()  //析构函数
{
	if (--*use == 0)   //析构的时候递减引用计数，如果为0
	{
		delete ps;    //释放string内存
		delete use;   //释放引用计数内存
	}
	std::cout << "using ~HasStr()" << std::endl;
}

inline void swap(HasPtr &lhs, HasPtr &rhs)    //定义swap的目的是优化代码，因此定义为inline
{
	using std::swap;               //避免使用标准库swap，即std::swap,因为std::swap优先级低于 参数类型 定义的swap版本
	std::cout << "using HasStr::swap()" << std::endl;
	swap(lhs.ps, rhs.ps);   //交换指针
	swap(lhs.i, rhs.i);     //交换int成员
}

int main()
{
	{
		std::string s = "want";
		std::string k = "swap";
		HasPtr hs(s), hk(k);
		swap(hs, hk);
		HasPtr* ps = new HasPtr;
	}
	system("pause");
	return 0;
}