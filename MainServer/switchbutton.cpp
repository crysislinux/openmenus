#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <qdeclarative.h>
#include <QDeclarativeItem>
#include <QDeclarativeView>
#include "switchbutton.h"
#include <QtGui>
#include <QDebug>

SwitchButton::SwitchButton(QWidget *parent) :
    QWidget(parent)
{
    QDeclarativeView *view = new QDeclarativeView(this);
    view->setSource(QUrl("qrc:SwitchButton.qml"));
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(view);
    setLayout(mainLayout);
    setFixedSize(60, 25);
    QObject *item = view->rootObject();
    connect(item, SIGNAL(_onClicked()), this, SIGNAL(on()));
    connect(item, SIGNAL(offClicked()), this, SIGNAL(off()));

    connect(this, SIGNAL(on()), this, SLOT(slot_on()));
    connect(this, SIGNAL(off()), this, SLOT(slot_off()));
}

void SwitchButton::slot_off()
{
    qDebug()<<"off";
}

void SwitchButton::slot_on()
{
    qDebug()<<"on";
}
