#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    qDebug() << HANDLED_FORMATS;
//    qDebug() << QPC_MEDIA_EXTLIST;

    te = 0;
    fud = 0;
    mse = 0;
    videoModel = 0;
    videoTags = 0;
    playbackOffset = "00:00:00";
    playbackEndpos = "23:59:59";

    QString downloadDir = ConfigHandler::instance()
                          ->load(DownloadDirectory,
                                 QStandardPaths::HomeLocation).toString();

    addAction(ui->actionReset);
    addAction(ui->actionActionGoToTags);
    addAction(ui->actionTabBrowser);
    addAction(ui->actionTabPlayer);
    addAction(ui->actionFilterFavorites);
    addAction(ui->actionFilterUntagged);
    addAction(ui->actionGoToUsedTags);
    addAction(ui->actionGoToSearch);
    addAction(ui->actionClearSearchCriteria);

    bool captureLinks = ConfigHandler::instance()
                        ->load(CaptureClipboard).toBool();
    ui->actionClipboardCapture->setChecked(captureLinks);
    clipMonitor.set(captureLinks);

    initConnections();

    ui->statusBar->setFocusProxy(& originalVideoUrlLabel);
    ui->tabBrowser->setFocusProxy(ui->videos);
    ui->tabPlayer->setFocusProxy(ui->mplayerWidget);
    ui->mplayerWidget->reset();

    initTagModel();
    initVideoModel();
    loadVideoModel();

    goToBrowser();
    ui->videos->selectRow(0);
    ui->tabBrowser->setFocus();
}

MainWindow::~MainWindow()
{;
    Connection::instance()->close();
    delete ui;
}

void MainWindow::setOptions(const CmdLineOptions & cmdLineOptions)
{
    options = cmdLineOptions;
//    qDebug() << cmdLineOptions;

    if (options.value("hashlist") == "1") {
        VideoModelHandler vmh;
        FilmTagCollection ftc = vmh.getFilms();

        QListIterator<FilmTag> it(ftc);
        while (it.hasNext()) {
            FilmTag ft = it.next();
            FilmHandler fh;
            Film f = fh.getFilmById(ft.id_film);


            qDebug() << QString("qpcol://%1: %2").arg(QString(f.fileHash())).arg(QString(f.filePath()));
        }

        close();
        exit(0);
        return;
    }

    if (options.contains("uri")) {
        QString uri = options.value("uri");
        FilmHandler fh;
        QRegExp rx("^qpcol://(\\w+)$");

        if (rx.indexIn(uri, 0) == -1) {
            QPCOL_MDEBUG("Hash not extracted from url");
            return;
        }

        QString hash = rx.cap(1);
        Film f = fh.getFilmByHash(hash);
        QPCOL_MDEBUG("Playing uri" << uri << "(hash" << hash <<") path:" << f.filePath());
        play(QFile(f.filePath()));
    }

    if (options.contains("file")) {
        QString file = options.value("file");

        QPCOL_MDEBUG("Playing file" << file);
        play(QFile(file));
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    delete te;
    e->accept();
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void MainWindow::initVideoModel()
{
    VideoModelHandler vmh;
    FilmTagCollection fc = vmh.getFilms();
    sourceVideoModel = new VideoModel(fc);

    if (videoModel == 0) {
        videoModel = new VideoFilterProxyModel();
    }
}

void MainWindow::initTagModel()
{
    TagModelHandler tmh;
    TagCollection tc = tmh.getTags();
    tagModel = new TagModel(tc);

    ui->availableFilterTags->setModel(tagModel);
    ui->availableFilterTags->setModelColumn(Tag::Name);
}

void MainWindow::enableEditorControls(bool enable)
{
    ui->buttonSaveNotesChanges->setEnabled(enable);
}

void MainWindow::loadVideoModel()
{
    videoModel->setFavoritesFilter(ui->favorites->isChecked());
    videoModel->setUntaggedFilter(ui->untagged->isChecked());
    videoModel->setFilterTagList(tagFilter);
    videoModel->setTextFilter(ui->search->text());

    videoModel->setSourceModel(sourceVideoModel);
    videoModel->setDynamicSortFilter(true);

    ui->videos->setModel(videoModel);

    ui->statusBar->showMessage(QString(tr("%1 videos loaded")).arg(videoModel->rowCount()), DEFAULT_MESSAGE_TIMEOUT);


    bool isReadOnly = sourceVideoModel->isReadOnly();

    ui->actionDelete->setDisabled(isReadOnly);
    ui->actionEditOriginalUrl->setDisabled(isReadOnly);
    ui->actionManageTags->setDisabled(isReadOnly);
    ui->actionMarkFavorite->setDisabled(isReadOnly);
    ui->actionInteresting->setDisabled(isReadOnly);
    ui->actionDelete->setDisabled(isReadOnly);
    ui->filmNotes->setDisabled(isReadOnly);
}

void MainWindow::refreshTagModel()
{
    delete tagModel;
    initTagModel();
}

void MainWindow::refreshTagFilters(Tag updatedTag)
{
    qDebug() << "Reloaded tag: " << updatedTag;

    if (tagFilter.isEmpty() || ! tagFilter.contains(updatedTag)) {
        return;
    }

    int i = 0;
    Tag tag;
    QListIterator<Tag> iterator(tagFilter);
    QString oldName;

    while (iterator.hasNext()) {
        tag = iterator.next();

        if (tag.id() == updatedTag.id()) {
            oldName = tag.name();
            tagFilter.replace(i, updatedTag);
            qDebug() << "Replaced tagfilter tag:" << tag << " at index " << i << " with " << updatedTag;
            break;
        }

        i++;
    }

    QListWidgetItem * oldItem = ui->filterTags->item(i);

    if (! oldItem) {
        return;
    }

    qDebug() << "Removing : " << oldName <<  " id  "<< oldItem->text();

    tagRowMap.remove(tag.id());
    tagRowMap.insert(updatedTag.id(), i);

    ui->filterTags->item(i)->setText(updatedTag.name());
}

void MainWindow::refreshVideoTagsModel()
{
//    int filmId = videoModel->index(ui->videos->currentIndex().row(), FilmTag::IdFilm).data().toInt();
    if (videoTags) {
        delete videoTags;
    }

    videoTags = new VideoTagsModel(currentVideoId);
    ui->currentFilmTagsTable->setModel(videoTags);
}

void MainWindow::setCurrentVideo(QModelIndex index)
{
    Q_CHECK_PTR(videoModel);

    currentVideo = videoModel->index(index.row(), FilmTag::FilePath).data().toString();
//    currentVideoId = videoModel->index(index.row(), FilmTag::IdFilm).data().toInt();
    currentVideoId = currentVideoData(FilmTag::IdFilm).toInt();

    HashHandler hh(currentVideo);
    currentVideoHash = hh.hash();
}

void MainWindow::refreshVideoModel()
{
    Q_CHECK_PTR(ui->videos);

    QModelIndex currentIndex = ui->videos->currentIndex();

//    int idFilm = videoModel->index(currentIndex.row(), FilmTag::IdFilm).data().toInt();
    int row = currentIndex.row();

//    delete videoModel;

    initVideoModel();
    loadVideoModel();

    ui->videos->selectRow(row);
}

void MainWindow::playSelected()
{
    QModelIndex index = ui->videos->currentIndex();
    playSelected(index);
}

void MainWindow::playSelected(QModelIndex index)
{
    if (! index.isValid()) {
        return;
    }

    setCurrentVideo(index);
    refreshVideoTagsModel();
    setFilmNotes(currentVideoId);

    QFileInfo fi(currentVideo);
    if (! fi.isReadable()) {
        QString message(tr("%1 is unreadable").arg(currentVideo));
        ui->statusBar->showMessage(message, DEFAULT_MESSAGE_TIMEOUT);
        return;
    }

    bool isFavorite = videoModel->index(index.row(), FilmTag::Favorite).data().toBool();
    QFont font;
    font.setBold(isFavorite);

    QStringList mplayerParams;

    SettingBool s_playlistMode(PlaylistMode);
    SettingBool ms_NormalizedVolume(NormalizedAudioVolume);
    SettingString ms_Vo(MplayerVideoOutput);
    SettingInt ms_Osd(MplayerOsdLevel);

    QString loop, osdlevel = QString("%1").arg(ms_Osd());

    if (! s_playlistMode.value()) {
        loop = QString("0");
    } else {
        qDebug() << "Playlist mode is enabled - forcing -loop 1 option passed to mplayer";
        loop = QString("1");
    }

    if (ms_NormalizedVolume.value()) {
        QPCOL_MDEBUG("Normalizing audio volume level");
        mplayerParams << "-af" << "volnorm=1:-8,volume=1:4";
    }

    mplayerParams << "-loop" << loop << "-osdlevel" << osdlevel << "-ss" << playbackOffset << "-endpos" << playbackEndpos;

    if (! ms_Vo().isEmpty()) {
        mplayerParams << "-vo" << ms_Vo();

        if (ms_Vo() == "vaapi") {
            mplayerParams << "-va" << "vaapi";
        }
    }

    ui->statusBar->showMessage(tr("Playing"), DEFAULT_MESSAGE_TIMEOUT);

    QPCOL_MDEBUG("Playing" << QString("qpcol://%1").arg(currentVideoHash));
    QPCOL_MDEBUG("Params" << mplayerParams);

    ui->mplayerWidget->reset();
    ui->mplayerWidget->getMplayerProcess()->setArgs(mplayerParams);

    ui->mplayerWidget->setMedia(currentVideo, font);
    ui->mplayerWidget->play();

    goToPlayer();
}

void MainWindow::play(const QFile & localFile)
{
    FilmTagCollection ftc;
    FilmTag ft;
    ft = localFile.fileName().toLocal8Bit();
    ftc.append(ft);

    sourceVideoModel = new VideoModel(ftc);
//    sourceVideoModel->setReadOnly(true);

    loadVideoModel();
    ui->videos->selectRow(0);

    setCurrentVideo(ui->videos->currentIndex());

    FilmHandler fh;
    Film f = fh.getFilmByHash(currentVideoHash);

    if (f) {
        ftc.clear();
        ft = f;
        ftc.append(ft);

        currentVideoId = f.id();
        sourceVideoModel = new VideoModel(ftc);
        sourceVideoModel->setReadOnly(false);

        refreshTagModel();
        refreshVideoTagsModel();
    } else {
        sourceVideoModel->setReadOnly(true);
    }

    playSelected();
}

void MainWindow::goToBrowser()
{
    favorite(ui->videos->currentIndex());
    ui->tabWidget->setCurrentIndex(0);
    ui->videos->setFocus();
}

void MainWindow::goToTagFilter()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->availableFilterTags->setFocus();
}

void MainWindow::goToCurrentFilter()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->filterTags->setFocus();
}

void MainWindow::goToPlayer()
{
    ui->actionDelete->setDisabled(true);
    ui->tabWidget->setCurrentIndex(1);
    ui->mplayerWidget->setFocus();
}

void MainWindow::initConnections()
{
    connect(ui->mplayerWidget, SIGNAL(stopped()),
            this, SLOT(stopped()));
    connect(ui->mplayerWidget, SIGNAL(processFinished(int)),
            this, SLOT(processFinished(int)));

    connect(ui->videos, SIGNAL(favorite(bool)),
            this, SLOT(favorite(bool)));

    connect(ui->currentFilmTagsTable, SIGNAL(mouseIn()),
            this, SLOT(mouseHoverInFilmTags()));
    connect(ui->currentFilmTagsTable, SIGNAL(mouseOut()),
            this, SLOT(mouseHoverOutFilmTags()));

    connect(ui->filmNotes, SIGNAL(mouseIn()),
            this, SLOT(mouseHoverInFilmNotes()));
    connect(ui->filmNotes, SIGNAL(mouseOut()),
            this, SLOT(mouseHoverOutFilmNotes()));

    ui->search->installEventFilter(this);
    ui->filmNotes->installEventFilter(this);
}

void MainWindow::stopped()
{
    Q_CHECK_PTR(ui->mplayerWidget->getMplayerProcess());

    ui->mplayerWidget->getMplayerProcess()->waitForFinished();
    ui->statusBar->showMessage(tr("Stopped"), DEFAULT_MESSAGE_TIMEOUT);

    goToBrowser();
}
// halt and go home?
void MainWindow::goToCurrentTab()
{
//    delete te;
    te = 0;

    return; // potem zmienię nazwę
    int currentTabIndex = ui->tabWidget->currentIndex();

    activateWindow();
    raise();

    switch (currentTabIndex) {
    case 0:
        ui->videos->focusWidget()->activateWindow();
        ui->videos->focusWidget()->raise();
        break;
    case 1:
        goToPlayer();
        break;
    default:
        goToBrowser();
        break;
    }
}

void MainWindow::addToFilter()
{
    if (! ui->availableFilterTags->currentIndex().isValid()) {
        return;
    }

    QModelIndex current, prev, next;

    current = ui->availableFilterTags->currentIndex();

    int row = current.row();
    prev = current.sibling(row-1, current.column());
    next = current.sibling(row+1, current.column());

    int tagId = tagModel->index(row, Tag::IdTag).data().toInt();
    ui->availableFilterTags->setRowHidden(row, true);

    TagHandler th(Connection::instance()->get());
    Tag tag = th.getTagById(tagId);

    if (tagFilter.contains(tag)) {
        return;
    }

    tagFilter.append(tag);
    tagRowMap.insert(tagId, row);
    qDebug() << "Added:" << tag;

    ui->filterTags->addItem(tag.name());
//    refreshVideoModel();
    videoModel->setFilterTagList(tagFilter);

    if (next.isValid()) {
        ui->availableFilterTags->setCurrentIndex(next);
    } else if (prev.isValid()) {
        ui->availableFilterTags->setCurrentIndex(prev);
    }
}

void MainWindow::removeFromFilter()
{
    if (tagFilter.isEmpty() || ui->filterTags->count() == 0 ||
        ! ui->filterTags->currentIndex().isValid()) {
        return;
    }

    QString tagName = ui->filterTags->currentItem()->text();
    ui->filterTags->takeItem(ui->filterTags->currentIndex().row());

    int i = 0;
    Tag tag;
    QListIterator<Tag> iterator(tagFilter);
    while (iterator.hasNext()) {
        tag = iterator.next();
        if (tag.name() == tagName) {
            tagFilter.removeAt(i);
            qDebug() << "Removed tag:" << tag;
            break;
        }
        i++;
    }

    ui->availableFilterTags->setRowHidden(tagRowMap.value(tag.id()), false);
    tagRowMap.remove(tag.id());
//    refreshVideoModel();
    videoModel->setFilterTagList(tagFilter);
}

void MainWindow::resetFilters()
{
    if (sourceVideoModel->isReadOnly()) {
        refreshVideoModel();
    }

    QHashIterator<int, int> iterator(tagRowMap);
    while (iterator.hasNext()) {
        iterator.next();
        ui->availableFilterTags->setRowHidden(iterator.value(), false);
    }

    tagRowMap.clear();
    tagFilter.clear();
    ui->filterTags->clear();
    ui->search->clear();
    ui->favorites->setChecked(false);
    ui->untagged->setChecked(false);

    videoModel->setTextFilter("");
    videoModel->setFavoritesFilter(false);
    videoModel->setUntaggedFilter(false);
    videoModel->setFilterTagList(tagFilter);
}

void MainWindow::openTagEditor()
{
    if (te) {
        return;
    }

    int idFilm = 0;

    //  pay attention to tabWdget->currentIndex. I think it should be checked by mplayerwidget, if it has media set
    if (ui->videos->currentIndex().isValid() && (ui->videos->hasFocus() || ui->tabWidget->currentIndex() == 1)) {
        idFilm = currentVideoData(FilmTag::IdFilm).toInt();
    }

    if (ui->tabWidget->currentIndex() == 1 && ! currentVideo.isEmpty()) {
        idFilm = currentVideoId;
    }

    te = new TagEditor(idFilm);

    connect(te, SIGNAL(refreshVideoModel()),
            this, SLOT(refreshVideoModel()));
    connect(te, SIGNAL(refreshTagModel()),
            this, SLOT(refreshTagModel()));
    connect(te, SIGNAL(tagUpdated(Tag)),
            this, SLOT(refreshTagFilters(Tag)));
    connect(te, SIGNAL(destroyed()),
            this, SLOT(goToCurrentTab()));
    connect(te, SIGNAL(refreshVideoTagsModel()),
            this, SLOT(refreshVideoTagsModel()));

    te->show();;
}

void MainWindow::favorite(bool is)
{
    if (ui->tabWidget->currentIndex() > 0) {
        ui->actionDelete->setDisabled(true);
    } else {
        ui->actionDelete->setDisabled(is);
    }
}

void MainWindow::favorite(QModelIndex index)
{
    if (! index.isValid()) {
        return;
    }

    QFont font;
    bool isFavorite = currentVideoData(FilmTag::Favorite).toBool();

    font.setBold(isFavorite);

    ui->actionDelete->setDisabled(isFavorite);
    ui->mplayerWidget->setMedia(ui->mplayerWidget->media(), font);
}

void MainWindow::toggleFavorite()
{
    int idFilm = currentVideoData(FilmTag::IdFilm).toInt();

    if (ui->tabWidget->currentIndex() > 0) {
        idFilm = currentVideoId;
    }

    FilmHandler fh;
    fh.toggleFavorite(idFilm);
    refreshVideoModel();
}

void MainWindow::toggleMarked()
{
    int idFilm = currentVideoData(FilmTag::IdFilm).toInt();
    FilmHandler fh;
    fh.toggleMarked(idFilm);
    refreshVideoModel();
}

void MainWindow::deleteVideo()
{
    int idFilm = currentVideoData(FilmTag::IdFilm).toInt();
    FilmHandler fh;
    Film film = fh.getFilmById(idFilm);

    if (film.isFavorite()) {
        return;
    }

    QString message;
    message = tr("You requested removal of following file:\n\n"
                 "%1\n\n"
                 "This operation can not be undone. "
                 "Are you sure you want to proceed?");

    if (QMessageBox::question(this,
                              tr("Delete video"),
                              message.arg(QString(film.fileName())),
                              QMessageBox::Yes | QMessageBox::No,
                              QMessageBox::Yes) != QMessageBox::Yes) {
        return;
    }

    ui->mplayerWidget->stop();

    qDebug() << "Removing" << film.filePath();
    bool result = QFile::remove(film.filePath());

    if (QFile::exists(film.filePath()) && ! result) {
        qDebug() << "failed";
        return;
    }

    fh.deleteVideo(idFilm);
    refreshVideoModel();
}

void MainWindow::directoryScanning()
{
    QString dir = ConfigHandler::instance()
                  ->load(LastScannedDirectory,
                         QStandardPaths::HomeLocation).toString();
    QString startDir = QFileDialog::getExistingDirectory(this,
                                                         tr("Select directory for scanning"),
                                                         dir,
                                                         QFileDialog::ShowDirsOnly);

    if (startDir.isEmpty()) {
        return;
    }

    ConfigHandler::instance()->save(LastScannedDirectory, startDir);

    QProgressDialog progress;
    progress.setWindowTitle(tr("Directory scanner"));
    progress.setLabelText(tr("Searching for new videos..."));
    progress.setCancelButtonText(tr("Abort"));

    progress.setMinimumDuration(0);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimum(0);
    progress.setAutoClose(false);

    DirScanner::scanResult.clear();
    DirScanner ds;

    connect(&progress, SIGNAL(canceled()),
            &ds, SLOT(stopSearch()));
    connect(&ds, SIGNAL(itemsCount(int)),
            &progress, SLOT(setMaximum(int)));
    connect(&ds, SIGNAL(currentItem(int)),
            &progress, SLOT(setValue(int)));

    ds.scanDirectory(startDir);

    if (! ds.isReady()) {
        return;
    }

    ds.prepareHashes();

    if (! ds.isReady()) {
        return;
    }

    FilmHandler fh;
    fh.addRemoveScanResult(DirScanner::scanResult);

    progress.setLabelText(tr("Searching dead entries against search directory..."));
    progress.setMaximum(DirScanner::scanResult.count());
    progress.setValue(1);

    fh.getDeadEntries(DirScanner::scanResult);

    progress.close();

    refreshVideoModel();
}

void MainWindow::pickDownloadDirectory()
{
    QString dir = ConfigHandler::instance()->load(DownloadDirectory,
                                                  LastScannedDirectory).toString();

    if (dir.isEmpty()) {
        dir = QStandardPaths::HomeLocation;
    }

    QString downloadDir = QFileDialog::getExistingDirectory(this,
                                                            tr("Select download directory"),
                                                            dir,
                                                            QFileDialog::ShowDirsOnly);

    if (downloadDir.isEmpty()) {
        return;
    }

    ConfigHandler::instance()->save(DownloadDirectory, downloadDir);
}

void MainWindow::setFilmNotes(QModelIndex index)
{
    enableEditorControls(false);

    if (! index.isValid()) {
        ui->filmNotes->clear();
        return;
    }

    int idFilm = currentVideoData(FilmTag::IdFilm).toInt();
    setFilmNotes(idFilm);
}

void MainWindow::setFilmNotes(int idFilm)
{
    FilmHandler fh;
    Film f = fh.getFilmById(idFilm);

    ui->filmNotes->setPlainText(f.notes());
    enableEditorControls(false);
}

void MainWindow::audioDumpComplete(int exitCode)
{
    QString result;
    result = exitCode == 0
            ? tr("success!")
            : tr("failed!");

    ui->statusBar->showMessage(tr("Dumping audio to mp3 file %1").arg(result), DEFAULT_MESSAGE_TIMEOUT);
}

void MainWindow::setTimeOffsets(QString start, QString endpos)
{
    playbackOffset = start;
    playbackEndpos = endpos;
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->search && event->type() == QEvent::KeyRelease) {
        videoModel->setTextFilter(ui->search->text());
    }

    if (object == ui->search && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
        Qt::KeyboardModifiers modifiers(keyEvent->modifiers());

        if (keyEvent->key() == Qt::Key_X && modifiers.testFlag(Qt::ControlModifier)) {
            ui->search->clear();
            videoModel->setTextFilter("");
        }
    }

    if (object == ui->filmNotes && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_Escape) {
            on_actionSaveNotes_triggered();
        }
     }

    return QObject::eventFilter(object, event);
}

void MainWindow::createDatabaseBackup()
{
    QString outputFile = QFileDialog::getSaveFileName(this,
                                 tr("Select output file"),
                                 QDir::homePath(),
                                 tr("SQL file (*.sql)"));

    if (outputFile.isEmpty()) {
        return;
    }

    QFile backupFile(outputFile);
    backupFile.open(QFile::WriteOnly | QFile::Text);

    TagHandler th;
    TagCollection tc = th.getAllTags();
    QListIterator<Tag> tagiterator(tc);

    while (tagiterator.hasNext()) {
        Tag t = tagiterator.next();

        QString sql = t.insertQuery();
        backupFile.write(sql.toUtf8());
    }

    FilmHandler fh;
    FilmCollection films = fh.getAllFilms();
    QListIterator<Film> filmiterator(films);

    while (filmiterator.hasNext()) {
        Film f = filmiterator.next();

        QString sql = f.insertFilmQuery();
        backupFile.write(sql.toUtf8());

        TagCollection tags = fh.getFilmTags(f.id());

        if (tags.isEmpty()) {
            continue;
        }

        sql = f.insertTagsQuery(tags);
        backupFile.write(sql.toUtf8());
    }

    backupFile.close();
}

void MainWindow::processFinished(int/* exitStatus*/)
{
    SettingBool s_playlistMode(PlaylistMode);

    if (! s_playlistMode()) {
        return;
    }

    Q_CHECK_PTR(videoModel);

    Q_ASSERT(videoModel != NULL);
    Q_ASSERT(ui->videos != NULL);

    QModelIndex current, next, first;
    current = ui->videos->currentIndex();

    int row = current.row();
    first = current.sibling(0, current.column());
    next = current.sibling(row+1, current.column());


    QPCOL_MDEBUG("Current row/col:" << current.row()<< current.column() << " // next row/col:" << next.row() << current.column() << "model rowcount" << videoModel->rowCount());


    if (! next.isValid()) {
        if (! first.isValid()) {
            QPCOL_MDEBUG("Index invalid");
            return;
        } else {
            setCurrentVideo(first);
            ui->videos->setCurrentIndex(first);
            ui->videos->selectRow(first.row());
        }
    } else {
        setCurrentVideo(next);
        ui->videos->setCurrentIndex(next);
        ui->videos->selectRow(next.row());
    }

    setFilmNotes(currentVideoId);
    refreshVideoTagsModel();

    QPCOL_MDEBUG("Setting media:" << currentVideo);

    ui->mplayerWidget->setMedia(currentVideo);
    ui->mplayerWidget->getMplayerProcess()->waitForStarted();
    ui->mplayerWidget->play();
}

void MainWindow::moveVideoFile()
{
    Film f = currentFilmFromModel();

    if (! f) {
        return;
    }

    QString currentPath = QFile::decodeName(f.filePath());
    QFileInfo finfo(currentPath);
    QMimeDatabase mimeDb;
    QString mimeExtension;
    mimeExtension = mimeDb.suffixForFileName(finfo.filePath());
    qDebug() << "Detected mime extension:" << mimeExtension;

    if (mimeExtension.isEmpty()) {
        mimeExtension = finfo.suffix();
    }

    QString newPath = QFileDialog::getSaveFileName(this, tr("Choose new path and name"),
                                                   currentPath,
                                                   tr("Video file (*.%1)").arg(mimeExtension));


    finfo.setFile(newPath);
    QByteArray targetFilePath = QFile::encodeName(QString("%1/%2.%3")
                                                  .arg(finfo.absolutePath())
                                                  .arg(finfo.completeBaseName())
                                                  .arg(mimeExtension));
    if (QFile::exists(newPath)) {
        qDebug() << "Not moving, target exists";
        return;
    }


    if (newPath.isEmpty() || QFile::encodeName(newPath) == f.filePath()) {
        QPCOL_MDEBUG("User abort");
        return;
    }

    qDebug() << "Moving" << currentPath << "to" << targetFilePath;

    QFile file(currentPath);
    if (! file.rename(currentPath, targetFilePath)) {
        QMessageBox::critical(this, tr("File not moved"), tr("Error while moving file to new directory."));
        return;
    }

    f.updatePath(targetFilePath);
    refreshVideoModel();
}


QVariant MainWindow::currentVideoData(FilmTag::Column column)
{
    Q_CHECK_PTR(ui->videos);

    QModelIndex currentIndex = ui->videos->currentIndex();

    if (! currentIndex.isValid()) {
        return QVariant();
    }

    return videoModel->index(currentIndex.row(), column).data();
}

Film MainWindow::currentFilmFromModel()
{
    int idFilm = currentVideoData(FilmTag::IdFilm).toInt();
    FilmHandler fh;

    return fh.getFilmById(idFilm);
}

void MainWindow::mouseHoverInFilmTags()
{
    QPCOL_MDEBUG("Hiding film notes (mouseIn signal)");
    ui->filmNotes->hide();
}

void MainWindow::mouseHoverOutFilmTags()
{
    QPCOL_MDEBUG("Showing film notes mouseOut signal)");

    ui->filmNotes->show();
}

void MainWindow::mouseHoverInFilmNotes()
{
    QPCOL_MDEBUG("Hiding film tag table (mouseIn signal)");

    ui->currentFilmTagsTable->hide();
}

void MainWindow::mouseHoverOutFilmNotes()
{
    QPCOL_MDEBUG("SHowingfilm tag table (mouseOut signal)");

    ui->currentFilmTagsTable->show();
}

/******************************************************************************
 *
 * Private slots of QtDesigner
 *
 ******************************************************************************/
// TODO: on action trigger Playing message overlaps URL widget
void MainWindow::on_actionPlay_triggered()
{
    Q_CHECK_PTR(ui->videos);

    on_videos_clicked(ui->videos->currentIndex());
    playSelected();
}

void MainWindow::on_videos_clicked(const QModelIndex &index)
{
    Q_CHECK_PTR(videoModel);

    int idFilm = videoModel->index(index.row(), FilmTag::IdFilm).data().toInt();
    FilmHandler fh;
    Film f = fh.getFilmById(idFilm);

    if (f.fileHash().isEmpty()) {
        HashHandler hh(f.filePath());
        f.setHash(hh.hash());
    }

    QUrl u(f.originalUrl());
    QString href("<a href=\"%1\">%1</a>");
    QString qpcolHref("<a href=\"%1\">%1</a>");

    if (! u.isValid() && f.fileHash().isEmpty()) {
        ui->statusBar->removeWidget(& originalVideoUrlLabel);
        return;
    }

    if ((f.originalUrl() == f.filePath() || f.originalUrl().isEmpty()) && ! f.fileHash().isEmpty()) {
        href.clear();
        href = QString("QPcol URL: %1").arg(qpcolHref.arg(f.qpcolUrl()));
    } else if (u.isValid() && ! f.fileHash().isEmpty()) {
        href = QString("Page URL: %1").arg(href.arg(u.toString()));
        href.append(" :: QPcol URL: ").append(qpcolHref.arg(f.qpcolUrl()));
    } else {
        qDebug() << "Setting video info on stratusbar: it should never go here";
        return;
    }

    ui->statusBar->clearMessage();
    ui->statusBar->removeWidget(& originalVideoUrlLabel);
    ui->statusBar->addWidget(& originalVideoUrlLabel, Qt::AlignLeft);

    originalVideoUrlLabel.setOpenExternalLinks(true);
    originalVideoUrlLabel.setText(href/*.arg(QString(f.originalUrl()))*/);
    originalVideoUrlLabel.setTextFormat(Qt::AutoText);
    originalVideoUrlLabel.setTextInteractionFlags(Qt::LinksAccessibleByMouse | Qt::TextBrowserInteraction);

    originalVideoUrlLabel.setCursor(QCursor(Qt::PointingHandCursor));
    originalVideoUrlLabel.show();
}

void MainWindow::on_actionReset_triggered()
{
    resetFilters();
}

void MainWindow::on_buttonAddFilterTag_clicked()
{
    addToFilter();
}

void MainWindow::on_buttonRemoveFilterTag_clicked()
{
    removeFromFilter();
}

void MainWindow::on_filterTags_activated(QModelIndex /*index*/)
{
    removeFromFilter();
}

void MainWindow::on_favorites_clicked()
{
    on_actionMarkFavorite_triggered();
}

void MainWindow::on_untagged_clicked()
{
    refreshVideoModel();
}

void MainWindow::on_availableFilterTags_activated(QModelIndex /*index*/)
{
    addToFilter();
}

void MainWindow::on_actionTabBrowser_triggered()
{
    goToBrowser();
}

void MainWindow::on_actionTabPlayer_triggered()
{
    goToPlayer();
}

void MainWindow::on_actionScanDirectory_triggered()
{
    directoryScanning();
}

//void MainWindow::on_actionDelete_activated()
//{
//    deleteVideo();
//}

void MainWindow::on_actionMarkFavorite_triggered()
{
    toggleFavorite();
}

void MainWindow::on_actionInteresting_triggered()
{
    toggleMarked();
}

void MainWindow::on_actionManageTags_triggered()
{
    openTagEditor();
}

void MainWindow::on_actionFilterFavorites_triggered()
{
    ui->favorites->toggle();
    videoModel->setFavoritesFilter(ui->favorites->isChecked());
}

void MainWindow::on_actionActionGoToTags_triggered()
{
    goToTagFilter();
}

void MainWindow::on_actionGoToUsedTags_triggered()
{
    goToCurrentFilter();
}

void MainWindow::on_actionFilterUntagged_triggered()
{
    ui->untagged->toggle();
    videoModel->setUntaggedFilter(ui->untagged->isChecked());
}

void MainWindow::on_actionGoToSearch_triggered()
{
    ui->search->setFocus();
}

void MainWindow::on_actionSetDownloadDirectory_triggered()
{
    pickDownloadDirectory();
}

void MainWindow::on_actionClipboardCapture_triggered(bool checked)
{
    captureLinks = checked;
    clipMonitor.set(checked);
    ConfigHandler::instance()->save(CaptureClipboard, captureLinks);
}

void MainWindow::on_actionBackupDatabase_triggered()
{
    createDatabaseBackup();
}

void MainWindow::on_actionSaveNotes_triggered()
{
    if (! ui->videos->currentIndex().isValid()) {
        return;
    }

    QTextDocument * document = ui->filmNotes->document();

    if (! document->isModified()) {
        return;
    }

    QString notes(ui->filmNotes->toPlainText());
    FilmHandler fh;
    Film f = fh.getFilmById(currentVideoId);

    f.setNotes(notes);
    enableEditorControls(false);

    ui->mplayerWidget->setFocus();
}

void MainWindow::on_actionEnableButtons_triggered()
{
    enableEditorControls(true);
}

void MainWindow::on_actionEditOriginalUrl_triggered()
{
    if (! ui->videos->currentIndex().isValid()) {
        return;
    }

    QString originalUrl = currentVideoData(FilmTag::OriginalUrl).toString();
    QString clipboardData = QApplication::clipboard()->text();

    if ( originalUrl.isEmpty() && QUrl::fromUserInput(clipboardData).isValid()) {
        originalUrl = clipboardData;
    }

    fud = new FilmUrlDialog();
    fud->setInputText(originalUrl);

    QDialog::DialogCode code = (QDialog::DialogCode)fud->exec();

    if (code == QDialog::Rejected) {
        return;
    }

    originalUrl = fud->inputText();

    Film f = currentFilmFromModel();
    f.setOriginalUrl(originalUrl);

    videoModel->invalidate();
//    emit videoModel->dataChanged(ui->videos->currentIndex(), ui->videos->currentIndex());

    qDebug() << "Original URL set:" << originalUrl;
}

void MainWindow::on_actionCopyFilePath_triggered()
{
    if (! ui->videos->currentIndex().isValid()) {
        return;
    }

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(currentFilmFromModel().filePath());
    ui->statusBar->showMessage(tr("File path copied to clipboard"), DEFAULT_MESSAGE_TIMEOUT);
}


void MainWindow::on_actionDumpAudio_triggered()
{
    if (! ui->videos->currentIndex().isValid()) {
            return;
    }

    SettingString ss_dir(DumpAudioDirectory, QDir::homePath());
    QString dir = ss_dir.value();

    Film f = currentFilmFromModel();
    QFileInfo fi(f.filePath());
    QString outFile = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                     QString("%1/%2.mp3").arg(dir).arg(fi.baseName()),
                                                     tr("MP3 file (*.mp3)"));
    fi.setFile(outFile);
    if (outFile.isEmpty() || outFile == f.filePath() || fi.fileName().isEmpty()) {
        QMessageBox::critical(this,
                              tr("File error"),
                              tr("Error occured during attempt to move/rename file. No changes were done."),
                              QMessageBox::Close);
        return;
    }

    QFileInfo dfi(outFile);
    ss_dir.setValue(dfi.absolutePath());
    ss_dir.save();

    ui->statusBar->showMessage(tr("Dumping audio to mp3 file %1").arg(outFile), DEFAULT_MESSAGE_TIMEOUT);

    AudioExtractor *ae = new AudioExtractor(this);
    connect(ae, SIGNAL(saved(int)),
            ae, SLOT(deleteLater()));
    connect(ae, SIGNAL(saved(int)),
            this, SLOT(audioDumpComplete(int)));
    ae->saveAudio(currentFilmFromModel().filePath(), outFile);
}

void MainWindow::on_actionDelete_triggered()
{
    deleteVideo();
}

void MainWindow::on_actionMoveVideoFile_triggered()
{
    moveVideoFile();
}

void MainWindow::on_actionSettings_triggered()
{
    mse = new SettingsEditor(this);

    connect(mse, SIGNAL(accepted()), mse, SLOT(deleteLater()));
    connect(mse, SIGNAL(rejected()), mse, SLOT(deleteLater()));

    mse->show();
}

void MainWindow::on_actionOpenFile_triggered()
{
    QString openVideoInitDir = ConfigHandler::instance()
            ->load(OpenLastVideoPlayDir, QDir::homePath())
            .toString();

    QString selectedFile = QFileDialog::getOpenFileName(this,
                                                        tr("Open local video"),
                                                        openVideoInitDir,
                                                        tr(HANDLED_FORMATS));

    QFileInfo finfo(selectedFile);

    if (! (finfo.isFile() && finfo.isReadable())) {
        return;
    }

    ConfigHandler::instance()->save(OpenLastVideoPlayDir, finfo.absolutePath());

    QPCOL_MDEBUG("Opening" << finfo.canonicalFilePath());

    play(QFile(selectedFile));
}

void MainWindow::on_actionAboutQt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_actionAbout_triggered()
{
    QString name, version, about;
//    QFile readme(QString("%1/share/qpcol/README.md").arg(QPCOL_PREFIX));

    name = QCoreApplication::applicationName();
    version = QCoreApplication::applicationVersion();

    qDebug() <<
        "appname:" << name <<
        "vertsion:" << version;/* <<
        "readmepath" << readme.fileName();*/

//    readme.open(QFile::ReadOnly | QFile::Text);
//    about = QString(readme.readAll());
//    readme.close();

    about = tr("Qt Video Collection manager.\nKeyboard-driven, profiled towards ease and convenience of use.\n"
               "To contact author, visit project page at <a href=\"http://qpcol.sourceforge.net\">SourceForce</a> or one of "
               "my repos at <a href=\"https://github.com/quntax\">GitHub</a> - not all are visible, but "
               " most of my projects (including this one) are licensed on BSD license.");
    QLabel aboutLabel;
    aboutLabel.setOpenExternalLinks(true);
    aboutLabel.setTextInteractionFlags(Qt::TextSelectableByMouse|Qt::LinksAccessibleByMouse);
    aboutLabel.setTextFormat(Qt::RichText);
    aboutLabel.setText(about);


//    QMessageBox aboutBox(this);
//    aboutBox.set
    QMessageBox::about(this,
                       tr("About %1-%2").arg(name).arg(version),
                       aboutLabel.text());
}

void MainWindow::on_actionPlayback_offset_triggered()
{
    TimeOffsetEditor *te = new TimeOffsetEditor;

    te->setStartTime(playbackOffset);
    te->setEndpos(playbackEndpos);

    connect(te, SIGNAL(accepted()), te, SLOT(deleteLater()));
    connect(te, SIGNAL(rejected()), te, SLOT(deleteLater()));
    connect(te, SIGNAL(timeOffsets(QString, QString)),
            this, SLOT(setTimeOffsets(QString, QString)));

    te->show();
}
