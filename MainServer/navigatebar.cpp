#include <QtGui>
#include <QDebug>
#include "mainwindow.h"
#include "signalbridge.h"
#include "navigatebar.h"
#include "button.h"

NavigateBar::NavigateBar(QWidget *parent) :
    QFrame(parent)
{
//    Button *b = new Button(":/images/listview.png", "ListView", this);
//    QHBoxLayout *mainLayout = new QHBoxLayout;
//    mainLayout->addWidget(b);
//    mainLayout->setMargin(0);
//    mainLayout->setContentsMargins(0,0,0,0);
//    setLayout(mainLayout);
    createWidgets();
    setContentsMargins(0,0,0,0);
    setFrameShape(QFrame::NoFrame);
    setStyleSheet(QString("QFrame{background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,\
                          stop: 0 #404040, stop: 1 #808080);}"));
    setFixedWidth(Button::TOOLWIDGET_W);
}

void NavigateBar::createWidgets()
{
    m_buttonStrList << "ListView" << "IconView" << "Statis.";
    for(int i=0;i<m_buttonStrList.count();i++){
        QString strImage = QString(":/images/%1.png").arg(i);
        m_buttonList.append(new Button(strImage, m_buttonStrList[i], this));
        m_buttonList.at(i)->move(0, i*Button::TOOLWIDGET_H + VALUE_DIS);
        connect(m_buttonList.at(i), SIGNAL(signal_parent(void*)), this, SLOT(slot_set(void*)));
        switch (i){
        case 0:
            connect(m_buttonList.at(i), SIGNAL(clicked()), MainWindow::signal, SIGNAL(listView()));
            m_buttonList.at(i)->setPress(true);
            break;
        case 1:
            connect(m_buttonList.at(i), SIGNAL(clicked()), MainWindow::signal, SIGNAL(iconView()));
            break;
        case 2:
            connect(m_buttonList.at(i), SIGNAL(clicked()), MainWindow::signal, SIGNAL(statistics()));
            break;
        default:
            break;
        }
    }
}

void NavigateBar::slot_set(void *pObject)
{
    for(int i=0;i<m_buttonStrList.count();i++){
        if(m_buttonList.at(i) != pObject){
            m_buttonList.at(i)->setPress(false);
        }
    }
}
















