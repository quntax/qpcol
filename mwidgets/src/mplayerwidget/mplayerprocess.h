#ifndef MPLAYERPROCESS_H
#define MPLAYERPROCESS_H
#ifndef MWIDGETS_RELEASE
    #define MDEBUG_PROCESS qDebug() << "[MplayerProcess]" <<
#else
    #define MDEBUG_PROCESS // -- release mode
#endif

#include <QtCore>
#include <QtGui>
#include <QObject>
#include <QWidget>

#include "mplayerparams.h"

class MplayerProcess : public QProcess
{
    Q_OBJECT

    friend class MplayerWidget;

public:
    /**
     * This enum contains mplayer options that can be customized by user.
     * For obvious reasons, options like -wid, -slave, -quiet or <mediaFile>
     * will always be passed to mplayer
     *
     * @brief The MPlayerOptions enum
     */
    enum MPlayerOptions {
        VideoOutput,
        VideoFilter,
        AudioFilter,
        Loop,
        FullScreen,
        OsdLevel
    };

    Q_ENUMS(MPlayerOptions)

    explicit MplayerProcess(QWidget *parent = 0);
    ~MplayerProcess();

    void setMedia(const QString &file);
    QStringList getDefaultArgs() { return defaultArguments; } const
    QStringList getUserArgs() { return userArguments; }
    void clearArgs() { userArguments.clear(); }
    void setArgs(QStringList & args) { userArguments = args; }
    void addArg(MPlayerOptions option) { userArguments << arg(option); }
    void addArg(MPlayerOptions option, QString & value) { userArguments.append(arg(option, value)); }
    void addArg(MPlayerOptions option, Vo::VideoOutput vo) { userArguments.append(arg(option, vo)); }
    void addArg(MPlayerOptions option, Vf::VideoFilter vf) { userArguments.append(arg(option, vf)); }
    void addArg(MPlayerOptions option, Af::AudioFilter af) { userArguments.append(arg(option, af)); }

    void start();
    void stop();
    void dispatch(QByteArray);

public slots:

signals:
    void mplayerStarted();
    void mplayerStopped();
    void mediaFailure();

    void received();
    void reply(QByteArray);
    void replied();

protected:
    QStringList arg(MPlayerOptions);
    QStringList arg(MPlayerOptions, QString &);
    QStringList arg(MPlayerOptions, Vo::VideoOutput);
    QStringList arg(MPlayerOptions, Vf::VideoFilter);
    QStringList arg(MPlayerOptions, Af::AudioFilter);

    QString mediaFile;
    QString executable;

    static const QStringList defaultArguments;
    QStringList userArguments;
    QStringList callArguments;


    QByteArray message;
    WId windowId;
//    int parentWidth;

protected slots:
    void readReply();

};

#endif // MPLAYERPROCESS_H
