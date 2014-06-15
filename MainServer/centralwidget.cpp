#include <QtGui>
#include "centralwidget.h"
#include "navigatebar.h"
#include "mainviewarea.h"
#include "informationbar.h"

CentralWidget::CentralWidget(QWidget *parent) :
    QFrame(parent)
{
    navigateBar = new NavigateBar;
    mainViewArea = new MainViewArea;
//    infoBar = new InformationBar;

    splitter = new QSplitter(this);
    splitter->setContentsMargins(0, 0, 0, 0);
    splitter->addWidget(navigateBar);
    splitter->addWidget(mainViewArea);
//    splitter->addWidget(infoBar);
//    splitter->setSizes(QList<int>()<<42<<300);
    splitter->setHandleWidth(1);
//    splitter->handle(2)->setStyleSheet("QSplitterHandle { background-color: black }");
//    splitter->setStyleSheet("QSplitter::handle { background-color: black }");
    splitter->handle(1)->setEnabled(false);


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(splitter);
    setFrameShape(QFrame::NoFrame);
    setLayout(mainLayout);
}
