#include "moviesand.h"

QWebElementCollection Moviesand::parse()
{
//    return webPage->mainFrame()->findAllElements("div.videos div.videoitem");
    return QWebElementCollection();
}

void Moviesand::extract(const QWebElement &/* element*/)
{
//    page = element.findFirst("div.video-item").findFirst("a").attribute("href");
//    thumbnail = element.findFirst("img.thumb").attribute("src");
//    title = element.findFirst("h2").toPlainText();
//    url = video(page);
//    description = element.findFirst("div.videodescription").toPlainText();
}

QString Moviesand::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp1("flashvars1.file = \"([^\"]*)");
    QRegExp regexp2("so.addVariable\\(\"file\", \"([^\"]+)\"\\);");

    if (regexp1.indexIn(html) == -1 && regexp2.indexIn(html) == -1) {
        return QString();
    } else {
        qDebug() << regexp1.cap(1);
        qDebug() << regexp2.cap(1);
        return regexp1.cap(1).isEmpty() ? regexp2.cap(1) : regexp1.cap(1);
    }
}

bool Moviesand::hasNext()
{
    return false;
}

bool Moviesand::hasPrevious()
{
    return false;
}

void Moviesand::next()
{
    QString next = webPage->mainFrame()->findFirstElement("li.navnext a").attribute("href");
    loadPage(QString(baseUrl()).append(next));
}

void Moviesand::previous()
{
    QString prev = webPage->mainFrame()->findFirstElement("li.navprev a").attribute("href");
    loadPage(QString(baseUrl()).append(prev));
}

QString Moviesand::baseUrl()
{
    return QString("http://www.moviesand.com/");
}

QString Moviesand::searchBaseUrl()
{
    return QString("http://");
}

QString Moviesand::name()
{
    return QString("Moviesand");
}
