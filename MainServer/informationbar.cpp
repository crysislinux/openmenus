#include "informationbar.h"

InformationBar::InformationBar(QWidget *parent) :
    QFrame(parent)
{
    setStyleSheet(QString("QFrame{background-color: white;}"));
    resize(QSize(60, sizeHint().height()));
}
