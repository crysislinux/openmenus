#include <QtGui>
#include "database.h"

Database::Database(QObject *parent) :
    QObject(parent)
{
}

bool Database::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("menusdb");
    db.setUserName("lg");
    db.setPassword("123456");

    if(!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());
        return false;
    }
    QSqlQuery query;
    query.exec("SELECT count(*) FROM sqlite_master WHERE type='table' AND name='menuList'");
    if(query.next()){
        int count = query.value(0).toInt();
        qDebug()<<count;
        if(count<1){
//            query.exec(QString("CREATE TABLE menuList(name VARCHAR(255))"));
            if(!query.exec(QString("CREATE TABLE menuList(menuName VARCHAR(255), menuIndex INT, unitPrice DEC(14,4))")))
                qDebug()<<query.lastError().text();
        }
    }
    return true;
}

void Database::addMenu(QString &name, QString &index, QString &unitPrice)
{
    QSqlQuery query;

    query.exec(QString("INSERT INTO menuList(menuName, menuIndex, unitPrice) VALUES('%1',%2,%3)").arg(name).arg(index).arg(unitPrice));
    query.exec(QString("SELECT * FROM menuList"));
    while(query.next()){
        qDebug()<<"name: "<<query.value(0).toString();
        qDebug()<<"index: "<<query.value(1).toInt();
        qDebug()<<"unitPrice: "<<query.value(2).toFloat();
    }
}















