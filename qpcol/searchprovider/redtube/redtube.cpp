#include "redtube.h"

QWebElementCollection Redtube::parse()
{
    return webPage->mainFrame()->findAllElements("div.videos div.videoitem");
}

void Redtube::extract(const QWebElement & element)
{
    page = element.findFirst("div.video-item").findFirst("a").attribute("href");
    thumbnail = element.findFirst("img.thumb").attribute("src");
    title = element.findFirst("h2").toPlainText();
    url = video(page);
    description = element.findFirst("div.videodescription").toPlainText();
}

QString Redtube::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp("<source src='([^']+)' type='.+'>\".+");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return regexp.cap(1);
    }
}

bool Redtube::hasNext()
{
    return ! webPage->mainFrame()->findFirstElement("li.navnext").isNull();
}

bool Redtube::hasPrevious()
{
    return ! webPage->mainFrame()->findFirstElement("li.navprev").isNull();
}

void Redtube::next()
{
    QString next = webPage->mainFrame()->findFirstElement("li.navnext a").attribute("href");
    loadPage(QString(baseUrl()).append(next));
}

void Redtube::previous()
{
    QString prev = webPage->mainFrame()->findFirstElement("li.navprev a").attribute("href");
    loadPage(QString(baseUrl()).append(prev));
}

QString Redtube::baseUrl()
{
    return QString("http://www.redtube.com/");
}

QString Redtube::searchBaseUrl()
{
    return QString("http://www.redtube.com/?search=");
}

QString Redtube::name()
{
    return QString("Redtube");
}
