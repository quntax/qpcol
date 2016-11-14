#include "filmtagslistview.h"

FilmTagsListView::FilmTagsListView(QWidget *parent)
    : QListView(parent)
{
    setMouseTracking(true);
}

FilmTagsListView::~FilmTagsListView()
{

}

void FilmTagsListView::enterEvent(QEvent * ev)
{
        emit mouseIn();

    QListView::enterEvent(ev);
}

void FilmTagsListView::leaveEvent(QEvent * ev)
{
    emit mouseOut();

    QListView::leaveEvent(ev);
}
