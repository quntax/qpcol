#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>
#include <QtPlugin>

#if defined(MEDIAWIDGET)
    #include "mediawidgetplugin.h"
#endif

#if defined(MPLAYERWIDGET)
    #include "mplayerwidgetplugin.h"
#endif

#if defined(PTABLE)
    #include "ptablewidgetplugin.h"
    #include "ptableviewplugin.h"
#endif

class MWidgetsPlugin
    : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.eu.merlin.MWidgetsPlugin")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    MWidgetsPlugin(QObject *parent = 0);
    virtual ~MWidgetsPlugin();

    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const Q_DECL_OVERRIDE;

private:
    QList<QDesignerCustomWidgetInterface*> widgets;
};
