#include <QtGui>
#include "managemenus.h"
#include "searchlineedit.h"
#include "addnewmenu.h"
#include "switchbutton.h"
#include <QSqlQuery>
#include <QDebug>
#include <QtAlgorithms>

MenusModel::MenusModel(QObject *parent) :
    QSqlTableModel(parent)
{
}
QVariant MenusModel::data(const QModelIndex &idx, int role) const
{
    if(role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;
    return QSqlTableModel::data(idx, role);
}
ManageMenus::ManageMenus(QWidget *parent) :
    QDialog(parent)
{

    setAttribute(Qt::WA_DeleteOnClose);

    m_model = new MenusModel(this);
    m_model->setTable("menuList");
    m_model->setHeaderData(ManageMenus_Name, Qt::Horizontal, tr("Name"));
    m_model->setHeaderData(ManageMenus_Price, Qt::Horizontal, tr("Price"));
    m_model->setHeaderData(ManageMenus_Description, Qt::Horizontal, tr("Description"));
    m_model->setHeaderData(ManageMenus_Images, Qt::Horizontal, tr("Images"));
    m_model->select();

    createWidgets();
    setWindowTitle(tr("Manage Menus"));
//    setWindowIcon(QIcon(":/images/OpenMenus.png"));
    resize(QSize(560, 400));
}

void ManageMenus::closeEvent(QCloseEvent *e)
{
    QDialog::closeEvent(e);
}

void ManageMenus::createWidgets()
{
    SwitchButton *showDetail = new SwitchButton;
    QPushButton *deleteSelected = new QPushButton(tr("Delete"));
    deleteSelected->setFocusPolicy(Qt::NoFocus);
    QPushButton *add = new QPushButton(tr("Add"));
    add->setFocusPolicy(Qt::NoFocus);
    SearchLineEdit *search = new SearchLineEdit;

    connect(add, SIGNAL(clicked()), this, SLOT(addMenuDialog()));
    connect(deleteSelected, SIGNAL(clicked()), this, SLOT(deleteSelected()));
    connect(search, SIGNAL(searchByName(QString&)), this, SLOT(searchByName(QString&)));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(showDetail);
    hLayout->addSpacing(10);
    hLayout->addWidget(deleteSelected);
    hLayout->addWidget(add);
    hLayout->addSpacing(18);
    hLayout->addWidget(search);

    tableView = new QTableView;

    tableView->setModel(m_model);
    tableView->setColumnHidden(ManageMenus_Id, true);
    tableView->setAlternatingRowColors(true);
    tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
//    tableView->setSpan(0, 1, 2, 1);


//    tableView->horizontalHeader()->setStretchLastSection(true);


    QPushButton *close = new QPushButton(tr("Close"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(close);

    connect(close, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hLayout);
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void ManageMenus::searchByName(QString& name)
{
    QString filter;
    if(!name.isEmpty()){
        filter = "name like \"%" + name + "%\"";
    }
    else
        filter = "";
    m_model->setFilter(filter);
    m_model->select();
}

void ManageMenus::deleteSelected()
{
    QModelIndexList menusSelected = tableView->selectionModel()->selectedRows(ManageMenus_Name);
    if(menusSelected.isEmpty()){
        QMessageBox::warning(this, tr("Delete Menus"), tr("Please select menu(s) to be deleted!"), QMessageBox::Ok);
        return;
    }
    QString names;
    QList<int> rowList;
    for(int i=0;i<menusSelected.count();i++){
        names+=m_model->data(menusSelected.at(i)).toString() + "; ";
        rowList.append(menusSelected.at(i).row());
    }
    qSort(rowList.begin(), rowList.end(), qGreater<int>());
    if(QMessageBox::warning(this, tr("Delete Menus"), tr("Are you sure to delete %1").arg(names), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
        for(int i=0;i<rowList.count();i++){
            m_model->removeRows(rowList.at(i), 1);
        }
        m_model->submitAll();
    }
}

void ManageMenus::addMenuDialog()
{

    AddNewMenu addNewMenuDialog(this);

    connect(&addNewMenuDialog, SIGNAL(addMenu(QString&,QString&,QString&,QString&,QString&)), this, SLOT(addMenuToDatabase(QString&,QString&,QString&,QString&,QString&)));
    addNewMenuDialog.exec();
}

void ManageMenus::addMenuToDatabase(QString &name, QString &imagePath, QString &imagesPath, QString &unitPrice, QString &description)
{ 
    m_model->insertRows(0, 1);
    m_model->setData(m_model->index(0, 1), name);
    m_model->setData(m_model->index(0, 2), unitPrice.toFloat());
    m_model->setData(m_model->index(0, 3), description);
    m_model->submitAll();
    QString images;
    QString stripedImages;
    int id = 0;
    QSqlQuery query;
    query.exec("SELECT last_insert_rowid()");

    if(query.next()){
        id = query.value(0).toInt();
        qDebug()<<"id: "<<id;
    }
    int imageCount = 0;
    if(!imagePath.isEmpty()){
        images = imagePath+";"+imagesPath;
//        qDebug()<<images;
    }
    else
        images = imagesPath;
    if(!images.isEmpty()){
        QDir dir(QDir::homePath());
        if(!dir.exists("OpenMenus/menus")){
            if(!dir.mkpath("OpenMenus/menus")){
                QMessageBox::critical(this, tr("ManageMenus"), tr("Dir create error"), QMessageBox::Ok);
                return;
            }
        }
        dir.cd("OpenMenus/menus");
        QStringList imagesList = images.split(";");
        for(int i=0; i<imagesList.count()-1; i++){
            QFileInfo imageInfo(imagesList.at(i));
            QFile image(imagesList.at(i));
            qDebug()<<image.fileName();

            QString imageName = QString::number(id)+"_"+QString::number(imageCount) + "." + imageInfo.suffix();
            if(image.copy(dir.absolutePath()+"/"+imageName)){
                stripedImages += imageName + ";";
                imageCount++;
            }else{
                qDebug()<<"copyerror: "<<imageName;
            }
        }
    }

    m_model->setFilter(QString("id = %1").arg(id));
    m_model->select();
    if(m_model->rowCount() == 1){
        m_model->setData(m_model->index(0, 4), stripedImages);
        m_model->submitAll();
        m_model->setFilter("");
        m_model->select();
    }
}

