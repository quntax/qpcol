#ifndef XHAMSTER_H
#define XHAMSTER_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

#include "searchprovider.h"

class Xhamster : public SearchProvider
{
    Q_OBJECT
//    Q_PLUGIN_METADATA(IID "org.eu.merlin.QPcol.XhamsterPlugin")
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

#endif // XHAMSTER_H
