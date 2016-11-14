#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#define PARENT_TYPE QWidget

#ifdef USING_PCH
    #include "precompiled.h"
#else
    #include <QtWidgets>
#endif

#include "tagdialog.h"
#include "tag.h"
#include "filmhandler.h"
#include "taghandler.h"

namespace Ui {
    class TagEditor;
}

class TagEditor : public PARENT_TYPE
{
        Q_OBJECT

    public:
        explicit TagEditor(int id, PARENT_TYPE *parent = 0);
        ~TagEditor();

    signals:
        void refreshVideoModel();
        void refreshTagModel();
        void refreshVideoTagsModel();
        void tagUpdated(Tag);

    public slots:
        void tagVideo(QListWidgetItem*);
        void untagVideo(QListWidgetItem*);

    protected slots:
        void loadFilmTags();
        void loadAvilableTags();

    protected:
        void changeEvent(QEvent *e);

    private:
        Ui::TagEditor *ui;
        Film film;

        TagCollection filmTags;
        QList<int> idFilmTags;
        TagCollection availableTags;
        QList<int> idAvailableTags;

    private slots:
        void on_actionDelete_triggered();
        void on_actionAdd_triggered();
        void on_actionClose_triggered();
        void on_actionRename_triggered();

        void on_removeTagFromFilm_clicked();
        void on_addTagToFilm_clicked();

        void addNewTag();
        void deleteTag();
        void renameTag();
};

#endif // TAGEDITOR_H
