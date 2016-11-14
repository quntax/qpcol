#ifndef HOTPORNSHOW_H
#define HOTPORNSHOW_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

#include "searchprovider.h"

class Hotpornshow : public SearchProvider
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
};

#endif // HOTPORNSHOW_H
