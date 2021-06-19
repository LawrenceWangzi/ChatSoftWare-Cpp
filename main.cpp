#include <iostream>
#include "ChatServer.h"
#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
	ChatServer chatServer;
	while (1)
	{
		int TheCsockfd = chatServer.AcceptMessageClient();
		if (-1==TheCsockfd)
		{
			chatServer.CloseConnectServer();
			exit(-1);
		}
	}
	return 0;
}
