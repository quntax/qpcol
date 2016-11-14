#include "tagmodel.h"

int TagModel::rowCount(const QModelIndex &) const
{
    return collection.count();
}


int TagModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant TagModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= collection.count())
        return QVariant();
    if (role == Qt::DisplayRole) {
        Tag current = collection.at(index.row());
        return current.column(index.column());
    } else {
        return QVariant();
    }
}
