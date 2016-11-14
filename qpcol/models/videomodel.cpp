#include "videomodel.h"

int VideoModel::rowCount(const QModelIndex &) const
{
    return collection.count();
}

int VideoModel::columnCount(const QModelIndex &) const
{
    return 12;
}

QVariant VideoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= collection.count())
        return QVariant();
    if (role == Qt::DisplayRole) {
        FilmTag current = collection.at(index.row());
        return QVariant(current.column(index.column()));
    } else {
        return QVariant();
    }
}

QVariant VideoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) {
        QString columnName;

        switch (section) {
        case FilmTag::FileName:
            columnName = "File name"; break;
        case FilmTag::TagNames:
            columnName = "Tags"; break;
        case FilmTag::Size:
            columnName = "Size"; break;
        case FilmTag::AddedWhen:
            columnName = "Date added"; break;
        default:
            columnName = QString("Column %1").arg(section);
        }

        return columnName;
    }
    else
        return QString("%1").arg(section);
}

void VideoModel::sort(int column, Qt::SortOrder order)
{
    switch (column) {
    case FilmTag::FileName:
        setCollection(vmh.getFilmsSorted(VideoModelHandler::FileName, order));
        break;
    case FilmTag::TagNames:
        setCollection(vmh.getFilmsSorted(VideoModelHandler::Tags, order));
        break;
    case FilmTag::Size:
        setCollection(vmh.getFilmsSorted(VideoModelHandler::Size, order));
        break;
    case FilmTag::AddedWhen:
        setCollection(vmh.getFilmsSorted(VideoModelHandler::AddedWhen, order));
        break;
    }
}
