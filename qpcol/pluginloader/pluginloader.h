#ifndef _PLUGINLOADER_H
#define	_PLUGINLOADER_H

#include "providers.h"

#include <QtCore>

class PluginLoader : public QObject {
    Q_OBJECT

public:
    static PluginLoader * instance();

    SearchProvider * provider(const QString &);
    SearchProvider * provider();
    ProviderMap map();

private:
    ProviderMap providerMap;
    SearchProvider *currentProvider;

    PluginLoader();
    PluginLoader(PluginLoader const &);
    static PluginLoader *loader;
    void operator=(PluginLoader const &);
    Provider mapProvider(const QString &);
};

#endif	/* _PLUGINLOADER_H */
