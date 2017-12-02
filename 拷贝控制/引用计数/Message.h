#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>
#include <set>
#include "Folder.h"

class Message
{
public:
	//���캯����folders����ʽ��ʼ��Ϊ��set
	explicit Message(const std::string &s=std::string()):info(s){}
	~Message();      //��������
	//�������Ƴ�Ա����������ָ��Message��ָ��
	Message(const Message &rhs);     //�������캯��������info��folders�Ŀ���������ÿ������rhs��Folder�����ָ��Message��ָ��
	Message& operator=(const Message &rhs);       //������ֵ���������rhs�����ݿ����������󣬲���ԭ��������Message��Folder��ɾ����������ӵ�����rhs��Folder��
	//�Ӹ����ļ��������/ɾ����Message
	void save(Folder &add);
	void remove(Folder &rmv);
	Message(Message &&msg);
	Message& operator=(Message &&rhs);

	friend void swap(Message &lhs, Message &rhs);   //�Զ���swap�汾����Ϊ��׼�ⶨ����string��set��swap�汾����ˣ������Լ���swap��������棬�����info��folder��Ա���в���Ҫ�Ŀ���

private:
	std::string info;      //ʵ����Ϣ�ı�
	std::set<Folder*> folders;       //������Message��Folder
	//�������캯����������ֵ������������������õĹ��ߺ���
	void add_to_Folders(const Message &hs);    //��Message��ӵ�hs.folders��ָ��ָ���Folder��
	void remove_from_Folders();                //���������folders��ָ��ָ���Folder��ɾ��
	void move_folders(Message * msg);
};


#endif // !_MESSAGE_H
