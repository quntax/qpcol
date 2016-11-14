#include "settingseditor.h"
#include "ui_settingseditor.h"

SettingsEditor::SettingsEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsEditor)
{
    ui->setupUi(this);

    // general settings
    s_playlistMode = PlaylistMode;
    s_videoOutput = MplayerVideoOutput;
    s_osdLevel = MplayerOsdLevel;
    s_normalizedVolume = NormalizedAudioVolume;

//    ui->checkboxPlaylistMode->setChecked(playlistMode.value().toBool());
//    ui->checkboxPlaylistMode->setChecked(b_playlistMode());

//    SettingBool b_playlistMode(PlaylistMode);
    ui->checkboxPlaylistMode->setChecked(s_playlistMode());

    // mplayer settings
    ui->valueVo->setCurrentText(s_videoOutput());
    ui->valueOsd->setCurrentIndex(s_osdLevel());
    ui->checkboxNormalizedVolume->setChecked(s_normalizedVolume());
}

SettingsEditor::~SettingsEditor()
{
    delete ui;
}

void SettingsEditor::on_buttonBox_accepted()
{
    QStringList params;
    ConfigHandler * ch = ConfigHandler::instance();

    if (ui->valueVo->currentText() != tr("<Default>")) {
        params << "-vo" << ui->valueVo->currentText();
        ch->save(MplayerVideoOutput, QVariant(ui->valueVo->currentText()));
    } else {
        ch->remove(MplayerVideoOutput);
    }

    params << "-osdlevel" << ui->valueOsd->currentText();
    ch->save(MplayerOsdLevel, QVariant(ui->valueOsd->currentIndex()));

    s_playlistMode.save(ui->checkboxPlaylistMode->isChecked());
    s_normalizedVolume.save(ui->checkboxNormalizedVolume->isChecked());

    qDebug() << "Saved changes" << params;
}

void SettingsEditor::on_buttonBox_rejected()
{
    qDebug() << "Changes discarded";
    close();
}
