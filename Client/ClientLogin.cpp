#include "ClientLogin.h"
#include "ui_ClientLogin.h"

ClientLogin::ClientLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientLogin)
{
    LoginSockfd =-1;
    ui->setupUi(this);
    //两个槽函数触发相关函数的运行
    connect(ui->ButtonLogin,SIGNAL(clicked()),this,SLOT(ClientLoginTo()));
    connect(ui->ButtonRegister,SIGNAL(clicked()),this,SLOT(ClientRegisterTo()));
}

ClientLogin::~ClientLogin()
{
    delete ui;
}
void ClientLogin::ClientLoginTo()
{
    if(LoginSockfd!=-1)
        CCS.ClientCloseSockfd(LoginSockfd);
    LoginSockfd = CCS.ClientConnectTo("127.0.0.1",8888);//服务器IP根据具体情况修改
    if(-1==LoginSockfd)
        return;

    ClientLoginInfo CLf;
    CLf.Theflag = 1;
    strcpy(CLf.index,ui->lineEditAccount->text().toStdString().c_str());
    strcpy(CLf.password,ui->lineEditPassword->text().toStdString().c_str());
    if(!strcmp(CLf.index,"")||!strcmp(CLf.index,""))
    {
        qDebug()<<"password or index is empty!"<<endl;
        return;
    }
    ssize_t TheSize= send(LoginSockfd,(void*)&CLf,sizeof(CLf),0);//发送
    if(-1==TheSize)
    {
        return;
    }
    int RecvFlag=0;
    TheSize=recv(LoginSockfd,&RecvFlag,sizeof(int),0);//接收
    if(1==RecvFlag)//could hava a error?
    {
        qDebug()<<"client login successful"<<endl;
        TheMainFace=new ClientInterface(LoginSockfd,atoi(CLf.index));
        TheMainFace->show();
        this->close();
    }

    else
    {
        return;
    }

}

void ClientLogin::ClientRegisterTo()
{
    if(-1==LoginSockfd)
    {
        ClientConnectServer CCS;
        LoginSockfd = CCS.ClientConnectTo("127.0.0.1",8888);//服务器IP根据具体情况修改
        if(-1==LoginSockfd)
        {
            qDebug()<<"register don't connect server"<<endl;
            return;
        }
    }
    TheRegister = new ClientRegister(LoginSockfd);
    TheRegister->show();
}
