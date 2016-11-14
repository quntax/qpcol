#include "videofilterproxymodel.h"

VideoFilterProxyModel::VideoFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

bool VideoFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
    QModelIndex indexTags = sourceModel()->index(source_row, FilmTag::IdTagList, source_parent);
    QModelIndex indexTagNames = sourceModel()->index(source_row, FilmTag::TagNames, source_parent);
    QModelIndex indexFavorite = sourceModel()->index(source_row, FilmTag::Favorite, source_parent);

    QVariantList filmTags = sourceModel()->data(indexTags).toList();

    bool isTagged = ! filmTags.isEmpty();
    bool isFavorite = sourceModel()->data(indexFavorite).toBool();
    bool useTagFilter = ! this->filterTagList.isEmpty();
    bool useTextFilter = ! this->textFilter.isEmpty();

    if (! (useTagFilter || this->useFavoritesFilter || this->useUntaggedFilter || useTextFilter)) {
        return true;
    }
    if (this->useUntaggedFilter && isTagged) {
        return false;
    }

    if ((this->useFavoritesFilter && ! isFavorite)
    || (useTagFilter && filmTags.isEmpty())) {
        return false;
    }

    QListIterator<QVariant> iterator(filterIdTagList);
    while (iterator.hasNext()) {
        if (! filmTags.contains(iterator.next().toInt())) {
            return false;
        }
    }

    QString tagNames = sourceModel()->data(indexTagNames).toString();

    if (useTextFilter) {
        QModelIndex indexFilePath = sourceModel()->index(source_row, FilmTag::FilePath, source_parent);
        QModelIndex indexOriginalUrl = sourceModel()->index(source_row, FilmTag::OriginalUrl, source_parent);
        QModelIndex indexFileNotes = sourceModel()->index(source_row, FilmTag::Notes, source_parent);

        QString filePath = sourceModel()->data(indexFilePath).toString();
        QString originalUrl = sourceModel()->data(indexOriginalUrl).toString();
        QString fileNotes = sourceModel()->data(indexFileNotes).toString();


        return tagNames.contains(this->textFilter, Qt::CaseInsensitive)
                || filePath.contains(this->textFilter, Qt::CaseInsensitive)
                || originalUrl.contains(this->textFilter, Qt::CaseInsensitive)
                || fileNotes.contains(this->textFilter, Qt::CaseInsensitive);

    }

    return true;
}

void VideoFilterProxyModel::setFilterTagList(TagCollection & tagList) {
    filterTagList = tagList;
    filterIdTagList.clear();

    QListIterator<Tag> iterator(tagList);
    while (iterator.hasNext()) {
        Tag t = iterator.next();
        filterIdTagList.append(t.id());
    }

    invalidateFilter();
}

void VideoFilterProxyModel::setFavoritesFilter(bool useFilter) {
    useFavoritesFilter = useFilter;
    invalidateFilter();
}

void VideoFilterProxyModel::setUntaggedFilter(bool useFilter) {
    useUntaggedFilter = useFilter;
    invalidateFilter();
}

void VideoFilterProxyModel::setTextFilter(const QString & text) {
    textFilter = text;
    invalidateFilter();
}
