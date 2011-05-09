#include "SearchViewDelegate.h"

#include <QPainter>
#include <QImageReader>

namespace gui
{
SearchViewDelegate::SearchViewDelegate(int imageSize, QObject *parent)
    :QItemDelegate(parent), mImageSize(imageSize)
    ,mBorderSize(10)
{
}

#if 0
void SearchViewDelegate::paint(QPainter *painter,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QString filename = index.model()->data(index,
            Qt::DisplayRole).toString();

//    if(option.state & QStyle::State_Selected)
//        painter->fillRect(option.rect, option.palette.highlight());

    painter->fillRect(option.rect, option.palette.highlight());
    painter->drawImage(option.rect, index.model()->data(index,
            Qt::DisplayRole).value<QImage>());

    painter->restore();
}
#endif

QSize SearchViewDelegate::sizeHint(const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::DisplayRole).toString();
    QFontMetrics fontMetrics(option.font);
    QRect textBoundingRect = fontMetrics.boundingRect(text);
    return QSize(qMax(mImageSize, textBoundingRect.width()) + mBorderSize,
                mImageSize + textBoundingRect.height() + mBorderSize);
}
}
