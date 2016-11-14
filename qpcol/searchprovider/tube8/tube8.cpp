#include "tube8.h"

QWebElementCollection Tube8::parse()
{
    return webPage->mainFrame()->findAllElements("div.thumb-wrapper");
}

void Tube8::extract(const QWebElement &element)
{
    page = element.findFirst("div.video-cont-wrapper").previousSibling().findFirst("a").attribute("href");
    thumbnail = element.findFirst("img.videoThumbs").attribute("src");
    title = element.findFirst("h2").toPlainText();
    url = video(page);
    description = element.findFirst("div.video-cont-wrapper").toPlainText();
}

QString Tube8::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp("var videourl=\"([^\"]+)\";");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return QUrl::fromPercentEncoding(regexp.cap(1).toLocal8Bit());
    }
}

bool Tube8::hasNext()
{
    return ! webPage->mainFrame()->findFirstElement("div.footer-pagination ul").lastChild().firstChild().attribute("href").isEmpty();
}

bool Tube8::hasPrevious()
{
    return ! webPage->mainFrame()->findFirstElement("div.footer-pagination ul").firstChild().firstChild().attribute("href").isEmpty();
}

void Tube8::next()
{
    QString next = webPage->mainFrame()->findFirstElement("div.footer-pagination ul").lastChild().firstChild().attribute("href");
    loadPage(QString(baseUrl()).append(next));
}

void Tube8::previous()
{
    QString previous = webPage->mainFrame()->findFirstElement("div.footer-pagination ul").firstChild().firstChild().attribute("href");
    loadPage(QString("%1%2").arg(baseUrl()).arg(previous));
}

QString Tube8::baseUrl()
{
    return QString("http://www.tube8.com/");
}

QString Tube8::searchBaseUrl()
{
    return QString("http://www.tube8.com/search.html?q=");

}

QString Tube8::name()
{
    return QString("Tube8");
}
