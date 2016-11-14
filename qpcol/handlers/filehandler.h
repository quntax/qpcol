#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#ifdef USING_PCH
    #include "precompiled.h"
#else
    #include <QDialog>
    #include <QFile>
#endif

class FileHandler : public QObject
{
    Q_OBJECT
    Q_ENUMS(FileMime)

public:
    enum FileMime {
        VideoMp4,
        VideoFlash,
        VideoAvi,
        VideoMpeg,
        VideoMatroska
    };
    explicit FileHandler(QObject *parent = 0);
    ~FileHandler();

    QString openFile(const QString &, const QString &);
    QString openDir(const QString &);

    bool saveFile(const QFile &);
    FileMime mimeType(const QFile &);
signals:

public slots:

protected:
    QFile m_File;

private:
    QObject *m_Parent;
};


typedef QPair<QString, FileHandler::FileMime> MimeData;
Q_DECLARE_METATYPE(MimeData)

#endif // FILEHANDLER_H
