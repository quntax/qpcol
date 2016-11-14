#include "hotpornshow.h"

QWebElementCollection Hotpornshow::parse()
{
    return webPage->mainFrame()->findAllElements("div.videos div.videoitem");
}

void Hotpornshow::extract(const QWebElement & element)
{
    page = element.findFirst("div.video-item").findFirst("a").attribute("href");
    thumbnail = element.findFirst("img.thumb").attribute("src");
    title = element.findFirst("h2").toPlainText();
    url = video(page);
    description = element.findFirst("div.videodescription").toPlainText();
}

QString Hotpornshow::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp("so.addVariable\\('file','([^']+)'\\);");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return regexp.cap(1);
    }
}

bool Hotpornshow::hasNext()
{
    return ! webPage->mainFrame()->findFirstElement("li.navnext").isNull();
}

bool Hotpornshow::hasPrevious()
{
    return ! webPage->mainFrame()->findFirstElement("li.navprev").isNull();
}

void Hotpornshow::next()
{
    QString next = webPage->mainFrame()->findFirstElement("li.navnext a").attribute("href");
    loadPage(QString(baseUrl()).append(next));
}

void Hotpornshow::previous()
{
    QString prev = webPage->mainFrame()->findFirstElement("li.navprev a").attribute("href");
    loadPage(QString(baseUrl()).append(prev));
}

QString Hotpornshow::baseUrl()
{
    return QString("hotpornshow.com");
}

QString Hotpornshow::searchBaseUrl()
{
    return QString("http://www.hotpornshow.com/search/?q=");
}

QString Hotpornshow::name()
{
    return QString("Hotpornshow");
}
