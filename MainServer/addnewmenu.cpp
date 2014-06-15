#include <QtGui>
#include "addnewmenu.h"
#include "ui_addnewmenu.h"

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>

AddNewMenu::AddNewMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewMenu)
{
    ui->setupUi(this);
    QRegExp regExp("[0-9]{1,14}([.][0-9]{0,4})?");
    ui->unitPrice->setValidator(new QRegExpValidator(regExp, this));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(ui->imagesButton, SIGNAL(clicked()), this, SLOT(selectImages()));
    connect(ui->mainImageButton, SIGNAL(clicked()), this, SLOT(selectMainImage()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->name, SIGNAL(textChanged(QString)), this, SLOT(enableOkButton()));
    connect(ui->unitPrice, SIGNAL(textChanged(QString)), this, SLOT(enableOkButton()));
    ui->name->setFocus();
    ui->okButton->setEnabled(false);
}

AddNewMenu::~AddNewMenu()
{
    delete ui;
}

void AddNewMenu::enableOkButton()
{
    if(!ui->name->text().isEmpty() && !ui->unitPrice->text().isEmpty())
        ui->okButton->setEnabled(true);
    else
        ui->okButton->setEnabled(false);
}

void AddNewMenu::okClicked()
{
    QString name = ui->name->text();
    QString imagePath = ui->imagePath->text();
    QString imagesPath = ui->imagesPath->text();
    QString price = ui->unitPrice->text();
    QString description = ui->description->toPlainText();



    emit addMenu(name, imagePath, imagesPath, price, description);
    close();
}

void AddNewMenu::selectImages()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                                    tr("Input main image"), ".", "Images (*.bmp *.png *.xpm *.jpg)");
    QString fileName;
    for (int i = 0; i < fileNames.size(); ++i){
        fileName += fileNames.at(i);
        fileName += ";";
    }
    ui->imagesPath->setText(fileName);
}

void AddNewMenu::selectMainImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Input images"), ".", "Images (*.bmp *.png *.xpm *.jpg)");
    if(!fileName.isEmpty())
        ui->imagePath->setText(fileName);
}
