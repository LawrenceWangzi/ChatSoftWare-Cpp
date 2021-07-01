#ifndef RECEIVEMESSAGETHREAD_H
#define RECEIVEMESSAGETHREAD_H
#include "Message.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <QDebug>

class ReceiveMessageThread:public QObject
{
    Q_OBJECT
public:
    ReceiveMessageThread(int ClientSockfd,QObject *parent=0);
    ~ReceiveMessageThread();

    void ClientStart();
    static void* ClientRun(void* TheArg);
signals:
    void SendTheMessageToSignal(Message* TheMessage);
private:
    int ClientSockfd;
    pthread_t TheThread;
};

#endif // RECEIVEMESSAGETHREAD_H
