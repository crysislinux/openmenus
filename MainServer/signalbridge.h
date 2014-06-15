#ifndef SIGNALBRIDGE_H
#define SIGNALBRIDGE_H

#include <QObject>
#include "message.h"
class SignalBridge : public QObject
{
    Q_OBJECT
public:
    explicit SignalBridge(QObject *parent = 0);
    
signals:
    void importMenus();
    void exportMenus();
    void manageMenus();
    void manageMenusTakenAway();
    void synchronous();
    void upload();
    void set();

    void listView();
    void iconView();
    void statistics();
    void addMenu(int,int,int);
    void addMenu(const OrderMessage &);
    void combineTableIndexCells(int);
    
public slots:
    
};

#endif // SIGNALBRIDGE_H
