#ifndef TAGDIALOG_H
#define TAGDIALOG_H
/*
#define QPCOL_PCH_DEF(...) ("" ifdef USING_PCH \
        ##include "precompiled.h" \
    ##else \
        #1include #1 \
    ##endif)
*/
//#include <QObject>
//QPCOL_PCH_DEF("<QWidget>")

#include "tag.h"
#include "taghandler.h"

#ifdef USING_PCH
    #include "precompiled.h"
#else
    #include <QDialog>
#endif

namespace Ui {
    class TagDialog;
}

class TagDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TagDialog(QWidget *parent = 0);
    void setTag(Tag);
    ~TagDialog();

signals:
    void saved();
    void tagUpdated(Tag);

protected slots:
    void checkTag(QString);
    void saveTag();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TagDialog *ui;
    TagHandler tagHandler;
    Tag tagCurrent;
};

#endif // TAGDIALOG_H
