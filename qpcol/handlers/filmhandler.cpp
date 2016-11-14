#include "filmhandler.h"

FilmHandler::FilmHandler()
{
    connection = Connection::instance()->get();
}

FilmHandler::FilmHandler(QSqlDatabase conn)
{
    connection = conn;
}

Film FilmHandler::getFilmById(int id_film)
{
    Film f;
    Query q("SELECT * FROM film WHERE id_film = ?", connection);
    q << id_film;

    QSqlQuery sql = q.execute();
    sql.next();

    f = sql;
    return f;
}

Film FilmHandler::getFilmByHash(QString hash)
{
    Film f;
    Query q("SELECT * FROM film WHERE hash LIKE ?", connection);
    q << hash;

    QSqlQuery sql = q.execute();
    sql.next();

    f = sql;
    return f;
}

Film FilmHandler::getLastQueryResult()
{
    return film;
}

FilmCollection FilmHandler::getAllFilms()
{
    filmCollection.clear();
    Query q("SELECT * FROM film ORDER BY added_when DESC", connection);

    QSqlQuery sql = q.execute();

    while (sql.next()) {
        Film f;
        f = sql;
        filmCollection.append(f);
    }

    return filmCollection;
}

FilmCollection FilmHandler::getAllActiveFilms()
{
    filmCollection.clear();
    Query q("SELECT * FROM film WHERE blacklist = 0", connection);

    QSqlQuery sql = q.execute();

    while (sql.next()) {
        Film f;
        f = sql;
        filmCollection.append(f);
    }

    return filmCollection;
}

FilmCollection FilmHandler::getFilmsByIdTag(int id_tag)
{
    filmCollection.clear();
    Query q("SELECT * FROM film "
            "JOIN film_tag USING(id_film) "
            "WHERE film_tag.id_tag = ? "
            "ORDER BY added_when DESC",
            connection);
    q << id_tag;

    QSqlQuery sql = q.execute();

    while (sql.next()) {
        Film f;
        f = sql;
        filmCollection.append(f);
    }

    return filmCollection;
}

TagCollection FilmHandler::getFilmTags(int id_film)
{
    return getFilmTags(id_film, Tag::Name);
}

TagCollection FilmHandler::getFilmTags(int id_film, Tag::Column orderBy = Tag::IdTag)
{
    QString sql("SELECT tag.id_tag, tag.tag "
              "FROM film_tag "
              "JOIN tag USING (id_tag) "
              "WHERE film_tag.id_film = ? "
              "ORDER BY %1");

    if (orderBy == Tag::IdTag) {
        sql = sql.arg("tag.id_film ASC");
    } else if (orderBy == Tag::Name) {
        sql = sql.arg("tag.tag ASC");
    }

    Query q(sql, connection);
    q << id_film;

    QSqlQuery sqlQuery = q.execute();
    TagCollection tc;

    while (sqlQuery.next()) {
        Tag t(sqlQuery);
        tc.append(t);
    }

    return tc;
}

QList<int> FilmHandler::getFilmIdTags(int id_film)
{
    Query q("SELECT tag.id_tag "
            "FROM film_tag "
            "JOIN tag USING (id_tag) "
            "WHERE film_tag.id_film = ?",
            connection);
    q << id_film;

    QSqlQuery sql = q.execute();
    QList<int> output;

    while (sql.next()) {
        output.append(sql.value(0).toInt());
    }

    return output;
}

void FilmHandler::toggleFavorite(int idFilm)
{
    Query q("UPDATE film SET favorite = NOT favorite WHERE id_film = ?",
            connection);
    q << idFilm;
    q.execute();
}

void FilmHandler::toggleMarked(int idFilm)
{
    Query q("UPDATE film SET marked = NOT marked WHERE id_film = ?",
            connection);

    q << idFilm;
    q.execute();
}

void FilmHandler::deleteVideo(int idFilm)
{
    Query q("UPDATE film SET blacklist = 1 WHERE id_film = ?",
            connection);
    q << idFilm;
    q.execute();
}

void FilmHandler::updateNotes(int idFilm, QByteArray filmNotes)
{
    Query q("UPDATE film SET notes = ? WHERE id_film = ?",
            connection);
    q << filmNotes << idFilm;
    q.execute();

    film.setNotes(filmNotes);
}

void FilmHandler::addRemoveScanResult(const HashList & scanResults)
{
    if (scanResults.isEmpty()) {
        return;
    }

    if (DATABASE_TYPE == SQLITE) {
        connection.transaction();
//        Query startTransaction("BEGIN TRANSACTION", connection);
//        startTransaction.execute();
    }

    if (DATABASE_TYPE == MYSQL) {
        Query startTransaction("START TRANSACTION", connection);
        startTransaction.execute();
    }

    QHashIterator<QByteArray, QString> iterator(scanResults);
    while (iterator.hasNext()) {
        iterator.next();

        Film f(getFilmByHash(iterator.key()));

        if (! f) { // add film
            qDebug() << "Adding" << iterator.value();

            Film newFilm(iterator.key(), iterator.value());
            newFilm.add();
        } else {
            if (f.isBlacklist()) {
                continue;
            }

            if (! QFile::exists(f.filePath())) {
                qDebug() << "Exists, but moved:" << f.filePath() << "=>" << iterator.value();
                f.updatePath(iterator.value());
            }
        }
    }


    if (DATABASE_TYPE == SQLITE) {
        connection.commit();
//        Query commitTransaction("COMMIT TRANSACTION", connection);
//        commitTransaction.execute();
    }

    if (DATABASE_TYPE == MYSQL) {
        Query commitTransaction("COMMIT", connection);
        commitTransaction.execute();
    }
}

QStringList FilmHandler::getDeadEntries(const HashList & scanResults)
{
    FilmCollection fc;
    fc = getAllActiveFilms();

    QListIterator<Film> filmiterator(fc);
    QStringList output;

    while (filmiterator.hasNext()) {
        Film f = filmiterator.next();
        QByteArray iHash = f.fileHash();
        QFileInfo info(QString(f.filePath()));

        if (! scanResults.contains(iHash) && ! info.isReadable()) {
            output.append(f.filePath());
            QString msg = QString("Not found in scan results: ID %1 %2 %3")
                .arg(f.id())
                .arg(QString(iHash))
                .arg(QString(f.filePath()));

            qDebug() << msg;
        }
    }

    return output;
}
