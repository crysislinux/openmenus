#include "message.h"

OrderMessage::OrderMessage()
    : m_tableId(-1)
{

}

void OrderMessage::addMenu(int id, int count)
{
    m_OrderMap.insert(id, count);
}


QDataStream & operator <<(QDataStream& out, const OrderMessage& s)
{
    out << s.m_tableId << s.m_OrderMap;
    return out;
}

QDataStream & operator >>(QDataStream& in, OrderMessage& s)
{
    in >> s.m_tableId >> s.m_OrderMap;
    return in;
}
