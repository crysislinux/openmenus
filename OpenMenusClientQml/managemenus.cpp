#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include "managemenus.h"
#include "message.h"

bool ManageMenus::isConnect = false;
ManageMenus::ManageMenus(QObject *parent) :
    QObject(parent)
{

    network = new QNetworkAccessManager(this);

    connect(network, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    network->get(QNetworkRequest(QUrl("http://127.0.0.1:8080/menus.xml")));

    m_filterModel.setSourceModel(&m_menuModel);
    m_filterModel.setFilterRegExp("[1-9]+[0-9]*");
    m_filterModel.setFilterRole(MenuModel::Count);
    m_filterModel.setDynamicSortFilter(true);
    socketClient = new QTcpSocket(this);
    connect(socketClient, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    connectToServer();
}



void ManageMenus::replyFinished(QNetworkReply *r)
{
    QByteArray response(r->readAll());
    QXmlStreamReader xml(response);
    while (!xml.atEnd()) {
        if(!xml.readNextStartElement())
            continue;
        if (xml.name() == "menu"){
//            qDebug()<<"menu";
            QString id;
            QString name;
            QString price;
            QString description;
            QString images;
            while(xml.name() != "menu" || xml.tokenType() != QXmlStreamReader::EndElement){
                if(!xml.readNextStartElement())
                    continue;
                if (xml.name() == "id")
                    id = xml.readElementText();
                else if(xml.name() == "name")
                    name = xml.readElementText();
                else if(xml.name() == "price")
                    price = xml.readElementText();
                else if(xml.name() == "description")
                    description = xml.readElementText();
                else if(xml.name() == "images")
                    images = xml.readElementText();

            }
//            qDebug()<<"id: "<<id<<"  name: "<<name<<"  price: "<<price<<" description: "<<description<<" images: "<<images;
            m_menuModel.addMenu(new Menu(name, id.toInt(), price.toFloat(), images, description));
        }
    }
}
void ManageMenus::socketReadyRead()
{

}
/*
void ManageMenus::submit()
{
    QByteArray block;
    QDataStream in(&block, QIODevice::WriteOnly);

    int orderCount = m_filterModel.rowCount();
    if(orderCount < 1){
        return;
    }
    int blockSize = (orderCount*2+1)*sizeof(int);
    int tableIndex = 0;
    in<<quint32(blockSize);
    in<<quint32(tableIndex);
    in<<quint32(orderCount);

    for(int i=0; i<m_filterModel.rowCount(); i++){
        QModelIndex modelIndex = m_filterModel.index(i,0);
        int index = m_filterModel.data(modelIndex, MenuModel::IndexRole).toInt();
        int count = m_filterModel.data(modelIndex, MenuModel::Count).toInt();
        qDebug()<<"index:"<<index<<"  count:"<<count ;
        in<<index;
        in<<count;
    }

    socketClient->write(block);
}
*/
void ManageMenus::submit()
{
    QByteArray block;
    QDataStream in(&block, QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_4_7);

    int orderCount = m_filterModel.rowCount();
    if(orderCount < 1){
        return;
    }
    int blockSize = (orderCount*2+1)*sizeof(int);
    int tableIndex = 0;
    OrderMessage message;
    message.setTableId(tableIndex);
    in<<quint32(blockSize);
//    in<<quint32(tableIndex);
//    in<<quint32(orderCount);

    for(int i=0; i<m_filterModel.rowCount(); i++){
        QModelIndex modelIndex = m_filterModel.index(i,0);
        int index = m_filterModel.data(modelIndex, MenuModel::IndexRole).toInt();
        int count = m_filterModel.data(modelIndex, MenuModel::Count).toInt();
        message.addMenu(index, count);
//        qDebug()<<"index:"<<index<<"  count:"<<count ;
//        in<<index;
//        in<<count;
    }
    in << message;
    socketClient->write(block);
}
void ManageMenus::disconnectToServer()
{
    isConnect = false;
}

void ManageMenus::connectToServer()
{
    if(isConnect){
        isConnect = false;
        socketClient->disconnectFromHost();
    }else{
        isConnect = true;
        socketClient->connectToHost(QString("127.0.0.1"), 1234);
    }
}
