#include "film.h"

Film::Film(const QSqlQuery &query)
{
    id_film = 0;
    *this = query;
}

Film::Film(const QByteArray & md5Hash)
{
    Query q("SELECT * FROM film WHERE hash = ?",
            Connection::instance()->get());
    q << md5Hash;
    *this = q.execute();
    q.finish();
}

Film::Film(const QByteArray &md5Hash, const QString &filePath)
{
    filepath = filePath.toUtf8();
    original_filepath = filePath.toUtf8();
    original_url = QByteArray("");
    hash = md5Hash;

    QFileInfo fi(filePath);
    filename = fi.fileName().toUtf8();
    size = fi.size();
    blacklist = 0;
    favorite = 0;
    marked = 0;
    added_when = QDateTime::currentDateTime();
    filmnotes = QByteArray("");
}

Film &Film::operator=(const QSqlQuery &query)
{
    if (! query.isValid()) {
        id_film = 0;
        return *this;
    }

    id_film = query.value(IdFilm).toInt();
    hash = query.value(Hash).toByteArray();
    filepath= query.value(FilePath).toByteArray();
    filename = query.value(FileName).toByteArray();
    size = query.value(Size).toInt();
    original_filepath = query.value(OriginalFilePath).toByteArray();
    original_url = query.value(OriginalUrl).toByteArray();
    blacklist = query.value(Blacklist).toBool();
    favorite = query.value(Favorite).toBool();
    marked= query.value(Marked).toBool();
    added_when = query.value(AddedWhen).toDateTime();
    filmnotes = query.value(Notes).toByteArray();

    return *this;
}

void Film::tag(const Tag &tag)
{
    Query q("INSERT INTO film_tag VALUES (?, ?)",
            Connection::instance()->get());
    q << id_film << tag.id();
    q.execute();
    q.finish();
}

void Film::untag(const Tag &tag)
{
    Query q("DELETE FROM film_tag WHERE id_film = ? AND id_tag = ?",
            Connection::instance()->get());
    q << id_film << tag.id();
    q.execute();
    q.finish();
}

void Film::add()
{
    Query q("INSERT INTO film (hash, filepath, filename, size, original_filepath) "
            "VALUES (?, ?, ?, ?, ?)", Connection::instance()->get());
    q << hash << filepath << filename << size << original_filepath;
    q.execute();
    q.finish();
}

void Film::updatePath(const QString &filepath)
{
    QFileInfo fi(filepath);
    QString filename = fi.fileName();

    Query q("UPDATE film SET filepath = ?, filename = ?, size = ? WHERE id_film = ?",
            Connection::instance()->get());
    q << filepath.toUtf8() << filename.toUtf8() << fi.size() << id_film;
    q.execute();
    q.finish();
}

// it will be null in most cases if added by dir scanning feature of QPcol
void Film::setOriginalUrl(const QString & url)
{
    Query q("UPDATE film SET original_url = ? WHERE id_film = ?",
            Connection::instance()->get());
    q << url.toLocal8Bit() << id_film;
    q.execute();
    q.finish();
}

void Film::setNotes(const QString & notes)
{
    filmnotes = notes.toUtf8();

    Query q("UPDATE film SET notes = ? WHERE id_film = ?",
            Connection::instance()->get());
    q << filmnotes << id_film;
    q.execute();
    q.finish();
}

void Film::setHash(const QByteArray & md5sum)
{
    hash = md5sum;
}

QString Film::insertFilmQuery()
{
    return QString("INSERT INTO `film` "
                   "VALUES(%1);\n").arg(queryPartFilm());
}

QString Film::queryPartFilm()
{
    QStringList filmData;
    filmData << QString::number(id_film)
            << QString(hash)
            << QString(filepath)
            << QString(filename)
            << QString::number(size)
            << QString(original_filepath)
            << QString::number(blacklist)
            << QString::number(favorite)
            << QString::number(marked)
            << timestampString()
            << QString(filmnotes);

    QStringList queryElements;
    QStringListIterator iterator(filmData);

    while (iterator.hasNext()) {
        QString element = iterator.next();
        element.replace('"', "\\\"");
        queryElements << element;
    }

    QString part = "\"" + queryElements.join("\", \"") + "\"";
    return part;
}

QString Film::timestampString()
{
    QString output = added_when.toString("yyyy-MM-dd hh:mm:ss");
    return output.isEmpty() ? QString("0000-00-00 00:00:00") : output;
}

QString Film::insertTagsQuery(const TagCollection &tags)
{
    QListIterator<Tag> iterator(tags);
    QStringList queries;

    while (iterator.hasNext()) {
        Tag t = iterator.next();
        QString sql = QString("INSERT INTO `film_tag` VALUES (%1, %2);").
                      arg(QString::number(id_film), QString::number(t.id()));
        queries << sql;
    }

    return queries.join("\n").append("\n");
}
