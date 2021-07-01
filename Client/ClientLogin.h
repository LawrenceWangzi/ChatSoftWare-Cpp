#ifndef CLIENTLOGIN_H
#define CLIENTLOGIN_H

#include <QDialog>
#include "ClientConnectServer.h"
#include "ClientInterface.h"
#include "ClientRegister.h"

namespace Ui {
class ClientLogin;
}

struct ClientLoginInfo
{
    char index[20]={0};
    char password[20]={0};
    int Theflag;
};

class ClientLogin : public QDialog
{
    Q_OBJECT

public:
    explicit ClientLogin(QWidget *parent=0 );//= nullptr
    ~ClientLogin();

private:
    Ui::ClientLogin *ui;
    ClientInterface* TheMainFace;
    ClientRegister* TheRegister;
    int  LoginSockfd;
    ClientConnectServer CCS;
private slots:
    void ClientLoginTo();
    void ClientRegisterTo();
};

#endif // CLIENTLOGIN_H
