#ifndef ANIMALMODEL_H
#define ANIMALMODEL_H

#include <QAbstractListModel>
#include <QStringList>

 class Animal
 {
 public:
     Animal(const QString &type, const QString &size);

     QString type() const;
     QString size() const;

 private:
     QString m_type;
     QString m_size;
 };
class AnimalModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AnimalRoles {
        TypeRole = Qt::UserRole + 1,
        SizeRole
    };

    AnimalModel(QObject *parent = 0);
    void addAnimal(const Animal &animal);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    QList<Animal> m_animals;
};

#endif // ANIMALMODEL_H
