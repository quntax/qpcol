#ifndef QHTTPHASH_H
#define QHTTPHASH_H

#include <QObject>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QCryptographicHash>
#include <QDebug>

class QHttpHash : public QObject
{
    Q_OBJECT

public:
    explicit QHttpHash(QObject *parent = 0) : QObject(parent) {}
    QHttpHash(const QUrl &, int, QObject *parent = 0);
    QHttpHash(const QString &, int, QObject *parent = 0);

    void calculate(const QUrl &, int);
    void calculate(const QString &, int);

    void setUrl(const QUrl &);
    void setUrl(const QString &);
    void setSize(int);

    QByteArray hash();
    void reset();

signals:
    void complete();
    void complete(QByteArray);

protected:
    QUrl url;
    int sampleSize;

    QNetworkAccessManager manager;
    QNetworkReply *reply;

    QByteArray receivedData;
    QByteArray result;

    void download();
    void setResult();

protected slots:
    void slotReadyRead();
    void slotFinished();
};

#endif // QHTTPHASH_H
