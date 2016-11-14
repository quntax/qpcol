#ifndef SETTINGSEDITOR_H
#define SETTINGSEDITOR_H

#ifdef USING_PCH
    #include "precompiled.h"
#else
    #include <QtWidgets/QDialog>
    #include <QDebug>
#endif

#include "confighandler.h"
#include "setting.h"

namespace Ui {
    class SettingsEditor;
}

class SettingsEditor : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsEditor(QWidget *parent = 0);
    ~SettingsEditor();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::SettingsEditor *ui;

    SettingBool s_playlistMode;
    SettingBool s_normalizedVolume;
    SettingString s_videoOutput;
    SettingInt s_osdLevel;
};

#endif // SETTINGSEDITOR_H
