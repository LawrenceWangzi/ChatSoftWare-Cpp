#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <QWidget>
#include <sys/types.h>
#include <sys/socket.h>
#include <QDebug>
#include <iostream>
#include <QCloseEvent>
#include <QTableWidgetItem>
#include "ClientConnectServer.h"
#include "Message.h"
#include "ReceiveMessageThread.h"

using namespace std;

struct TheOnlineUserInformation{
    char index[20]={0};
    char UserName[20]={0};
};

namespace Ui {
class ClientInterface;
}

class ClientInterface : public QWidget
{
    Q_OBJECT

public://声明为explicit的构造函数不能在隐式转换中使用
    explicit ClientInterface(int InterfaceSockfd,int MyIndex,QWidget *parent = 0);//nullptr
    ~ClientInterface();

protected://关闭事件
    void closeEvent(QCloseEvent *event);
private:
    Ui::ClientInterface *ui;
    int InterfaceSockfd;

    Message message;

    int TheChatType;//聊天类型 0表示全部，1表示一个对一个

    int MyIndex;
    int ToTheUserIndex;
    QString ToTheUserName;

    ReceiveMessageThread* recvThread;

    void ReceiveOnlineUserInformation();
    void DeleteMessage();

private slots:
    void ClientGetItem(QTableWidgetItem* item);
    void ButtonOneSlot();
    void ButtonAllSlot();
    void ButtonSendSlot();
    void ReceiveMessage(Message *message);
};

#endif // CLIENTINTERFACE_H
