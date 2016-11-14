#include "qhttprequestabstract.h"

QHttpRequestAbstract::QHttpRequestAbstract(QObject *parent) :
    QObject(parent)
{
    _authenticate = false;
    _redirection = false;

    setFriendlySeparator(false);
    setContentType(Html);
    setAcceptCompression(false);

    _userAgent = QByteArray(USER_AGENT).append(" (Qt " + QByteArray(qVersion()) +
                                               "; " + /*QLibraryInfo::build() */QSysInfo::buildAbi() +
                                               "; " + QHostInfo::localHostName() + ")");
}



/**
 * Decompressing GZIP data using qUncompress() was found here:
 * http://www.qtcentre.org/threads/30031-qUncompress-data-from-gzip
 *
 * @param QByteArray
 * @return QByteArray
 */
QByteArray QHttpRequestAbstract::_decompressReply(QByteArray compressedData) {
    compressedData.remove(0, 10);
    compressedData.chop(12);

    quint8 buffer[BUFFER_SIZE];

    z_stream cmpr_stream;

    cmpr_stream.next_in = (unsigned char *)compressedData.data();
    cmpr_stream.avail_in = compressedData.size();
    cmpr_stream.total_in = 0;

    cmpr_stream.next_out = buffer;
    cmpr_stream.avail_out = BUFFER_SIZE;
    cmpr_stream.total_out = 0;

    cmpr_stream.zalloc = Z_NULL;
    cmpr_stream.zfree = Z_NULL;

    if( inflateInit2(&cmpr_stream, -8 ) != Z_OK) {
        qDebug() << "cmpr_stream error!";
    }

    QByteArray uncompressed;

    do {
        int status = inflate(&cmpr_stream, Z_SYNC_FLUSH);

        if (status == Z_OK || status == Z_STREAM_END) {
            uncompressed.append(QByteArray::fromRawData(
                    (char *)buffer,
                    BUFFER_SIZE - cmpr_stream.avail_out));

            cmpr_stream.next_out = buffer;
            cmpr_stream.avail_out = BUFFER_SIZE;
        } else {
            inflateEnd(&cmpr_stream);
        }

        if (status == Z_STREAM_END) {
            inflateEnd(&cmpr_stream);
            break;
        }

    } while (cmpr_stream.avail_out == 0);

    return uncompressed;
}

void QHttpRequestAbstract::_setInternalContentType(ContentType contentType) {
    switch (contentType) {
        case Html:
            _contentType = CONTENT_TYPE_HTML;
            break;
        case Xml:
            _contentType = CONTENT_TYPE_XML;
            break;
        case FormUrlEncoded:
            _contentType = CONTENT_TYPE_FORM;
            break;
    }
}

QHttpRequestAbstract::ContentType QHttpRequestAbstract::_getInternalContentType(const QString &contentType) const {
    QString contentTypeStringMap[] = { CONTENT_TYPE_HTML, CONTENT_TYPE_XML, CONTENT_TYPE_FORM };
    ContentType contentTypeMap [] = { Html, Xml, FormUrlEncoded };

    for (int i = 0; i < 3; i++) {
        if (contentType == contentTypeStringMap[i]) {
            return contentTypeMap[i];
        }
    }

    return Html;
}


QUrl QHttpRequestAbstract::_getQueryUrl() const {
    if (_parameters.isEmpty()) {
        return QUrl(_url);
    }

    QString url(_url);

    QHashIterator<QString, QString> iterator(_parameters);
    url.append(_querySeparator);

    while (iterator.hasNext()) {
        if (iterator.hasPrevious()) {
            url.append(_queryItemSeparator);
        }

        iterator.next();
        url.append(iterator.key() + _valueSeparator + iterator.value());
    }

    return QUrl(url);
}

QNetworkRequest QHttpRequestAbstract::_getNetworkRequest() {
    QNetworkRequest request;

    request.setRawHeader("User-Agent", _userAgent);
    request.setRawHeader("Accept-Encoding", _acceptCompression ? "gzip, deflate, identity" : "identity");
    request.setRawHeader("Accept-Charset", "ISO-8859-2,utf-8;q=0.7,*;q=0.7");
    request.setRawHeader("Connection", "close");

    QHashIterator<QByteArray, QByteArray> iterator(_extraHeaders);
    while (iterator.hasNext()) {
        iterator.next();
        request.setRawHeader(iterator.key(), iterator.value());
    }

    if (_authenticate) {
        request.setRawHeader("Authorization", "Basic " +
                             QByteArray(QString("%1:%2").arg(_username).arg(_password).toLocal8Bit()).toBase64());
    }

    return request;
}


QHttpRequestAbstract::ContentType QHttpRequestAbstract::getContentType() const {
    return _getInternalContentType(_contentType);
}


void QHttpRequestAbstract::setUrl(const QString &url) {
    _url = QUrl::fromUserInput(url).toString(QUrl::StripTrailingSlash);
}

void QHttpRequestAbstract::setAuthentication(const QString &username, const QString &password) {
    _authenticate = true;
    _username = username;
    _password = password;
}

void QHttpRequestAbstract::setQuery(const QHash<QString, QString> &parameters) {
    _parameters = parameters;
}

void QHttpRequestAbstract::addQueryParameter(const QString &key, const QString &value) {
    _parameters.insert(key, value);
}

void QHttpRequestAbstract::setFriendlySeparator(bool friendlySeparator) {
    if (friendlySeparator) {
        _querySeparator = '/';
        _queryItemSeparator = '/';
        _valueSeparator = '/';
    } else {
        _querySeparator = '?';
        _queryItemSeparator = '&';
        _valueSeparator = '=';
    }
}

void QHttpRequestAbstract::addHttpHeader(const QByteArray &name, const QByteArray &value) {
    _extraHeaders.insert(name, value);
}

void QHttpRequestAbstract::setContentType(ContentType contentType) {
    _setInternalContentType(contentType);
}

void QHttpRequestAbstract::setAcceptCompression(bool accept) {
    _acceptCompression = accept;
}

void QHttpRequestAbstract::sslErrorHandler(QNetworkReply *reply, const QList<QSslError> & sslErrors) {
    qDebug() << "Following SSL errors occured:";

    QListIterator<QSslError> iterator(sslErrors);
    while (iterator.hasNext()) {
        QSslError sslError = iterator.next();
        qDebug() << QString("SSL Error %1 (%2)").arg(sslError.error()).arg(sslError.errorString());
    }

    reply->ignoreSslErrors();
}

void QHttpRequestAbstract::errorHandler(QNetworkReply::NetworkError error) {
    _errorCode = error;
}
