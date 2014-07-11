#include "mylistmodel.h"

MyListModel::MyListModel(QList<Student> *ss, QObject *parent) :
    QAbstractListModel(parent)
{
    s = ss;
}

QVariant MyListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || s == NULL)
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return s->at(index.row()).name;
    }
    if (role == Qt::CheckStateRole) {
        return s->at(index.row()).present;
    }

    return QVariant();
}


bool MyListModel::setData (const QModelIndex & index, const QVariant & value, int role)
{
    if (!index.isValid() || s == NULL)
        return false;
    if (role == Qt::EditRole) {
        (*s)[index.row()].name = value.toString();
    }
    if (role == Qt::CheckStateRole) {
        (*s)[index.row()].present = (Qt::CheckState)value.toUInt();
    }
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags MyListModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
        return (Qt::ItemIsEnabled |
                Qt::ItemIsSelectable |
                Qt::ItemIsDragEnabled |
                Qt::ItemIsEditable |
                Qt::ItemIsUserCheckable);

    return Qt::ItemIsDropEnabled;
}

bool MyListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;

    if (row >= s->size() || row + count <= 0 || s == NULL)
        return false;

    int beginRow = qMax(0, row);
    int endRow = qMin(row + count - 1, s->size() - 1);

    beginRemoveRows(parent, beginRow, endRow);

    while (beginRow <= endRow) {
        s->removeAt(beginRow);
        ++beginRow;
    }

    endRemoveRows();
    return true;
}

QModelIndex MyListModel::addEntry(QString ent)
{
    if (s == NULL) return QModelIndex();

    beginInsertRows(QModelIndex(), s->size(), s->size());

    Student st; st.name = ent; st.present = Qt::Checked;
    s->append(st);

    endInsertRows();
    return index(s->size()-1, 0);
}

int MyListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || s == NULL)
        return 0;
    else
        return s->size();
}

Qt::DropActions MyListModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}
