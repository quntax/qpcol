#include "tagmodelhandler.h"

TagCollection TagModelHandler::getTags()
{
    QString q = "SELECT * FROM tag ORDER BY tag";
    Query query(q, connection);

    QSqlQuery sql = query.execute();

    while (sql.next()) {
        Tag t(sql);
        tagCollection.append(t);
    }

    sql.finish();
    return tagCollection;
}
