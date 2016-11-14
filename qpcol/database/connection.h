#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtCore>
#include <QtSql>

#include "database.h"

class Connection
{
public:
    static Connection* instance();
    QSqlDatabase get();
    void close();

private:
    Connection() {}

    static Connection* self;
    QSqlDatabase conn;
};

#endif // CONNECTION_H
