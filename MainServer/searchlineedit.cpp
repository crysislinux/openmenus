#include <QtGui>
#include "searchlineedit.h"

SearchLineEdit::SearchLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    searchCategory = new QComboBox(this);
    searchCategory->addItem(QIcon(":/images/listview.png"),tr("id"));
    searchCategory->addItem(QIcon(":/images/course.png"),tr("name"));
    searchCategory->setCursor(Qt::ArrowCursor);
    searchCategory->setStyleSheet(QString("QComboBox { border: none; padding: 0px; }"
                                  "QComboBox::drop-down { border-image: url(:/images/down-arrow.png); border-width: 8px; width: 5px; height: 5px;  subcontrol-origin: margin; subcontrol-position: center right;}"
                                          ));
    searchButton = new QPushButton(this);
    searchButton->setIcon(QIcon(":/images/search.png"));
    searchButton->setStyleSheet("QPushButton { border: none; padding: 0px; }");
    searchButton->setCursor(Qt::PointingHandCursor);
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
  //  setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(searchCategory->sizeHint().width() + frameWidth + 1));
    setStyleSheet(QString("SearchLineEdit { color: gray;  padding-left: %1px; padding-right: %2px;} ").arg(searchCategory->sizeHint().width()).arg(searchButton->sizeHint().width()));
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), searchCategory->sizeHint().width() + frameWidth * 2 + 150 + searchButton->sizeHint().width()),
        qMax(msz.height(), searchCategory->sizeHint().height() + frameWidth * 2 + 2));

    connect(searchCategory, SIGNAL(currentIndexChanged(int)), this, SLOT(setHintText(int)));
    connect(this, SIGNAL(textChanged(QString)), this, SLOT(setInputFlag()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(startSearch()));
    connect(this, SIGNAL(returnPressed()), this, SLOT(startSearch()));
    searchCategory->setCurrentIndex(1);
    hasInput = false;
}

void SearchLineEdit::startSearch()
{
    QString name;
    switch (searchCategory->currentIndex()){
    case 0:break;
    case 1:
        if(hasInput){
            name = text();
        }
        emit searchByName(name);
        break;
    default:break;
    }
}

void SearchLineEdit::setInputFlag()
{
    if(text().isEmpty())
        hasInput = false;
    else
        hasInput = true;
}

void SearchLineEdit::setHintText(int index)
{
    switch(index){
    case 0:
        setText(tr("Enter course index"));
        break;
    case 1:
        setText(tr("Enter course name"));
        break;
    case 2:
        setText(tr("2"));
        break;
    default:break;
    }
    hasInput = false;
}

void SearchLineEdit::resizeEvent(QResizeEvent *)
{
    QSize sz1 = searchButton->sizeHint();
    QSize sz2 = searchCategory->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    searchButton->move(rect().right() - frameWidth - sz1.width(),
        (rect().bottom() + 1 - sz1.height())/2);
    searchCategory->move(rect().left(),
          (rect().bottom() +1 - sz2.height())/2);
}


void SearchLineEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    if(!hasInput)
        clear();
    setStyleSheet(QString("SearchLineEdit { color: black;  padding-left: %1px; padding-right: %2px;} ").arg(searchCategory->sizeHint().width()).arg(searchButton->sizeHint().width()));
}

void SearchLineEdit::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    if(text().isEmpty()){
        setStyleSheet(QString("SearchLineEdit { color: gray;  padding-left: %1px; padding-right: %2px;} ").arg(searchCategory->sizeHint().width()).arg(searchButton->sizeHint().width()));
        setHintText(searchCategory->currentIndex());
        hasInput = false;
    }
}
