#include "pluginloader.h"

PluginLoader *PluginLoader::loader = 0;

PluginLoader::PluginLoader() {
    currentProvider = 0;

    // todo MACRO checks
//    providerMap.insert("Girlfriendvideos", p_Girlfriendvideos);
//    providerMap.insert("Hotpornshow", p_Hotpornshow);
//    providerMap.insert("Meendo", p_Meendo);
//    providerMap.insert("Moviesand", p_Moviesand);
//    providerMap.insert("Pornhub", p_Pornhub);
//    providerMap.insert("Redtube", p_Redtube);
//    providerMap.insert("Slutload", p_Slutload);
//    providerMap.insert("Stileproject", p_Stileproject);
//    providerMap.insert("Submityourflicks", p_Submityourflicks);
//    providerMap.insert("Tube8", p_Tube8);
//    providerMap.insert("Xflogger", p_Xflogger);
    providerMap.insert("Xhamster", p_Xhamster);
    providerMap.insert("Xvideos", p_Xvideos);
//    providerMap.insert("Youjizz", p_Youjizz);
//    providerMap.insert("Youporn", p_Youporn);
}

PluginLoader * PluginLoader::instance() {
    if (! loader) {
        loader = new PluginLoader();
    }

    return loader;
}

SearchProvider * PluginLoader::provider()
{
    return currentProvider;
}

SearchProvider * PluginLoader::provider(const QString &name)
{
    Provider p = mapProvider(name);

    switch (p) {
//    case p_Girlfriendvideos:
//        currentProvider = new Girlfriendvideos; break;
//    case p_Hotpornshow:
//        currentProvider = new Hotpornshow; break;
//    case p_Meendo:
//        currentProvider = new Meendo; break;
//    case p_Moviesand:
//        currentProvider = new Moviesand; break;
//    case p_Pornhub:
//        currentProvider = new Pornhub; break;
//    case p_Redtube:
//        currentProvider =  new Redtube; break;
//    case p_Slutload:
//        currentProvider = new Slutload; break;
//    case p_Stileproject:
//        currentProvider = new Stileproject; break;
//    case p_Submityourflicks:
//        currentProvider = new Submityourflicks; break;
//    case p_Tube8:
//        currentProvider = new Tube8; break;
//    case p_Xflogger:
//        currentProvider = new Xflogger; break;
    case p_Xhamster:
        currentProvider = new Xhamster; break;
    case p_Xvideos:
        currentProvider = new Xvideos; break;
//    case p_Youjizz:
//        currentProvider = new Youjizz; break;
//    case p_Youporn:
//        currentProvider = new Youporn; break;
    }

    return currentProvider;
}

Provider PluginLoader::mapProvider(const QString &name)
{
    return providerMap.value(name);
}

ProviderMap PluginLoader::map()
{
    return providerMap;
}
