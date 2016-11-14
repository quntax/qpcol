#ifndef FILMHANDLER_H
#define FILMHANDLER_H

#include <QtCore>
#include <QtSql>

#include "film.h"
#include "tag.h"
#include "database.h"
#include "query.h"
#include "connection.h"
#include "dirscanner.h"

class FilmHandler
{
    public:
        FilmHandler();
        FilmHandler(QSqlDatabase);

        Film getFilmById(int);
        Film getFilmByHash(QString);
        Film getLastQueryResult();

        FilmCollection getAllFilms();
        FilmCollection getAllActiveFilms();
        FilmCollection getFilmsByIdTag(int);
        TagCollection getFilmTags(int);
        TagCollection getFilmTags(int, Tag::Column orderBy);
        QList<int> getFilmIdTags(int);

        void toggleFavorite(int);
        void toggleMarked(int);
        void deleteVideo(int);
        void updateNotes(int, QByteArray);

        void addRemoveScanResult(const HashList &);
        QStringList getDeadEntries(const HashList &);

    private:
        Film film;
        FilmCollection filmCollection;
        QSqlDatabase connection;
};

#endif // FILMHANDLER_H
