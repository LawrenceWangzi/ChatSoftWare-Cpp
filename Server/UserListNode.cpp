#include "UserListNode.h"
/*利用链表的思想，管理上线与下线的用户
如果用户上线就在链表添加一个结点；如果用户下线了，就删除一个结点
*/

UserListNode::UserListNode():
	HeadNode(NULL), UserListMLength(0)
{
	//设置头结点
	ListNode* listnode = (ListNode*)new(ListNode);
	listnode->NextNode = NULL;
	HeadNode = listnode;
}


UserListNode::~UserListNode()
{
}

//当新的用户上线，则添加进来
void UserListNode::PushNode(UserKey Userkey)
{
	ListNode* listnode = (ListNode*)new(ListNode);
	listnode->Userkey = Userkey;
	listnode->NextNode = this->HeadNode->NextNode;
	this->HeadNode->NextNode = listnode;
	UserListMLength++;
}

//用户下线后，删除一个结点
void UserListNode::PopNode(int Nodecsockfd)
{
	ListNode* CurrentNode = HeadNode;
	while (CurrentNode->NextNode!=NULL)
	{
		if (CurrentNode->NextNode->Userkey.KeyCsockfd == Nodecsockfd)//找到Nodecsockfd指定值得用户
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
//当前在线用户个数
int  UserListNode::ListLength()
{
	this->UserListMLength;
}
//根据index信息查询用户，从而利用套接字描述符 进行1对1用户通信
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
//展示在线用户的账号和文件描述符
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
