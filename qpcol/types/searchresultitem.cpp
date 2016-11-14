#include "searchresultitem.h"

SearchResultItem &SearchResultItem::operator=(const SearchResultItem &other)
{
    videoImage = QPixmap();
    videoUrl = other.videoUrl;
    videoTitle = other.videoTitle;
    videoDescription = other.videoDescription;
    videoThumbnail = other.videoThumbnail;
    itemHash = other.itemHash;

    return *this;
}

void SearchResultItem::setUrl(const QString &url)
{
    videoUrl = url;
}

void SearchResultItem::setTitle(const QString &title)
{
    videoTitle = title;
}

void SearchResultItem::setDescription(const QString &description)
{
    videoDescription = description;
}

void SearchResultItem::setThumbnail(const QString &thumbnail)
{
    videoThumbnail = thumbnail;
}

void SearchResultItem::setPixmap(QPixmap pixmap)
{
    videoImage = pixmap;
}

void SearchResultItem::setHash(const QByteArray &input)
{
    itemHash = input;
}

QString SearchResultItem::url()
{
    return videoUrl;
}

QString SearchResultItem::title()
{
    return videoTitle;
}

QString SearchResultItem::description()
{
    return videoDescription;
}

QString SearchResultItem::thumbnail()
{
    return videoThumbnail;
}

QPixmap SearchResultItem::image()
{
    return videoImage;
}

QSize SearchResultItem::thumbnailSize() const
{
    return QSize(140, 100);
}

QByteArray SearchResultItem::hash()
{
    return itemHash;
}
