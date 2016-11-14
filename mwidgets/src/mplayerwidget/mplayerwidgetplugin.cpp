#include "mplayerwidgetplugin.h"

MplayerWidgetPlugin::MplayerWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void MplayerWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MplayerWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MplayerWidgetPlugin::createWidget(QWidget *parent)
{
    return new MplayerWidget(parent);
}

QString MplayerWidgetPlugin::name() const
{
    return QLatin1String("MplayerWidget");
}

QString MplayerWidgetPlugin::group() const
{
    return QLatin1String("Multimedia Widgets");
}

QIcon MplayerWidgetPlugin::icon() const
{
    return QIcon();
}

QString MplayerWidgetPlugin::toolTip() const
{
    return QLatin1String("Video player with embedded mplayer");
}

QString MplayerWidgetPlugin::whatsThis() const
{
    return QLatin1String("Embedded mplayer");
}

bool MplayerWidgetPlugin::isContainer() const
{
    return false;
}

QString MplayerWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"MplayerWidget\" name=\"mplayerWidget\">\n</widget>\n");
}

QString MplayerWidgetPlugin::includeFile() const
{
    return QLatin1String("<MplayerWidget>");
}

//Q_DECL_INTERFACE(s)
//Q_EXPORT_PLUGIN2(mplayerwidgetplugin, MplayerWidgetPlugin)
