#include "filmurldialog.h"
#include "ui_filmurldialog.h"

FilmUrlDialog::FilmUrlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilmUrlDialog)
{
    ui->setupUi(this);
}

FilmUrlDialog::~FilmUrlDialog()
{
    delete ui;
}

void FilmUrlDialog::setInputText(const QString & inputText)
{
    ui->lineEdit->setText(inputText);
}

QString FilmUrlDialog::inputText()
{
    return ui->lineEdit->text().trimmed();
}

void FilmUrlDialog::changeEvent(QEvent *e)
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
