#include "videotagsmodel.h"

VideoTagsModel::VideoTagsModel(int idFilm, QObject *parent) :
    QStringListModel(parent)
{
    FilmHandler fh;
    tc = fh.getFilmTags(idFilm);

    QListIterator<Tag> i(tc);

    while (i.hasNext()) {
        Tag t = i.next();
        tagNames.append(t.name());
    }

    setStringList(tagNames);
}
