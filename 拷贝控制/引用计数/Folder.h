#ifndef _FOLDER_H
#define _FOLDER_H

#include <string>
#include <set>

class Message;     //声明Message类，避免相互包含

class Folder
{
public:
	Folder() {}         //默认构造函数，隐式初始化message为空set
	//拷贝控制成员
	//拷贝构造函数
	Folder(const Folder &hs);
	//拷贝复制运算符
	Folder& operator=(const Folder &rhs);
	//析构函数
	~Folder();

	void addMsg( Message *f);   //将参数指向的Message添加到本对象的包含列表message
	void rmvMsg( Message *f);   //将参数从本对象的包含列表message中删除
private:
	std::set<Message *> message;        //保存指向本Folder中包含的Messagede的指针
	//供拷贝控制成员使用的成员函数工具
	void add_to_Message(const Folder &rhs);
	void remove_from_Message();
};


#endif // !_FOLDER_H

