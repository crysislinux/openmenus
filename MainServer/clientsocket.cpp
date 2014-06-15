#include "clientsocket.h"
#include "mainwindow.h"
#include "signalbridge.h"


ClientSocket::ClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()),
            this, SLOT(readClient()));
    connect(this, SIGNAL(disconnected()),
            this, SLOT(deleteLater()));
    connect(this, SIGNAL(addMenus(const OrderMessage&)), MainWindow::signal, SIGNAL(addMenu(const OrderMessage&)));
    nextBlockSize = 0;
}

void ClientSocket::readClient()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_4_7);

    if(0 == nextBlockSize){
        if(bytesAvailable() < sizeof(quint32))
            return;
        in >> nextBlockSize;
    }
    if(bytesAvailable() < nextBlockSize)
        return;


    OrderMessage message;
    in >> message;
    emit addMenus(message);
//    emit courseCount(courseNum);
    nextBlockSize = 0;
}
