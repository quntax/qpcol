#ifndef MPLAYERDISPATCHER_H
#define MPLAYERDISPATCHER_H

#ifndef MWIDGETS_RELEASE
    #define MDEBUG_DISPATCHER qDebug() << "[MplayerDispatcher]" <<
#else
    #define MDEBUG_DISPATCHER // -- release mode
#endif

#include <QtGui>
#include <QtGlobal>
#include <QtCore>
#include <QObject>
#include <QWidget>

#include "mplayerprocess.h"
#include "mplayerslave.h"

class MplayerDispatcher : public QObject
{
    Q_OBJECT

public:
    explicit MplayerDispatcher(QObject *parent = 0);

    void setReceiver(MplayerProcess *playerObject);
    bool eventFilter(QObject *object, QEvent *event);
    void command(const QString &);
    void command(const QString &, int);
    void command(const QString &, int, int);
    QByteArray query(const QString &);
//    QSize getResolution();

signals:
    void quit();
    void fullscreen();
    void windowMode();
    void pause();
    void resume();
    void mute();
    void unmute();

public slots:
    void dispatchPause();
    void dispatchMute();
    void seekForward(int);
    void seekReverse(int);
    void display();
    void volumeUp();
    void volumeDown();

protected:
    MplayerProcess *mplayer;
    QString request;
    QByteArray reply;

    void processKeyEvent(QKeyEvent *keyEvent, bool modifier);

protected slots:
    void queryPause();
    void readReply(QByteArray replyData);
};

#endif // MPLAYERDISPATCHER_H
