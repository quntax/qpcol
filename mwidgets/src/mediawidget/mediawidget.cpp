#include "mediawidget.h"

MediaWidget::MediaWidget(QWidget *parent) :
    QWidget(parent)
{
    player = 0;
    playerMuted = false;

    initWidgets();
    initPlayer();

    volume = player->volume();
}

void MediaWidget::initWidgets()
{
    // WIDGETS
    videoFrame = new fsContainer(QSizePolicy(QSizePolicy::Expanding,
                                             QSizePolicy::Expanding), this);
    sliderFrame = new fsContainer(QSizePolicy(QSizePolicy::Expanding,
                                              QSizePolicy::Minimum), this);
    buttonFrame = new fsContainer(QSizePolicy(QSizePolicy::Minimum,
                                              QSizePolicy::Minimum), this);

    buttonSelectMedia = new fsButton(ICON_EJECT, true, buttonFrame);
    buttonPlay = new fsButton(QString(ICON_PLAY), true, buttonFrame);
    buttonStop = new fsButton(QString(ICON_STOP), true, buttonFrame);
    buttonPause = new fsButton(QString(ICON_PAUSE), true, buttonFrame);
    buttonPause->setCheckable(true);

    buttonMute = new fsButton(QString(ICON_VOLUME), buttonFrame);
    buttonMute->setCheckable(true);

    buttonDownload = new fsButton(QString(ICON_DOWNLOAD), true, buttonFrame);
    buttonWget = new fsButton(QString(ICON_WGET), true, buttonFrame);

    s1 = new fsSeparator(buttonFrame);
    s2 = new fsSeparator(buttonFrame);

    // SIGNALS & SLOTS CONNECTIONS
    connect(buttonSelectMedia, SIGNAL(clicked()),
            this, SLOT(selectMediaDialog()));
    connect(buttonPlay, SIGNAL(clicked()),
            this, SLOT(play()));
    connect(buttonStop, SIGNAL(clicked()),
            this, SLOT(stop()));
    connect(buttonPause, SIGNAL(clicked()),
            this, SLOT(pause()));
    connect(buttonDownload, SIGNAL(clicked()),
            this, SLOT(download()));
    connect(buttonWget, SIGNAL(clicked()),
            this, SLOT(downloadWget()));
    connect(buttonMute, SIGNAL(clicked()),
            this, SLOT(mute()));
    connect(this, SIGNAL(loaded()),
            this, SLOT(resetControls()));

    // LAYOUT
    buttonsLayout = new QHBoxLayout;
    buttonsLayout->setSpacing(1);
    buttonsLayout->addWidget(buttonWget);
    buttonsLayout->addWidget(buttonDownload);
    buttonsLayout->addWidget(s1);
    buttonsLayout->addWidget(buttonMute);
    buttonsLayout->addWidget(s2);
    buttonsLayout->addWidget(buttonSelectMedia);
    buttonsLayout->addWidget(buttonPlay);
    buttonsLayout->addWidget(buttonPause);
    buttonsLayout->addWidget(buttonStop);
    buttonsLayout->setContentsMargins(0, 0, INTERNAL_MARGIN, 0);
    buttonFrame->setLayout(buttonsLayout);

    controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(sliderFrame);
    controlsLayout->addSpacing(5);
    controlsLayout->addWidget(buttonFrame);
    controlsLayout->setContentsMargins(0, 0, 0, 0);

    grid = new QGridLayout;
    grid->addWidget(videoFrame, 0, 0);
    grid->addLayout(controlsLayout, 1, 0);
    grid->setContentsMargins(1, 1, 1, 1);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setLayout(grid);
    setMinimumSize(QSize(300, 200));

    disableControls();
}

void MediaWidget::initPlayer()
{
    if (player) {
        delete videoFrame->layout();
        delete sliderFrame->layout();
    }

    player = new MediaPlayer(videoFrame);
    player->seekSlider->setParent(sliderFrame);
    connect(player, SIGNAL(started()),
            this, SLOT(startPlayer()));
    connect(player, SIGNAL(stopped()),
            this, SLOT(stopPlayer()));

    videoLayout = new QHBoxLayout;
    videoLayout->addWidget(player);
    videoLayout->setContentsMargins(INTERNAL_MARGIN, INTERNAL_MARGIN, INTERNAL_MARGIN, INTERNAL_MARGIN);
    videoFrame->setLayout(videoLayout);

    sliderLayout = new QHBoxLayout;
    sliderLayout->addWidget(player->seekSlider);
    sliderLayout->setContentsMargins(INTERNAL_MARGIN, 0, 0, 0);
    sliderFrame->setLayout(sliderLayout);

    player->show();
}

void MediaWidget::startPlayer()
{
    if (! player) {
        return;
    }

    buttonStop->setEnabled(true);
    buttonPause->setEnabled(true);
    buttonPause->setChecked(false);

    emit started();
}

void MediaWidget::stopPlayer()
{
    connect(player, SIGNAL(destroyed()),
            this, SLOT(reset()));

    player->seekSlider->deleteLater();
    player->deleteLater();
}

void MediaWidget::pause()
{
    if (! player) {
        return;
    }

    if (player->isPaused()) {
        player->play();
        buttonPause->setChecked(false);
        emit resumed();
    } else {
        player->pause();
        buttonPause->setChecked(true);
        emit paused();
    }
}

void MediaWidget::resetControls()
{
    buttonPlay->setEnabled(isMediaResource());

    buttonStop->setEnabled(false);

    buttonPause->setChecked(false);
    buttonPause->setEnabled(false);

    buttonMute->setEnabled(true);
    buttonMute->setChecked(playerMuted);

    buttonDownload->setEnabled(isMediaResource());
    buttonWget->setEnabled(isMediaResource());
}

void MediaWidget::disableControls()
{
    buttonSelectMedia->setEnabled(true);

    buttonPlay->setEnabled(false);

    buttonStop->setEnabled(false);

    buttonPause->setChecked(false);
    buttonPause->setEnabled(false);

    buttonMute->setChecked(false);
    buttonMute->setEnabled(false);

    buttonDownload->setEnabled(false);
    buttonWget->setEnabled(false);
}

void MediaWidget::setMedia(const QString &url)
{
    if (! player) {
        return;
    }

    mediaResource = url;
    player->load(QUrl(mediaResource));
    player->stop();
}

void MediaWidget::reset()
{
    initPlayer();

    player->load(QUrl(mediaResource));
    emit stopped();
    emit loaded();
}

void MediaWidget::download()
{
    if (downloadDirectory.isEmpty()) {
        downloadDirectory = QDir::homePath();
    }

    DownloadDialog * d = new DownloadDialog;
    connect(d, SIGNAL(downloadCompleted(QString)),
            this, SIGNAL(downloadCompleted(QString)));
    d->download(mediaResource, downloadDirectory);

    emit downloadStarted(mediaResource);
}

void MediaWidget::play()
{
    if (! player) {
        return;
    }

    player->play();
}

void MediaWidget::stop()
{
    if (! player) {
        return;
    }

    player->stop();
}

void MediaWidget::mute()
{
    if (! player) {
        return;
    }

    Q_CHECK_PTR(player);

    if (playerMuted) {
        player->setVolume(volume);

        buttonMute->setChecked(false);
        buttonMute->setThemeIcon(QString(ICON_VOLUME));

        playerMuted = false;
        emit unmuted();
    } else {
        volume = player->volume();
        player->setVolume(0);

        buttonMute->setChecked(true);
        buttonMute->setThemeIcon(QString(ICON_MUTE));

        playerMuted = true;
        emit muted();
    }
}

bool MediaWidget::isMediaResource()
{
    return ! mediaResource.isEmpty();
}

QString MediaWidget::getMediaTime(QString format)
{
    int totalTimeMs = player->totalTime();
    QTime zero(0, 0, 0,0 );

    return zero.addMSecs(totalTimeMs).toString(format);
}

void MediaWidget::selectMediaDialog()
{
    bool ok;
    QString userMedia = QInputDialog::getText(this, tr("Open media"),
                                              tr("Local or remote media"),
                                              QLineEdit::Normal,
                                              QDir::home().dirName(), &ok);


    if (ok && QUrl::fromUserInput(userMedia).isValid()) {
        setMedia(userMedia);
    }
}

QString MediaWidget::getMedia()
{
    return mediaResource;
}

void MediaWidget::setDownloadDirectory(const QString &directory)
{
    downloadDirectory = directory;
}

QString MediaWidget::getDownloadDirectory()
{
    return downloadDirectory;
}

void MediaWidget::downloadWget() {
    QString program = "konsole";
    QStringList arguments;

    if (downloadDirectory.isEmpty()) {
        downloadDirectory = QDir::homePath();
    }

    arguments
            << "--workdir"
            << downloadDirectory
            << "--separate"
            << "--new-tab"
            << "-e"
            << "wget"
            << mediaResource;

    QProcess *wgetProcess = new QProcess();
    wgetProcess->setWorkingDirectory(downloadDirectory);
    wgetProcess->startDetached(program, arguments);

    qDebug() << QString("process detached:\n%1 %2").arg(program).arg(arguments.join(" "));

    emit downloadStarted(mediaResource);
}
