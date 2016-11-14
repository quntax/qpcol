#ifndef GIRLFRIENDVIDEOS_H
#define GIRLFRIENDVIDEOS_H

#include <QtCore>
#include <QtGui>
//#include <QWebElement>

#include "searchprovider.h"

class Girlfriendvideos : public SearchProvider
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

#endif // GIRLFRIENDVIDEOS_H
