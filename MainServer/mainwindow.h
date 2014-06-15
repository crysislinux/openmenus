#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class SignalBridge;
class QToolBar;
class QStatusBar;
class QMenuBar;
class QAction;
class QMenu;
class CentralWidget;
class ManageMenus;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    static SignalBridge *signal;
    
signals:
    
public slots:
    void about();
    void synchronous();
    void manageMenus();
    void exportMenus();
    void importMenus();
private:
    QMenuBar *_menuBar;
    QToolBar *toolBar;

    QAction *importAct;
    QAction *exportAct;
    QAction *manageMenusAct;
    QAction *manageTakeAwayAct;
    QAction *synchronousAct;
    QAction *uploadAct;
    QAction *setAct;
    QAction *aboutAct;
    QAction *exitAct;

    QMenu *menuMenu;
    QMenu *viewMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;

    CentralWidget *_centralWidget;
    ManageMenus *manageMenusDialog;

    void creatMenus();
    void creatToolBar();
    void creatActions();
    void loadSettings();
    void saveSettings();
    void setupDatabase();
    void createServer();
};

#endif // MAINWINDOW_H
