#ifndef MANAGEMENUS_H
#define MANAGEMENUS_H

#include <QDialog>
#include <QSqlTableModel>

class QTableView;

class MenusModel : public QSqlTableModel
{
    Q_OBJECT
public:
    MenusModel(QObject *parent = 0);
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
};

class ManageMenus : public QDialog
{
    Q_OBJECT
public:
    enum{
        ManageMenus_Id = 0,
        ManageMenus_Name = 1,
        ManageMenus_Price = 2,
        ManageMenus_Description = 3,
        ManageMenus_Images = 4
    };
    explicit ManageMenus(QWidget *parent = 0);
    
protected:
    void closeEvent(QCloseEvent *);
signals:
    
public slots:
    void addMenuDialog();
    void addMenuToDatabase(QString &name, QString &imagePath, QString &imagesPath, QString &unitPrice, QString &description);
    void deleteSelected();
    void searchByName(QString &name);
private:
    void createWidgets();
    MenusModel *m_model;
    QTableView *tableView;
};

#endif // MANAGEMENUS_H
