#ifndef DIRSCANNER_H
#define DIRSCANNER_H

#include "film.h"
#include "hashhandler.h"

#include <QtCore>

typedef QHash<QByteArray, QString> HashList;

class DirScanner : public QObject
{
        Q_OBJECT

public:
    DirScanner();
    bool scanDirectory(const QString &);
    QStringList prepareHashes();
    inline bool isReady() { return ready; }

    static HashList scanResult;

public slots:
    void stopSearch();
    void reset();

signals:
    void itemsCount(int);
    void currentItem(int);

protected:
    bool checkExtension(const QString &);

private:
    QStringList videoFiles;
    QStringList duplicates;
    QString searchDirectory;

    bool ready;
    int itemsAmount;
    int itemCounter;
};

#endif // DIRSCANNER_H
