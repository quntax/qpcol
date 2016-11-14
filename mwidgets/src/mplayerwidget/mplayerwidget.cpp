#include "mplayerwidget.h"

/*******************************************************************************
 * CONSTRUCTORS, DESTRUCTOR
 ******************************************************************************/

MplayerWidget::MplayerWidget(QWidget *parent) :
        QWidget(parent)
{
    initConnections();
    initWidget();
    initPlayer();
}

MplayerWidget::MplayerWidget(const QString & source, QWidget *parent) :
    QWidget(parent)
{
    initConnections();
    initWidget();
    initPlayer();
    setMedia(source);
}

MplayerWidget::~MplayerWidget()
{
    destroyPlayer();
}

/*******************************************************************************
 * PUBLIC METHODS
 ******************************************************************************/

void MplayerWidget::setMedia(const QString &source)
{
    mediaFile = source;
    mplayer->setMedia(source);
    mediaInfo->alignText(source);
}

void MplayerWidget::setMedia(const QString & source, const QFont & font)
{
    mediaInfo->setFont(font);
    setMedia(source);
}

/*
QSize MplayerWidget::sizeHint() const
{
    return QSize(640, 360);
}
*/
/*******************************************************************************
 * PUBLIC SLOTS
 ******************************************************************************/

void MplayerWidget::play()
{
    if (mplayer->state() == QProcess::Running) {
        stop(false);
        mplayer->start();
    }

    mplayerContainer->show();
    mplayer->start();

    emit started();
}

void MplayerWidget::pause()
{
    buttonPause->setChecked(true);
}

void MplayerWidget::resume()
{
    buttonPause->setChecked(false);
}

void MplayerWidget::stop(bool intended)
{
    if (mplayer->state() == QProcess::NotRunning) {
        return;
    }

    windowed();

    mplayer->blockSignals(true);
    destroyPlayer();
    initPlayer();
    mplayer->setMedia(mediaFile);

    if (intended) {
       emit stopped();
    }
}

void MplayerWidget::mute()
{
    buttonMute->setChecked(true);
    buttonMute->setThemeIcon(ThemeIconMuted);
}

void MplayerWidget::unmute()
{
    buttonMute->setChecked(false);
    buttonMute->setThemeIcon(ThemeIconUnmuted);
}

void MplayerWidget::fullscreen()
{
    if (! isFs) {
        layoutIndex = verticalLayout->indexOf(mplayerFrame);
        verticalLayout->removeWidget(mplayerFrame);

        mplayerFrame->setParent(0);
        mplayerFrame->setWindowFlags(
                    mplayerFrame->windowFlags() |
                    Qt::CustomizeWindowHint |
                    Qt::WindowStaysOnTopHint |
                    Qt::WindowMaximizeButtonHint |
                    Qt::WindowCloseButtonHint);
        mplayerFrame->setWindowState(mplayerFrame->windowState() | Qt::WindowFullScreen);
        mplayerFrame->setPalette(black);
        mplayerFrame->show();
        mplayerFrame->setFocus();
        grabKeyboard();

        isFs = true;
    } else {
        windowed();
    }
}

void MplayerWidget::windowed()
{
    if (isFs) {
        mplayerFrame->setWindowState(mplayerFrame->windowState() & ~Qt::WindowFullScreen);
        mplayerFrame->setParent(this);

        verticalLayout->insertWidget(layoutIndex, mplayerFrame);

        mplayerFrame->setPalette(original);
        mplayerFrame->adjustSize();
        mplayerFrame->show();
        mplayerFrame->setFocus();

        releaseKeyboard();

        isFs = false;
    }
}

void MplayerWidget::reset()
{
    destroyPlayer();
    delete mplayerContainer;
    mplayerContainer = new QWidget(this);
    initPlayer();
}

/*******************************************************************************
 * PROTECTED SLOTS
 ******************************************************************************/

void MplayerWidget::setButtonsPlayback()
{
    buttonMute->setEnabled(true);
    buttonPlay->setEnabled(true);
    buttonFullscreen->setEnabled(true);
    buttonPause->setEnabled(true);
    buttonPause->setChecked(false);
    buttonStop->setEnabled(true);
}

void MplayerWidget::setButtonsHold()
{
    buttonMute->setEnabled(false);
    buttonMute->setChecked(false);
    buttonPlay->setDisabled(mplayer->mediaFile.isEmpty());
    buttonFullscreen->setEnabled(false);
    buttonPause->setEnabled(false);
    buttonPause->setChecked(false);
    buttonStop->setEnabled(false);
}

/*******************************************************************************
 * PRIVATE METHODS
 ******************************************************************************/

void MplayerWidget::initWidget()
{
    mplayerFrame = new QFrame(this);
    mplayerFrame->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,
                                            QSizePolicy::MinimumExpanding));

    original = mplayerFrame->palette();
    black.setColor(mplayerFrame->backgroundRole(), Qt::black);

    mediaInfo = new fsLabel(QSizePolicy(QSizePolicy::Expanding,
                                        QSizePolicy::Maximum), this);
    passFocus(mediaInfo);

    buttonsContainer = new fsContainer(QSizePolicy(QSizePolicy::Minimum,
                                                   QSizePolicy::Maximum), this);
    passFocus(buttonsContainer);

    buttonMute = new fsButton(ThemeIconUnmuted, true, buttonsContainer);
    buttonMute->setCheckable(true);
    passFocus(buttonMute);
    connect(buttonMute, SIGNAL(clicked()),
            &dispatcher, SLOT(dispatchMute()));

    buttonFullscreen = new fsButton(ThemeIconFullscreen, true, buttonsContainer);
    passFocus(buttonFullscreen);
    connect(buttonFullscreen, SIGNAL(clicked()),
            this, SLOT(fullscreen()));

    s1 = new fsSeparator(buttonsContainer);

    buttonPlay = new fsButton(ThemeIconPlay, true, buttonsContainer);
    passFocus(buttonPlay);
    connect(buttonPlay, SIGNAL(clicked()),
            this, SLOT(play()));

    buttonPause = new fsButton(ThemeIconPause, true, buttonsContainer);
    buttonPause->setCheckable(true);
    passFocus(buttonPause);
    connect(buttonPause, SIGNAL(clicked()),
            &dispatcher, SLOT(dispatchPause()));

    buttonStop = new fsButton(ThemeIconStop, true, buttonsContainer);
    passFocus(buttonStop);
    connect(buttonStop, SIGNAL(clicked()),
            this, SLOT(stop()));

    mplayerContainer = new QWidget(this);
    installEventFilter(&dispatcher);
}

void MplayerWidget::initPlayer()
{
    if (! layout()) {
        createLayout();
    }

    isFs = false;
    mplayer = new MplayerProcess(mplayerContainer);
    connect(mplayer, SIGNAL(mplayerStarted()),
            this, SLOT(setButtonsPlayback()));
    connect(mplayer, SIGNAL(mplayerStopped()),
            this, SLOT(setButtonsHold()));
    connect(mplayer, SIGNAL(finished(int)),
            this, SIGNAL(processFinished(int)));

    dispatcher.setReceiver(mplayer);
    passFocus(this);
}

void MplayerWidget::initConnections()
{
    connect(&dispatcher, SIGNAL(quit()),
            this, SLOT(stop()));
    connect(&dispatcher, SIGNAL(fullscreen()),
            this, SLOT(fullscreen()));
    connect(&dispatcher, SIGNAL(windowMode()),
            this, SLOT(windowed()));

    // pause/resume
    connect(&dispatcher, SIGNAL(pause()),
            this, SLOT(pause()));
    connect(&dispatcher, SIGNAL(resume()),
            this, SLOT(resume()));

    // mute unmute
    connect(&dispatcher, SIGNAL(mute()),
            this, SLOT(mute()));
    connect(&dispatcher, SIGNAL(unmute()),
            this, SLOT(unmute()));
}

void MplayerWidget::destroyPlayer()
{
    mplayer->blockSignals(true);
    mplayer->close();
    mplayer->kill();
    mplayer->deleteLater();

    clearLayout();
}

void MplayerWidget::createLayout()
{
    mplayerFrame->setFrameShape(QFrame::StyledPanel);
    mplayerFrame->setFrameShadow(QFrame::Plain);
    mplayerFrame->setLineWidth(1);
    mplayerFrame->setMidLineWidth(0);
    mplayerFrame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    mediaInfo->setFrameShape(QFrame::StyledPanel);
    mediaInfo->setFrameShadow(QFrame::Plain);
    mediaInfo->setLineWidth(1);
    mediaInfo->setMidLineWidth(0);

    QSizePolicy p(QSizePolicy::Preferred, QSizePolicy::Preferred);

    p.setHorizontalStretch(0);
    p.setVerticalStretch(0);
    p.setHeightForWidth(true);

    setSizePolicy(p);

    setSizeIncrement(QSize(0, 0));
    setContentsMargins(0, 0, 0, 0);

    QGridLayout * mplayerFrameLayout = new QGridLayout;
    mplayerFrameLayout->addWidget(mplayerContainer);
    mplayerFrame->setLayout(mplayerFrameLayout);

    QHBoxLayout * buttonsLayout = new QHBoxLayout;
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->addWidget(buttonMute);
    buttonsLayout->addWidget(buttonFullscreen);
    buttonsLayout->addWidget(s1);
    buttonsLayout->addWidget(buttonPlay);
    buttonsLayout->addWidget(buttonPause);
    buttonsLayout->addWidget(buttonStop);

    buttonsContainer->setLayout(buttonsLayout);

    QHBoxLayout * horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(mediaInfo);
    horizontalLayout->addWidget(buttonsContainer);

    verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(mplayerFrame);
    verticalLayout->addLayout(horizontalLayout);

    QGridLayout * grid = new QGridLayout;
    grid->addLayout(verticalLayout, 0, 0);
    setLayout(grid);
}

void MplayerWidget::clearLayout()
{
    delete mplayerFrame->layout();
    delete buttonsContainer->layout();
    delete layout();
}

void MplayerWidget::passFocus(QWidget *widget)
{
    widget->setFocusProxy(mplayerFrame);
}
