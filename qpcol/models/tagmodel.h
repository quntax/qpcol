#ifndef TAGMODEL_H
#define TAGMODEL_H

#include <QAbstractListModel>
#include "taghandler.h"

class TagModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TagModel(const TagCollection &t = TagCollection(), QObject *parent = 0) :
            QAbstractListModel(parent) { collection = t; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &) const;

protected:
    TagCollection collection;

};

#endif // TAGMODEL_H
