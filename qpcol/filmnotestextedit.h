#ifndef FILMNOTESTEXTEDIT_H
#define FILMNOTESTEXTEDIT_H

#include <QtWidgets/QWidget>

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000

#include <QPlainTextEdit>
#else
#include <QtGui/QWidget>
#endif

class FilmNotesTextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit FilmNotesTextEdit(QWidget *parent = 0);
    ~FilmNotesTextEdit();

signals:
    void mouseIn();
    void mouseOut();

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

};

#endif // FILMNOTESTEXTEDIT_H
