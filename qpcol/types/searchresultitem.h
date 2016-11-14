#ifndef SEARCHRESULTITEM_H
#define SEARCHRESULTITEM_H

#include <QtCore>
#include <QtGui>

class SearchResultItem
{
public:
    SearchResultItem &operator=(const SearchResultItem &);

    QString url();
    QString title();
    QString description();
    QString thumbnail();
    QPixmap image();
    QByteArray hash();

    void setUrl(const QString &);
    void setTitle(const QString &);
    void setDescription(const QString &);
    void setThumbnail(const QString &);
    void setPixmap(QPixmap);
    void setHash(const QByteArray &);

    QSize thumbnailSize() const;

protected:
    QString videoUrl;
    QString videoTitle;
    QString videoDescription;
    QString videoThumbnail;
    QPixmap videoImage;
    QByteArray itemHash;
};

Q_DECLARE_METATYPE(SearchResultItem)

#endif // SEARCHRESULTITEM_H
