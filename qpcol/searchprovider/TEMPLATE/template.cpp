#include "%PLUGIN_FILE%.h"

QWebElementCollection %PLUGIN_NAME%::parse()
{
    return webPage->mainFrame()->findAllElements("div.videos div.videoitem");
}

void %PLUGIN_NAME%::extract(const QWebElement & element)
{
    page = element.findFirst("div.video-item").findFirst("a").attribute("href");
    thumbnail = element.findFirst("img.thumb").attribute("src");
    title = element.findFirst("h2").toPlainText();
    url = video(page);
    description = element.findFirst("div.videodescription").toPlainText();
}

QString %PLUGIN_NAME%::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp("regexp");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return regexp.cap(1);
    }
}

bool %PLUGIN_NAME%::hasNext()
{
    return ! webPage->mainFrame()->findFirstElement("li.navnext").isNull();
}

bool %PLUGIN_NAME%::hasPrevious()
{
    return ! webPage->mainFrame()->findFirstElement("li.navprev").isNull();
}

void %PLUGIN_NAME%::next()
{
    QString next = webPage->mainFrame()->findFirstElement("li.navnext a").attribute("href");
    loadPage(QString(baseUrl()).append(next));
}

void %PLUGIN_NAME%::previous()
{
    QString prev = webPage->mainFrame()->findFirstElement("li.navprev a").attribute("href");
    loadPage(QString(baseUrl()).append(prev));
}

QString %PLUGIN_NAME%::baseUrl()
{
    return QString("http://");
}

QString %PLUGIN_NAME%::searchBaseUrl()
{
    return QString("http://");
}

QString %PLUGIN_NAME%::name()
{
    return QString("%PLUGIN_NAME%");
}
