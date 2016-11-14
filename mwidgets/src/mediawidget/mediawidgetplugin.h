#ifndef MEDIAWIDGETPLUGIN_H
#define MEDIAWIDGETPLUGIN_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include <QtPlugin>

#include "mediawidget.h"

class MediaWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit MediaWidgetPlugin(QObject *parent = 0);

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

#endif // MEDIAWIDGETPLUGIN_H
