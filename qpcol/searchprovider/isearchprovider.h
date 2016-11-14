/*
 * Subclassess of this interface should reimplement (assuming they subclass
 * SearchProvider class, not directly this interface):
 * parse() - should set title, description and page properties
 * extract() - should create and emit extracted(SearchResultItem)
 * video() - should extract video url and store it in url property (?)
 * Actually, only search and helper functions are reimplemented in
 * SearchProvider subclass
 */
#ifndef ISEARCHPROVIDER_H
#define ISEARCHPROVIDER_H

#include <QtCore>
#include <QtWebKit>

class SearchProviderInterface
{
    public:
        virtual ~SearchProviderInterface() {}

        virtual void search(const QString &) = 0;
        virtual QWebElementCollection parse() = 0;
        virtual void extract(const QWebElement &) = 0;
        virtual QString video(const QString &) = 0; // provide video page html here

        virtual bool hasNext() = 0;
        virtual bool hasPrevious() = 0;
        virtual void next() = 0;
        virtual void previous()= 0;

        virtual QString baseUrl() = 0;
        virtual QString searchBaseUrl() = 0;
        virtual QString name() = 0;
};

Q_DECLARE_INTERFACE(SearchProviderInterface, "org.eu.merlin.QPcol.SearchProviderPluginInterface/1.0")

#endif // ISEARCHPROVIDER_H
