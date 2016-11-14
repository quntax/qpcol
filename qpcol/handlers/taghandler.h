#ifndef TAGHANDLER_H
#define TAGHANDLER_H

#include <QtCore>
#include <QtSql>

#include "tag.h"
#include "database.h"
#include "query.h"

class TagHandler
{
public:
    TagHandler();
    TagHandler(QSqlDatabase);

    Tag getTagById(int);
    Tag getTagByName(QString);

    Tag getLastQueryResult();
    TagCollection getAllTags();

    void addTag(const QString &);
    void deleteTag(const QString &);
    void renameTag(int, const QString &);

private:
    Tag tag;
    TagCollection tagCollection;
    QSqlDatabase connection;
};

#endif // TAGHANDLER_H
