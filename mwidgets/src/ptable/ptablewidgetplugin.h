#ifndef PTABLEWIDGETPLUGIN_H
#define PTABLEWIDGETPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include "ptablewidget.h"

class PTableWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    PTableWidgetPlugin(QObject *parent = 0);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

private:
    bool m_initialized;
};

#endif // PTABLEWIDGETPLUGIN_H
