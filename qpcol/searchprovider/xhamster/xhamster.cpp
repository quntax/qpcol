#include "xhamster.h"

QWebElementCollection Xhamster::parse()
{
    return webPage->mainFrame()->findAllElements("td#video_title td");
}

void Xhamster::extract(const QWebElement &element)
{
    page = QString("%1%2").arg(baseUrl()).arg(element.findFirst("a").attribute("href"));
    thumbnail = element.findFirst("img").attribute("src");
    title = element.findFirst("div.moduleFeaturedTitle a").toPlainText();
    url = video(page);
    QString details = element.findFirst("div.moduleFeaturedDetails").toInnerXml();
    description = details.left(QStringMatcher("<br").indexIn(details));
}

QString Xhamster::video(const QString &html)
{
    QRegExp fileRegexp("&amp;srv=(.+)&amp;image=");
    QString vid;

    if (fileRegexp.indexIn(html) != -1) {
        vid = QUrl::fromPercentEncoding(fileRegexp.cap(1).toLocal8Bit());
        vid = vid.replace("&amp;file=", "/key=");

        if (vid.startsWith("/key=")) {
            vid = vid.remove(0, QString("/key=").length());
        }

        QPCOL_MDEBUG("Video URL" << vid);
    }

    return vid;
}

bool Xhamster::hasNext()
{
    return ! webPage->mainFrame()->findFirstElement("span.navNext").isNull();
}

bool Xhamster::hasPrevious()
{
    return ! webPage->mainFrame()->findFirstElement("span.navPrev").isNull();
}

void Xhamster::next()
{
    QString next = webPage->mainFrame()->findFirstElement("span.navNext a").attribute("href");
    loadPage(QString(baseUrl()).append(next));
}

void Xhamster::previous()
{
    QString previous = webPage->mainFrame()->findFirstElement("span.navPrev a").attribute("href");
    loadPage(QString("%1%2").arg(baseUrl()).arg(previous));
}

QString Xhamster::baseUrl()
{
    return QString("http://xhamster.com/");
}

QString Xhamster::searchBaseUrl()
{
    return QString("http://xhamster.com/search.php?qcat=video&q=");
}

QString Xhamster::name()
{
    return QString("Xhamster");
}
