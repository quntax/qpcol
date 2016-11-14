#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QtGui>
#include <QtCore>
#include <QWidget>

#include <phonon4qt5/phonon/VideoPlayer>
#include <phonon4qt5/phonon/SeekSlider>
#include <phonon4qt5/phonon/MediaSource>

#include <FlatStyle>

using namespace Phonon;

class MediaPlayer : public VideoPlayer
{
    friend class MediaWidget;

    Q_OBJECT
public:
    explicit MediaPlayer(fsContainer *parent = 0);

    bool isMuted();

signals:
    void started();
    void stopped();

public slots:
    void play();
    void stop();

private:
    SeekSlider * seekSlider;
    MediaSource mediaSource;
};

#endif // MEDIAPLAYER_H
