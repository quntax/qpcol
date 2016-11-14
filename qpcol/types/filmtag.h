#ifndef FILMTAG_H
#define FILMTAG_H

#include <QtCore>
#include <QtSql>
#include "query.h"
#include "tag.h"
#include "film.h"

struct FilmTag {
    int id_film;
    QByteArray filepath;
    QByteArray filename;
    QByteArray tag_list;
    bool favorite;
    int size;
    QDateTime added_when;
    bool blacklist;
    bool marked;
    TagCollection tags;
    QVariantList idTagList;
    QByteArray filmnotes;
    QByteArray original_url;

    enum Column {
        IdFilm      = 0,
        FilePath    = 1,
        FileName    = 2,
        TagNames    = 3,
        Favorite    = 4,
        Size        = 5,
        AddedWhen   = 6,
        Blacklist   = 7,
        Marked      = 8,
        Notes       = 9,
        OriginalUrl = 10,
        IdTagList   = 11
    };

    FilmTag &operator=(QSqlQuery q) {
        id_film =       q.value(IdFilm).toInt();
        filepath=       q.value(FilePath).toByteArray();
        filename =      q.value(FileName).toByteArray();
        tag_list =      q.value(TagNames).toByteArray();
        favorite =      q.value(Favorite).toBool();
        size =          q.value(Size).toInt();
        added_when =    q.value(AddedWhen).toDateTime();
        blacklist =     q.value(Blacklist).toBool();
        marked =        q.value(Marked).toBool();
        tags =          filmTags(q.value(IdFilm).toInt());
        filmnotes =     q.value(Notes).toByteArray();
        original_url =  q.value(OriginalUrl).toByteArray();

        return *this;
    }

    FilmTag &operator=(Film film) {
        TagCollection tc = filmTags(film.id());

        id_film =       film.id();
        filepath=       film.filePath();
        filename =      film.fileName();
        tag_list =      column(TagNames).toByteArray();
        favorite =      film.isFavorite();
        size =          film.fileSize();
        added_when =    QDateTime::fromString(film.timestampString(), "yyyy-MM-dd hh:mm:ss");
        blacklist =     film.isBlacklist();
        marked =        film.isMarked();
        tags =          tc;
        filmnotes =     film.notes();
        original_url =  film.originalUrl();

        return *this;
    }

    FilmTag &operator=(const QByteArray &localFile) {
        QFileInfo fi(localFile);

        id_film = 0;
        filepath = localFile;
        filename = fi.fileName().toLocal8Bit();
        size = fi.size() / 1048576;
        original_url = localFile;
        blacklist = false;
        marked = false;
        favorite = false;

        return *this;
    }

    TagCollection filmTags(int idFilm) {
        Query q("SELECT tag.id_tag, tag.tag "
                "FROM film_tag "
                "JOIN tag USING (id_tag) "
                "WHERE id_film = ?",
                Connection::instance()->get());
        q << idFilm;
        QSqlQuery sql = q.execute();
        TagCollection tc;
        idTagList.clear();

        while (sql.next()) {
            Tag t(sql);
            tc.append(t);
            idTagList.append(t.id());
        }

        return tc;
    }

    QVariant column(int index) {
        switch (index) {
            case IdFilm:
                return id_film;
            case FilePath:
                return filepath;
            case FileName:
                return filename;
            case TagNames:
                return tag_list;
            case Favorite:
                return favorite;
            case Size:
                return size;
            case AddedWhen:
                if (added_when.isValid())
                    return added_when;
                else
                    return QVariant();
            case Blacklist:
                return blacklist;
            case Marked:
                return marked;
            case Notes:
                return filmnotes;
            case OriginalUrl:
                return original_url;
            case IdTagList:
                return idTagList;
        }

        return QVariant();
    }
};

typedef QList<FilmTag> FilmTagCollection;

#endif // FILMTAG_H
