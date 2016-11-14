#include "query.h"

Query::Query(const QString & queryString, QSqlDatabase dbconn)
{
    connection = dbconn;
    queryObject = QSqlQuery(queryString, connection);
    _paramBound = 0;

    queryObject.prepare(queryString);
}

QSqlQuery Query::execute()
{
    queryObject.exec();

    return queryObject;
}

void Query::finish()
{
    if (queryObject.isActive()) {
        queryObject.finish();
    }
//    delete &queryObject;
    queryObject = QSqlQuery();
}

Query &Query::operator <<(QVariant &param)
{
    queryObject.addBindValue(param);
//    queryObject.bindValue(_paramBound++, param);

    return *this;
}

Query &Query::operator <<(int &param)
{
    QVariant p(param);
    queryObject.addBindValue(p);
//    queryObject.bindValue(_paramBound++, p);

    return *this;
}

Query &Query::operator <<(const int &param)
{
    QVariant p(param);
    queryObject.addBindValue(p);
//    queryObject.bindValue(_paramBound++, p);

    return *this;
}

Query &Query::operator <<(const QString &param)
{
    QVariant p(param);
    queryObject.addBindValue(p);
//    queryObject.bindValue(_paramBound++, p);

    return *this;
}

Query &Query::operator <<(QString &param)
{
    QVariant p(param);
//    queryObject.bindValue(_paramBound++, p);
    queryObject.addBindValue(p);
    return *this;
}

Query &Query::operator <<(QByteArray &param)
{
    QVariant p(param);
    queryObject.addBindValue(p);
//    queryObject.bindValue(_paramBound++, p);

    return *this;
}

Query &Query::operator <<(const QByteArray &param)
{
    QVariant p(param);
    queryObject.addBindValue(p);
//    queryObject.bindValue(_paramBound++, p);

    return *this;
}

Query &Query::operator <<(QDate &param)
{
    QVariant p(param);
    queryObject.addBindValue(p);
//    queryObject.bindValue(_paramBound++, p);

    return *this;
}

Query::~Query()
{
    queryObject.finish();
//    queryObject.clear();
}
