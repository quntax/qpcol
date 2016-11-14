#include "mplayerprocess.h"


const QStringList MplayerProcess::defaultArguments = QStringList()
                                               << "-slave"
                                               << "-quiet"
                                               << "-fs"
                                               << "-wid";

/*******************************************************************************
 * CONSTRUCTORS, DESTRUCTORS
 ******************************************************************************/

MplayerProcess::MplayerProcess(QWidget *parent) :
    QProcess(parent)
{
//    parentWidth = parent->width();

    windowId = parent->winId();
    connect(this, SIGNAL(readyRead()),
            this, SLOT(readReply()));

    // yup, quick workaround
    emit mplayerStopped();
}

MplayerProcess::~MplayerProcess()
{
    emit mplayerStopped();
}

/*******************************************************************************
 * PUBLIC METHODS
 ******************************************************************************/

void MplayerProcess::start()
{
    if (state() == QProcess::Running) {
        return;
    }

    QFileInfo fi(mediaFile);

    if (mediaFile.isEmpty() || ! fi.isReadable()) {
        emit mediaFailure();
        return;
    }

    QProcess::start(executable, callArguments);
    waitForStarted();

    emit mplayerStarted();

    MDEBUG_PROCESS "command line:" << QString("%1 %2").arg(executable).arg(callArguments.join(" "));
}

void MplayerProcess::stop()
{
    stop();
    emit mplayerStopped();
}

void MplayerProcess::dispatch(QByteArray command)
{
    MDEBUG_PROCESS "dispatching request:" << command;
    write(command + '\n');
    waitForBytesWritten();

    emit received();
}

QStringList MplayerProcess::arg(MplayerProcess::MPlayerOptions option)
{
    QStringList strOpt;

    switch (option) {
        case VideoOutput:
            strOpt << "-vo";
            break;
        case VideoFilter:
            strOpt << "-vf";
            break;
        case AudioFilter:
            strOpt << "-af";
            break;
        case Loop:
            strOpt << "-loop";
            break;
        case FullScreen:
            strOpt << "-fs";
            break;
        case OsdLevel:
            strOpt << "-osdlevel";
            break;
    }

    userArguments.append(strOpt);
    return userArguments;
}

QStringList MplayerProcess::arg(MplayerProcess::MPlayerOptions option, QString & value)
{
    QStringList strOpt = arg(option);
    strOpt << value;

    userArguments.append(strOpt);
    return userArguments;
}

QStringList MplayerProcess::arg(MplayerProcess::MPlayerOptions option, Vo::VideoOutput vo)
{
    QStringList strOpt = arg(option);
    QString strVo;

    switch (vo) {
        case Vo::Xv:
            strVo = "xv";
            break;
        case Vo::X11:
            strVo = "x11";
            break;
        case Vo::Vaapi:
            strVo = "vaapi";
            break;
        case Vo::Gl:
            strVo = "gl";
            break;
        case Vo::Gl_nosw:
            strVo = "gl_nosw";
            break;
    case Vo::Xover:
        strVo = "xover";
        break;

    }

    strOpt << strVo;
    userArguments.append(strOpt);
    return userArguments;
}

QStringList MplayerProcess::arg(MplayerProcess::MPlayerOptions option, Vf::VideoFilter vf)
{
    QStringList strOpt = arg(option);
    QString strVf;

    switch (vf) {
        case Vf::Vaapi:
            strVf = "vaapi";
            break;
    }

    strOpt << strVf;
    userArguments.append(strOpt);
    return userArguments;
}

QStringList MplayerProcess::arg(MplayerProcess::MPlayerOptions option, Af::AudioFilter af)
{
    QStringList strOpt = arg(option);
    QString strAf;

    switch (af) {
    case Af::NormalizeVolume:
        strAf = "volnorm=1:-10,volume=1:4";
        break;
    }

    strOpt << strAf;
    userArguments.append(strOpt);
    return userArguments;
}

void MplayerProcess::setMedia(const QString &file)
{
    mediaFile = file;
    executable = QString("mplayer");
    callArguments.clear();
    callArguments << userArguments
                  << defaultArguments
                  << QString::number(windowId)
                  << mediaFile;

    MDEBUG_PROCESS callArguments;

    emit mplayerStopped();
}

/*******************************************************************************
 * PROTECTED SLOTS
 ******************************************************************************/

void MplayerProcess::readReply()
{
    QByteArray replyData = readAll();
    emit reply(replyData);
    emit replied();
}
