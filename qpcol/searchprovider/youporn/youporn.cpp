#include "youporn.h"

Youporn::Youporn()
{
    QNetworkCookieJar *cookieJar = new QNetworkCookieJar;
    QNetworkCookie cookie("age_check", "1");
    QList<QNetworkCookie> cookiesList;
    cookiesList = cookieJar->cookiesForUrl(QUrl(baseUrl()));
    cookiesList.append(cookie);
    cookieJar->setCookiesFromUrl(cookiesList, QUrl(baseUrl()));

    downloader = new QHttpDownload;
    connect(downloader, SIGNAL(chunk(QByteArray)),
            this, SLOT(addHtml(QByteArray)));
    connect(downloader, SIGNAL(complete(QByteArray)),
            this, SLOT(setHtml(QByteArray)));
    connect(this, SIGNAL(gotHtml()),
            &loop, SLOT(quit()));

    downloader->setCookieJar(cookieJar);
}

//void Youporn::loadPage(const QString &/*url*/)
//{

//}

QWebElementCollection Youporn::parse()
{
    return webPage->mainFrame()->findAllElements("div#video-listing ul.clearfix li");
}

void Youporn::extract(const QWebElement &element)
{
    page = element.findFirst("div.video-item").findFirst("a").attribute("href");
    qDebug() << page;
    thumbnail = element.findFirst("img").attribute("src");
    title = element.findFirst("h1").toPlainText();
    url = video(page);
    description = element.findFirst("div.duration_views").toPlainText();
}

QString Youporn::video(const QString &address)
{
    downloader->download(address);
    loop.exec();

    QRegExp regexp("<a href=\"([^\"]+)\">MP4 - For Windows 7, Mac and iPad</a>");

    if (regexp.indexIn(html) == -1) {
        html.clear();
        return QString();
    } else {
        html.clear();
        return regexp.cap(1);
    }
}

bool Youporn::hasNext()
{
    return false;
}

bool Youporn::hasPrevious()
{
    return false;
}

void Youporn::next()
{

}

void Youporn::previous()
{

}

QString Youporn::baseUrl()
{
    return QString("http://youporn.com");
}

QString Youporn::searchBaseUrl()
{
    return QString("http://youporn.com/search?query=");
}

QString Youporn::name()
{
    return QString("Youporn");
}

void Youporn::addHtml(QByteArray replyData)
{
    html.append(replyData);
//    emit gotHtml();
}

void Youporn::setHtml(QByteArray/* replyData*/)
{
//    html = replyData;
    emit gotHtml();
}
