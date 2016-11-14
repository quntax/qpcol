#include "mplayerdispatcher.h"

/*******************************************************************************
 * CONSTRUCTORS, DESTRUCTORS
 ******************************************************************************/

MplayerDispatcher::MplayerDispatcher(QObject *parent) :
    QObject(parent)
{
}

/*******************************************************************************
 * PUBLIC METHODS
 ******************************************************************************/

void MplayerDispatcher::setReceiver(MplayerProcess *playerObject)
{
    mplayer = playerObject;
    connect(mplayer, SIGNAL(reply(QByteArray)),
            this, SLOT(readReply(QByteArray)));
//    connect(mplayer, SIGNAL(received()),
//            this, SLOT(queryPause()));
}

// TODO mouse wheel event
bool MplayerDispatcher::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
        QFlags<Qt::KeyboardModifier> flags(keyEvent->modifiers());

        processKeyEvent(keyEvent, flags.testFlag(Qt::ShiftModifier));

        return true;
    }

    return QObject::eventFilter(object, event);
}

//QSize MplayerDispatcher::getResolution()
//{
//    QRegExp rx(RxResolution);
//    QByteArray resolution = query(Resolution);

//    rx.indexIn(resolution);
//    if (rx.indexIn(resolution) != -1) {
//    }

//    MDEBUG_DISPATCHER "Resolution:" << rx.cap(1) <<"*"<< rx.cap(2);
//    return QSize(rx.cap(1).toInt(), rx.cap(2).toInt());
//}

/*******************************************************************************
 * PUBLIC SLOTS
 ******************************************************************************/

void MplayerDispatcher::dispatchPause()
{
    QRegExp rx(RxPauseStatus);
    QByteArray statusPause= query(PauseStatus);

    if (rx.indexIn(statusPause) != -1) {
        emit (rx.cap(1) == "no" ? pause() : resume());
    }

    request = Pause;
    mplayer->dispatch(QByteArray(Pause));
}

void MplayerDispatcher::dispatchMute()
{
    QRegExp rx(RxMuteStatus);
    QByteArray statusMute = query(MuteStatus);

    if (rx.indexIn(statusMute) != -1) {
        emit (rx.cap(1) == "no" ? mute() : unmute());
    }

    command(Mute);
}

void MplayerDispatcher::seekForward(int seconds)
{
    command(SeekForward, seconds);
}

void MplayerDispatcher::seekReverse(int seconds)
{
    command(SeekReverse, seconds);
}

void MplayerDispatcher::display()
{
    command(Osd);
}

void MplayerDispatcher::volumeUp()
{
    command(VolumeUp, 5);
}

void MplayerDispatcher::volumeDown()
{
    command(VolumeDown, 5);
}

/*******************************************************************************
 * PROTECTED METHODS
 ******************************************************************************/

void MplayerDispatcher::processKeyEvent(QKeyEvent *keyEvent, bool modifier) {
    switch (keyEvent->key()) {
    case Qt::Key_Q:
    case Qt::Key_Escape:
    case Qt::Key_Return:
//        emit windowMode();
        emit quit();
        return;
    case Qt::Key_F:
        emit fullscreen();
        return;
    case Qt::Key_Space:
        dispatchPause();
        break;
    case Qt::Key_M:
        if (modifier) break;
        dispatchMute();
        break;
    case Qt::Key_Right:
        seekForward(10);
        break;
    case Qt::Key_Left:
        seekReverse(10);
        break;
    case Qt::Key_Up:
        seekForward(60);
        break;
    case Qt::Key_Down:
        seekReverse(60);
        break;
    case Qt::Key_PageUp:
        seekForward(600);
        break;
    case Qt::Key_PageDown:
        seekReverse(600);
        break;
    case Qt::Key_O: // oooo, oh letter
        if (modifier) break;
        display();
        break;
    case Qt::Key_0: // digit
        volumeUp();
        emit unmute();
        break;
    case Qt::Key_9:
        volumeDown();
        break;
//    case Qt::Key_O:
//        command(keyEvent, keyEvent->key());
//        break;
    default:
        break;
        //command(KeyEvent, keyEvent->key()); // allow only predefined behaviors
    }
}

void MplayerDispatcher::command(const QString &cmd)
{
    request = cmd;
    mplayer->dispatch(cmd.toLocal8Bit());
    emit resume();
}

void MplayerDispatcher::command(const QString &cmd, int param)
{
    command(cmd.arg(param));
}

void MplayerDispatcher::command(const QString &cmd, int param1, int param2)
{
    command(cmd.arg(param1).arg(param2));
}

QByteArray MplayerDispatcher::query(const QString &query)
{
    QEventLoop loop;
    connect(mplayer, SIGNAL(replied()),
            &loop, SLOT(quit()));

    request = query;
    mplayer->dispatch(query.toLocal8Bit());

    loop.exec();

    return reply;
}

/*******************************************************************************
 * PROTECTED SLOTS
 ******************************************************************************/

void MplayerDispatcher::queryPause()
{ // ????????????????????????????????
//    QRegExp rx(RxPauseStatus);
//    QByteArray statusPause = queryPause(PauseStatus);

//    if (rx.indexIn(statusPause) != -1) {
//        emit rx.cap(1) == "no" ? pause() : resume();
//    }
}

void MplayerDispatcher::readReply(QByteArray replyData)
{
    reply = replyData;
    MDEBUG_DISPATCHER "reply from process:" << reply;
}
