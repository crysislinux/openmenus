#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QWidget>

class SwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = 0);
signals:
    void on();
    void off();
    
public slots:
    void slot_on();
    void slot_off();
};

#endif // SWITCHBUTTON_H
