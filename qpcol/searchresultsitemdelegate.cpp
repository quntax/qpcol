#include "searchresultsitemdelegate.h"

SearchResultsItemDelegate::SearchResultsItemDelegate(QObject * parent) :
    QStyledItemDelegate(parent)
{

}

void SearchResultsItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    painter->save();

    QStyleOptionViewItemV4 opt(option);
    initStyleOption(&opt, index);

    QString title = index.data(Qt::DisplayRole).toString();
    QString url = index.data(Qt::UserRole+1).toString();
    QString details = index.data(Qt::UserRole+2).toString();

    QPixmap pixmap = qvariant_cast<QPixmap>(index.data(Qt::DecorationRole));
    QPixmap pixmapScaled = pixmap.scaledToHeight(100, Qt::SmoothTransformation);

    QRect iconArea = option.rect.adjusted(0, 0, -260, 0);

    QRect titleBackground = option.rect.adjusted(0, 0, 0, -75);
    QRect titleSeparator = option.rect.adjusted(0, 25, 0, -70);
    QRect urlBackground = option.rect.adjusted(0, 30, 0, -20);
    QRect detailsBackground = option.rect.adjusted(0, 80, 0, 0);

    painter->fillRect(titleBackground, option.palette.alternateBase());
    painter->fillRect(titleSeparator, option.palette.dark());
    painter->fillRect(urlBackground, option.palette.light());
    painter->fillRect(detailsBackground, option.palette.midlight());

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    QRect titleArea = option.rect.adjusted(140, 2, RIGHT_MARGIN, -75);
    QRect urlArea = option.rect.adjusted(140, 30, RIGHT_MARGIN, -20);
    QRect detailsArea = option.rect.adjusted(140, 80, RIGHT_MARGIN, 0);

    painter->drawPixmap(iconArea, pixmapScaled, pixmap.rect());

    QTextOption titleOption;
    titleOption.setAlignment(Qt::AlignTop| Qt::AlignLeft);
    titleOption.setWrapMode(QTextOption::NoWrap);

    QFont titleFont;
    titleFont.setBold(true);
    titleFont.setPointSize(11);

    QFontMetrics fm(titleFont, painter->device());
    QString titleText = fm.elidedText(title, Qt::ElideRight, 240);

    painter->setFont(titleFont);
    painter->drawText(titleArea, titleText, titleOption);

    QFont urlFont;
    urlFont.setPointSize(8);
    urlFont.setUnderline(true);

    QTextOption dataOptions;
    dataOptions.setAlignment(Qt::AlignTop | Qt::AlignLeft);
    dataOptions.setWrapMode(QTextOption::WrapAnywhere);

    painter->setFont(urlFont);
    painter->drawText(urlArea, url, dataOptions);

    QFont detailsFont;
    detailsFont.setPointSize(8);
    detailsFont.setItalic(true);

    painter->setFont(detailsFont);
    painter->drawText(detailsArea, details, dataOptions);

    painter->restore();
}

QSize SearchResultsItemDelegate::sizeHint(const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    return QSize(400, 100);
}
