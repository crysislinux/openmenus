#include "server.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    connect(this, SIGNAL(destroyed()),
            this, SLOT(disconnectAll()));
}

void Server::incomingConnection(int socketId)
{
    ClientSocket *socket = new ClientSocket(this);
    socket->setSocketDescriptor(socketId);
    socketList.push_back(socket);
    connect(socket, SIGNAL(checkInformation(int,int,int)),
            this, SIGNAL(sendInformation(int,int,int)));
    connect(socket, SIGNAL(courseCount(int)),
            this, SIGNAL(courseCount(int)));
}

void Server::disconnectAll()
{
    QList<ClientSocket*>::iterator i = socketList.begin();
    ClientSocket *socket;
    while(i != socketList.end()){
        socket = *i++;
        socket->disconnectFromHost();
    }
}






















