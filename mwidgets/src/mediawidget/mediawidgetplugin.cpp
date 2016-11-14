#include "mediawidgetplugin.h"

MediaWidgetPlugin::MediaWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void MediaWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MediaWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MediaWidgetPlugin::createWidget(QWidget *parent)
{
    return new MediaWidget(parent);
}

QString MediaWidgetPlugin::name() const
{
    return QLatin1String("MediaWidget");
}

QString MediaWidgetPlugin::group() const
{
    return QLatin1String("Multimedia Widgets");
}

QIcon MediaWidgetPlugin::icon() const
{
    return QIcon();
}

QString MediaWidgetPlugin::toolTip() const
{
    return QLatin1String("Video player compoenent with option to download video files");
}

QString MediaWidgetPlugin::whatsThis() const
{
    return QLatin1String("Embedded phonon video player and downloader, using qhttprequest library");
}

bool MediaWidgetPlugin::isContainer() const
{
    return false;
}

QString MediaWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"MediaWidget\" name=\"mediaWidget\">\n</widget>\n");
}

QString MediaWidgetPlugin::includeFile() const
{
    return QLatin1String("<MediaWidget>");
}

//Q_EXPORT_PLUGIN2(mediawidgetplugin, MediaWidgetPlugin)
