#ifndef FILMTAGSLISTVIEW
#define FILMTAGSLISTVIEW

#include "mainwindow.h"

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>

#include <QListView>
#include <QResizeEvent>
#else
#include <QtGui/QWidget>
#endif

//class MainWindow;

//namespace Ui {
//    class MainWindow : public Ui::MainWindow;
//}

;

class FilmTagsListView : public QListView
{
    Q_OBJECT

public:
    explicit FilmTagsListView(QWidget *parent = 0);
    ~FilmTagsListView();

signals:
    void mouseIn();
    void mouseOut();

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

};

#endif // FILMTAGSLISTVIEW
