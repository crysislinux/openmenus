#include "ordermodel.h"
#include "server.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QtGui>
#include "mainwindow.h"
#include "signalbridge.h"


OrderItem::OrderItem(int id, int peopleNum, int tableNo, float totalPrice, const QString &name, float price, int count)
    : m_id(id), m_peopleNum(peopleNum), m_tableNo(tableNo), m_totalPrice(totalPrice), m_name(name), m_price(price), m_count(count)
{

}

int OrderItem::id() const
{
    return m_id;
}
int OrderItem::peopleNum() const
{
    return m_peopleNum;
}
int OrderItem::tableNo() const
{
    return m_tableNo;
}

float OrderItem::totalPrice() const
{
    return m_totalPrice;
}
QString OrderItem::name() const
{
    return m_name;
}

float OrderItem::price() const
{
    return m_price;
}

int OrderItem::count() const
{
    return m_count;
}

OrderModel::OrderModel(QObject *parent) :
    QAbstractTableModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    setRoleNames(roles);
    m_model = new QSqlTableModel(this);
    m_model->setTable("menuList");
    connect(MainWindow::signal, SIGNAL(addMenu(int,int,int)), this, SLOT(addMenu(int,int,int)));
    connect(MainWindow::signal, SIGNAL(addMenu(const OrderMessage&)), this, SLOT(addMenu(const OrderMessage&)));
    connect(this, SIGNAL(combineTableIndexCells(int)), MainWindow::signal, SIGNAL(combineTableIndexCells(int)));
}

void OrderModel::addMenu(const OrderItem &menu)
{
    beginInsertRows(QModelIndex(), m_menus.count(), m_menus.count());
    m_menus.prepend(menu);
    endInsertRows();
}

#include <QDebug>
void OrderModel::addMenu(int tableIndex, int courseIndex, int num)
{   
    qDebug()<<"id: "<<courseIndex;
    m_model->setFilter(QString("id = %1").arg(courseIndex));
    m_model->select();
    qDebug()<<"rowCount: "<<m_model->rowCount();
    if(m_model->rowCount() == 1){
        QSqlRecord record = m_model->record(0);
        beginInsertRows(QModelIndex(), m_menus.count(), m_menus.count());
        m_menus.prepend(OrderItem(courseIndex, 0, tableIndex, 0, record.value("name").toString(), record.value("price").toFloat(), num));
        endInsertRows();
    }
}

void OrderModel::addMenu(const OrderMessage &orderMessage)
{
    float totalPrice = 0;
    qDebug()<<"count: " << orderMessage.count();
    OrderRecord orderRecord = orderMessage.orderMap();
    QList<int> ids = orderRecord.keys();
    qSort(ids.begin(), ids.end(), qGreater<int>());
    foreach(int id, ids){
        foreach(int count, orderRecord.values(id)){
            m_model->setFilter(QString("id = %1").arg(id));
            m_model->select();
            if(m_model->rowCount() == 1){
                QSqlRecord record = m_model->record(0);
                totalPrice += record.value("price").toFloat()*count;
                beginInsertRows(QModelIndex(), m_menus.count(), m_menus.count());
                m_menus.prepend(OrderItem(orderMessage.tableId(), 0, orderMessage.tableId(), totalPrice, record.value("name").toString(), record.value("price").toFloat(), count));
//                m_menus<<OrderItem(orderMessage.tableId(), 0, orderMessage.tableId(), totalPrice, record.value("name").toString(), record.value("price").toFloat(), count);
                endInsertRows();
            }
        }
    }
    emit combineTableIndexCells(orderMessage.count());
}

int OrderModel::rowCount(const QModelIndex &parent) const
{
    return m_menus.count();
}

int OrderModel::columnCount(const QModelIndex &parent) const
{
    return 7;
}

QVariant OrderModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    const OrderItem &menu = m_menus[index.row()];
    if(role == Qt::DisplayRole){
        if(index.column() == 0)
            return menu.id();
        else if(index.column() == 1)
            return menu.tableNo();
        else if(index.column() == 2)
            return menu.peopleNum();
        else if(index.column() == 3)
            return menu.totalPrice();
        else if(index.column() == 4)
            return menu.name();
        else if(index.column() == 5)
            return menu.price();
        else if(index.column() == 6)
            return menu.count();
    }
    if(role == NameRole)
        return menu.name();

    return QVariant();
}

QVariant OrderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            if(section == 1)
                return QString(tr("TableNo."));
            else if(section == 2)
                return QString(tr("PeopleNum"));
            else if(section == 3)
                return QString(tr("TotalPrice"));
            else if(section == 4)
                return QString(tr("Name"));
            else if(section == 5)
                return QString(tr("Price"));
            else if(section == 6)
                return QString(tr("Count"));
        }

    }
    return QVariant();
}
/*
Qt::ItemFlags OrderModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags &= ~Qt::ItemIsUserCheckable;
    return flags;
}
*/
