#include "ReceiveMessageThread.h"


ReceiveMessageThread::ReceiveMessageThread(int ClientSockfd, QObject *parent):
    ClientSockfd(ClientSockfd), QObject(parent)
{
}


ReceiveMessageThread::~ReceiveMessageThread()
{
}
//创建线程的函数
void ReceiveMessageThread::ClientStart()
{
    int TheRet = pthread_create(&TheThread, NULL, ClientRun, this);
    if (0 != TheRet)
        qDebug() << "it's fail to create thread" << endl;
}
//线程的回调函数
void* ReceiveMessageThread::ClientRun(void* TheArg)
{
    ReceiveMessageThread* recvThread = (ReceiveMessageThread*)(TheArg);
    Message runMsg;
    while (1)
    {
        //接收信息
        int TheRet = recv(recvThread->ClientSockfd,&runMsg,sizeof(runMsg),0);
        if (-1==TheRet||0==TheRet)
            break;
        emit recvThread->SendTheMessageToSignal(&runMsg);
        qDebug() << "receive a message from " << runMsg.FromTheUserIndex << ":" << runMsg.message << endl;
    }
}
