#ifndef XVIDEOS_H
#define XVIDEOS_H

#include "searchprovider.h"

class Xvideos : public SearchProvider
{
    Q_OBJECT
//    Q_PLUGIN_METADATA(IID "org.eu.merlin.QPcol.XvideosPLugin")
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

#endif // XVIDEOS_H
