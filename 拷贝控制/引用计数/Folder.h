#ifndef _FOLDER_H
#define _FOLDER_H

#include <string>
#include <set>

class Message;     //����Message�࣬�����໥����

class Folder
{
public:
	Folder() {}         //Ĭ�Ϲ��캯������ʽ��ʼ��messageΪ��set
	//�������Ƴ�Ա
	//�������캯��
	Folder(const Folder &hs);
	//�������������
	Folder& operator=(const Folder &rhs);
	//��������
	~Folder();

	void addMsg( Message *f);   //������ָ���Message��ӵ�������İ����б�message
	void rmvMsg( Message *f);   //�������ӱ�����İ����б�message��ɾ��
private:
	std::set<Message *> message;        //����ָ��Folder�а�����Messagede��ָ��
	//���������Ƴ�Աʹ�õĳ�Ա��������
	void add_to_Message(const Folder &rhs);
	void remove_from_Message();
};


#endif // !_FOLDER_H

