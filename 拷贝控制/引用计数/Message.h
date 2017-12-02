#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>
#include <set>
#include "Folder.h"

class Message
{
public:
	//构造函数，folders被隐式初始化为空set
	explicit Message(const std::string &s=std::string()):info(s){}
	~Message();      //析构函数
	//拷贝控制成员，用来管理指向本Message的指针
	Message(const Message &rhs);     //拷贝构造函数，创建info和folders的拷贝，并在每个包含rhs的Folder中添加指向本Message的指针
	Message& operator=(const Message &rhs);       //拷贝赋值运算符，将rhs的内容拷贝至本对象，并从原来包含本Message的Folder中删除，将它添加到包含rhs的Folder中
	//从给定的集合中添加/删除本Message
	void save(Folder &add);
	void remove(Folder &rmv);
	Message(Message &&msg);
	Message& operator=(Message &&rhs);

	friend void swap(Message &lhs, Message &rhs);   //自定义swap版本。因为标准库定义了string和set的swap版本，因此，定义自己的swap会从中受益，避免对info和folder成员进行不必要的拷贝

private:
	std::string info;      //实际消息文本
	std::set<Folder*> folders;       //包含本Message的Folder
	//拷贝构造函数、拷贝赋值运算符、析构函数所用的工具函数
	void add_to_Folders(const Message &hs);    //将Message添加到hs.folders内指针指向的Folder中
	void remove_from_Folders();                //将本对象从folders内指针指向的Folder中删除
	void move_folders(Message * msg);
};


#endif // !_MESSAGE_H
