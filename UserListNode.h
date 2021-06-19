#ifndef USERLISTNODE_H
#define USERLISTNODE_H
#include <string>
#include <iostream>
#include "UserKey.h"
#include <cstring>

using namespace std;

struct ListNode
{
	UserKey Userkey;
	ListNode* NextNode;
};

class UserListNode
{
public:
	UserListNode();
	~UserListNode();

	void PushNode(UserKey Userkey);
	void PopNode(int Nodecsockfd);
	int ListLength();
	int ListSelectSockfd(const char *Index);
	void ListShow();
	ListNode* & ListGetHeadNode();

private:
	ListNode* HeadNode;
	int UserListMLength;
};

#endif //USERLISTNODE_H
