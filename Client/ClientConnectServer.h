#ifndef CLIENTCONNECTSERVER_H
#define CLIENTCONNECTSERVER_H
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string>
#include<QDebug>

using namespace std;

class ClientConnectServer
{
public:
    ClientConnectServer();
    ~ClientConnectServer();

    int ClientConnectTo(string TheIpAddr,short ThePort);
    static void ClientCloseSockfd(int ClientSockfd);

private:
    struct sockaddr_in SockAddr;
};

#endif // CLIENTCONNECTSERVER_H
