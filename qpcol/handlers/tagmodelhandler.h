#ifndef TAGMODELHANDLER_H
#define TAGMODELHANDLER_H

#include "tag.h"
#include "database.h"
#include "query.h"
#include "connection.h"

class TagModelHandler
{
public:
    TagModelHandler() { connection = Connection::instance()->get(); }

    TagCollection getTags();

private:
    TagCollection tagCollection;
    QSqlDatabase connection;
};

#endif // TAGMODELHANDLER_H
