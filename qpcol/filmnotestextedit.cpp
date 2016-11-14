#include "filmnotestextedit.h"

FilmNotesTextEdit::FilmNotesTextEdit(QWidget *parent) : QPlainTextEdit(parent)
{
    setMouseTracking(true);
}

FilmNotesTextEdit::~FilmNotesTextEdit()
{

}

void FilmNotesTextEdit::enterEvent(QEvent * ev)
{
    emit mouseIn();

    QPlainTextEdit::enterEvent(ev);
}

void FilmNotesTextEdit::leaveEvent(QEvent * ev)
{
    emit mouseOut();

    QPlainTextEdit::leaveEvent(ev);
}
