#include "ClientInterface.h"
#include "ui_ClientInterface.h"

ClientInterface::ClientInterface(int InterfaceSockfd,int MyIndex,QWidget *parent) :
    InterfaceSockfd(InterfaceSockfd),MyIndex(MyIndex),QWidget(parent),
    ui(new Ui::ClientInterface)
{
    ui->setupUi(this);

    TheChatType=0;//4行  参数初始化
    ToTheUserIndex=0;
    message.ToTheUserIndex=0;
    message.FromTheUserIndex=this->MyIndex;

    ui->ButtonAll->setEnabled(false);//控件设置

    ui->TheTableWidgetUserList->setColumnCount(2);//设置column为2
    QStringList QSlist;//字符串变量定义
    QSlist<<"the user index"<<"user name";
    ui->TheTableWidgetUserList->setHorizontalHeaderLabels(QSlist);
    ui->TheTableWidgetUserList->verticalHeader()->setVisible(false);//隐藏行表头
    ui->TheTableWidgetUserList->setSelectionBehavior(QAbstractItemView::SelectRows); //单击选择一行
    ui->TheTableWidgetUserList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->TheTableWidgetUserList->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置每行内容不可更改



    ui->TheTableWidgetMessagePage->setColumnCount(1);
    ui->TheTableWidgetMessagePage->setShowGrid(false);
    ui->TheTableWidgetMessagePage->setColumnWidth(0,500);
    ui->TheTableWidgetMessagePage->verticalHeader()->setVisible(false);
    ui->TheTableWidgetMessagePage->horizontalHeader()->setVisible(false);
    ui->TheTableWidgetMessagePage->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ReceiveOnlineUserInformation();//接收在线用户信息

    recvThread =new ReceiveMessageThread(InterfaceSockfd);//接收信息的线程
    recvThread->ClientStart();//启动

    connect(ui->TheTableWidgetUserList,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(ClientGetItem(QTableWidgetItem*)));
    connect(ui->ButtonOne,SIGNAL(clicked()),this,SLOT(ButtonOneSlot()));
    connect(ui->ButtonAll,SIGNAL(clicked()),this,SLOT(ButtonAllSlot()));
    connect(ui->ButtonSend,SIGNAL(clicked()),this,SLOT(ButtonSendSlot()));
    connect(recvThread,SIGNAL(sendMsg_signal(Message*)),this,SLOT(ReceiveMessage(Message*)));
}

ClientInterface::~ClientInterface()
{
    delete ui;
}
//关闭连接
void ClientInterface::closeEvent(QCloseEvent *event)
{
    ClientConnectServer::ClientCloseSockfd(InterfaceSockfd);
}
void ClientInterface::ReceiveOnlineUserInformation()
{
    int TheLength = 0;
    recv(InterfaceSockfd,&TheLength,sizeof(int),0);//接收信息
    qDebug()<<"current online user count is"<<TheLength<<endl;
    TheOnlineUserInformation TOUF;

    int i=0;
    while(TheLength--)
    {   //遍历接收用户信息
        recv(InterfaceSockfd,&TOUF,sizeof (TOUF),0);
        ui->TheTableWidgetUserList->insertRow(i);
        ui->TheTableWidgetUserList->setItem(i,0,new QTableWidgetItem(TOUF.index));
        ui->TheTableWidgetUserList->setItem(i,1,new QTableWidgetItem(TOUF.UserName));
        i++;
        qDebug()<<"the user index:"<<TOUF.index<<" name:"<<TOUF.UserName<<endl;
    }

}

void ClientInterface::ClientGetItem(QTableWidgetItem* item)
{
    if(1==TheChatType)
    {   //设置控件
        int TheRowNumber = ui->TheTableWidgetUserList->currentRow();
        ToTheUserIndex=ui->TheTableWidgetUserList->item(TheRowNumber,0)->data(Qt::DisplayRole).toString().toInt();
        ToTheUserName=ui->TheTableWidgetUserList->item(TheRowNumber,1)->data(Qt::DisplayRole).toString();
        ui->TheChatUser->setText(ToTheUserName);
        message.ToTheUserIndex=ToTheUserIndex;
        ui->ButtonSend->setEnabled(false);
    }
}

void ClientInterface::ButtonOneSlot()
{   //设置控件
    ui->ButtonAll->setEnabled(true);
    ui->ButtonOne->setEnabled(false);
    this->ui->TheTableWidgetUserList->setSelectionMode(QAbstractItemView::SingleSelection);
    TheChatType = 1;

    ui->ButtonSend->setEnabled(false);

    DeleteMessage();
}

void ClientInterface::ButtonAllSlot()
{
    ui->ButtonAll->setEnabled(false);
    ui->TheChatUser->setText("everyone");
    ui->ButtonOne->setEnabled(true);
    ui->ButtonSend->setEnabled(true);
    TheChatType =0;
    ToTheUserIndex = 0;
    message.ToTheUserIndex = ToTheUserIndex;

    DeleteMessage();
}

void ClientInterface::ButtonSendSlot()//发送信息
{
    QString messageStr= ui->lineEditMessage->text();
    if(messageStr=="")
        return;
    message.ToTheUserIndex =ToTheUserIndex;
    strcpy(message.message,messageStr.toStdString().c_str());
    send(InterfaceSockfd,&message,sizeof (message),0);//发送信息
    int TheRowCount = ui->TheTableWidgetMessagePage->rowCount();
    ui->TheTableWidgetMessagePage->insertRow(TheRowCount);
    ui->TheTableWidgetMessagePage->setItem(TheRowCount,0,new QTableWidgetItem(QString(message.message)+":我"));
    QTableWidgetItem* QWTitem = ui->TheTableWidgetMessagePage->item(TheRowCount,0);
    QWTitem->setTextAlignment(Qt::AlignRight);
}

void ClientInterface::ReceiveMessage(Message* message)
{
    if(TheChatType==1)//一对一聊天模式
    {
        if(0==message->ToTheUserIndex)
        {
            return;
        }
        ToTheUserIndex = message->FromTheUserIndex;
        ui->ButtonSend->setEnabled(true);
    }
    if(0==TheChatType)//群聊模式
    {
        if(0!=message->ToTheUserIndex)
        {
            return;
        }
    }
    //控件的信息处理
    if(message->FromTheUserIndex==this->message.FromTheUserIndex)
        return;
    int TheRowCount = ui->TheTableWidgetMessagePage->rowCount();
    ui->TheTableWidgetMessagePage->insertRow(TheRowCount);
    ui->TheTableWidgetMessagePage->setItem(TheRowCount,0,new QTableWidgetItem(QString(message->FromTheUserName)+": "+QString(message->message)));
}

void ClientInterface::DeleteMessage()
{   //删除控件的信息
    int TheRowCount = ui->TheTableWidgetMessagePage->rowCount();
    while (TheRowCount)
    {
        TheRowCount--;
        ui->TheTableWidgetMessagePage->removeRow(TheRowCount);
    }
}
