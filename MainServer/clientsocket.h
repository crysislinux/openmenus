#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include "../OpenMenusClientQml/message.h"

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = 0);

signals:
    void checkInformation(int tableIndex, int courseIndex, int num);
    void addMenus(const OrderMessage &orderMessage);
    void courseCount(int courseCount);
public slots:
    void readClient();
private:
    quint32 nextBlockSize;
};

#endif // CLIENTSOCKET_H
