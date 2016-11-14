#ifndef QUERY_H
#define QUERY_H

#include <QtCore>
#include <QtSql>

#include "connection.h"

class Query
{
public:
    Query(const QString &, QSqlDatabase);
    ~Query();
    QSqlQuery execute();
    void finish();
    Query &operator<<(QVariant &param);
    Query &operator<<(int &param);
    Query &operator<<(const int &param);
    Query &operator<<(QString &param);
    Query &operator<<(const QString &param);
    Query &operator<<(QByteArray &param);
    Query &operator<<(const QByteArray &param);
    Query &operator<<(QDate &param);

protected:
    QSqlQuery queryObject;
    QSqlDatabase connection;

private:
    int _paramBound;
};

#endif // QUERY_H
