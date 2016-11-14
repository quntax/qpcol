#ifndef XFLOGGER_H
#define XFLOGGER_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

#include "searchprovider.h"

class Xflogger : public SearchProvider
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
    void gotXml();

protected slots:
    void addXml(QByteArray);
    void setXml(QByteArray);

private:
    QString captureUrl(QString);
    QMutex mutex;
    QByteArray xml;
    QHttpDownload *downloader;
    QEventLoop loop;
};

#endif // XFLOGGER_H
