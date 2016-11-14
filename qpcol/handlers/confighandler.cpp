#include "confighandler.h"

ConfigHandler * ConfigHandler::handler = 0;

ConfigHandler * ConfigHandler::instance()
{
    if (! handler) {
        handler = new ConfigHandler;
    }

    Q_CHECK_PTR(handler);
    return handler;
}

void ConfigHandler::save(Parameter type, const QVariant &value)
{
    QMutexLocker locker(&mutex);

    settings.setValue(SettingsMap[type], value);
    settings.sync();

    locker.unlock();
}

QVariant ConfigHandler::load(Parameter type, const QVariant &defaultValue)
{
    return settings.value(SettingsMap[type], defaultValue);
}

QVariant ConfigHandler::load(Parameter type, const Parameter &defaultValue)
{
    return settings.value(SettingsMap[type], load(defaultValue));
}

void ConfigHandler::remove(Parameter type)
{
    if (! settings.contains(SettingsMap[type])) {
        return;
    }

    QMutexLocker locker(&mutex);

    settings.remove(SettingsMap[type]);
    settings.sync();

    locker.unlock();
}
