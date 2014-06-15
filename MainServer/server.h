#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QList>
#include "clientsocket.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

signals:
    void sendInformation(int tableIndex, int courseIndex, int num);
    void courseCount(int courseCount);
public slots:
    void disconnectAll();
private:
    void incomingConnection(int socketId);
    QList<ClientSocket*> socketList;
};

#endif // SERVER_H
