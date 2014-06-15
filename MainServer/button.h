#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>

class Button : public QToolButton
{
    Q_OBJECT
public:
    explicit Button(const QString &strImage = 0, const QString &strInfo = 0, QWidget *parent = 0);
    static const int TOOLICON_WH = 30;
    static const int TOOLWIDGET_W = 70;
    static const int TOOLWIDGET_H = 50;
    void setPress(bool isPressed);
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent *);
signals:
    void signal_parent(void *);
    
public slots:
    void slot_pressed();

private:
    bool m_over;
    bool m_press;
    QString m_strImage;
    QString m_strInfo;

    void setOver(bool isOver);
    void painterinfo(int nTopPartOpacity,int nBottomPartOpacity,QPainter *pPainter);
};

#endif // BUTTON_H
