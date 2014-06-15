#ifndef MESSAGE_H
#define MESSAGE_H

#include <QMap>
#include <QDataStream>

typedef QMap<int, int> OrderRecord;
class OrderMessage
{
public:
    OrderMessage();
    void setTableId(int tableId){m_tableId = tableId;}
    void addMenu(int id, int count);
    int count() const {return m_OrderMap.count();}
    int tableId() const {return m_tableId;}
    QMap<int, int> orderMap() const {return m_OrderMap;}

private:
    int m_tableId;
    QMap<int, int> m_OrderMap;
    friend QDataStream & operator <<(QDataStream& out, const OrderMessage& s);
    friend QDataStream & operator >>(QDataStream& in, OrderMessage& s);

};

#endif // MESSAGE_H
