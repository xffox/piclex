#ifndef SEARCH_VIEW_DELEGATE_H
#define SEARCH_VIEW_DELEGATE_H

#include <QAbstractItemDelegate>

namespace gui
{
class SearchViewDelegate: public QAbstractItemDelegate
{
    Q_OBJECT

public:
    SearchViewDelegate(int imageMaxSize, QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
            const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
            const QModelIndex &index) const;

private:
    QSize getScaledImageSize(const QImageReader &imageReader) const;

private:
    int mImageMaxSize;
};
}

#endif//SEARCH_VIEW_DELEGATE_H
