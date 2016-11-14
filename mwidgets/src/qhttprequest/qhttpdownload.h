#ifndef QHTTPDOWNLOAD_H
#define QHTTPDOWNLOAD_H
#define QHDDEBUG qDebug() <<

#include <QtNetwork/QtNetwork>
#include <QUrl>

class QHttpDownload : public QObject
{
    Q_OBJECT
public:
    explicit QHttpDownload(QObject *parent = 0);

    void download(const QString &);
    void download(const QUrl &);
    void download();
    void setCookieJar(QNetworkCookieJar *cookies);

signals:
    void complete(QByteArray);
    void chunk(QByteArray);
    void clear();
    void downloadProgress(qint64, qint64);

protected:
    QUrl url;
//    QNetworkCookieJar *cookieJar;

    QNetworkAccessManager manager;
    QNetworkReply *reply;

    QByteArray receivedData;

protected slots:
    void slotReadyRead();
    void slotFinished();

};

#endif // QHTTPDOWNLOAD_H
