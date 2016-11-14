#include "tag.h"

Tag::Tag(const QSqlQuery &sql)
{
    *this = sql;
}

Tag &Tag::operator=(const QSqlQuery &sql)
{
    if (! sql.isValid()) {
        // invalidate tag
        id_tag = 0;
        tag = "";
        return *this;
    }

    id_tag = sql.value(IdTag).toInt();
    tag = sql.value(Name).toByteArray();

    return *this;
}

QDebug operator<<(QDebug debug, const Tag &tag)
{
    debug.nospace() << "Tag(" << tag.id() << ", " << tag.name() << ")";
    return debug.space();
}

QVariant Tag::column(int index)
{
    switch (index) {
    case IdTag:
        return id_tag;
    case Name:
        return tag;
    default:
        return QVariant();
    }
}

bool Tag::operator ==(const Tag &other)
{
    return (id_tag == other.id_tag);
}

QString Tag::insertQuery()
{
    return QString("INSERT INTO `tag` VALUES (%1);\n").arg(queryPart());
}

QString Tag::queryPart()
{
    QStringList parts;
    parts << QString::number(id_tag)
            << tag.replace('"', "\\\"");

    QString part = "\"" + parts.join("\", \"") + "\"";
    return part;
}
