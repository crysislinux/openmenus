#include "menumodel.h"
#include <QDebug>

Menu::Menu(const QString &name, const int index, const float unitPrice, const QString &image, const QString &description)
    : m_name(name), m_index(index), m_image(image), m_unitPrice(unitPrice), m_description(description), m_count(0)
{
}

QString Menu::description() const
{
    return m_description;
}
int Menu::menuIndex() const
{
    return m_menuIndex;
}
QString Menu::name() const
{
    return m_name;
}

int Menu::index() const
{
    return m_index;
}

int Menu::count() const
{
    return m_count;
}
float Menu::unitPrice() const
{
    return m_unitPrice;
}

QString Menu::image() const
{
    return m_image;
}

void Menu::setCount(int count)
{
    m_count = count;
}

int MenuModel::m_menuIndexBase = 0;
MenuModel::MenuModel(QObject *parent)
    : QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IndexRole] = "index";
    roles[UnitPriceRole] = "unitPrice";
    roles[Image] = "image";
    roles[Count] = "count";
    roles[MenuIndex] = "menuIndex";
    roles[DesIndex] = "description";
    setRoleNames(roles);
}

void MenuModel::setCount(int index, int count)
{
    Menu &menu = *m_menus[index];
    qDebug()<<"index="<<index<<":"<<count;
    menu.setCount(count);
    QModelIndex topLeft = createIndex(index,0);
    emit dataChanged(topLeft, topLeft);
}
int MenuModel::getCount(int index)
{
    Menu &menu = *m_menus[index];
    return menu.count();
}

void MenuModel::addMenu(Menu *menu)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    menu->setMenuIndex(m_menuIndexBase++);
    m_menus << menu;
    endInsertRows();
}

int MenuModel::rowCount(const QModelIndex & parent) const {
    return m_menus.count();
}

bool MenuModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() > m_menus.count())
        return false;
    Menu *menu = m_menus[index.row()];

    if (role == Count)
        menu->setCount(value.toInt());
    return true;
}

QVariant MenuModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() > m_menus.count())
        return QVariant();

    const Menu &menu = *m_menus[index.row()];
    if (role == NameRole)
        return menu.name();
    else if (role == IndexRole)
        return menu.index();
    else if (role == UnitPriceRole)
        return menu.unitPrice();
    else if (role == Image)
        return menu.image();
    else if (role == Count)
        return menu.count();
    else if (role == MenuIndex)
        return menu.menuIndex();
    else if(role == DesIndex)
        return menu.description();
    return QVariant();
}
