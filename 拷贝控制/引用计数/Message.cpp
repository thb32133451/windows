#include <string>
#include <set>
#include "Message.h"


Message::~Message()
{
	for (auto f : folders)
		f->rmvMsg(this);
}

Message::Message(const Message & rhs):info(rhs.info),folders(rhs.folders)                   //�������캯��������info��folders�Ŀ���������ÿ������rhs��Folder�����ָ��Message��ָ��
{
	add_to_Folders(rhs);
}

Message & Message::operator=(const Message & rhs)             //������ֵ���������rhs�����ݿ����������󣬲���ԭ��������Message��Folder��ɾ����������ӵ�����rhs��Folder��
{
	//ͨ����ɾ��ָ���ڲ��������������Ը�ֵ���
	remove_from_Folders();        //��������Folder
	info = rhs.info;              //����rhs����
	folders = rhs.folders;
	add_to_Folders(rhs);          //����Message��ӵ�rhs��Folder�б���
	return *this;
	// TODO: �ڴ˴����� return ���
}

void Message::save(Folder &add)
{
	folders.insert(&add);      //������Folder��ӵ��������Folder�б���
	add.addMsg(this);          //����Message��ӵ�add��Message������
}

void Message::remove(Folder &rmv)
{
	folders.erase(&rmv);
	rmv.rmvMsg(this);
}

Message::Message(Message && msg):info(std::move(msg.info))       //ʹ��move���ƶ�info
{
	move_folders(&msg);     //�ƶ�folders������Folderָ��
}

Message & Message::operator=(Message && rhs)
{
	if (this != &rhs)          //����Ը�ֵ
	{
		remove_from_Folders();
		info = std::move(rhs.info);      //�ƶ���ֵinfo
		move_folders(&rhs);              //�ƶ���ֵfolders�����°�����Message��Folder
	}
	return *this;
	// TODO: �ڴ˴����� return ���
}

void Message::add_to_Folders(const Message & hs)
{
	for (auto f : hs.folders)        //��ÿ������hs��Folder
		f->addMsg(this);             //��Folder���һ��ָ��Message��ָ��
}

void Message::remove_from_Folders()           //���������folders��ָ��ָ���Folder��ɾ��
{
	for (auto f : folders)
		f->rmvMsg(this);
}

void Message::move_folders(Message * msg)
{
	folders = std::move(msg->folders);       //ʹ��set���ƶ���ֵ�����
	for (auto i : folders) {                 //��ÿ��folder
		i->rmvMsg(msg);                      //ɾ����Message
		//������set��ӳ�Ա���ܻ�����ڴ棬��ζ�ſ��ܻ��׳�bad_alloc�쳣����˱���������ʹ��noexpect
		i->addMsg(this);                     //��ӱ�Message
	}
	msg->folders.clear();                    //ȷ������msg���޺���
}

void swap(Message & lhs, Message & rhs)  //�Զ����swap������Ҫ����ָ�򱻽���Message��ָ��
{
	using std::swap;    //�������ϸ���˵����Ҫ��������һ����ϰ��
	//��ÿ��Message����ԭ�����ڵ�Folder��ɾ��
	for (auto f : lhs.folders)
		f->rmvMsg(&lhs);
	for (auto f : rhs.folders)
		f->rmvMsg(&rhs);
	//����lhs��rhs�����ݳ�Ա
	swap(lhs.info, rhs.info);    //ʹ��swap(string&,string&)
	swap(lhs.folders, rhs.folders);   //ʹ��swap(set&,set&)
	//��ÿ��Message��ӵ����µ�Folder��
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}
