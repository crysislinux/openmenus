#ifndef ADDNEWMENU_H
#define ADDNEWMENU_H

#include <QDialog>
#include <QString>

namespace Ui {
    class AddNewMenu;
}

class AddNewMenu : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewMenu(QWidget *parent = 0);
    ~AddNewMenu();

signals:
    bool addMenu(QString &name, QString &imagePath, QString &imagesPath, QString &unitPrice, QString &description);

public slots:
    void okClicked();
    void selectMainImage();
    void selectImages();
    void enableOkButton();
private:
    Ui::AddNewMenu *ui;
};

#endif // ADDNEWMENU_H
