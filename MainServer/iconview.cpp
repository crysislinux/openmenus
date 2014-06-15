#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <qdeclarative.h>
#include <QDeclarativeItem>
#include <QDeclarativeView>
#include <QtGui>
#include <QDebug>
#include <QAbstractItemModel>
#include "iconview.h"

IconView::IconView(QAbstractItemModel *model, QWidget *parent) :
    QFrame(parent), m_model(model)
{
    QDeclarativeView *view = new QDeclarativeView(this);
    QDeclarativeContext *ctxt = view->rootContext();
    ctxt->setContextProperty("orderModel", m_model);
    ctxt->setContextProperty("sizeData", this);
    view->setSource(QUrl("qrc:IconView.qml"));
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(view);
    setLayout(mainLayout);
}

void IconView::resizeEvent(QResizeEvent *e)
{
    QFrame::resizeEvent(e);
    int width = size().width();
    int height = size().height();
    emit sizeChanged(width, height);
}
