#include "stileproject.h"

QWebElementCollection Stileproject::parse()
{
     return webPage->mainFrame()->findAllElements("div.videolist div.videoitem");
}

void Stileproject::extract(const QWebElement &element)
{
    QString relativeUrl = element.findFirst("div.videometa div.videotitle a").attribute("href");
    page = QString("%1%2").arg(baseUrl()).arg(relativeUrl);
    thumbnail = element.findFirst("img").attribute("src");
    title = element.findFirst("div.videometa div.videotitle a").attribute("title");
    url = video(page);
    description = element.findFirst("div.duration").toPlainText();
}

QString Stileproject::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp("\"file\":(\"|\')([^(\"|\')]+)(\"|\'),");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return regexp.cap(2).replace("\\", "");
    }
}

bool Stileproject::hasNext()
{
    return true;
}

bool Stileproject::hasPrevious()
{
    return true;
}

void Stileproject::next()
{
    QString next = webPage->mainFrame()->findFirstElement("div.pagination").lastChild().attribute("href");
    loadPage(QString(baseUrl()).append(next));
}

void Stileproject::previous()
{
    QString previous = webPage->mainFrame()->findFirstElement("div.pagination").firstChild().attribute("href");
    loadPage(QString(baseUrl()).append(previous));
}

QString Stileproject::baseUrl()
{
    return QString("http://www.stileproject.com/");
}

QString Stileproject::searchBaseUrl()
{
    return QString("http://www.stileproject.com/video/search.html?query=");
}

QString Stileproject::name()
{
    return QString("Stileproject");
}
