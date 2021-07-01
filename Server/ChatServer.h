#ifndef SERVER_H
#define SERVER_H
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "UserKey.h"
#include "UserListNode.h"
#include "MysqlDataBase.h"
#include "ChatUserThread.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

class ChatServer
{
public:
	ChatServer();
	~ChatServer();

	bool AcceptMessageClient();
	void CloseConnectServer();

private:
	struct sockaddr_in ServerAddr;
	int ServerSockfd;
	UserListNode* listNode;
	MysqlDataBase* database;

	void ServerInit();//  失败：ServerSockfd返回-1，成功：ServerSockfd 返回其值；
};

#endif // SERVER_H
