#ifndef CHARUSERTHREAD_H
#define CHARUSERTHREAD_H
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "UserKey.h"
#include "UserListNode.h"
#include "Message.h"

struct OnlineChatUserInfo
{
	char index[20] = { 0 };
	char name[20] = { 0 };
};

class ChatUserThread
{
public:
	ChatUserThread(UserKey Userkey,UserListNode* listnode);
	~ChatUserThread();

	void ChatUserStart();
private:
	pthread_t ChatPthread;
	UserKey ThreadMUser;
	UserListNode* ThreadMList;

	static void* ThreadRun(void* ThreadArg);
};
#endif // CHARUSERTHREAD_H


