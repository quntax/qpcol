#include "tageditor.h"
#include "ui_tageditor.h"

TagEditor::TagEditor(int id, PARENT_TYPE *parent) :
    PARENT_TYPE(parent),
    ui(new Ui::TagEditor)
{
    setAttribute(Qt::WA_DeleteOnClose, true);

    FilmHandler fh;
    film = fh.getFilmById(id);

    ui->setupUi(this);
    addAction(ui->actionAdd);
    addAction(ui->actionClose);
    addAction(ui->actionDelete);
    addAction(ui->actionRename);

    ui->filmTags->setEnabled(film);
    ui->addTagToFilm->setEnabled(film);
    ui->removeTagFromFilm->setEnabled(film);

    loadFilmTags();
    loadAvilableTags();
}

TagEditor::~TagEditor()
{
    delete ui;
}

void TagEditor::changeEvent(QEvent *e)
{
    PARENT_TYPE::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TagEditor::loadFilmTags()
{
    if (film) {
        FilmHandler fh;
        filmTags = fh.getFilmTags(film.id());
    }

    ui->filmTags->clear();

    QListIterator<Tag> iterator(filmTags);
    while (iterator.hasNext()) {
        Tag tag = iterator.next();
        ui->filmTags->addItem(tag.name());
    }
}
\
void TagEditor::loadAvilableTags()
{
    TagHandler th;
    availableTags = th.getAllTags();
    ui->availableTags->clear();

    int i = 0;
    QListIterator<Tag> iterator(availableTags);
    while (iterator.hasNext()) {
        Tag tag = iterator.next();
        if (filmTags.contains(tag)) {
            availableTags.takeAt(i);
            i++;
            continue;
        }

        ui->availableTags->addItem(tag.name());
    }

    emit refreshVideoTagsModel();
}

void TagEditor::tagVideo(QListWidgetItem *item)
{
    int row = ui->availableTags->row(item);
    TagHandler th;
    Tag tag = th.getTagByName(item->data(Qt::DisplayRole).toString());
    film.tag(tag);

    loadFilmTags();
    loadAvilableTags();

    do {
        ui->availableTags->setCurrentRow(row--);
    } while (row >= 0 && ! ui->availableTags->currentIndex().isValid());

    emit refreshVideoTagsModel();
}

void TagEditor::untagVideo(QListWidgetItem *item)
{
    int row = ui->filmTags->row(item);
    TagHandler th;
    Tag tag = th.getTagByName(item->data(Qt::DisplayRole).toString());
    film.untag(tag);

    loadFilmTags();
    loadAvilableTags();

    do {
        ui->filmTags->setCurrentRow(row--);
    } while (row >= 0 && ! ui->filmTags->currentIndex().isValid());

    emit refreshVideoTagsModel();
}

void TagEditor::on_addTagToFilm_clicked()
{
    if (! ui->availableTags->currentItem()) return;
    tagVideo(ui->availableTags->currentItem());
}

void TagEditor::on_removeTagFromFilm_clicked()
{
    if (! ui->filmTags->currentItem()) return;
    untagVideo(ui->filmTags->currentItem());
}

void TagEditor::addNewTag()
{
    TagDialog * td = new TagDialog(this);

    connect(td, SIGNAL(saved()),
            this, SLOT(loadAvilableTags()));
    connect(td, SIGNAL(saved()),
            this, SIGNAL(refreshTagModel()));

    td->show();
}

void TagEditor::on_actionClose_triggered()
{
    emit refreshVideoModel();
    close();
//    deleteLater();
}

void TagEditor::on_actionAdd_triggered()
{
    addNewTag();
}

void TagEditor::on_actionDelete_triggered()
{
    deleteTag();
}

void TagEditor::deleteTag()
{
    if (ui->availableTags->count() == 0 ||
        ! ui->availableTags->currentItem())
    {
        return;
    }

    QString tagName = ui->availableTags->currentItem()->text();
    FilmHandler fh;
    TagHandler th;

    Tag tag = th.getTagByName(tagName);
    FilmCollection fc = fh.getFilmsByIdTag(tag.id());

    int filmsTagged = fc.count();

    if (filmsTagged > 0) {
        QString warning(tr("There are %1 films tagged with \"%2\"\n"
                           "Untag them first in order to delete tag completely."));
        QMessageBox::information(this,
                                 tr("Tag in use"),
                                 warning.arg(filmsTagged).arg(tagName),
                                 QMessageBox::Ok);

        return;
    }


    th.deleteTag(tagName);

    loadFilmTags();
    loadAvilableTags();

    emit refreshTagModel();
}

void TagEditor::on_actionRename_triggered()
{
    renameTag();
}

void TagEditor::renameTag()
{
    if (ui->availableTags->count() == 0) {
        return;
    }

    QListWidget * activeList = new QListWidget;

    if (ui->filmTags->hasFocus()) {
        activeList = ui->filmTags;
    } else {
        activeList = ui->availableTags;
    }

    QString tagName = activeList->currentItem()->text();
    TagHandler th;

    Tag tag = th.getTagByName(tagName);

    TagDialog *td = new TagDialog(this);

    connect(td, SIGNAL(saved()),
            this, SLOT(loadFilmTags()));
    connect(td, SIGNAL(saved()),
            this, SLOT(loadAvilableTags()));
    connect(td, SIGNAL(saved()),
            this, SIGNAL(refreshTagModel()));
    connect(td, SIGNAL(tagUpdated(Tag)),
            this, SIGNAL(tagUpdated(Tag)));
//    connect(td, SIGNAL(saved()),
//            this, SIGNAL(refreshVideoModel()));

    td->setTag(tag);
    td->show();
}
