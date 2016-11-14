#ifndef CONFIGURATIONPARAMETER_H
#define CONFIGURATIONPARAMETER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include "confighandler.h"

template<ConfigHandler::Settings parameter, class T>
class ConfigurationParameter
{
public:
    ConfigurationParameter(const ConfigHandler::Settings &, const T &);
    ~ConfigurationParameter();

    void save(T);
    T load(const T &);

    void setValue(const T &);
    T getValue();

protected:
    ConfigHandler::Settings m_Param;
    T value;
};

#endif // CONFIGURATIONPARAMETER_H
