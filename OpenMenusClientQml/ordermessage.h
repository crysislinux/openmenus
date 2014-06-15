#ifndef ORDERMESSAGE_H
#define ORDERMESSAGE_H

#include <QObject>

class OrderMessage : public QObject
{
    Q_OBJECT
public:
    explicit OrderMessage(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // ORDERMESSAGE_H
