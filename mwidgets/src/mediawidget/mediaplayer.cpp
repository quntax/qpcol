#include "mediaplayer.h"

MediaPlayer::MediaPlayer(fsContainer *parent) :
    VideoPlayer(parent)
{
    seekSlider = new SeekSlider(parent);
    connect(this, SIGNAL(finished()),
            SIGNAL(stopped()));
}

void MediaPlayer::play()
{
    VideoPlayer::play();
    seekSlider->setMediaObject(mediaObject());
    emit started();
}

void MediaPlayer::stop()
{
    VideoPlayer::stop();
    emit stopped();
}

bool MediaPlayer::isMuted()
{
    return (volume() == 0);
}
