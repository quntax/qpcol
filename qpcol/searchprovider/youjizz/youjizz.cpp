#include "youjizz.h"

QWebElementCollection Youjizz::parse()
{
    return webPage->mainFrame()->findAllElements("div#main span#miniatura");
}

void Youjizz::extract(const QWebElement &element)
{
    QString relativeUrl = element.findFirst("a.frame").attribute("href");
    page = QString("%1%2").arg(baseUrl()).arg(relativeUrl);
    thumbnail = element.findFirst("img").attribute("src");
    title = element.findFirst("span.pic").nextSibling().toPlainText().trimmed();
    url = video(page);
    description = element.findFirst("span.thumbtime span").toPlainText();
}

QString Youjizz::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp("so.addVariable\\(\"file\",\"([^\"]+)\"\\);");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return regexp.cap(1);
    }
}

bool Youjizz::hasNext()
{
    return false; // TODO
}

bool Youjizz::hasPrevious()
{
    return false; // TODO
}

void Youjizz::next()
{
    // TODO
}

void Youjizz::previous()
{
    // TODO
}

QString Youjizz::baseUrl()
{
    return QString("http://www.youjizz.com/");
}

QString Youjizz::searchBaseUrl()
{
    return QString("http://www.youjizz.com/srch.php?q=");
}

QString Youjizz::name()
{
    return QString("Youjizz");
}
