/**************************************************************************
 **
 ** This free software may be freelty distributed in accordance with The BSD
 ** License.
 **
 ** Copyright (c) 2015 merlin
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are met:
 ** Redistributions of source code must retain the above copyright notice,
 ** this list of conditions and the following disclaimer.
 ** Redistributions in binary form must reproduce the above copyright notice,
 ** this list of conditions and the following disclaimer in the documentation
 ** and/or other materials provided with the distribution.
 ** Neither the name of the author nor the names of its contributors may be used
 ** to endorse or promote products derived from this software without specific
 ** prior written permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 ** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 ** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND **  FITNESS FOR A PARTICULAR
 ** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 ** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 ** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 ** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 ** OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 ** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 ** OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 ** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **
 **************************************************************************/

#include "qpcolapplication.h"

QPcolApplication::QPcolApplication(int & argc, char ** argv) : QApplication(argc, argv)
{
    // set appname
    QCoreApplication::setApplicationName("QPcol");
    QCoreApplication::setOrganizationName("merlin");
    QCoreApplication::setOrganizationDomain("org.eu.merlin");
    QCoreApplication::setApplicationVersion(QPCOL_VERSION);

    // set locales - later
//    QString locale = QLocale::system().name();

//    QString appDir = QCoreApplication::applicationDirPath();
//    QString prefix(appDir.split("/", QString::SkipEmptyParts).at(0));
//    QString path = QString("%1/share/qpcol/").arg(prefix);
//    QString file = QString("qpcol_%1").arg(locale);

    // check pid or gtfo
    qint64 pid = applicationPid();
    m_pidFile = getApplicationPidFile(pid);
//    QFile * pidFile;

    if (m_pidFile == NULL) {
        qDebug() << "pidFile is NULL, quitting";
//        closeAllWindows();
//        quit();
        return;
    }

    connect(this, SIGNAL(aboutToQuit()),
            this, SLOT(flushPidFile()));
}

QPcolApplication::~QPcolApplication()
{
//    flushPidFile();
}

QFile *QPcolApplication::getApplicationPidFile(qint64 appPid)
{
    QString pidFilePath = QString("%1/%2/%3.pid")
            .arg(QDir::tempPath())
            .arg(QCoreApplication::organizationDomain())
            .arg(QCoreApplication::applicationName());

    QFile * pidFile = new QFile(pidFilePath);
    fi = QFileInfo(*pidFile);
    bool ioResult;

    if (! fi.absoluteDir().exists()) {
        ioResult = fi.absoluteDir().mkpath(fi.absolutePath());

        if (! ioResult) {
            // dupa
            delete pidFile;
            return NULL;
        }
    }


    if (pidFile->exists() && ! pidFile->size() == 0) {
        ! pidFile->isOpen() && (ioResult = pidFile->open(QIODevice::ReadOnly | QIODevice::Text));

        if (! ioResult) {
            // dupa...
            delete pidFile;
            return NULL;
        }

        qint64 currentPid = pidFile->readAll().toInt();
        pidFile->close();

        if (currentPid == appPid) {
            // all ok
            return pidFile;
        }

        delete pidFile;
        return NULL;
    }

    pidFile->open(QIODevice::WriteOnly | QIODevice::Text);
    pidFile->write(QString("%1").arg(appPid).toLocal8Bit());
    pidFile->flush();
    pidFile->close();

    return pidFile;
}

bool QPcolApplication::isPidFileValid()
{
    return m_pidFile != NULL && m_pidFile->exists();
}

void QPcolApplication::showPidFileWarning()
{
    // not ok, other instance or zombie pid
    QMessageBox::warning(0,
                         /*QCoreApplication::*/translate("main", "QPcol pidfile is locked"),
                         /*QCoreApplication::*/translate("main", "PID file already exists. It means that either other instance is already running,"
                            "or it crashed and left lock file. If you are sure about the "
                            "second possibility, remove %1 file and run QPcol again").arg(fi.absoluteFilePath()), QMessageBox::Close);

}

void QPcolApplication::flushPidFile()
{
    if (! m_pidFile || m_pidFile == NULL) {
        return;
    }

    m_pidFile->remove();
    delete m_pidFile;
}

