#include "listview.h"
#include <QDebug>
#include <QtGui>

ListView::ListView(QAbstractTableModel *model, QWidget *parent) :
    QTableView(parent), m_model(model)
{
    setModel(m_model);
    setFrameShape(QFrame::NoFrame);
//    setAlternatingRowColors(true);
    horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ContiguousSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    verticalHeader()->setHidden(true);
    setColumnHidden(0, true);
    setColumnHidden(2, true);
    setFocusPolicy(Qt::NoFocus);
}

void ListView::combineTableIndexCells(int rows)
{
    clearSelection();
    clearSpans();
    setSpan(0, 1, rows, 1);
    setSpan(0, 2, rows, 1);
    setSpan(0, 3, rows, 1);
    QMap<int, int> map;
    foreach(int key, m_map.keys()){
        map.insert(key, m_map.value(key));
    }
    m_map.clear();
    foreach(int key, map.keys()){
        m_map.insert(key+rows, map.value(key));
    }
    foreach(int key, m_map.keys()){
        int _rows = m_map.value(key);
        setSpan(key, 1, _rows, 1);
        setSpan(key, 2, _rows, 1);
        setSpan(key, 3, _rows, 1);
    }
    m_map.insert(0, rows);
}
