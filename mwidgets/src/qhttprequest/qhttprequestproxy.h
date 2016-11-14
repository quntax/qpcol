#ifndef QHTTPREQUESTPROXY_H
#define QHTTPREQUESTPROXY_H

#include "qhttprequestabstract.h"

class QHttpRequestProxy : public QHttpRequestAbstract
{
    Q_OBJECT
public:
    explicit QHttpRequestProxy(QObject *parent = 0);

    virtual void download(const QString & url);

signals:
    void finished(QByteArray);

public slots:
    void finished(QNetworkReply *);
    void slotReplyFinished();
    void slotReadyRead();

protected:
    QNetworkAccessManager qnam;
    QUrl remoteUrl;
    QByteArray data;

    void get();

};

#endif // QHTTPREQUESTPROXY_H
