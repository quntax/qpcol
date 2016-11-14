#include "pornhub.h"

QWebElementCollection Pornhub::parse()
{
    return webPage->mainFrame()->findAllElements("ul.nf-videos li.videoblock div.wrap");
}

void Pornhub::extract(const QWebElement & element)
{
    page = element.findFirst("a").attribute("href");
    thumbnail = element.findFirst("img.rotating").attribute("src");
    title = element.findFirst("h5.title").toPlainText();
    url = video(page);
    description = element.findFirst("var.duration").toPlainText();
}

QString Pornhub::video(const QString &address)
{
    QByteArray html = fetch(address);
    QRegExp regexp("<param name=\"FlashVars\" value=\"options=([^\"]*)");

    if (regexp.indexIn(html) == -1) {
        return QString();
    } else {
        return captureUrl(regexp.cap(1));
    }
}

bool Pornhub::hasNext()
{
//    return ! webPage->mainFrame()->findFirstElement("li.navnext").isNull();
    return false;
}

bool Pornhub::hasPrevious()
{
//    return ! webPage->mainFrame()->findFirstElement("li.navprev").isNull();
    return false;
}

void Pornhub::next()
{
//    QString next = webPage->mainFrame()->findFirstElement("li.navnext a").attribute("href");
//    loadPage(QString(baseUrl()).append(next));
}

void Pornhub::previous()
{
//    QString prev = webPage->mainFrame()->findFirstElement("li.navprev a").attribute("href");
//    loadPage(QString(baseUrl()).append(prev));
}

QString Pornhub::baseUrl()
{
    return QString("http://www.pornhub.com");
}

QString Pornhub::searchBaseUrl()
{
    return QString("http://www.pornhub.com/video/search?search=");
}

QString Pornhub::name()
{
    return QString("Pornhub");
}

void Pornhub::chunkAddress(QByteArray urlChunk)
{
    xmlData.append(urlChunk);
}

void Pornhub::setAddress(QByteArray urlAddress)
{
    xmlData = urlAddress;
    emit gotAddress();
}

QString Pornhub::captureUrl(QString xmlUrl)
{
    QMutexLocker locker(&mutex);

    downloader = new QHttpDownload;
    connect(downloader, SIGNAL(chunk(QByteArray)),
            this, SLOT(chunkAddress(QByteArray)));
    connect(downloader, SIGNAL(complete(QByteArray)),
            this, SLOT(setAddress(QByteArray)));
    connect(this, SIGNAL(gotAddress()),
            &loop, SLOT(quit()));

    downloader->download(xmlUrl);
    loop.exec();

    QRegExp parsedRegexp("<flv_url>(.*)</flv_url>");
    QString videoUrl;

    if (parsedRegexp.indexIn(xmlData) > -1) {
        videoUrl = parsedRegexp.cap(1);
    }

    xmlData.clear();

    return videoUrl;
}
