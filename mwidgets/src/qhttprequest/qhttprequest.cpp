#include "qhttprequest.h"

QHttpRequest::QHttpRequest(QObject * parent) : QHttpRequestAbstract(parent)
{
    _downloadFile = new QFile();
}

QString QHttpRequest::getDownloadFileName() {
    QFileInfo fileinfo(QString(_getQueryUrl().path()));
    QString saveName = fileinfo.fileName();

    if (saveName.isEmpty()) {
        qsrand(QTime().msec());
        saveName = QString("download_%1").arg(qrand());
    }

    return saveName;
}

QByteArray QHttpRequest::get() {
    return sendRequest(GET);
}

QByteArray QHttpRequest::post() {
    return sendRequest(POST);
}

QByteArray QHttpRequest::put() {
    return sendRequest(PUT);
}

QByteArray QHttpRequest::deleteResource() {
    return sendRequest(DELETE);
}

void QHttpRequest::download() {
    sendRequest(DOWNLOAD);
}

void QHttpRequest::download(const QString &dir) {
    setDownloadDirectory(dir);
    sendRequest(DOWNLOAD);
}

void QHttpRequest::setDownloadDirectory(const QString &dir) {
    QString saveName = getDownloadFileName();

    _downloadFile->setFileName(QString("%1/%2").arg(dir).arg(saveName));

    if (_downloadFile->exists()) {
    _downloadFile->remove();
    }

    _downloadFile->open(QFile::ReadWrite);
}

QByteArray QHttpRequest::sendRequest(int method) {
    QEventLoop eventLoop;
    _requestMethod = method;

    connect(this, SIGNAL(replyReceived()),
            &eventLoop, SLOT(quit()));

    _manager = new QNetworkAccessManager(this);
    _cookieJar = new QNetworkCookieJar(this);
    _manager->setCookieJar(_cookieJar);

    connect(_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply *)));
    connect(_manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            this, SLOT(sslErrorHandler(QNetworkReply*,QList<QSslError>)));

    QNetworkRequest request = _getNetworkRequest();

    if (_getQueryUrl().scheme() == "https") {
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    }

    QNetworkReply * reply = 0;

    if (method == GET || method == DELETE) {
        request.setUrl(_getQueryUrl());
        reply = _manager->get(request);
    }

    if (method == POST || method == PUT) {
        setFriendlySeparator(false);
        QByteArray query = _getQueryUrl().query(QUrl::FullyEncoded).toLocal8Bit();
        QUrl url(_getQueryUrl().toString(QUrl::RemoveQuery));

        request.setUrl(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, _contentType);
        request.setHeader(QNetworkRequest::ContentLengthHeader, query.length());

        if (method == POST) {
            reply = _manager->post(request, query);
        } else {
            reply = _manager->put(request, query);
        }
    }

    if (method == DOWNLOAD) {
        if (! _downloadFile->isOpen()) {
            setDownloadDirectory(QDir::tempPath());
        }

        request.setUrl(_url);
        reply = _manager->get(request);

        _reply = reply;
        connect(_reply, SIGNAL(readyRead()),
                this, SLOT(slotReadyRead()));
        connect(_reply, SIGNAL(downloadProgress(qint64, qint64)),
            SIGNAL(downloadProgress(qint64, qint64)));
        connect(_reply, SIGNAL(readyRead()),
                SIGNAL(readyRead()));
    }

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(errorHandler(QNetworkReply::NetworkError)));

    if (! (method == DOWNLOAD)) {
        eventLoop.exec();
    }

    return _replyData;
}

void QHttpRequest::slotReadyRead() {
    if (_reply->bytesAvailable() > 0) {
        _downloadFile->write(_reply->readAll());
    }
}

void QHttpRequest::replyFinished(QNetworkReply *reply) {
    if (_errorCode != QNetworkReply::NoError) {
        QVariant attribute = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

        if (! attribute.isNull()) {
            QUrl url = QUrl(attribute.toString());

            if (! url.isRelative()) {
                _url = attribute.toString();
            } else {
                _url = reply->url().toString(QUrl::RemovePath |
                                             QUrl::RemoveQuery |
                                             QUrl::StripTrailingSlash)
                       .append("/" + attribute.toString());
            }

            qDebug() << "Redirection to " << _url;
            sendRequest(_requestMethod);

            return;
        } else {
            qDebug() << QString("Network error: %1 (%2)").arg(_errorCode).arg(reply->errorString());
        }
    }

    _replyData = reply->readAll();

    if (reply->rawHeader("Content-Encoding").contains("gzip")) {
        _replyData = _decompressReply(_replyData);
    }

    if (_requestMethod == DOWNLOAD) {
        _downloadFile->flush();
        _downloadFile->close();
        _reply->deleteLater();
    }

    reply->deleteLater();
    emit replyReceived();
}
