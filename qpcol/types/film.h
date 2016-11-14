#ifndef FILM_H
#define FILM_H

#include <QtCore>
#include <QtSql>
#include "query.h"
#include "tag.h"
/*
#define QPC_MEDIA_EXTENSIONS(prefix) (\
    (#prefix) "flv" \
    (#prefix) "avi" \
    (#prefix) "wmv" \
    (#prefix) "mp4" \
    (#prefix) "mpg" \
    (#prefix) "mpeg" \
    (#prefix) "3gp")

#define QPC_MEDIA_EXTLIST QPC_MEDIA_EXTENSIONS("*.")
#define QPC_STR(arg) #arg
#define HANDLED_FORMATS QPC_STR(QPC_MEDIA_EXTLIST)

#define QPC_FILEDIALOG_EXTLIST QPC_MEDIA_EXTLIST
#defind QFILEDIALOG_EXTLIST tr("Video " QPC_FILEDIALOG_EXTLIST")"
*/
#define HANDLED_FORMATS "*.flv *.avi *.wmv *.mp4 *.mpg *.mpg *.mpeg *.3gp *.mkv"

class Film {
public:
    inline Film() { id_film = 0; }
    Film(const QSqlQuery &);
    Film(const QByteArray &);
    Film(const QByteArray &, const QString &);

    enum Column {
        IdFilm          = 0,
        Hash            = 1,
        FilePath        = 2,
        FileName        = 3,
        Size            = 4,
        OriginalFilePath= 5,
        OriginalUrl     = 6,
        Blacklist       = 7,
        Favorite        = 8,
        Marked          = 9,
        AddedWhen       = 10,
        Notes           = 11
    };


    int id() const { return id_film; }
    bool isFavorite() const { return favorite; }
    bool isBlacklist() const { return blacklist; }
    bool isMarked() const { return marked; }
    QByteArray filePath() const { return filepath; }
    QByteArray fileName() const { return filename; }
    QByteArray originalUrl() const { return original_url; }
    QByteArray notes() const { return filmnotes; }
    QByteArray fileHash() const { return hash; }
    QString timestampString();
    int fileSize() const { return size; }

    void tag(const Tag &);
    void untag(const Tag &);

    void add();
    void updatePath(const QString &);
    void setOriginalUrl(const QString &);
    void setNotes(const QString &);
    void setHash(const QByteArray &);

    QString insertFilmQuery();
    QString insertTagsQuery(const TagCollection &);
    QString qpcolUrl() { return hash.isEmpty() ? QString() : QString("qpcol://%1").arg(QString(hash)); }

    Film &operator=(const QSqlQuery &);
    operator bool() const { return (id_film > 0); }

private:
    int id_film;
    QByteArray hash;
    QByteArray filepath;
    QByteArray filename;
    int size;
    QByteArray original_filepath;
    QByteArray original_url;
    bool blacklist;
    bool favorite;
    bool marked;
    QDateTime added_when;
    QByteArray filmnotes;

    QString queryPartFilm();
};

typedef QList<Film> FilmCollection;

Q_DECLARE_METATYPE(Film)
Q_DECLARE_METATYPE(FilmCollection)

#endif // FILM_H
