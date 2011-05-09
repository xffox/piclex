#ifndef SEARCH_VIEW_DELEGATE_H
#define SEARCH_VIEW_DELEGATE_H

#include <QItemDelegate>

namespace gui
{
class SearchViewDelegate: public QItemDelegate
{
    Q_OBJECT

public:
    SearchViewDelegate(int imageSize, QObject *parent = 0);

#if 0
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
            const QModelIndex &index) const;
#endif

    QSize sizeHint(const QStyleOptionViewItem &option,
            const QModelIndex &index) const;

private:
    int mImageSize;

    const int mBorderSize;
};
}

#endif//SEARCH_VIEW_DELEGATE_H
