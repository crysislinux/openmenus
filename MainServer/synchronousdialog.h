#ifndef SYNCHRONOUSDIALOG_H
#define SYNCHRONOUSDIALOG_H

#include <QDialog>
class QProgressBar;

class SynchronousDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SynchronousDialog(QWidget *parent = 0);
    
protected:
    void closeEvent(QCloseEvent *e);
signals:
    
public slots:
    void begin();
    
private:
    QProgressBar *progressBar;
    bool isCompleted;
};

#endif // SYNCHRONOUSDIALOG_H
