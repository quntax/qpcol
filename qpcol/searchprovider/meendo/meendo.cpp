#include "meendo.h"

QWebElementCollection Meendo::parse()
{
    return webPage->mainFrame()->findAllElements("div.videos div.videoitem");
}

void Meendo::extract(const QWebElement & element)
{
    page = element.findFirst("div.video-item").findFirst("a").attribute("href");
    thumbnail = element.findFirst("img.thumb").attribute("src");
    title = element.findFirst("h2").toPlainText();
    url = video(page);
    description = element.findFirst("div.videodescription").toPlainText();
}

QString Meendo::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp("video_url: '([^']+)',");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return regexp.cap(1);
    }
}

bool Meendo::hasNext()
{
    return ! webPage->mainFrame()->findFirstElement("li.navnext").isNull();
}

bool Meendo::hasPrevious()
{
    return ! webPage->mainFrame()->findFirstElement("li.navprev").isNull();
}

void Meendo::next()
{
    QString next = webPage->mainFrame()->findFirstElement("li.navnext a").attribute("href");
    loadPage(QString(baseUrl()).append(next));
}

void Meendo::previous()
{
    QString prev = webPage->mainFrame()->findFirstElement("li.navprev a").attribute("href");
    loadPage(QString(baseUrl()).append(prev));
}

QString Meendo::baseUrl()
{
    return QString("http://www.meendo.");
}

QString Meendo::searchBaseUrl()
{
    return QString("http://");
}

QString Meendo::name()
{
    return QString("Meendo");
}
