#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <QObject>
#include <QString>
#include <QSettings>
#include <QMutexLocker>

#include "options.h"

class ConfigHandler : public QObject
{
    Q_OBJECT

public:
    static ConfigHandler *instance();

    void save(Parameter, const QVariant &);
    QVariant load(Parameter, const QVariant &defaultValue = QVariant());
    QVariant load(Parameter, const Parameter &);
    void remove(Parameter);

private:
    QSettings settings;
    mutable QMutex mutex;

    static ConfigHandler * handler;
    explicit ConfigHandler(QObject *parent = 0) : QObject(parent) {}
    ConfigHandler(const ConfigHandler &) : QObject() {}
};

#endif // CONFIGHANDLER_H
