#ifndef FILMURLDIALOG_H
#define FILMURLDIALOG_H

#include <QDialog>

namespace Ui {
    class FilmUrlDialog;
}

class FilmUrlDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FilmUrlDialog(QWidget *parent = 0);
        ~FilmUrlDialog();

        void setInputText(const QString &);
        QString inputText();

    protected:
        void changeEvent(QEvent *e);

    private:
        Ui::FilmUrlDialog *ui;
};

#endif // FILMURLDIALOG_H
