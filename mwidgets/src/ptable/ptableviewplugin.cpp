#include "ptableviewplugin.h"

PTableViewPlugin::PTableViewPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void PTableViewPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here
    m_initialized = true;
}

bool PTableViewPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *PTableViewPlugin::createWidget(QWidget *parent)
{
    return new PTableView(parent);
}

QString PTableViewPlugin::name() const
{
    return QLatin1String("PTableView");
}

QString PTableViewPlugin::group() const
{
    return QLatin1String("Multimedia Widgets");
}

QIcon PTableViewPlugin::icon() const
{
    return QIcon();
}

QString PTableViewPlugin::toolTip() const
{
    return QLatin1String("QTableView with proportionas columns size");
}

QString PTableViewPlugin::whatsThis() const
{
    return QLatin1String("QTableView replacement");
}

bool PTableViewPlugin::isContainer() const
{
    return false;
}

QString PTableViewPlugin::domXml() const
{
    return QLatin1String("<widget class=\"PTableView\" name=\"PTableView\">\n</widget>\n");
}

QString PTableViewPlugin::includeFile() const
{
    return QLatin1String("<PTableView>");
}

//Q_EXPORT_PLUGIN2(PTableViewPlugin, PTableViewPlugin)
