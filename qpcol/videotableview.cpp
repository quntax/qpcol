#include "videotableview.h"

VideoTableView::VideoTableView(QWidget *parent) :
    PTableView(parent)
{
    setItemDelegate(new VideoTableItemDelegate);
    initColumnsWidth();
    setColumnsWidth();
    connect(horizontalHeader(), SIGNAL(sectionResized(int,int,int)),
            this, SLOT(columnResized(int,int,int)));
}

VideoTableView::~VideoTableView()
{
    ConfigHandler *c = ConfigHandler::instance();

    c->save(ColumnWidth_FileName, columnsWidth[FileName]);
    c->save(ColumnWidth_Tags, columnsWidth[Tags]);
    c->save(ColumnWidth_Size, columnsWidth[Size]);
}

void VideoTableView::setModel(QAbstractItemModel *model)
{
    QModelIndex idx(currentIndex());
    QTableView::setModel(model);

    if (idx.isValid()) {
        setRootIndex(idx);
    }

    setColumnHidden(FilmTag::IdFilm, true);
    setColumnHidden(FilmTag::FilePath, true);
    setColumnHidden(FilmTag::Favorite, true);
    setColumnHidden(FilmTag::Blacklist, true);
    setColumnHidden(FilmTag::Marked, true);
    setColumnHidden(FilmTag::Notes, true);
    setColumnHidden(FilmTag::OriginalUrl, true);
    setColumnHidden(FilmTag::IdTagList, true);
}

void VideoTableView::sortByColumn(int column, Qt::SortOrder order)
{
    QTableView::sortByColumn(column, order);
}

void VideoTableView::initColumnsWidth()
{
    ConfigHandler *c = ConfigHandler::instance();

    columnsWidth[FileName]  = c->load(ColumnWidth_FileName, 45).toInt();
    columnsWidth[Tags]      = c->load(ColumnWidth_Tags, 20).toInt();
    columnsWidth[Size]      = c->load(ColumnWidth_Size, 10).toInt();
}

void VideoTableView::setColumnsWidth()
{
    int tableWidth = width();

    setColumnWidth(FilmTag::FileName, tableWidth*columnsWidth[FileName]/100);
    setColumnWidth(FilmTag::TagNames, tableWidth*columnsWidth[Tags]/100);
    setColumnWidth(FilmTag::Size, tableWidth*columnsWidth[Size]/100);
}

void VideoTableView::resizeEvent(QResizeEvent *e)
{
    QTableView::resizeEvent(e);
    setColumnsWidth();
}

void VideoTableView::columnResized(int column, int/* oldWidth*/, int newWidth)
{
    int localIndex;

    switch (column) {
    case FilmTag::FileName:
        localIndex = FileName; break;
    case FilmTag::TagNames:
        localIndex = Tags; break;
    case FilmTag::Size:
        localIndex = Size; break;
    case FilmTag::AddedWhen:
        localIndex = AddedWhen; break;
    default:
        return;
    }

    columnsWidth[localIndex] = qRound((float)newWidth*100/geometry().width());
}

void VideoTableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (! current.isValid()) {
        return;
    }

    int idFilm = current.model()->index(current.row(), FilmTag::IdFilm).data().toInt();
    FilmHandler fh;
    Film f = fh.getFilmById(idFilm);

    emit favorite(f.isFavorite());
    emit indexChanged(current);

    QTableView::currentChanged(current, previous);
}
