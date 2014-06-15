#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QtSql>
#include <QObject>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);
    static bool createConnection();
    static void addMenu(QString &name, QString &index, QString &unitPrice);
signals:

public slots:

private:

};

#endif // DATABASE_H
