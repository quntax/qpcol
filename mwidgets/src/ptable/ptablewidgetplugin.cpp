#include "ptablewidgetplugin.h"

PTableWidgetPlugin::PTableWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void PTableWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here
    m_initialized = true;
}

bool PTableWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *PTableWidgetPlugin::createWidget(QWidget *parent)
{
    return new PTableWidget(parent);
}

QString PTableWidgetPlugin::name() const
{
    return QLatin1String("PTableWidget");
}

QString PTableWidgetPlugin::group() const
{
    return QLatin1String("Multimedia Widgets");
}

QIcon PTableWidgetPlugin::icon() const
{
    return QIcon();
}

QString PTableWidgetPlugin::toolTip() const
{
    return QLatin1String("QTableWidget with proportionas columns size");
}

QString PTableWidgetPlugin::whatsThis() const
{
    return QLatin1String("QTableWidget replacement");
}

bool PTableWidgetPlugin::isContainer() const
{
    return false;
}

QString PTableWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"PTableWidget\" name=\"PTableWidget\">\n</widget>\n");
}

QString PTableWidgetPlugin::includeFile() const
{
    return QLatin1String("<PTableWidget>");
}

//Q_EXPORT_PLUGIN2(PTableWidgetPlugin, PTableWidgetPlugin)
