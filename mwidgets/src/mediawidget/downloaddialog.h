#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H

#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <QWidget>

#include "qhttpdownload.h"

class DownloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DownloadDialog(QWidget *parent = 0);
    ~DownloadDialog();

    void download(const QString &, const QString &);
    void downloadToFile(const QString &, const QString &);

    QString getTargetFile() const;
    QString getSourceUrl() const;

public slots:
    void updateProgressBar(qint64, qint64);
    void cancel();
    void complete();
    void reset();
    void cleanup();

signals:
    void downloadCompleted(const QString &);
    void downloadCompleted(DownloadDialog *);
    void downloadCompleted(DownloadDialog *, const QString &);

protected slots:
    void saveChunk(QByteArray);

private:
    QFile targetFile;
    QString sourceUrl;

    QString dir;
    QString file;

    QPixmap pixmap;
    QString dialogText;

    QLabel *imageLabel;
    QLabel *textLabel;

    QPushButton *buttonAbort;
    QDialogButtonBox *buttonBox;
    QProgressBar *progressBar;

    QHttpDownload *downloader;

    bool checkTargetExists(const QString &url, const QString &directory);
};

#endif // DOWNLOADDIALOG_H
