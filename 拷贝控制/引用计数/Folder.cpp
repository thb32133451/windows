#include <string>
#include <set>
#include "Folder.h"
#include "Message.h"

Folder::Folder(const Folder & hs):message(hs.message)   //拷贝构造函数
{
	add_to_Message(hs);       //在被包含的对象的set中添加本Folder（set中不会有重复元素）
}

Folder & Folder::operator=(const Folder & rhs)
{
	auto save = rhs.message;    //先临时保存右侧Folder的包含列表，以防止自赋值时失去源数据
	remove_from_Message();     //将本对象从message列表中被包含的对象中删除
	//拷贝rhs对象成员
	message = save;
	add_to_Message(*this);
	return *this;
	// TODO: 在此处插入 return 语句
}

Folder::~Folder()
{
	remove_from_Message();
}

void Folder::addMsg( Message * f)
{
	message.insert(f);
}

void Folder::rmvMsg( Message * f)
{
	message.erase(f);
}

void Folder::add_to_Message(const Folder & rhs)   //将rhs.message列表中包含的对象添加到自己的message包含列表中
{
	for (auto f : rhs.message)
		f->save(*this);
}

void Folder::remove_from_Message()   //将本对象从message列表中被包含的对象中删除
{
	for (auto f : message)
		f->remove(*this);
}
