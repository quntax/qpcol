#include "searchresulthandler.h"

SearchResultHandler::SearchResultHandler(QObject *parent) :
    QObject(parent)
{
}

void SearchResultHandler::setUrl(const QString &url)
{
    hash = QCryptographicHash::hash(url.toLocal8Bit(),
                                    QCryptographicHash::Md5).toHex();
}

void SearchResultHandler::handle(SearchResultItem receivedItem)
{
    if (receivedItem.hash() != hash) {
        return;
    }

    QPCOL_RESULT_HANDLER(receivedItem);

    item = receivedItem;

    httpDownload = new QHttpDownload;
    connect(httpDownload, SIGNAL(complete(QByteArray)),
            this, SLOT(sendItem(QByteArray)));

    httpDownload->download(item.thumbnail());
}

void SearchResultHandler::sendItem(QByteArray data)
{
    httpDownload->deleteLater();
    httpDownload = 0;

    QPixmap pixmap;
    pixmap.loadFromData(data);
    item.setPixmap(pixmap);

    emit itemCreated(item);
}

QListWidgetItem * operator<<(QListWidgetItem *listItem, SearchResultItem resultItem)
{
    listItem->setData(Qt::DisplayRole, QVariant(resultItem.title()));
    listItem->setData(Qt::DecorationRole,
                      QVariant(resultItem.image().scaled(resultItem.thumbnailSize(),
                                                         Qt::KeepAspectRatio)));
    listItem->setData(Qt::UserRole + 1, resultItem.url());
    listItem->setData(Qt::UserRole + 2, resultItem.description());

    return listItem;
}
