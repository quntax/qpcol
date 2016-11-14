#ifndef VIDEOTABLEVIEW_H
#define VIDEOTABLEVIEW_H

#ifdef USING_PCH
    #include "precompiled.h"
#else
    #include <PTable>
#endif

#include "filmhandler.h"
#include "filmtag.h"
#include "videotableitemdelegate.h"
#include "confighandler.h"

class VideoTableView : public PTableView
{
    Q_OBJECT
    Q_ENUMS(Column)

public:
    enum Column {
        FileName,
        Tags,
        Size,
        AddedWhen
    };

    explicit VideoTableView(QWidget *parent = 0);
    ~VideoTableView();

    void setModel(QAbstractItemModel *model);
    void sortByColumn(int, Qt::SortOrder);

signals:
    void favorite(bool);
    void indexChanged(const QModelIndex &);

protected slots:
    void resizeEvent(QResizeEvent *);
    void columnResized(int column, int oldWidth, int newWidth);

protected:
    void initColumnsWidth();
    void setColumnsWidth();

    void currentChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    int columnsWidth[4];

};

#endif // VIDEOTABLEVIEW_H
