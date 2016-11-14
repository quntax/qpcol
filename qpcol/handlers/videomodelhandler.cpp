#include "videomodelhandler.h"

const QString VideoModelHandler::sorting[] =
{
    "id_film",
    "filename",
    "tag_list",
    "size",
    "added_when"
};

const QString VideoModelHandler::order[] = { "ASC", "DESC" };

VideoModelHandler::VideoModelHandler()
{
    connection = Connection::instance()->get();
}

VideoModelHandler::VideoModelHandler(QSqlDatabase conn)
{
    connection = conn;
}

FilmTagCollection VideoModelHandler::getFilms()
{
    return getFilmsSorted(AddedWhen, Qt::DescendingOrder);
}

FilmTagCollection VideoModelHandler::getFilmsSorted(Sorting s, Qt::SortOrder o)
{
    filmTagCollection.clear();
    query = getQuery();
    setSorting(s, o);

    Query q(query, connection);
    QSqlQuery sql = q.execute();

    while (sql.next()) {
        FilmTag f;
        f = sql;
        filmTagCollection.append(f);
    }

    sql.finish();
    return filmTagCollection;
}

QString VideoModelHandler::getQuery()
{
    QString q;

    if (DATABASE_TYPE == MYSQL) {
        q = "SELECT id_film, filepath, filename, GROUP_CONCAT(CONCAT_WS(', ', tag.tag)) as tag_list, "
            "favorite, ROUND(size/1048576) as size, "
            "added_when, blacklist, marked, notes, original_url "
            "FROM film "
            "LEFT JOIN film_tag using (id_film) "
            "LEFT JOIN tag USING (id_tag) "
            "WHERE blacklist = 0 "
            "GROUP BY id_film ";
    }

    if (DATABASE_TYPE == SQLITE) {
        q = "SELECT id_film, filepath, filename, GROUP_CONCAT(tag.tag) as tag_list, "
            "favorite, ROUND(size/1048576) as size, "
            "added_when, blacklist, marked, notes, original_url "
            "FROM film "
            "LEFT JOIN film_tag using (id_film) "
            "LEFT JOIN tag USING (id_tag) "
            "WHERE blacklist = 0 "
            "GROUP BY id_film ";
    }
    sortSuffix.clear();

    return q;
}

void VideoModelHandler::setSorting(Sorting s, Qt::SortOrder o)
{
    sortSuffix = QString("ORDER BY %1 %2, %3 %4")
                 .arg(sorting[s])
                 .arg(order[o])
                 .arg(sorting[IdFilm])
                 .arg(order[o]);
    query.append(sortSuffix);
}
