#ifndef MYLISTMODEL_H
#define MYLISTMODEL_H

#include <QAbstractListModel>
#include "data.h"

class MyListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MyListModel(QList<Student> *ss, QObject *parent = 0);
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool removeRows(int row, int count, const QModelIndex &parent);
    QModelIndex addEntry(QString ent);

    int rowCount(const QModelIndex &parent) const;
    Qt::DropActions supportedDropActions() const;

    bool setData (const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    QList<Student> *s;
signals:
    
public slots:
    
};

#endif // MYLISTMODEL_H
