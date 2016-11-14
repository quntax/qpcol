#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H

#include <QAbstractTableModel>
#include "filmtag.h"
#include "videomodelhandler.h"

class VideoModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    VideoModel(const FilmTagCollection &f = FilmTagCollection(), QObject *parent = 0) :
            QAbstractTableModel(parent) { setCollection(f); }

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setCollection(const FilmTagCollection &f) { collection = f; }
    void sort(int column, Qt::SortOrder order);

    void setReadOnly(bool s) { readOnly = s; }
    bool isReadOnly() { return readOnly; }

protected:
    FilmTagCollection collection;
    VideoModelHandler vmh;
    bool readOnly;
};

#endif // VIDEOMODEL_H
