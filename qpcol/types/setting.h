#ifndef SETTING_H
#define SETTING_H

#ifdef USING_PCH
    #include "precompiled.h"
#else
    #include <QObject>
    #include <QDebug>
#endif

#include "confighandler.h"
#include "options.h"

template<typename T>
class Setting
{
public:
    Setting();
    Setting(const Parameter &,
            T defaultValue = T());
    ~Setting();

    T value();
    void setValue(T);
    void setValue(const Parameter &, T);
    void load(T defaultValue = T());
    void save();
    void save(T);

    T operator()();

signals:
    void saved(Parameter);

protected:
    Parameter m_Parameter;
    QString m_Name;
    QVariant m_Value;
    bool valid;

    ConfigHandler * ch;
};

typedef Setting<bool> SettingBool;
typedef Setting<QString> SettingString;
typedef Setting<int> SettingInt;


//typedef QList<(SettingSettings;

#endif // SETTING_H
