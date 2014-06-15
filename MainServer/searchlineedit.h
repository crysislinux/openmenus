#ifndef SEARCHLINEEDIT_H
#define SEARCHLINEEDIT_H

#include <QLineEdit>
class QComboBox;
class QPushButton;

class SearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit SearchLineEdit(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);
signals:
    void searchByName(QString &name);

public slots:
    void setHintText(int index);
    void setInputFlag();
    void startSearch();
private:
    QComboBox *searchCategory;
    QPushButton *searchButton;
    bool hasInput;
};

#endif // SEARCHLINEEDIT_H
