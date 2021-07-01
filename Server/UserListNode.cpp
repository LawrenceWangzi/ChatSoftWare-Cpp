#include "UserListNode.h"
/*���������˼�룬�������������ߵ��û�
����û����߾����������һ����㣻����û������ˣ���ɾ��һ�����
*/

UserListNode::UserListNode():
	HeadNode(NULL), UserListMLength(0)
{
	//����ͷ���
	ListNode* listnode = (ListNode*)new(ListNode);
	listnode->NextNode = NULL;
	HeadNode = listnode;
}


UserListNode::~UserListNode()
{
}

//���µ��û����ߣ�����ӽ���
void UserListNode::PushNode(UserKey Userkey)
{
	ListNode* listnode = (ListNode*)new(ListNode);
	listnode->Userkey = Userkey;
	listnode->NextNode = this->HeadNode->NextNode;
	this->HeadNode->NextNode = listnode;
	UserListMLength++;
}

//�û����ߺ�ɾ��һ�����
void UserListNode::PopNode(int Nodecsockfd)
{
	ListNode* CurrentNode = HeadNode;
	while (CurrentNode->NextNode!=NULL)
	{
		if (CurrentNode->NextNode->Userkey.KeyCsockfd == Nodecsockfd)//�ҵ�Nodecsockfdָ��ֵ���û�
		{
			ListNode* Listqueue = CurrentNode->NextNode;
			CurrentNode->NextNode = Listqueue->NextNode;
			delete Listqueue;
			UserListMLength--;
			return;
		}
		else
			CurrentNode = CurrentNode->NextNode;

		

	}

}
//��ǰ�����û�����
int  UserListNode::ListLength()
{
	this->UserListMLength;
}
//����index��Ϣ��ѯ�û����Ӷ������׽��������� ����1��1�û�ͨ��
int UserListNode::ListSelectSockfd(const char *Index)
{
	ListNode*  CurrentNode = HeadNode->NextNode;
	while (CurrentNode!=NULL)
	{
		if (!strcmp(CurrentNode->Userkey.KeyIndex.c_str(), Index))
			return CurrentNode->Userkey.KeyCsockfd;
		else
			CurrentNode = CurrentNode->NextNode;	

	}
	return -1;
}
ListNode* &  UserListNode::ListGetHeadNode()
{
	return this->HeadNode;
}
//չʾ�����û����˺ź��ļ�������
void  UserListNode::ListShow()
{
	cout << "ListShow()" << endl;
	ListNode* CurrentNode = HeadNode->NextNode;
	while (CurrentNode!=NULL)
	{
		cout << "the user id is:" << CurrentNode->Userkey.KeyIndex << endl;
		cout << " the user sockfd is" << CurrentNode->Userkey.KeyCsockfd << endl;
		CurrentNode = CurrentNode->NextNode;
	}
}
