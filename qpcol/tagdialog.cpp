#include "tagdialog.h"
#include "ui_tagdialog.h"

TagDialog::TagDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TagDialog)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    ui->setupUi(this);

    connect(ui->newTagName, SIGNAL(textChanged(QString)),
            this, SLOT(checkTag(QString)));
}

TagDialog::~TagDialog()
{
    delete ui;
}

void TagDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void TagDialog::checkTag(QString tagname)
{
    if (tagname.isEmpty()) {
        ui->warningText->clear();
        ui->okButton->setEnabled(false);

        return;
    }

    Tag tagCandidate = tagHandler.getTagByName(tagname.toUtf8());

    if (tagCurrent) {
        setWindowTitle(tr("Rename tag"));
        ui->label->setText(tr("Please provide new name for tag \"%1\"").arg(QString(tagCurrent.name())));
    }

    if ((tagCurrent && tagCurrent.name() == tagname) || (tagCandidate && tagCandidate.name() == tagname)) {
        ui->warningText->setText(tr("Tag already exists"));
        ui->okButton->setEnabled(false);

        return;
    } else if (tagCurrent) {
        // case, when we edit! the one tag
        ui->warningText->clear();
        ui->okButton->setEnabled(tagCurrent.name() != tagname);

        return;
    } else if (! tagCandidate && ! tagCurrent) {
        // create new tag mode
        ui->label->repaint();
        ui->warningText->clear();
        ui->okButton->setEnabled(true);

        return;
    }
}

void TagDialog::saveTag()
{
    if (! ui->okButton->isEnabled()) {
        return;
    }

    TagHandler th;
    QString newName = ui->newTagName->text();

    if (th.getTagById(tagCurrent.id())) {
        th.renameTag(tagCurrent.id(), newName);
    } else {
        th.addTag(newName);
    }

    setTag(th.getTagByName(newName));

    emit saved();
    emit tagUpdated(tagCurrent);

    close();
}

void TagDialog::setTag(Tag tag)
{
    tagCurrent = tag;
    ui->newTagName->setText(tag.name());
}
