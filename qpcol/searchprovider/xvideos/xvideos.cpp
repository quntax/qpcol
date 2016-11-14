#include "xvideos.h"

QWebElementCollection Xvideos::parse()
{
    return webPage->mainFrame()->findAllElements("div.thumbBlock");
}

void Xvideos::extract(const QWebElement & element)
{
    thumbnail = element.findFirst("img").attribute("src");
    title = element.findFirst("p").toPlainText();

    QString page = element.findFirst("a").attribute("href");
    url = video(page);

    description = element.findFirst("p.metadata").toPlainText();
}

QString Xvideos::video(const QString &html)
{
//    QByteArray html = fetch(address);
    QRegExp regexp("flashvars=\"id_video=([0-9]*)&amp;theskin=default&amp;flv_url=(.*)&amp;url_bigthumb=");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return QUrl::fromPercentEncoding(regexp.cap(2).toLocal8Bit()).toLocal8Bit();;
    }
}

bool Xvideos::hasNext()
{
    return ! webPage->mainFrame()->findFirstElement("a.sel").nextSibling().attribute("href").isEmpty();
}

bool Xvideos::hasPrevious()
{
    return ! webPage->mainFrame()->findFirstElement("a.sel").previousSibling().attribute("href").isEmpty();
}

void Xvideos::next()
{
    QString next = webPage->mainFrame()->findFirstElement("a.sel").nextSibling().attribute("href");
    loadPage(QString(baseUrl()).append(next.right(next.length()-1)));
}

void Xvideos::previous()
{
    QString previous = webPage->mainFrame()->findFirstElement("a.sel").nextSibling().attribute("href");
    loadPage(QString(baseUrl()).append(previous.right(previous.length()-1)));
}

QString Xvideos::baseUrl()
{
    return QString("http://www.xvideos.com/");
}

QString Xvideos::searchBaseUrl()
{
    return QString("http://www.xvideos.com/?k=");
}

QString Xvideos::name()
{
    return QString("Xvideos");
}
