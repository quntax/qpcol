#include "searchprovider.h"

SearchProvider::SearchProvider()
{
    webPage = new QWebPage;
    connect(webPage, SIGNAL(loadStarted()),
            this, SIGNAL(loadStarted()));
    connect(webPage, SIGNAL(loadFinished(bool)),
            this, SLOT(loadFinished(bool)));

//    webView= new QWebView();
//    connect(webView, SIGNAL(loadFinished(bool)),
//            this, SLOT(loadFinished(bool)));
}

SearchProvider::~SearchProvider()
{
    webPage->deleteLater();

    if (webView) {
        webView->deleteLater();
    }
}

void SearchProvider::search(const QString &phrase)
{
    searchUrl = QString("%1%2").arg(searchBaseUrl()).arg(phrase);
    emit searchResultsPageUrl(searchUrl);
    // experiment - webkit in mainwindow will load it and notify provider instance, when page content is available
    // connect signals and slots somewhere
    // loadPage(searchUrl);
}

void SearchProvider::sendItem()
{
    SearchResultItem item;

    item.setUrl(url);
    item.setTitle(title);
    item.setDescription(description);
    item.setThumbnail(thumbnail);
    item.setHash(searchHash);

    emit extracted(item);
}

/**
 * This loads search results page in order to  get HTML to process
 * @brief SearchProvider::loadPage
 * @param url
 */
void SearchProvider::loadPage(const QString &url)
{
    qDebug() << "Loading URL:" << QUrl::fromUserInput(url).toEncoded();
    searchHash = urlHash(url);

    emit hash(searchHash);
    return;
    emit loadStarted();

//    QHttpRequest request;
//    request.setUrl(url);
//    QString contents = request.get();

    QHttpDownload * download = new QHttpDownload;
    connect(download, SIGNAL(complete(QByteArray)),
            this, SLOT(setContents(QByteArray)));
    download->download(url);
}

void SearchProvider::loadFinished(bool status)
{
    webPage = webView->page();
    emit loadFinished();

    if (! status) {
        return;
    }

//    webView->setPage();
    QString html = webView->page()->mainFrame()->toHtml();

//    qDebug() << html;

    emit videoUrl(html);
    return;// html;

    QWebElementCollection result = parse();
    foreach(QWebElement element, result) {
        queue.enqueue(element);
    }

    while (! queue.isEmpty()) {
        extract(queue.dequeue());
        sendItem();
    }

    emit complete();
}

void SearchProvider::setContents(QByteArray data)
{
    contents = data;
    webPage->mainFrame()->setHtml(contents);
}

QByteArray SearchProvider::fetch(const QString &address)
{
    webView->load(QUrl(address));
    return QByteArray();
//    connect(wv, SIGNAL(loadFinished(bool))
//    QByteArray html = wv->page()->mainFrame()->toHtml().toUtf8();

//    qDebug() << html;

//    return html;
//    page->set
    QHttpDownload * download = new QHttpDownload;
//    QHttpRequest request;
//    request.setUrl(address);
    connect(download, SIGNAL(complete(QByteArray)),
            this, SLOT(setContents(QByteArray)));

    download->download(address);
    QByteArray html/* = request.get()*/;

    return html;
}

QByteArray SearchProvider::urlHash(const QString &input)
{
    return HashHandler::calculate(input.toLocal8Bit());
}

