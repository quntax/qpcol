#ifndef TAG_H
#define TAG_H

#include <QtCore>
#include <QtSql>

class Tag {
public:
    inline Tag() { id_tag = 0; tag = QByteArray(); }
    Tag(const QSqlQuery &sql);

    enum Column {
        IdTag   = 0,
        Name = 1
    };

    inline int id() const { return id_tag; }
    inline QByteArray name() const { return tag; }

    QVariant column(int index);
    Tag &operator=(const QSqlQuery &);
    bool operator==(const Tag &);
    operator bool() const { return (id_tag > 0); }

    QString insertQuery();

private:
    int id_tag;
    QByteArray tag;

    QString queryPart();
};

typedef QList<Tag> TagCollection;

Q_DECLARE_METATYPE(Tag)
Q_DECLARE_METATYPE(TagCollection)

QDebug operator<<(QDebug, const Tag &);

#endif // TAG_H
