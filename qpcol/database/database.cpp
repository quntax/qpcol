#include "database.h"
#include "confighandler.h"
#include "qsqlquery.h"

Database::Database(QByteArray host, QByteArray user, QByteArray pass, QByteArray name)
{
    dbaccess.hostname = host;
    dbaccess.username = user;
    dbaccess.password = pass;
    dbaccess.database = name;
}

QSqlDatabase Database::connection()
{
    if (! conn.isOpen()) {
        if (DATABASE_TYPE == SQLITE) {

            conn = QSqlDatabase::addDatabase("QSQLITE");
            conn.setDatabaseName(sqliteLocation());
            conn.open();

            QSqlQuery query("PRAGMA foreign_keys = true", conn);
            query.exec();
            query.finish();

//            QSqlQuery utf("PRAGMA encoding = \"UTF-8\"", conn);
//            utf.exec();
        }

        if (DATABASE_TYPE == MYSQL) {
            conn = QSqlDatabase::addDatabase("QMYSQL");
            conn.setHostName(dbaccess.hostname);;
            conn.setUserName(dbaccess.username);
            conn.setPassword(dbaccess.password);
            conn.setDatabaseName(dbaccess.database);
            conn.open();
        }

    }

    return conn;
}

QString Database::sqliteLocation()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                    QCoreApplication::organizationName(),
                    QCoreApplication::applicationName());
    QString dir = QFileInfo(settings.fileName()).absolutePath();

    return dir.append(QDir::separator()).append(DBNAME);
}

int Database::sqliteCheck()
{
    QFileInfo qfi(sqliteLocation());

    if (! qfi.exists()) return 1;
    if (! qfi.isReadable()) return 2;
    if (! qfi.isWritable()) return 3;

    return 0; // means OK
}

//void Database::init(const QString & path)
//{
//    QString scriptPath = path.append("/qpcol.sql");
//    QSqlQuery query(Connection::inst)
//    QFile scriptFile("/path/to/your/script.sql");

//    if (scriptFile.open(QIODevice::ReadOnly)) {
//        // The SQLite driver executes only a swingle (the first) query in the QSqlQuery
//        //  if the script contains more queries, it needs to be splitted.
//        QStringList scriptQueries = QTextStream(&scriptFile).readAll().split(';');

//        foreach (QString queryTxt, scriptQueries) {
//            if (queryTxt.trimmed().isEmpty()) {
//                continue;
//            }

//            if (! query.exec(queryTxt)) {
//                qFatal(QString("One of the query failed to execute."
//                            " Error detail: " + query.lastError().text()).toLocal8Bit());
//            }

//            query.finish();
//        }
//    }
//}
