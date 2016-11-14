#include "submityourflicks.h"

QWebElementCollection Submityourflicks::parse()
{
//    return webPage->mainFrame()->findAllElements("div.videos div.videoitem");
    return QWebElementCollection();
}

void Submityourflicks::extract(const QWebElement &/* element*/)
{
//    page = element.findFirst("div.video-item").findFirst("a").attribute("href");
//    thumbnail = element.findFirst("img.thumb").attribute("src");
//    title = element.findFirst("h2").toPlainText();
//    url = video(page);
//    description = element.findFirst("div.videodescription").toPlainText();
}

QString Submityourflicks::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp("so.addVariable\\(\"file\", \"([^\"]*)\"\\);");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return QUrl::fromPercentEncoding(regexp.cap(1).toLocal8Bit());
    }
}

bool Submityourflicks::hasNext()
{
    return ! webPage->mainFrame()->findFirstElement("li.navnext").isNull();
}

bool Submityourflicks::hasPrevious()
{
    return ! webPage->mainFrame()->findFirstElement("li.navprev").isNull();
}

void Submityourflicks::next()
{
    QString next = webPage->mainFrame()->findFirstElement("li.navnext a").attribute("href");
    loadPage(QString(baseUrl()).append(next));
}

void Submityourflicks::previous()
{
    QString prev = webPage->mainFrame()->findFirstElement("li.navprev a").attribute("href");
    loadPage(QString(baseUrl()).append(prev));
}

QString Submityourflicks::baseUrl()
{
    return QString("http://www.submityourflicks.com/");
}

QString Submityourflicks::searchBaseUrl()
{
    return QString("http://");
}

QString Submityourflicks::name()
{
    return QString("Submityourflicks");
}
