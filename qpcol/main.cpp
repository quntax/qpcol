#ifdef USING_PCH
    #include "precompiled.h"
#else
    #include <QtCore>
    #include <QtGui>
    #include <QWidgetSet>
    #include <QCoreApplication>
    #include <QApplication>
    #include <QString>
    #include <QFile>
#endif

#include <MWidgets>

#include "qpcolapplication.h"
#include "filmtagslistview.h"
#include "filmnotestextedit.h"
#include "messenger.h"
#include "options.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QPcolApplication a(argc, argv);

    QString locale = QLocale::system().name();
//    QString appDir = QCoreApplication::applicationDirPath();
    QString prefix(QPCOL_PREFIX);
    QString path = QString("%1/share/qpcol/").arg(prefix);
    QString file = QString("qpcol_%1").arg(locale);

    QCommandLineParser parser;

    parser.setApplicationDescription(QCoreApplication::translate("main", "Personal video collection manager. Keyboard-oriented, quick & convenient."));
    parser.addVersionOption();
    parser.addHelpOption();

    QCommandLineOption hashlistOption(QStringList() << "hashlist",
                                 QCoreApplication::translate("main", "Print list of all registered, active videos with hashes"));
    parser.addOption(hashlistOption);

    QCommandLineOption uriOption(QStringList() << "u" << "uri",
                                 QCoreApplication::translate("main", "Video URI in format qpcol://<hash>"),
                                 QCoreApplication::translate("main", "uri"));
    parser.addOption(uriOption);

    QCommandLineOption fileOption(QStringList() << "f" << "file",
                                 QCoreApplication::translate("main", "Local file path to open"),
                                 QCoreApplication::translate("main", "filename"));
    parser.addOption(fileOption);

    QCommandLineOption addOption(QStringList() << "a" << "add",
                                  QCoreApplication::translate("main", "File will be added to db, if not found yet"),
                                  QCoreApplication::translate("main", "filename"));
    parser.addOption(addOption);

    parser.process(a);

    QTranslator translator;
    translator.load("/" + path + file);
    a.installTranslator(&translator);

    CmdLineOptions options;

    parser.isSet("hashlist") ? options.insert("hashlist", "1") : NULL;
    parser.isSet("uri") ? options.insert("uri", parser.value("uri")) : NULL;
    parser.isSet("file") ? options.insert("file", parser.value("file")) : NULL;

    // not handled as for now
    options.insert("add", parser.value("add"));

    if (! a.isPidFileValid()) {
//        if (options.contains("uri")) {
//            qDebug() << "Executing separate process for qpcol://";

//            QProcess * proc = new QProcess(QCoreApplication::instance());

//            proc->setProgram(QCoreApplication::applicationFilePath());
//            proc->setArguments(QStringList() << "u" << options.value("uri"));
//            proc->start();

//            proc->waitForStarted(1000);
//        } else {
            a.showPidFileWarning();
//        }

        a.exit(1);
        a.deleteLater();

        return 1;
    }

    MainWindow w;
    w.setOptions(options);
    w.showMaximized();


    return a.exec();
}
