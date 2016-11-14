#include "qhttphash.h"

QHttpHash::QHttpHash(const QUrl &address, int bytes, QObject *parent) :
    QObject(parent)
{
    calculate(address, bytes);
}

QHttpHash::QHttpHash(const QString &address, int bytes, QObject *parent) :
    QObject(parent)
{
    calculate(address, bytes);
}

void QHttpHash::setUrl(const QUrl &address)
{
    url = address;
}

void QHttpHash::setUrl(const QString &address)
{
    url = QUrl::fromUserInput(address);
}

void QHttpHash::setSize(int bytes)
{
    sampleSize = bytes;
}

void QHttpHash::calculate(const QUrl &address, int bytes)
{
    setUrl(address);
    setSize(bytes);

    download();
}

void QHttpHash::calculate(const QString &address, int bytes)
{
    setUrl(address);
    setSize(bytes);

    download();
}

QByteArray QHttpHash::hash()
{
    return result;
}

void QHttpHash::download()
{
    reply = manager.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(slotFinished()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(slotReadyRead()));
}

void QHttpHash::slotReadyRead()
{
    receivedData.append(reply->readAll());

    if (receivedData.size() >= sampleSize) {
        setResult();
    }
}

void QHttpHash::slotFinished()
{
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) {
        reset();
    } else if (! redirectionTarget.isNull()) {
        qDebug() << "Redirect?";
        QUrl newUrl = url.resolved(redirectionTarget.toUrl());
        url = newUrl;

        reset();
        download();
        return;
    }

    if (result.isEmpty()) {
        setResult();
    }
}

void QHttpHash::setResult()
{
    qDebug() << "Calculating...";
    receivedData.truncate(sampleSize);
    result = QCryptographicHash::hash(receivedData,
                                      QCryptographicHash::Md5).toHex();
    reply->blockSignals(true);
    reply->deleteLater();
    reply = 0;

    emit complete();
    emit complete(result);
}

void QHttpHash::reset()
{
    if (reply) {
        reply->blockSignals(true);
        reply->deleteLater();
        reply = 0;
    }

    result.clear();
    receivedData.clear();
}
