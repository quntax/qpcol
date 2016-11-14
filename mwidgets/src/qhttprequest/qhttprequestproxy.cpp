#include "qhttprequestproxy.h"

QHttpRequestProxy::QHttpRequestProxy(QObject *parent) :
    QHttpRequestAbstract(parent)
{
    connect(&qnam, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finished(QNetworkReply*)));
//    connect(&qnam, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
//            parent, SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
}

void QHttpRequestProxy::download(const QString & url) {
    remoteUrl = QUrl::fromUserInput(url);
    setUrl(url);
    get();
}

void QHttpRequestProxy::get() {
    QNetworkRequest request = _getNetworkRequest();
    request.setUrl(remoteUrl);

    _reply = qnam.get(request);
    connect(_reply, SIGNAL(finished()),
            this, SLOT(slotReplyFinished()));
    connect(_reply, SIGNAL(readyRead()),
            this, SLOT(slotReadyRead()));
}

void QHttpRequestProxy::slotReplyFinished()
{
    QVariant redirectionTarget = _reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if (_reply->error()) {
        qDebug() << QString("HTTP Error: %1").arg(_reply->errorString());
    } else if (!redirectionTarget.isNull()) {
        remoteUrl = remoteUrl.resolved(redirectionTarget.toUrl());
        setUrl(remoteUrl.toString());
        get();

        return;
    } else {
        qDebug() << "Complete reply received";
//        emit finished(data);
    }

    _reply->deleteLater();
    _reply = 0;
}

void QHttpRequestProxy::slotReadyRead() {
    data.append(_reply->readAll());
}

void QHttpRequestProxy::finished(QNetworkReply *) {
    qDebug() << "Signal finished from manager, emitting buffer";
    qDebug() << data;
    emit finished(data);
//    deleteLater();
}
