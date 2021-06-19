#include "UserListNode.h"


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
void UserListNode :: PushNode(UserKey Userkey)
{
	ListNode* listnode = (ListNode*)new(ListNode);
	listnode->Userkey = Userkey;
	listnode->NextNode = this->HeadNode->NextNode;
	this->HeadNode->NextNode = listnode;
	UserListMLength++;
}
//用户下线后，删除一个结点
void UserListNode :: PopNode(int Nodecsockfd)
{
	ListNode* CurrentNode = HeadNode;
	while (CurrentNode->NextNode!=NULL)
	{
		if (CurrentNode->NextNode->Userkey.KeyCsockfd == Nodecsockfd)
		{
			ListNode* queue = CurrentNode->NextNode;
			CurrentNode->NextNode = queue->NextNode;
			delete queue;
			UserListMLength--;
			return;
		}
		else
			CurrentNode = CurrentNode->NextNode;

		

	}

}

int  UserListNode::ListLength()
{
	this->UserListMLength;
}
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
