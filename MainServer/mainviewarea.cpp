#include <QtGui>
#include <QDebug>
#include "mainwindow.h"
#include "signalbridge.h"
#include "mainviewarea.h"
#include "ordermodel.h"
#include "iconview.h"
#include "listview.h"

MainViewArea::MainViewArea(QWidget *parent) :
    QFrame(parent)
{
    setFrameShape(QFrame::NoFrame);
    OrderModel *model = new OrderModel(this);

    m_listView = new ListView(model);
    m_iconView = new IconView(model);

    m_stackedWidget = new QStackedWidget;
//    m_stackedWidget->addWidget(m_listView);
    m_stackedWidget->addWidget(m_listView);
    m_stackedWidget->addWidget(m_iconView);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_stackedWidget);
    setLayout(mainLayout);
//    setFrameShape(QFrame::NoFrame);
    connect(MainWindow::signal, SIGNAL(listView()), this, SLOT(switchToListView()));
    connect(MainWindow::signal, SIGNAL(iconView()), this, SLOT(switchToIconView()));
    connect(MainWindow::signal, SIGNAL(statistics()), this, SLOT(switchToStatisticalView()));
    connect(MainWindow::signal, SIGNAL(combineTableIndexCells(int)), m_listView, SLOT(combineTableIndexCells(int)));
}

void MainViewArea::switchToListView()
{
    m_stackedWidget->setCurrentWidget(m_listView);
}

void MainViewArea::switchToIconView()
{
    m_stackedWidget->setCurrentWidget(m_iconView);
}

void MainViewArea::switchToStatisticalView()
{

}
