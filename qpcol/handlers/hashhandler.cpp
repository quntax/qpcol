#include "hashhandler.h"

HashHandler::HashHandler(const QByteArray &buffer)
{
    md5sum = calculate(buffer);
}

HashHandler::HashHandler(const QString &filename)
{
    md5sum = calculate(filename);
}

QByteArray HashHandler::calculate(const QByteArray &buffer)
{
    return QCryptographicHash::hash(buffer, QCryptographicHash::Md5).toHex();
}

QByteArray HashHandler::calculate(const QString &filename)
{
    QFile file(filename);
    QByteArray fileData;

    if (! file.open(QIODevice::ReadOnly)) {
        return QByteArray();
    }

    fileData = file.read(HASH_LENGTH);
    file.close();

    if (fileData.isEmpty()) {
        return QByteArray();
    }

    return calculate(fileData);
}

QByteArray HashHandler::hash()
{
    return md5sum;
}
