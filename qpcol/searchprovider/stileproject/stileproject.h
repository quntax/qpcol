#ifndef STILEPROJECT_H
#define STILEPROJECT_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

#include "searchprovider.h"

class Stileproject : public SearchProvider
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

#endif // STILEPROJECT_H