#ifndef YOUPORN_H
#define YOUPORN_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

#include "searchprovider.h"

class Youporn : public SearchProvider
{
    Q_OBJECT
    Q_INTERFACES(SearchProviderInterface)

public:
    Youporn();
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
    void gotHtml();

protected:
//    void loadPage(const QString &);

    QByteArray html;
    QHttpDownload *downloader;
    QEventLoop loop;

protected slots:
    void addHtml(QByteArray);
    void setHtml(QByteArray);
};

#endif // YOUPORN_H
