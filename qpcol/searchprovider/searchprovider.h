#ifndef SEARCHPROVIDER_H
#define SEARCHPROVIDER_H

#include "hashhandler.h"
#include "isearchprovider.h"
#include "searchresultitem.h"
#include "searchresulthandler.h"
#include "qhttprequest.h"
#include "qhttpdownload.h"
#include "messenger.h"

//#ifdef QPCOL_RELEASE
//#define QPCOL_MDEBUG(x) /* (x) */
//#else
//#define QPCOL_MDEBUG(args...) qDebug() << QString("%1:%2").arg(__FILE__).arg(__LINE__) << args
//#endif


#include <QtCore>
#include <QtGui>
#include <QtWebKitWidgets>

class SearchProvider :
        public QObject,
        public SearchProviderInterface
{
    Q_OBJECT
    Q_INTERFACES(SearchProviderInterface)

public:
    SearchProvider();
    ~SearchProvider();

    void search(const QString &);

signals:
    void searchResultsPageUrl(const QString &);
    // remove this
    void videoUrl(const QString &);
    void loadStarted();
    void loadFinished();
    void extracted(SearchResultItem);
    void hash(QByteArray);
    void complete();

protected:
    QByteArray searchHash;
    QString searchUrl;

    QWebView * webView;
    QWebPage * webPage;
    QQueue<QWebElement> queue;

    QString page;
    QString thumbnail;
    QString title;
    QString url;
    QString description;

    QByteArray contents;

    void loadPage(const QString &);
    void sendItem();
    QByteArray fetch(const QString &);
    QByteArray urlHash(const QString &);

protected slots:
    void loadFinished(bool);
    void setContents(QByteArray);
};

#endif // SEARCHPROVIDER_H
