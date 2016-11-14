#include "connection.h"

Connection* Connection::self = 0;

Connection* Connection::instance()
{
    if (self == 0) {
        self = new Connection;
        Database db("localhost", "merlin", "merlin", DBNAME);
        self->conn = db.connection();
    }

    return self;
}

QSqlDatabase Connection::get()
{
    return self->conn;
}

void Connection::close()
{
    self->conn.close();
//    self->conn.removeDatabase("qt_sql_default_connection");
//    delete self;
}
