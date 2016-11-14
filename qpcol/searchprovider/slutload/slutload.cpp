#include "slutload.h"

QWebElementCollection Slutload::parse()
{
//    return webPage->mainFrame()->findAllElements("div.videos div.videoitem");
    return QWebElementCollection();
}

void Slutload::extract(const QWebElement &/* element*/)
{
//    page = element.findFirst("div.video-item").findFirst("a").attribute("href");
//    thumbnail = element.findFirst("img.thumb").attribute("src");
//    title = element.findFirst("h2").toPlainText();
//    url = video(page);
//    description = element.findFirst("div.videodescription").toPlainText();
}

QString Slutload::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp("<a rel=\"nofollow\" class=\"download\" href=\"([^\"]+)\">Download \\([0-9\\.]+ MB\\)</a>");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return regexp.cap(1);
    }
}

bool Slutload::hasNext()
{
    return ! webPage->mainFrame()->findFirstElement("li.navnext").isNull();
}

bool Slutload::hasPrevious()
{
    return false;
}

void Slutload::next()
{

}

void Slutload::previous()
{

}

QString Slutload::baseUrl()
{
    return QString("http://www.slutload.com");
}

QString Slutload::searchBaseUrl()
{
    return QString("http://");
}

QString Slutload::name()
{
    return QString("Slutload");
}
