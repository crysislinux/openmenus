#include <QtGui>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "quazip/quazip.h"
#include "quazip/quazipfile.h"
#include "mainwindow.h"
#include "signalbridge.h"
#include "centralwidget.h"
#include "managemenus.h"
#include "synchronousdialog.h"
#include "webserver.h"
#include "server.h"

SignalBridge *MainWindow::signal = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), manageMenusDialog(0)
{
    signal = new SignalBridge(this);

    WebServer *webServer = new WebServer(QString(), this);
    webServer->start();

    creatActions();
    creatMenus();
    creatToolBar();
    setupDatabase();
    createServer();
    _centralWidget = new CentralWidget(this);
    setCentralWidget(_centralWidget);

//    setStyleSheet(QString("QToolBar{background-image: url(:/images/background.jpg);}"));
//    setStyleSheet(QString("QMainWindow{background-image: url(:/images/background.jpg);}"));
    setWindowTitle(tr("OpenMenus"));
    setWindowIcon(QIcon(":/images/OpenMenus.png"));
    resize(QSize(800, 600));
}
void MainWindow::createServer()
{
    Server *server = new Server(this);
    if(!server->listen(QHostAddress::Any, 1234)){
        QMessageBox::warning(0, tr("Error"), tr("failed to bind to port!"),
                              QMessageBox::Ok);
        return;
    }
    connect(server, SIGNAL(sendInformation(int,int,int)),
            signal, SIGNAL(addMenu(int,int,int)));
//    connect(server, SIGNAL(courseCount(int)),
//            this, SLOT(combineTableIndexCells(int)));
}
void MainWindow::creatActions()
{
    importAct = new QAction(QIcon(":/images/import.png"), tr("Import"), this);
    importAct->setToolTip(tr("import menus"));
    connect(importAct, SIGNAL(triggered()), this, SLOT(importMenus()));

    exportAct = new QAction(QIcon(":/images/export.png"), tr("Export"), this);
    exportAct->setToolTip(tr("export menus"));
    connect(exportAct, SIGNAL(triggered()), this, SLOT(exportMenus()));

    manageMenusAct = new QAction(QIcon(":/images/manage_menus.png"), tr("Manage"), this);
    manageMenusAct->setToolTip(tr("manage menus"));
    connect(manageMenusAct, SIGNAL(triggered()), this, SLOT(manageMenus()));

    manageTakeAwayAct = new QAction(QIcon(":/images/manage_take_away.png"), tr("Take Away"), this);
    manageTakeAwayAct->setToolTip(tr("manage menus that taken away"));
    connect(manageTakeAwayAct, SIGNAL(triggered()), signal, SIGNAL(manageMenusTakenAway()));

    synchronousAct = new QAction(QIcon(":/images/synchronous.png"), tr("Synchronous"), this);
    synchronousAct->setToolTip(tr("synchronous menus to terminal devices"));
    connect(synchronousAct, SIGNAL(triggered()), this, SLOT(synchronous()));

    uploadAct = new QAction(QIcon(":/images/upload.png"), tr("Upload"), this);
    uploadAct->setToolTip(tr("upload menus to main server"));
    connect(uploadAct, SIGNAL(triggered()), signal, SIGNAL(upload()));

    setAct = new QAction(QIcon(":/images/set.png"), tr("Settings"), this);
    setAct->setToolTip(tr("settings"));
    connect(setAct, SIGNAL(triggered()), signal, SIGNAL(set()));

    aboutAct = new QAction(QIcon(":/images/about.png"), tr("About"), this);
    aboutAct->setToolTip(tr("about OpenMenus"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    exitAct = new QAction(QIcon(":/images/exit.png"), tr("Exit"), this);
    exitAct->setToolTip(tr("exit"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::setupDatabase()
{
    QDir dir(QDir::homePath());
    if(!dir.exists("OpenMenus/menus")){
        if(!dir.mkpath("OpenMenus/menus")){
            QMessageBox::critical(this, tr("ManageMenus"), tr("Dir create error"), QMessageBox::Ok);
            return;
        }
    }
    dir.cd("OpenMenus/menus");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setDatabaseName(dir.absolutePath()+"/menus.db");
    db.setUserName("lg");
    db.setPassword("12345");

    if(!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());
    }
    QSqlQuery query;
    query.exec("SELECT count(*) FROM sqlite_master WHERE type='table' AND name='menuList'");
    if(query.next()){
        int count = query.value(0).toInt();
        qDebug()<<count;
        if(count<1){
            if(!query.exec(QString("CREATE TABLE menuList(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(256), price DEC(14,4), description VARCHAR(4096), images VARCHAR(1024))"))){
                qDebug()<<"error:  "<<query.lastError().text();
            }
        }
    }
}

void MainWindow::creatMenus()
{
    _menuBar = menuBar();
    menuMenu = _menuBar->addMenu(tr("&Menu"));
    viewMenu = _menuBar->addMenu(tr("&View"));
    optionsMenu = _menuBar->addMenu(tr("&Options"));
    helpMenu = _menuBar->addMenu(tr("&Help"));

    menuMenu->addAction(importAct);
    menuMenu->addAction(exportAct);
    menuMenu->addSeparator();
    menuMenu->addAction(manageMenusAct);
    menuMenu->addAction(manageTakeAwayAct);
    menuMenu->addSeparator();
    menuMenu->addAction(synchronousAct);
    menuMenu->addAction(uploadAct);
}

void MainWindow::creatToolBar()
{
    toolBar = addToolBar(tr("ToolBar"));
    toolBar->setIconSize(QSize(32, 32));
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->setMovable(false);

    toolBar->addAction(importAct);
    toolBar->addAction(exportAct);
    toolBar->addAction(manageMenusAct);
    toolBar->addAction(manageTakeAwayAct);
    toolBar->addAction(synchronousAct);
    toolBar->addAction(uploadAct);
    toolBar->addAction(setAct);
    toolBar->addSeparator();
    toolBar->addAction(aboutAct);
    toolBar->addSeparator();
    toolBar->addAction(exitAct);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About OpenMenus"),
                       tr("<h2>OpenMenus 2.0.0</h2>"
                          "<p>CopyRright &copy; 2012 LG."
                          "<p>OpenMenus是一个点菜系统的服务器软件，请与OpenMenusClient点菜软件配合使用."));
}

void MainWindow::synchronous()
{
    SynchronousDialog s(this);
    s.exec();
}

void MainWindow::manageMenus()
{
    ManageMenus *m = new ManageMenus(this);
    m->show();
}

void MainWindow::importMenus()
{
    QDir dir(QDir::homePath());
    if(!dir.exists("OpenMenus/menus")){
        if(!dir.mkpath("OpenMenus/menus")){
            QMessageBox::critical(this, tr("ManageMenus"), tr("Dir create error"), QMessageBox::Ok);
            return;
        }
    }
    dir.cd("OpenMenus/menus");
    QString zipName = QFileDialog::getOpenFileName(this, tr("Open Import File"),QDir::homePath()+"/OpenMenus",tr("Menus (*.exp)"));
    if(zipName.isEmpty())
        return;
    QuaZip zip(zipName);
    zip.setFileNameCodec("UTF8");
    zip.setCommentCodec("UTF8");
    if(!zip.open(QuaZip::mdUnzip)){
        qWarning()<<QString("Couldn't open %1").arg(zipName);
        return;
    }
    for(bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()){
        QString fileName = QDir::homePath() + "/OpenMenus/menus/" + zip.getCurrentFileName();
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly)){
            qWarning()<< QString(tr("Couldn't open %1").arg(fileName));
            return;
        }
        QuaZipFile zipFile(&zip);
        if (!zipFile.open(QIODevice::ReadOnly)) {
               qWarning("testRead(): file.open(): %d", zipFile.getZipError());
               return;
        }

        while (!zipFile.atEnd()) {
            char buf[4096];
            qint64 l = zipFile.read(buf, 4096);
            if (l <= 0) {
                qWarning()<<"Couldn't read "<<zip.getCurrentFileName();
                return;
            }
            if (file.write(buf, l) != l) {
                qWarning()<<"Couldn't write to "<< fileName;
                return;
            }
        }
        file.close();
        zipFile.close();
    }
    zip.close();
}

void MainWindow::exportMenus()
{
    QDir dir(QDir::homePath()+"/OpenMenus/menus");
    if(!dir.exists())
        return;
    QString zipName = QFileDialog::getSaveFileName(this, tr("Export Menus"),QDir::homePath()+"/OpenMenus/OpenMenus",tr("Menus (*.exp)"));
    if(zipName.isEmpty())
        return;
    QuaZip zip(zipName);
    zip.setFileNameCodec("UTF8");
    zip.setCommentCodec("UTF8");
    if(!zip.open(QuaZip::mdCreate)){
        qWarning()<<QString("Couldn't open %1").arg(zipName);
        return;
    }

    QSqlTableModel model;
    model.setTable("menuList");
    model.select();
    QStringList files;
    for(int i=0;i<model.rowCount(); i++){
        QSqlRecord record = model.record(i);
        QStringList images = record.value("images").toString().split(";");
        images.removeLast();
        files += images;
    }
    files << "menus.xml"<<"noimage.jpg"<<"menus.db";
    foreach(QString fileName, files){
        QString filePath = QDir(dir).filePath(fileName);
        QFileInfo fileInfo(filePath);
        if(!fileInfo.exists()){
            continue;
        }
        QuaZipFile zipFile(&zip);
        if(!zipFile.open(QIODevice::WriteOnly, QuaZipNewInfo(fileName, filePath), 0, 0, fileInfo.isDir() ? 0 : 8)){
            qWarning()<<"Couldn't open " << fileName.toUtf8();
            return;
        }
        if(!fileInfo.isDir()){

            QFile file(filePath);
            if(!file.open(QIODevice::ReadOnly)){
                qWarning("Couldn't open %s", filePath.toUtf8().constData());
                return;
            }
            while (!file.atEnd()) {
                char buf[4096];
                qint64 l = file.read(buf, 4096);
                if (l <= 0) {
                qWarning("Couldn't read %s", filePath.toUtf8().constData());
                return;
                }
                if (zipFile.write(buf, l) != l) {
                    qWarning("Couldn't write to %s in %s",filePath.toUtf8().constData(),zipName.toUtf8().constData());
                    return;
                }
            }
            file.close();
        }
        zipFile.close();
    }
    zip.close();
    QMessageBox::information(this, "Export Menus", QString("Export complete!\nExport file: %1").arg(zipName), QMessageBox::Ok);
}

void MainWindow::loadSettings()
{

}

void MainWindow::saveSettings()
{

}
