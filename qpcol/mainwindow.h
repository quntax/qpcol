#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef USING_PCH
    #include "precompiled.h"
#else
    #include <QtCore>
    #include <QtGui>
    #include <QWidgetSet>
    #include <QString>
    #include <QFile>
#endif

#include <MWidgets>

#include "messenger.h"
#include "tag.h"
#include "film.h"
#include "filmtag.h"
#include "videotableview.h"
#include "videomodel.h"
#include "tagmodel.h"
#include "videotagsmodel.h"
#include "videofilterproxymodel.h"
#include "videomodelhandler.h"
#include "filmtagslistview.h"
#include "tagmodelhandler.h"
#include "tageditor.h"
#include "filmurldialog.h"
#include "dirscanner.h"
#include "confighandler.h"
#include "clipboardgrabber.h"
#include "audioextractor.h"
#include "settingseditor.h"
#include "timeoffseteditor.h"

#include "options.h"
#include "setting.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT
        Q_ENUMS(DownloadListRow)

    public:
        enum DownloadListRow {
            PageUrl,
            VideoUrl
        };

        const static int DEFAULT_MESSAGE_TIMEOUT = 1000;

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void setOptions(const CmdLineOptions &);

    public slots:
        void playSelected();
        void playSelected(QModelIndex);
        void play(const QFile &);

    protected slots:
        void goToBrowser();
        void goToTagFilter();
        void goToCurrentFilter();
        void goToPlayer();
        void stopped();
        void goToCurrentTab();

        void addToFilter();
        void removeFromFilter();
        void resetFilters();

        void refreshVideoModel();
        void refreshTagModel();
        void refreshTagFilters(Tag);
        void refreshVideoTagsModel();

        void setCurrentVideo(QModelIndex);
        void openTagEditor();

        void favorite(bool);
        void favorite(QModelIndex);

        void toggleFavorite();
        void toggleMarked();

        void deleteVideo();
        void directoryScanning();

        void pickDownloadDirectory();
        void createDatabaseBackup();

        void processFinished(int);
        void moveVideoFile();
        void setFilmNotes(QModelIndex);
        void setFilmNotes(int);
        void audioDumpComplete(int);
        void setTimeOffsets(QString, QString);

        void mouseHoverInFilmTags();
        void mouseHoverOutFilmTags();
        void mouseHoverInFilmNotes();
        void mouseHoverOutFilmNotes();


    protected:
        void changeEvent(QEvent *e);
        void closeEvent(QCloseEvent *event);
        bool eventFilter(QObject *, QEvent *);

        void initConnections();
        void loadVideoModel();
        void clearSearchCriteria();

        QVariant currentVideoData(FilmTag::Column);
        Film currentFilmFromModel();

    private:
        bool captureLinks;
//        bool captureLinks;

        Ui::MainWindow *ui;
        VideoModel * sourceVideoModel;
        VideoFilterProxyModel * videoModel;
        VideoTagsModel * videoTags;
        TagModel * tagModel;
        TagEditor * te;
        FilmUrlDialog * fud;
        SettingsEditor * mse;

        int currentVideoId;
        QString currentVideo;
        QString searchPhrase;
        QString currentVideoHash;
        QString playbackOffset;
        QString playbackEndpos;

        QLabel originalVideoUrlLabel;

        ClipboardGrabber clipMonitor;
        QString providerName;

        TagCollection tagFilter;
        QHash<int, int> tagRowMap;

        QMutex mutex;
        CmdLineOptions options;

        void initVideoModel();
        void initTagModel();
        void enableEditorControls(bool);

    private slots:
        void on_actionBackupDatabase_triggered();
        void on_actionClipboardCapture_triggered(bool checked);
        void on_actionSetDownloadDirectory_triggered();
        void on_actionGoToSearch_triggered();
        void on_actionFilterUntagged_triggered();
        void on_actionGoToUsedTags_triggered();
        void on_actionActionGoToTags_triggered();
        void on_actionFilterFavorites_triggered();
        void on_actionManageTags_triggered();
        void on_actionInteresting_triggered();
        void on_actionMarkFavorite_triggered();
//        void on_actionDelete_activated();
        void on_actionScanDirectory_triggered();
        void on_actionTabPlayer_triggered();
        void on_actionTabBrowser_triggered();
        void on_availableFilterTags_activated(QModelIndex index);
        void on_untagged_clicked();
        void on_favorites_clicked();
        void on_filterTags_activated(QModelIndex index);
        void on_buttonRemoveFilterTag_clicked();
        void on_buttonAddFilterTag_clicked();
        void on_actionReset_triggered();
        void on_actionPlay_triggered();
        void on_videos_clicked(const QModelIndex &index);
        void on_actionSaveNotes_triggered();
        void on_actionEnableButtons_triggered();
        void on_actionEditOriginalUrl_triggered();
        void on_actionCopyFilePath_triggered();
        void on_actionDumpAudio_triggered();
        void on_actionDelete_triggered();
        void on_actionMoveVideoFile_triggered();
        void on_actionSettings_triggered();
        void on_actionOpenFile_triggered();
        void on_actionAboutQt_triggered();
        void on_actionAbout_triggered();
        void on_actionPlayback_offset_triggered();
};

#endif // MAINWINDOW_H
