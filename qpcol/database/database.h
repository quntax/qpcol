#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore>
#include <QtSql>

// TODO: drop it, leave only sqlite support
#define SQLITE 0
#define MYSQL 1
#define DATABASE_TYPE SQLITE

#if DATABASE_TYPE == SQLITE
#define DBNAME "qpcol.db"
#elif DATABASE_TYPE == MYSQL
#define DBNAME "qpcol"
#endif

typedef struct {
    QByteArray hostname;
    QByteArray username;
    QByteArray password;
    QByteArray database;
} DBAccess;

class Database {

public:
    Database(QByteArray host, QByteArray user, QByteArray pass, QByteArray name);

    static int sqliteCheck();
//    static void init(const QString &);
    QSqlDatabase connection();


    void set(DBAccess a) {dbaccess = a; }
    DBAccess get() { return dbaccess; }

    QByteArray hostname() { return dbaccess.hostname; }
    QByteArray username() { return dbaccess.username; }
    QByteArray password() { return dbaccess.password; }
    QByteArray database() { return dbaccess.database; }

protected:
    static QString sqliteLocation();

    DBAccess dbaccess;
    QSqlDatabase conn;
};

#endif // DATABASE_H
