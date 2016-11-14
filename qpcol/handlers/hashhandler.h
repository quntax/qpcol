#ifndef HASHHANDLER_H
#define HASHHANDLER_H

//#define HASH_LENGTH 262144
#define HASH_LENGTH 100000

#include <QtCore>

class HashHandler
{
public:
    HashHandler() {}
    HashHandler(const QByteArray &);
    HashHandler(const QString &);

    QByteArray hash();
    static QByteArray calculate(const QByteArray &);
    static QByteArray calculate(const QString &);

private:
    QByteArray md5sum;
};

#endif // HASHHANDLER_H
