#ifndef QHTTPREQUEST_H
#define QHTTPREQUEST_H

#include "qhttprequestabstract.h"

// TODO: referer support (public method and on redirection
class QHttpRequest : public QHttpRequestAbstract {
    Q_OBJECT

public:
    QHttpRequest(QObject * parent = 0);

    void setDownloadDirectory(const QString & dir);
    QString getDownloadFileName();

    QByteArray get();
    QByteArray post();
    QByteArray put();
    QByteArray deleteResource();
    QByteArray sendRequest(int method);

    void download();
    virtual void download(const QString & url);

public slots:
    void replyFinished(QNetworkReply * reply);
    void slotReadyRead();

signals:
    void replyReceived();
    void readyRead();
    void downloadProgress(qint64, qint64);
};

#endif // QHTTPREQUEST_H
