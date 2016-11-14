#include "setting.h"

template<typename T>
Setting<T>::Setting()
{
    valid = false;
    m_Value = QVariant();
}

template<typename T>
Setting<T>::~Setting()
{
    ch = 0;
    delete ch;
}

template<typename T>
Setting<T>::Setting(const Parameter & parameter,
                 T defaultValue)
{
    ch = ConfigHandler::instance();

    m_Parameter = parameter;
    m_Name = SettingsMap[parameter];

    load(defaultValue);
    valid = m_Value.isValid() && ! m_Value.isNull();
}

template<typename T>
T Setting<T>::value()
{
        return m_Value.value<T>();
}

template<typename T>
void Setting<T>::setValue(T value)
{
    valid = false;
    m_Value = value;

    if (m_Value.isValid() && ! m_Value.isNull()) {
        valid = true;
    }
}

template<typename T>
void Setting<T>::setValue(const Parameter & parameter, T value)
{
    m_Parameter = parameter;
    setValue(value);
}

template<typename T>
void Setting<T>::load(T defaultValue)
{
    QVariant v = ch->load(m_Parameter, defaultValue);
    m_Value = v.isValid() && ! v.isNull() ? v : QVariant();
    valid = m_Value.isValid() && ! m_Value.isNull();
}

template<typename T>
void Setting<T>::save()
{
    if (! valid) {
        qDebug() << "Setting not saved, validation failed";
        return;
    }

    ch->save(m_Parameter, m_Value);
}

template<typename T>
void Setting<T>::save(T value)
{
    setValue(value);
    save();
}

template<typename T>
T Setting<T>::operator()()
{
    return m_Value.value<T>();
}

template class Setting<bool>;
template class Setting<int>;
template class Setting<QString>;
