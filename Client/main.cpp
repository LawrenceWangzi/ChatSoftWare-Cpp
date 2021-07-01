//#include "widget.h"
#include "ClientLogin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientLogin w;
    w.show();
    return a.exec();
}
