#ifndef VIDEOMODELHANDLER_H
#define VIDEOMODELHANDLER_H

#include <QtCore>
#include <QtSql>

#include "film.h"
#include "filmtag.h"
#include "database.h"
#include "query.h"
#include "connection.h"

class VideoModelHandler
{
public:
    enum Sorting {
        IdFilm,
        FileName,
        Tags,
        Size,
        AddedWhen,
    };

    static const QString sorting[];
    static const QString order[];

    VideoModelHandler();
    VideoModelHandler(QSqlDatabase);

    FilmTagCollection getFilms();
    FilmTagCollection getFilmsSorted(Sorting, Qt::SortOrder);

private:
    FilmTag filmTag;
    FilmTagCollection filmTagCollection;
    QSqlDatabase connection;

    QString query;
    QString sortSuffix;

    QString getQuery();
    void setSorting(Sorting, Qt::SortOrder);
};

#endif // VIDEOMODELHANDLER_H
