#include "mwidgetsplugin.h"

MWidgetsPlugin::MWidgetsPlugin(QObject *parent)
    : QObject(parent)
{
#if defined(MEDIAWIDGET)
    widgets.append(new MediaWidgetPlugin(this));
#endif
#if defined(MPLAYERWIDGET)
    widgets.append(new MplayerWidgetPlugin(this));
#endif
#if defined(PTABLE)
    widgets.append(new PTableWidgetPlugin(this));
    widgets.append(new PTableViewPlugin(this));
#endif
}

MWidgetsPlugin::~MWidgetsPlugin()
{

}

QList<QDesignerCustomWidgetInterface*> MWidgetsPlugin::customWidgets() const
{
    return widgets;
}
