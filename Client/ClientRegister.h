#ifndef CLIENTREGISTER_H
#define CLIENTREGISTER_H

#include <QDialog>
#include<sys/types.h>
#include<sys/socket.h>

namespace Ui {
class ClientRegister;
}

struct ClientRegisterInfomation
{
    char InfoName[20]={0};
    char InfoPwd[20]={0};
    int InfoFlag;
};
class ClientRegister : public QDialog
{
    Q_OBJECT

public:
    explicit ClientRegister(int RegisterSockfd,QWidget *parent = 0);
    //QWidget *parent = nullptr
    ~ClientRegister();

private:
    Ui::ClientRegister *ui;
    int RegisterSockfd;

private slots:
    void RegisterCommitTo();
};

#endif // CLIENTREGISTER_H
