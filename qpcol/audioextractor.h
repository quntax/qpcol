#ifndef AUDIOEXTRACTOR_H
#define AUDIOEXTRACTOR_H

#include <QObject>
#include <QProcess>
#include <QDebug>

class AudioExtractor : public QObject
{
        Q_OBJECT
    public:
        explicit AudioExtractor(QObject *parent = 0);
        ~AudioExtractor();

    signals:
        void saved(int);

    public slots:
        void saveAudio(const QString &, const QString &);

    protected:
        QProcess * ffmpegProcess;
};

#endif // AUDIOEXTRACTOR_H
