#ifndef VIDEOTABLEITEMDELEGATE_H
#define VIDEOTABLEITEMDELEGATE_H

#ifdef USING_PCH
    #include "precompiled.h"
#else
    #include <QtGui>
    #include <QStyledItemDelegate>
#endif

#include <MWidgets>

#include "filmtag.h"

class VideoTableItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit VideoTableItemDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;
    QString displayText(const QVariant &value, const QLocale &locale) const;

private:
    bool isMarked(const QModelIndex &) const;
    bool isFavorite(const QModelIndex &) const;
    bool hasNotes(const QModelIndex &) const;
};

#endif // VIDEOTABLEITEMDELEGATE_H
