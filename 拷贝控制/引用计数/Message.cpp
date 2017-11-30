#include <string>
#include <set>
#include "Message.h"


Message::~Message()
{
	for (auto f : folders)
		f->rmvMsg(this);
}

Message::Message(const Message & rhs):info(rhs.info),folders(rhs.folders)                   //拷贝构造函数，创建info和folders的拷贝，并在每个包含rhs的Folder中添加指向本Message的指针
{
	add_to_Folders(rhs);
}

Message & Message::operator=(const Message & rhs)             //拷贝赋值运算符，将rhs的内容拷贝至本对象，并从原来包含本Message的Folder中删除，将它添加到包含rhs的Folder中
{
	//通过先删除指针在插入他们来处理自赋值情况
	remove_from_Folders();        //更新已有Folder
	info = rhs.info;              //拷贝rhs内容
	folders = rhs.folders;
	add_to_Folders(rhs);          //将本Message添加到rhs的Folder列表中
	return *this;
	// TODO: 在此处插入 return 语句
}

void Message::save(Folder &add)
{
	folders.insert(&add);      //将给定Folder添加到本对象的Folder列表中
	add.addMsg(this);          //将本Message添加到add的Message集合中
}

void Message::remove(Folder &rmv)
{
	folders.erase(&rmv);
	rmv.rmvMsg(this);
}

void Message::add_to_Folders(const Message & hs)
{
	for (auto f : hs.folders)        //对每个包含hs的Folder
		f->addMsg(this);             //向Folder添加一个指向本Message的指针
}

void Message::remove_from_Folders()           //将本对象从folders内指针指向的Folder中删除
{
	for (auto f : folders)
		f->rmvMsg(this);
}

void swap(Message & lhs, Message & rhs)  //自定义的swap，但需要管理指向被交换Message的指针
{
	using std::swap;    //本类中严格来说不需要，但这是一个好习惯
	//将每个Message从它原来所在的Folder中删除
	for (auto f : lhs.folders)
		f->rmvMsg(&lhs);
	for (auto f : rhs.folders)
		f->rmvMsg(&rhs);
	//交换lhs和rhs的数据成员
	swap(lhs.info, rhs.info);    //使用swap(string&,string&)
	swap(lhs.folders, rhs.folders);   //使用swap(set&,set&)
	//将每个Message添加到它新的Folder中
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}
