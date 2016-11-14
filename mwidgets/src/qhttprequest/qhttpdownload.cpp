#include "qhttpdownload.h"

QHttpDownload::QHttpDownload(QObject *parent) :
    QObject(parent)
{
//    cookieJar = 0;
}

void QHttpDownload::download(const QString &resource)
{
    download(QUrl::fromUserInput(resource));
}

void QHttpDownload::download(const QUrl &resource)
{
    url = resource;
    download();
}

void QHttpDownload::download()
{
    reply = manager.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(slotFinished()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SIGNAL(downloadProgress(qint64, qint64)));
    QHDDEBUG "Downloading" << url.toString();
}

void QHttpDownload::slotReadyRead()
{
    QByteArray data = reply->readAll();
    receivedData.append(data);
    emit chunk(data);
}

void QHttpDownload::slotFinished()
{
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) {
        receivedData.clear();
        emit clear();
    } else if (! redirectionTarget.isNull()) {
        QUrl newUrl = url.resolved(redirectionTarget.toUrl());
        url = newUrl;

        reply->deleteLater();
        receivedData.clear();
        emit clear();
        download();
        return;
    }

    emit complete(receivedData);

    reply->deleteLater();
    reply = 0;
}

void QHttpDownload::setCookieJar(QNetworkCookieJar *cookies)
{
    manager.setCookieJar(cookies);
}
