#ifndef MENUMODEL_H
#define MENUMODEL_H

#include <QAbstractListModel>
#include <QStringList>


 class Menu : public QObject
 {
    Q_OBJECT
 public:
     Menu(const QString &name, const int index, const float unitPrice, const QString &image, const QString &description);
     Q_PROPERTY(int count READ count WRITE setCount)

     QString name() const;
     int index() const;
     int count() const;
     float unitPrice() const;
     QString image() const;
     int menuIndex() const;
     void setCount(int count);
     void setMenuIndex(int index){m_menuIndex = index;}
     QString description() const;
 private:
     int m_menuIndex;
     QString m_name;
     int m_index;
     float m_unitPrice;
     QString m_image;
     int m_count;
     QString m_description;
 };
class MenuModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MenuRoles {
        NameRole = Qt::UserRole + 1,
        IndexRole,
        UnitPriceRole,
        Image,
        Count,
        MenuIndex,
        DesIndex
    };

    MenuModel(QObject *parent = 0);
    void addMenu(Menu *menu);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
//    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Q_INVOKABLE void setCount(int index, int count);
    Q_INVOKABLE int getCount(int index);
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Q_INVOKABLE QString number(float value) {return QString::number(value);}
private:
    QList<Menu *> m_menus;
    static int m_menuIndexBase;
};

#endif // MENUMODEL_H
