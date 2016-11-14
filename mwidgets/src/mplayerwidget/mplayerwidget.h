#ifndef MPLAYERWIDGET_H
#define MPLAYERWIDGET_H

#ifndef MWIDGETS_RELEASE
    #define MDEBUG_WIDGET qDebug() << "[MplayerWidget]" <<
#else
    #define MDEBUG_WIDGET // -- Release mode
#endif

#define ThemeIconMuted      "audio-volume-muted"
#define ThemeIconUnmuted    "audio-volume-high"
#define ThemeIconFullscreen "view-fullscreen"
#define ThemeIconPlay       "media-playback-start"
#define ThemeIconPause      "media-playback-pause"
#define ThemeIconStop       "media-playback-stop"
#define ThemeIconBrowse     "inode-directory"

#include <QtGui>
#include <QtCore>
#include <QObject>
#include <QtWidgets>
#include <QtUiPlugin/QDesignerExportWidget>

#include <FlatStyle>

#include "mplayerprocess.h"
#include "mplayerdispatcher.h"

class QDESIGNER_WIDGET_EXPORT MplayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MplayerWidget(QWidget *parent = 0);
    MplayerWidget(const QString &source, QWidget *parent = 0);
    ~MplayerWidget();

    void setMedia(const QString &);
    void setMedia(const QString &, const QFont &);
    QString media() { return mediaFile; }
    bool onFullscreen() { return isFs; }

    MplayerProcess * getMplayerProcess() { return mplayer; }

public slots:
    void play();
    void stop(bool intended = true);
    void pause();
    void resume();
    void fullscreen();
    void windowed();
    void mute();
    void unmute();
    void reset();

signals:
    void started();
    void stopped();
    void processFinished(int);


protected slots:
    void setButtonsPlayback();
    void setButtonsHold();

private:
    QWidget *mplayerContainer;

    MplayerProcess *mplayer;
    MplayerDispatcher dispatcher;

    QFrame *mplayerFrame;
    QVBoxLayout * verticalLayout;

    fsLabel *mediaInfo;

    QSize frameSize;

    fsContainer * buttonsContainer;

    fsSeparator * s1;

    fsButton * buttonMute;
    fsButton * buttonFullscreen;
    fsButton * buttonPlay;
    fsButton * buttonPause;
    fsButton * buttonStop;

    QString mediaFile;

    void initConnections();
    void initWidget();
    void initPlayer();
    void destroyPlayer();

    void createLayout();
    void clearLayout();

    void passFocus(QWidget *);

    QPalette black;
    QPalette original;

    bool isFs;
    int layoutIndex;
};

#endif // MPLAYERWIDGET_H
