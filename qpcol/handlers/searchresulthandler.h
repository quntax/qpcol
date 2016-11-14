#ifndef SEARCHHANDLER_H
#define SEARCHHANDLER_H

#ifdef QPCOL_RELEASE
#define QPCOL_RESULT_HANDLER(ITEM) \
        if (ITEM.url().isEmpty()) { \
            return; \
        }
#else
#define QPCOL_RESULT_HANDLER(ITEM) // ITEM
#endif

class SearchResultHandler : public QObject
{
    Q_OBJECT
public:
    explicit SearchResultHandler(QObject *parent = 0);
    void setUrl(const QString &);

public slots:
    void handle(SearchResultItem);
    inline void setHash(const QByteArray &input) { hash = input; }

signals:
    void itemCreated(SearchResultItem);

protected slots:
    void sendItem(QByteArray);

protected:
    QByteArray hash;
    QHttpDownload * httpDownload;
    SearchResultItem item;
};

QListWidgetItem *operator<<(QListWidgetItem *, SearchResultItem);

#endif // SEARCHHANDLER_H
