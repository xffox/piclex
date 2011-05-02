#include "SearchViewDelegate.h"

#include <QPainter>
#include <QImageReader>

namespace gui
{
SearchViewDelegate::SearchViewDelegate(int imageMaxSize, QObject *parent)
    :QAbstractItemDelegate(parent), mImageMaxSize(imageMaxSize)
{
}

void SearchViewDelegate::paint(QPainter *painter,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QString filename = index.model()->data(index,
            Qt::DisplayRole).toString();

    QImageReader imageReader(filename);

    QSize scaledSize = getScaledImageSize(imageReader);

    QRect targetRect(QPoint(option.rect.x(), option.rect.y()),
            scaledSize);

    imageReader.setScaledSize(scaledSize);

    painter->drawImage(targetRect, imageReader.read());

    painter->restore();
}

QSize SearchViewDelegate::sizeHint(const QStyleOptionViewItem &,
        const QModelIndex &index) const
{
    QString filename = index.model()->data(index,
            Qt::DisplayRole).toString();

    return getScaledImageSize(QImageReader(filename)); 
}

QSize SearchViewDelegate::getScaledImageSize(const QImageReader &imageReader) const
{
    QSize imageSize = imageReader.size();
    int maxSize = qMax(imageSize.width(), imageSize.height());
    if(maxSize > mImageMaxSize)
    {
        double scaleCoef = static_cast<double>(mImageMaxSize)/maxSize;

        imageSize.setWidth(imageSize.width()*scaleCoef);
        imageSize.setHeight(imageSize.height()*scaleCoef);
    }

    return imageSize;
}

}
