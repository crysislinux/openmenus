#include <QtGui>
#include <QDebug>
#include "button.h"

Button::Button(const QString &strImage,const QString &strInfo,QWidget *parent) :
    QToolButton(parent), m_over(false), m_press(false), m_strImage(strImage), m_strInfo(strInfo)
{
    QPalette objPalette = palette();
    objPalette.setColor(QPalette::ButtonText, QColor(220,220,220));
    setPalette(objPalette);

    QFont &objFont = const_cast<QFont &>(font());
    objFont.setWeight(QFont::Bold);

    setStyleSheet("QToolButton{border:0px;}");

    setIconSize(QSize(TOOLICON_WH,TOOLICON_WH));
//    resize(TOOLWIDGET_W,TOOLWIDGET_H);
    setFixedSize(TOOLWIDGET_W, TOOLWIDGET_H);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    setIcon(QPixmap(strImage));
    setText(strInfo);

    connect(this,SIGNAL(pressed()),this,SLOT(slot_pressed()));
}

void Button::slot_pressed()
{
    setPress(true);
    emit signal_parent(this);
}

void Button::enterEvent(QEvent *)
{
    setOver(true);
}

void Button::leaveEvent(QEvent *)
{
    setOver(false);
}

void Button::setOver(bool isOver)
{
    if(isOver != m_over){
        m_over = isOver;
        update();
    }
}

void Button::setPress(bool isPressed)
{
    if(isPressed){
        QPalette objPalette = palette();
        objPalette.setColor(QPalette::ButtonText, QColor(64,64,64));
        setPalette(objPalette);
    }else{
        QPalette objPalette = palette();
        objPalette.setColor(QPalette::ButtonText, QColor(220,220,220));
        setPalette(objPalette);
    }

    if(isPressed != m_press){
        m_press = isPressed;       
        update();
    }
}

void Button::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if(m_press){
        painterinfo(150,200,&painter);
    }else if(m_over){
         painterinfo(10,20,&painter);
    }
    QToolButton::paintEvent(e);
}

void Button::painterinfo(int nTopPartOpacity,int nBottomPartOpacity,QPainter *pPainter)
{

    QPen objPen(Qt::NoBrush,1);
    pPainter->setPen(objPen);

    QLinearGradient objLinear(rect().topLeft(),rect().topRight());

    objLinear.setColorAt(0,QColor(192,192,192,nTopPartOpacity));

    objLinear.setColorAt(0.5,QColor(211,211,211,255));

    objLinear.setColorAt(1,QColor(245,245,245,nBottomPartOpacity));
    QBrush objBrush(objLinear);
    pPainter->setBrush(objBrush);

//    pPainter->drawRoundedRect(rect(),5,5);
    pPainter->drawRect(rect());
//    qDebug()<<rect().width()<<":"<<rect().height();
}
