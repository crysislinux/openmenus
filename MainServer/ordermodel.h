#ifndef LISTVIEWMODEL_H
#define LISTVIEWMODEL_H

#include <QAbstractTableModel>
#include "message.h"

class OrderItem
{
public:
    OrderItem(int id, int peopleNum, int tableNo, float totalPrice, const QString &name, float price, int count);
    int id() const;
    int peopleNum() const;
    int tableNo() const;
    float totalPrice() const;
    QString name() const;
    float price() const;
    int count() const;
private:
    int m_id;
    int m_peopleNum;
    int m_tableNo;
    float m_totalPrice;
    QString m_name;
    float m_price;
    int m_count;
};

class QSqlTableModel;
class OrderModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum AnimalRoles{
        NameRole = Qt::UserRole + 1
    };
    explicit OrderModel(QObject *parent = 0);    
    int rowCount( const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
//    Qt::ItemFlags flags(const QModelIndex &index) const;

signals:
    void combineTableIndexCells(int);
public slots:
    void addMenu(const OrderItem &menu);
    void addMenu(int tableIndex, int courseIndex, int num);
    void addMenu(const OrderMessage &orderMessage);
private:
    QSqlTableModel *m_model;
    QList<OrderItem> m_menus;
};

#endif // LISTVIEWMODEL_H
