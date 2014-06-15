#ifndef MAINVIEWAREA_H
#define MAINVIEWAREA_H

#include <QFrame>
class ListView;
class QStackedWidget;
class IconView;

class MainViewArea : public QFrame
{
    Q_OBJECT
public:
    explicit MainViewArea(QWidget *parent = 0);
    
signals:
    
public slots:
    void switchToListView();
    void switchToIconView();
    void switchToStatisticalView();
    
private:
    ListView *m_listView;
    IconView *m_iconView ;
    QStackedWidget *m_stackedWidget;
};

#endif // MAINVIEWAREA_H
