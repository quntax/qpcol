#include "videotableitemdelegate.h"

VideoTableItemDelegate::VideoTableItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void VideoTableItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, QModelIndex());
    painter->save();

    QStyleOptionViewItemV4 newOption(option);
    QString currentText = displayText(index.data(Qt::DisplayRole), QLocale::system());

    if (index.column() == FilmTag::Size) {
        currentText.append(" MB");
    }

    QRect textArea = newOption.rect.adjusted(2, 0, 0, 0);
    QFont textFont = newOption.font;

    if (index.column() == FilmTag::FileName
        && (isMarked(index) || isFavorite(index))) {
        QString iconResource = isFavorite(index) ? ":/icons/emblem-favorite.png" : ":/icons/emblem-new.png";
        QPixmap icon(iconResource);
        QRect iconArea = newOption.rect.adjusted(2, 2, -(textArea.width() - 16), -2);
        painter->drawPixmap(iconArea, icon);

        textArea = newOption.rect.adjusted(22, 0, 0, 0);
    }

    if (hasNotes(index) && index.column() == FilmTag::TagNames) {
        QString iconResource = ":/icons/knotes.png";
        QPixmap icon(iconResource);
        QRect iconArea = newOption.rect.adjusted(2, 2, -(textArea.width() - 16), -2);
        painter->drawPixmap(iconArea, icon);

        textArea = newOption.rect.adjusted(22, 0, 0, 0);
    }

    if (isMarked(index)) {
        textFont.setItalic(true);
        painter->setPen(Qt::darkGreen);
    }

    if (isFavorite(index)) {
        textFont.setBold(true);
    }

    QTextOption filenameOption;
    filenameOption.setAlignment(Qt::AlignVCenter| Qt::AlignLeft);

    QFontMetrics fm(textFont, painter->device());
    QString filenameText = fm.elidedText(currentText, Qt::ElideRight, textArea.width());

    painter->setFont(textFont);
    painter->drawText(textArea, filenameText, filenameOption);

    painter->restore();
}

bool VideoTableItemDelegate::isMarked(const QModelIndex &index) const
{
    return index.model()->index(index.row(), FilmTag::Marked).data().toBool();
}

bool VideoTableItemDelegate::isFavorite(const QModelIndex &index) const
{
    return index.model()->index(index.row(), FilmTag::Favorite).data().toBool();
}

bool VideoTableItemDelegate::hasNotes(const QModelIndex & index) const
{
    return ! index.model()->index(index.row(), FilmTag::Notes).data().toString().isEmpty();
}

QString VideoTableItemDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    if (value.type() == QVariant::DateTime) {
        QString dateString = value.toDateTime().toString("yyyy-MM-dd hh:mm:ss");

        if (! value.toDateTime().isValid()) {
            dateString = "0000-00-00 00:00:00";
        }

        return dateString;
    } else {
        return QStyledItemDelegate::displayText(value, locale);
    }
}
