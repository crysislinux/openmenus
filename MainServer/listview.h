#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QTableView>
#include <QList>
#include <QMap>

class ListView : public QTableView
{
    Q_OBJECT
public:
    explicit ListView(QAbstractTableModel *model, QWidget *parent = 0);

    
signals:
    
public slots:
    void combineTableIndexCells(int rows);
private:
    QAbstractTableModel *m_model;
    QMap<int, int> m_map;
};

#endif // LISTVIEW_H
