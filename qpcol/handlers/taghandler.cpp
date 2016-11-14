#include "taghandler.h"

TagHandler::TagHandler()
{
    connection = Connection::instance()->get();
}

TagHandler::TagHandler(QSqlDatabase conn)
{
    connection = conn;
}

Tag TagHandler::getTagById(int id_tag)
{
    Query q("SELECT * FROM tag WHERE id_tag = ?", connection);
    q << id_tag;

    QSqlQuery sql = q.execute();
    sql.next();

    tag = sql;
    sql.finish();
    return tag;
}

Tag TagHandler::getTagByName(QString name)
{
    Query q("SELECT * FROM `tag` WHERE `tag` = ?", connection);
    q << name;

    QSqlQuery sql = q.execute();
    sql.next();

    tag = sql;
    sql.finish();
    return tag;
}

Tag TagHandler::getLastQueryResult()
{
    return tag;
}

TagCollection TagHandler::getAllTags()
{
    Query q("SELECT * FROM tag ORDER BY tag", connection);
    QSqlQuery sql = q.execute();

    tagCollection.clear();
    while (sql.next()) {
        Tag t(sql);
        tagCollection.append(t);
    }

    sql.finish();
    return tagCollection;
}

void TagHandler::addTag(const QString &tagName)
{
    Query q("INSERT INTO tag (tag) VALUES (?)", connection);
    q << tagName;
    q.execute();
    q.finish();
}

void TagHandler::deleteTag(const QString &tagName)
{
    Query q("DELETE FROM tag WHERE tag = ?", connection);
    q << tagName;
    q.execute();
    q.finish();
}

void TagHandler::renameTag(int idTag, const QString & tagName)
{
    Query q("UPDATE tag SET tag = ? WHERE id_tag = ?", connection);
    q << tagName << idTag;
    q.execute();
    q.finish();
}
