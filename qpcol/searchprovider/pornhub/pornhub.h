#ifndef PORNHUB_H
#define PORNHUB_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

#include "searchprovider.h"

class Pornhub : public SearchProvider
{
    Q_OBJECT
    Q_INTERFACES(SearchProviderInterface)

public:
    QWebElementCollection parse();
    void extract(const QWebElement &);
    QString video(const QString &);

    bool hasNext();
    bool hasPrevious();
    void next();
    void previous();

    QString baseUrl();
    QString searchBaseUrl();
    QString name();

signals:
    void gotAddress();

protected:
    QByteArray xmlData;
    QHttpDownload *downloader;
    QEventLoop loop;
    QMutex mutex;

    QString captureUrl(QString);


protected slots:
    void chunkAddress(QByteArray);
    void setAddress(QByteArray);
};

#endif // PORNHUB_H
