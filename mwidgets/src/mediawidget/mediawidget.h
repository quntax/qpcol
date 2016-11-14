#ifndef MEDIAWIDGET_H
#define MEDIAWIDGET_H

#define INTERNAL_MARGIN 3

#define ICON_EJECT      "media-eject"
#define ICON_PLAY       "media-playback-start"
#define ICON_STOP       "media-playback-stop"
#define ICON_PAUSE      "media-playback-pause"

#define ICON_MUTE       "audio-volume-muted"
#define ICON_VOLUME     "audio-volume-high"

#define ICON_DOWNLOAD   "download"
#define ICON_WGET       "go-jump-definition"

#define TIME_FORMAT     "hh:mm:ss"

#include <Qt>
#include <QtGui>
#include <QtCore>
#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

#include <phonon4qt5/phonon/VideoPlayer>
#include <phonon4qt5/phonon/SeekSlider>
#include <phonon4qt5/phonon/MediaObject>
#include <phonon4qt5/phonon/MediaSource>

#include <FlatStyle>

#include "mediaplayer.h"
#include "downloaddialog.h"

using namespace Phonon;

class QDESIGNER_WIDGET_EXPORT MediaWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit MediaWidget(QWidget *parent = 0);

        MediaPlayer * mediaPlayer() { return player; }

        void setMedia(const QString & url);
        QString getMedia();

        void setDownloadDirectory(const QString & directory);
        QString getDownloadDirectory();

        void setVolume(float volume);
        float getVolume();

        bool isMediaResource();

        QString getMediaTime(QString format = TIME_FORMAT);

    public slots:
        void selectMediaDialog();
        void play();
        void stop();
        void pause();
        void reset();
        void mute();
        void download();
        void downloadWget();

    signals:
        void started();
        void stopped();
        void paused();
        void resumed();
        void loaded();
        void muted();
        void unmuted();
        void downloadStarted(const QString &);
        void downloadCompleted(const QString &);

    protected slots:
        void resetControls();
        void disableControls();

        void startPlayer();
        void stopPlayer();

    private:
        MediaPlayer * player;

        fsContainer * videoFrame;
        fsContainer * sliderFrame;
        fsContainer * buttonFrame;

        fsButton * buttonSelectMedia;
        fsButton * buttonPlay;
        fsButton * buttonStop;
        fsButton * buttonPause;

        fsButton * buttonMute;

        fsButton * buttonDownload;
        fsButton * buttonWget;

        fsSeparator * s1;
        fsSeparator * s2;

        QHBoxLayout * videoLayout;
        QHBoxLayout * buttonsLayout;
        QHBoxLayout * sliderLayout;
        QHBoxLayout * controlsLayout;

        QVBoxLayout * elementsLayout;
        QGridLayout * grid;

        QString downloadDirectory;
        QString mediaResource;

        bool playerMuted;
        float volume;

        void initWidgets();
        void initPlayer();
        void initLayout();
};

#endif // MEDIAWIDGET_H
