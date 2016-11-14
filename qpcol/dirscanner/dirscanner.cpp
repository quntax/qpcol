#include "dirscanner.h"

HashList DirScanner::scanResult;// = HashList();

DirScanner::DirScanner()
{
    ready = true;
    itemsAmount = 0;
    itemCounter = 0;
}

bool DirScanner::scanDirectory(const QString & directory) {
    if (searchDirectory.isEmpty()) {
        searchDirectory = directory;
    }

    QDir entry;

    entry.setPath(directory);
    entry.setFilter(QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoSymLinks);

    QStringList items = entry.entryList();

    if (items.isEmpty()) {
        return false;
    }

    QStringListIterator iterator(items);
    while (iterator.hasNext()) {
        if (! ready) {
            return false;
        }

        QString item = iterator.next();
        QString itemPath = QString("%1/%2").arg(directory).arg(item);
        QFileInfo info(itemPath);

        if (info.isFile() && info.size() < HASH_LENGTH) {
            continue;
        }

        if (info.isFile() && info.isReadable() && checkExtension(info.suffix())) {
            videoFiles.append(itemPath);
        } else if (info.isDir() && info.isReadable() && item != "." && item != "..") {
            scanDirectory(itemPath);
        }
    }

    return true;
}

QStringList DirScanner::prepareHashes()
{
    itemsAmount = videoFiles.count();

    emit itemsCount(itemsAmount);
    QStringListIterator iterator(videoFiles);
    while (iterator.hasNext()) {
        if (! ready) {
            return duplicates;
        }

        emit currentItem(itemCounter++);

        QString item = iterator.next();

        HashHandler hashHandler(item);
        QByteArray hash = hashHandler.hash();

        if (hash.isEmpty()) {
            continue;
        }

        if (DirScanner::scanResult.contains(hash)) {
            QString duplicated = DirScanner::scanResult.value(hash);

            qDebug() << "Obsolete duplicate:" << duplicated << QString("(qpcol://%1)").arg(QString(hash));

            duplicates.append(item);
            continue;
        }

        DirScanner::scanResult.insert(hash, item);
    }

    return duplicates;
}

void DirScanner::stopSearch()
{
    ready = false;
}

void DirScanner::reset()
{
    searchDirectory.clear();
    videoFiles.clear();
    duplicates.clear();

    ready = true;
    itemsAmount = 0;
    itemCounter = 0;
}

bool DirScanner::checkExtension(const QString & extension) {
    // TODO: defined const
    QString extensions(HANDLED_FORMATS);
    return extensions.contains(extension);
}
