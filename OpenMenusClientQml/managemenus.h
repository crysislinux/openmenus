#ifndef MANAGEMENUS_H
#define MANAGEMENUS_H

#include <QObject>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <menumodel.h>
#include <QTcpSocket>
class QNetworkAccessManager;
class QNetworkReply;

class ManageMenus : public QObject
{
    Q_OBJECT
public:
    explicit ManageMenus(QObject *parent = 0);
    MenuModel &menuModel(){return m_menuModel;}
    QSortFilterProxyModel &orderFormModel(){return m_filterModel;}

signals:
    
public slots:
    void submit();
    void replyFinished(QNetworkReply*);
    void socketReadyRead();
//    void getImages(QNetworkReply*);

private:
    MenuModel m_menuModel;
    QSortFilterProxyModel m_filterModel;
    static bool isConnect;
    QTcpSocket *socketClient;
    QNetworkAccessManager *network;
    QNetworkAccessManager *imagesManager;

    void disconnectToServer();
    void connectToServer();
};

#endif // MANAGEMENUS_H
