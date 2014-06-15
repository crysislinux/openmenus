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

    return true;
}

















