#ifndef SEARCHRESULTSITEMDELEGATE_H
#define SEARCHRESULTSITEMDELEGATE_H

#define RIGHT_MARGIN    -5

#include <QtCore>
#include <QtGui>
#include <QStyledItemDelegate>

class SearchResultsItemDelegate : public QStyledItemDelegate
{
public:
    SearchResultsItemDelegate(QObject *parent=0);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // SEARCHRESULTSITEMDELEGATE_H
