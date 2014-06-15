#ifndef ICONVIEW_H
#define ICONVIEW_H

#include <QFrame>
class QAbstractItemModel;

class IconView : public QFrame
{
    Q_OBJECT
public:
    explicit IconView(QAbstractItemModel *model, QWidget *parent = 0);
protected:
    void resizeEvent(QResizeEvent *e);
signals:
    void sizeChanged(int width, int height);
public slots:
private:
    QAbstractItemModel *m_model;
};

#endif // ICONVIEW_H
