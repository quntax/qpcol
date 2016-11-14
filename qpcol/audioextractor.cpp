#include "audioextractor.h"

AudioExtractor::AudioExtractor(QObject *parent) : QObject(parent)
{
    ffmpegProcess = new QProcess(parent);
    connect(ffmpegProcess, SIGNAL(finished(int)),
            this, SIGNAL(saved(int)));
}

AudioExtractor::~AudioExtractor()
{
    qDebug() << "Saved";
}

void AudioExtractor::saveAudio(const QString & input, const QString & output)
{

    QStringList arguments;
    arguments << "-i" << input << "-y" << output;
    ffmpegProcess->start("ffmpeg", arguments);

    qDebug() << "Saving audio to" << output;

    ffmpegProcess->waitForStarted();
}

