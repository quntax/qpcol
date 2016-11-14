#include "xflogger.h"

QWebElementCollection Xflogger::parse()
{
    return webPage->mainFrame()->findAllElements("div.videos div.videoitem");
}

void Xflogger::extract(const QWebElement & element)
{
    page = element.findFirst("div.video-item").findFirst("a").attribute("href");
    thumbnail = element.findFirst("img.thumb").attribute("src");
    title = element.findFirst("h2").toPlainText();
    url = video(page);
    description = element.findFirst("div.videodescription").toPlainText();
}

QString Xflogger::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp("www.xflogger.com/media/player/player.swf\\?f=([^\"]+)\"");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return captureUrl(regexp.cap(1));
    }
}

bool Xflogger::hasNext()
{
    return false;
}

bool Xflogger::hasPrevious()
{
    return false;
}

void Xflogger::next()
{
    QString next = webPage->mainFrame()->findFirstElement("li.navnext a").attribute("href");
    loadPage(QString(baseUrl()).append(next));
}

void Xflogger::previous()
{
    QString prev = webPage->mainFrame()->findFirstElement("li.navprev a").attribute("href");
    loadPage(QString(baseUrl()).append(prev));
}

QString Xflogger::baseUrl()
{
    return QString("http://www.xflogger.com");
}

QString Xflogger::searchBaseUrl()
{
    return QString("http://www.xflogger.com/search?search_type=videos&search_query=");
}

QString Xflogger::name()
{
    return QString("Xflogger");
}

void Xflogger::addXml(QByteArray replyData)
{
    xml.append(replyData);
}

void Xflogger::setXml(QByteArray replyData)
{
    xml = replyData;
    emit gotXml();
}

QString Xflogger::captureUrl(QString xmlUrl)
{
    QMutexLocker locker(&mutex);

    downloader = new QHttpDownload;
    connect(downloader, SIGNAL(chunk(QByteArray)),
            this, SLOT(addXml(QByteArray)));
    connect(downloader, SIGNAL(complete(QByteArray)),
            this, SLOT(setXml(QByteArray)));
    connect(this, SIGNAL(gotXml()),
            &loop, SLOT(quit()));

    downloader->download(xmlUrl);
    loop.exec();

    QRegExp parsedRegexp("<src>(.*)</src>");
    QString videoUrl;

    parsedRegexp.setMinimal(true);

    if (parsedRegexp.indexIn(xml) > -1) {
        videoUrl = parsedRegexp.cap(1);
    }

    xml.clear();

    return videoUrl;
}
