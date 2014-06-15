#include <QtGui>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "synchronousdialog.h"

SynchronousDialog::SynchronousDialog(QWidget *parent) :
    QDialog(parent), isCompleted(true)
{
    progressBar = new QProgressBar;
    progressBar->setMaximum(100);
    progressBar->setMinimum(0);
    QLabel *label = new QLabel(tr("Process"));
    QHBoxLayout *progressLayout = new QHBoxLayout;
    progressLayout->addWidget(label);
    progressLayout->addWidget(progressBar);
    QPushButton *begin = new QPushButton(tr("Synchronous"));
    QPushButton *cancel = new QPushButton(tr("Cancel"));
    connect(begin, SIGNAL(clicked()), this, SLOT(begin()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(begin);
    buttonLayout->addWidget(cancel);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(progressLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setWindowTitle(tr("Synchronous"));
}
#include <QDebug>
void SynchronousDialog::begin()
{
    QDir dir(QDir::homePath());
    if(!dir.exists("OpenMenus/menus")){
        if(!dir.mkpath("OpenMenus/menus")){
            QMessageBox::critical(this, tr("Synchronous"), tr("Dir create error"), QMessageBox::Ok);
            return;
        }
    }
    dir.cd("OpenMenus/menus");
    QString fileName = dir.absolutePath()+"/menus.xml";
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::critical(this, tr("Synchronous"), tr("menus.xml create error"), QMessageBox::Ok);
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("entry");

    QSqlTableModel model;
    model.setTable("menuList");
    model.select();
    int idIndex = model.record().indexOf("id");
    int nameIndex = model.record().indexOf("name");
    int priceIndex = model.record().indexOf("price");
    int desIndex = model.record().indexOf("description");
    int imagesIndex = model.record().indexOf("images");
    int step = 0;
    if(model.rowCount() > 0)
        step = (progressBar->maximum()-progressBar->minimum())/model.rowCount();
    for(int i=0;i<model.rowCount();i++){
        QSqlRecord record = model.record(i);
        QString id = record.value(idIndex).toString();
        QString name = record.value(nameIndex).toString();
        QString price = record.value(priceIndex).toString();
        QString description = record.value(desIndex).toString();
        QString images = record.value(imagesIndex).toString();
        xmlWriter.writeStartElement("menu");
        xmlWriter.writeTextElement("id", id);
        xmlWriter.writeTextElement("name", name);
        xmlWriter.writeTextElement("price", price);
        xmlWriter.writeTextElement("description", description);
        xmlWriter.writeTextElement("images", images);
        xmlWriter.writeEndElement();
        progressBar->setValue(step*i);
    }
    progressBar->setValue(progressBar->maximum());
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    isCompleted = true;
    QMessageBox::information(this, tr("Synchronous"), tr("Synchronous complete"), QMessageBox::Ok);
    close();
}

void SynchronousDialog::closeEvent(QCloseEvent *e)
{
    if(!isCompleted){
        QMessageBox::warning(0, tr("Synchronous"), tr("You must wait untill the synchronous is complete"), QMessageBox::Ok);
        e->ignore();
        return;
    }
    QDialog::closeEvent(e);
}
