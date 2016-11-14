#include "downloaddialog.h"

DownloadDialog::DownloadDialog(QWidget * parent) : QDialog(parent)
{
    dialogText = QString("Downloading file:\n%1\n\nTarget directory:\n%2\n");
    pixmap = QIcon::fromTheme("download").pixmap(QSize(48, 48));
}

DownloadDialog::~DownloadDialog()
{
    destroy();
}

// TODO prompt for directory if not known.... give a chance to change if known
void DownloadDialog::download(const QString &url, const QString &directory)
{
    if (checkTargetExists(url, directory)) {
        close();
        return;
    }

    imageLabel = new QLabel;
    imageLabel->setPixmap(pixmap);

    QFileInfo urlInfo(url);
    textLabel = new QLabel(dialogText.arg(urlInfo.fileName()).arg(directory));

    buttonAbort = new QPushButton(QIcon::fromTheme("dialog-cancel"), tr("Abort"));
    connect(buttonAbort, SIGNAL(clicked()),
            this, SLOT(cancel()));

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(buttonAbort, QDialogButtonBox::RejectRole);

    progressBar = new QProgressBar;
    progressBar->setValue(0);
    progressBar->setFormat("%v / %m KB (%p%)");

    QHBoxLayout * iconAndTextLayout = new QHBoxLayout;
    iconAndTextLayout->setSpacing(22);
    iconAndTextLayout->setContentsMargins(11, 11, 11, 11);
    iconAndTextLayout->addWidget(imageLabel);
    iconAndTextLayout->addWidget(textLabel);

    QHBoxLayout * abortButtonLayout = new QHBoxLayout;
    abortButtonLayout->addStretch();
    abortButtonLayout->addWidget(buttonBox);

    QVBoxLayout * completeLayout = new QVBoxLayout;
    completeLayout->addLayout(iconAndTextLayout);
    completeLayout->addWidget(progressBar);
    completeLayout->addLayout(abortButtonLayout);

    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->addLayout(completeLayout, 0, 0);
    setLayout(mainLayout);

    setMaximumSize(width(), height());
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setWindowTitle(QString(tr("%1 -  downloading")).arg(file));
    show();

    targetFile.open(QFile::WriteOnly);

    downloader = new QHttpDownload;
    connect(downloader, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateProgressBar(qint64,qint64)));
    connect(downloader, SIGNAL(chunk(QByteArray)),
            this, SLOT(saveChunk(QByteArray)));
    connect(downloader, SIGNAL(clear()),
            this, SLOT(reset()));
    connect(downloader, SIGNAL(complete(QByteArray)),
            this, SLOT(complete()));

    sourceUrl = url;

    downloader->download(url);
}

void DownloadDialog::downloadToFile(const QString &remoteFile, const QString &localFile)
{
    sourceUrl = remoteFile;
    targetFile.setFileName(localFile);

    dir = QFileInfo(targetFile).dir().canonicalPath();
    file = QFileInfo(targetFile).fileName();

    imageLabel = new QLabel;
    imageLabel->setPixmap(pixmap);

    QFileInfo urlInfo(remoteFile);
    textLabel = new QLabel(dialogText.arg(urlInfo.fileName()).arg(targetFile.fileName()));

    buttonAbort = new QPushButton(QIcon::fromTheme("dialog-cancel"), tr("Abort"));
    connect(buttonAbort, SIGNAL(clicked()),
            this, SLOT(cancel()));

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(buttonAbort, QDialogButtonBox::RejectRole);

    progressBar = new QProgressBar;
    progressBar->setValue(0);
    progressBar->setFormat("%v / %m KB (%p%)");

    QHBoxLayout * iconAndTextLayout = new QHBoxLayout;
    iconAndTextLayout->setSpacing(22);
    iconAndTextLayout->setContentsMargins(11, 11, 11, 11);
    iconAndTextLayout->addWidget(imageLabel);
    iconAndTextLayout->addWidget(textLabel);

    QHBoxLayout * abortButtonLayout = new QHBoxLayout;
    abortButtonLayout->addStretch();
    abortButtonLayout->addWidget(buttonBox);

    QVBoxLayout * completeLayout = new QVBoxLayout;
    completeLayout->addLayout(iconAndTextLayout);
    completeLayout->addWidget(progressBar);
    completeLayout->addLayout(abortButtonLayout);

    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->addLayout(completeLayout, 0, 0);
    setLayout(mainLayout);

    setMaximumSize(width(), height());
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setWindowTitle(QString(tr("%1 -  downloading")).arg(file));
    show();

    bool ioResult = targetFile.open(QFile::WriteOnly);

    if (! ioResult) {
        qDebug() << "Could not open target file";
        cleanup();
        return;
    }

    downloader = new QHttpDownload;
    connect(downloader, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateProgressBar(qint64,qint64)));
    connect(downloader, SIGNAL(chunk(QByteArray)),
            this, SLOT(saveChunk(QByteArray)));
    connect(downloader, SIGNAL(clear()),
            this, SLOT(reset()));
    connect(downloader, SIGNAL(complete(QByteArray)),
            this, SLOT(complete()));

    downloader->download(remoteFile);
}

void DownloadDialog::cancel()
{
    downloader->blockSignals(true);
    downloader->disconnect();

    targetFile.remove();
    cleanup();
}

void DownloadDialog::updateProgressBar(qint64 val, qint64 max) {
    progressBar->setValue(qRound((qreal)val/1024));
    progressBar->setMaximum(qRound((qreal)max/1024));
}

void DownloadDialog::complete() {
    targetFile.flush();
    targetFile.close();

    emit downloadCompleted(sourceUrl);
    emit downloadCompleted(this);
    emit downloadCompleted(this, sourceUrl);
}

void DownloadDialog::saveChunk(QByteArray chunk)
{
    targetFile.write(chunk);
}
QString DownloadDialog::getSourceUrl() const
{
    return sourceUrl;
}

QString DownloadDialog::getTargetFile() const
{
    return QFile::decodeName(targetFile.fileName().toLocal8Bit());
}

void DownloadDialog::reset()
{
    targetFile.flush();
    targetFile.resize(0);
}

void DownloadDialog::cleanup()
{
    downloader->deleteLater();
    downloader = 0;
    close();
}

bool DownloadDialog::checkTargetExists(const QString &url, const QString &directory)
{
    QFileInfo info(url);

    file = info.fileName();
    if (file.isEmpty()) {
        file = QString("download_%1").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
    }

    dir = directory;
    QString filename = QString("%1/%2").arg(dir).arg(file);

    QString message = QString(tr("File with name %1 already exists in directory %2\n"
                              "You can click \"Yes\" to continue download, overwriting it,\n"
                              "\"No\" to abort or \"Ignore\" to download file\n"
                              "with randomly picked new name.\n\n"
                              "Do you wish to proceed?")).arg(file).arg(dir);
    if (QFile::exists(filename)) {
        int result = QMessageBox::question(
                this,
                tr("File exists"),
                message,
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Ignore,
                QMessageBox::No);

        if (result == QMessageBox::No) {
            return true;
        }

        if (result == QMessageBox::Ignore) {
            file.prepend(QCryptographicHash::hash(QDateTime::currentDateTime().toString().toLocal8Bit(),
                                                  QCryptographicHash::Md5).toHex());
            filename = QString("%1/%2").arg(dir).arg(file);
        }
    }

    targetFile.setFileName(filename);

    return false;
}

