#include "girlfriendvideos.h"

QWebElementCollection Girlfriendvideos::parse()
{
//    return webPage->mainFrame()->findAllElements("div.videos div.videoitem");
    return QWebElementCollection();
}

void Girlfriendvideos::extract(const QWebElement &/* element*/)
{
//    page = element.findFirst("div.video-item").findFirst("a").attribute("href");
//    thumbnail = element.findFirst("img.thumb").attribute("src");
//    title = element.findFirst("h2").toPlainText();
//    url = video(page);
//    description = element.findFirst("div.videodescription").toPlainText();
}

QString Girlfriendvideos::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp("<a href=\"([^\"]+)\">Download this video</a>");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return QString("%1%2").arg(baseUrl(), regexp.cap(1));
    }
}

bool Girlfriendvideos::hasNext()
{
//    return ! webPage->mainFrame()->findFirstElement("li.navnext").isNull();
    return false;
}

bool Girlfriendvideos::hasPrevious()
{
//    return ! webPage->mainFrame()->findFirstElement("li.navprev").isNull();
    return false;
}

void Girlfriendvideos::next()
{
//    QString next = webPage->mainFrame()->findFirstElement("li.navnext a").attribute("href");
//    loadPage(QString(baseUrl()).append(next));
}

void Girlfriendvideos::previous()
{
//    QString prev = webPage->mainFrame()->findFirstElement("li.navprev a").attribute("href");
//    loadPage(QString(baseUrl()).append(prev));
}

QString Girlfriendvideos::baseUrl()
{
    return QString("http://girlfriendvideos.com/");
}

QString Girlfriendvideos::searchBaseUrl()
{
    return QString("http://");
}

QString Girlfriendvideos::name()
{
    return QString("Girlfriendvideos");
}
