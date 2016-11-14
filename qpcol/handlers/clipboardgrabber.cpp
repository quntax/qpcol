#include "clipboardgrabber.h"

ClipboardGrabber::ClipboardGrabber(QObject *parent) :
    QObject(parent)
{
    clipboard = QApplication::clipboard();
    connect(clipboard, SIGNAL(dataChanged()),
            this, SLOT(queryPlugins()));
}

void ClipboardGrabber::queryPlugins()
{
    if (! enabled) {
        return;
    }

//    ProviderMap p = PluginLoader::instance()->map();
//    QHashIterator<QString, Provider> iterator(p);
//    qDebug() << "Clipboard URL:" << clipboard->text();
//    while (iterator.hasNext()) {
//        iterator.next();
//        plugin = PluginLoader::instance()->provider(iterator.key());

////        if (clipboard->text().startsWith(plugin->baseUrl())) {
//        if (clipboard->text().contains(plugin->baseUrl())) {
//            QString videoUrl = plugin->video(clipboard->text());

//            qDebug() << "Plugin returned URL:" << videoUrl;

//            if (videoUrl.isEmpty()) {
//                return;
//            }

//            emit urlFound(clipboard->text(), videoUrl);
//        }
//    }
}

void ClipboardGrabber::set(bool isset)
{
    enabled = isset;
}
