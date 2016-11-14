#ifndef MEENDO_H
#define MEENDO_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

#include "searchprovider.h"

class Meendo : public SearchProvider
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

#endif // MEENDO_H
