#ifndef CLIPBOARDGRABBER_H
#define CLIPBOARDGRABBER_H

#include "confighandler.h"

#include <QObject>
#include <QApplication>
#include <QClipboard>

class ClipboardGrabber : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardGrabber(QObject *parent = 0);

    void set(bool);

signals:
    void urlFound(const QString &, const QString &);
//    void downloadCompleted(const QString &);

private:
    QClipboard *clipboard;
//    SearchProvider *plugin;

    bool enabled;

public slots:
    void queryPlugins();
};

#endif // CLIPBOARDGRABBER_H
