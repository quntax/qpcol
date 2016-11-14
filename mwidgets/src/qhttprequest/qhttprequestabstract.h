#ifndef QHTTPREQUESTABSTRACT_H
#define QHTTPREQUESTABSTRACT_H

//#define USER_AGENT          "QHttpRequest-0.3.3/mwidgets-##VERSION"
#define USER_AGENT          "QHttpRequest-##VERSION"

#define CONTENT_TYPE_HTML   "text/html; charset=utf-8"
#define CONTENT_TYPE_XML    "text/xml; charset=utf-8"
#define CONTENT_TYPE_FORM   "application/x-www-form-urlencoded"

#define BUFFER_SIZE         65536

#include <QtCore>
#include <QtNetwork/QtNetwork>
#include <QSysInfo>

#include "zlib.h"

class QHttpRequestAbstract : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ContentType _contentType READ getContentType WRITE setContentType)
    Q_ENUMS(ContentType)

public:
    static const int GET    = 1;
    static const int POST   = 2;
    static const int PUT    = 3;
    static const int DELETE = 4;
    static const int DOWNLOAD=5;

    enum ContentType { Html, Xml, FormUrlEncoded };

    explicit QHttpRequestAbstract(QObject *parent = 0);

    void setUrl(const QString & url);
    void setAuthentication(const QString & username, const QString & password);
    void setQuery(const QHash<QString, QString> & parameters);
    void addQueryParameter(const QString & key, const QString & value);
    void setFriendlySeparator(bool friendlySeparator);
    void addHttpHeader(const QByteArray & name, const QByteArray & value);
    void setContentType(ContentType contentType);
    void setAcceptCompression(bool accept);

    ContentType getContentType() const;

    virtual void download(const QString & url) = 0;

signals:
    void replyReceived();

public slots:
    virtual void sslErrorHandler(QNetworkReply * reply, const QList<QSslError> & sslErrors);
    virtual void errorHandler(QNetworkReply::NetworkError error);

protected:
    bool _authenticate;
    bool _redirection;
    bool _acceptCompression;
    int _requestMethod;

    QByteArray _userAgent;

    QString _url;
    QString _username;
    QString _password;
    QString _contentType;

    QHash<QString, QString> _parameters;
    QHash<QByteArray, QByteArray> _extraHeaders;
    QNetworkAccessManager * _manager;
    QNetworkCookieJar * _cookieJar;

    QNetworkReply * _reply;
    QByteArray _replyData;
    QNetworkReply::NetworkError _errorCode;

    QChar _querySeparator;
    QChar _queryItemSeparator;
    QChar _valueSeparator;

    QFile * _downloadFile;

    QUrl _getQueryUrl() const;
    QNetworkRequest _getNetworkRequest();

    QByteArray _decompressReply(QByteArray compressData);

    ContentType _getInternalContentType(const QString & contentType) const;
    void _setInternalContentType(ContentType contentType);
};

#endif // QHTTPREQUESTABSTRACT_H
