#include "ClientRegister.h"
#include "ui_ClientRegister.h"

ClientRegister::ClientRegister(int RegisterSockfd,QWidget *parent) :
    RegisterSockfd(RegisterSockfd),QDialog(parent),
    ui(new Ui::ClientRegister)
{
    ui->setupUi(this);
    //pushButton_Commit这个控件，触发了提交函数
    connect(ui->pushButton_Commit,SIGNAL(clicked()),this,SLOT(RegisterCommitTo()));
}

ClientRegister::~ClientRegister()
{
    delete ui;
}

void ClientRegister::RegisterCommitTo()
{
    ClientRegisterInfomation Crf;
    memset(&Crf,0,sizeof(Crf));
    Crf.InfoFlag=2;
    if(ui->LE_name->text()==""||ui->LE_password->text()=="")
        return;
    strcpy(Crf.InfoName,ui->LE_name->text().toStdString().c_str());//复制文本
    strcpy(Crf.InfoPwd,ui->LE_password->text().toStdString().c_str());
    send(RegisterSockfd,&Crf,sizeof(Crf),0);//发送内容
    char RegisterAccount[20]={0};
    recv(RegisterSockfd,RegisterAccount,sizeof(RegisterAccount),0);//接收内容
    ui->labelNewAccount->setText(QString(RegisterAccount));
}
