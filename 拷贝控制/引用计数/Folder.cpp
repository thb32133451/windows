#include <string>
#include <set>
#include "Folder.h"
#include "Message.h"

Folder::Folder(const Folder & hs):message(hs.message)   //�������캯��
{
	add_to_Message(hs);       //�ڱ������Ķ����set����ӱ�Folder��set�в������ظ�Ԫ�أ�
}

Folder & Folder::operator=(const Folder & rhs)
{
	auto save = rhs.message;    //����ʱ�����Ҳ�Folder�İ����б��Է�ֹ�Ը�ֵʱʧȥԴ����
	remove_from_Message();     //���������message�б��б������Ķ�����ɾ��
	//����rhs�����Ա
	message = save;
	add_to_Message(*this);
	return *this;
	// TODO: �ڴ˴����� return ���
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

void Folder::add_to_Message(const Folder & rhs)   //��rhs.message�б��а����Ķ�����ӵ��Լ���message�����б���
{
	for (auto f : rhs.message)
		f->save(*this);
}

void Folder::remove_from_Message()   //���������message�б��б������Ķ�����ɾ��
{
	for (auto f : message)
		f->remove(*this);
}
