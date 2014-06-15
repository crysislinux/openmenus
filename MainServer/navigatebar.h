#ifndef NAVIGATEBAR_H
#define NAVIGATEBAR_H

#include <QFrame>
class Button;

class NavigateBar : public QFrame
{
    Q_OBJECT
public:
    explicit NavigateBar(QWidget *parent = 0);
    static const int WIDGET_CNT = 2;
    static const int VALUE_DIS = 0;
signals:
    
public slots:
    void slot_set(void * pObject);
    
private:
    QList<Button *> m_buttonList;
    QList<QString> m_buttonStrList;
    void createWidgets();
};

#endif // NAVIGATEBAR_H
