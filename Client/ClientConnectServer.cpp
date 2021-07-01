#include "ClientConnectServer.h"

ClientConnectServer::ClientConnectServer()
{

}
ClientConnectServer::~ClientConnectServer()
{

}
int ClientConnectServer::ClientConnectTo(string TheIpAddr, short ThePort)
{
    //初始化 socket的addr
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(ThePort);
    SockAddr.sin_addr.s_addr = inet_addr(TheIpAddr.c_str());
    //定义套接字描述符TheSockfd
    int TheSockfd =socket(AF_INET,SOCK_STREAM,0);
    if(-1==TheSockfd)
    {
        return -1;
    }
    //连接到服务器
    int TheRes = connect(TheSockfd,(struct sockaddr*)&SockAddr,sizeof (SockAddr));
    if(-1==TheRes)
    {
        close(TheSockfd);
        return -1;
    }
    qDebug()<<"connect server successful"<<endl;
    return TheSockfd;
}

void ClientConnectServer::ClientCloseSockfd(int ClientSockfd)
{
    close(ClientSockfd);
}
