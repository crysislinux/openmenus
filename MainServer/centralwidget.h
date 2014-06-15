#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QFrame>
class QSplitter;
class NavigateBar;
class MainViewArea;
class InformationBar;

class CentralWidget : public QFrame
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    
private:

    QSplitter *splitter;
    NavigateBar *navigateBar;
    MainViewArea *mainViewArea;
    InformationBar *infoBar;
};

#endif // CENTRALWIDGET_H
