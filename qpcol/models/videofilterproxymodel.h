#ifndef VIDEOFILTERPROXYMODEL_H
#define VIDEOFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "tag.h"
#include "filmtag.h"
#include "filmhandler.h"

class VideoFilterProxyModel : public QSortFilterProxyModel
{
        Q_OBJECT

    public:
        explicit VideoFilterProxyModel(QObject *parent = 0);

        void setFilterTagList(TagCollection &);
        void setFavoritesFilter(bool useFilter);
        void setUntaggedFilter(bool useFilter);
        void setTextFilter(const QString & text);

    protected:
        bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
        bool useFavoritesFilter;
        bool useUntaggedFilter;

        QString textFilter;

        QList<Tag> filterTagList;
        QVariantList filterIdTagList;
};

#endif // VIDEOFILTERPROXYMODEL_H
