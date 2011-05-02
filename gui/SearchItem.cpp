#include "SearchItem.h"

#include <memory>

#include <QThreadPool>

#include "SearchModel.h"
#include "ImageReadRunnable.h"

namespace gui
{
SearchItem::SearchItem(SearchModel *searchModel, const QString &filename)
    :QObject(searchModel), mSearchModel(searchModel), mFilename(filename)
    ,mDefaultSize(100)
{
    readPixmap();
}

const QString &SearchItem::getFilename() const
{
    return mFilename;
}

const QPixmap &SearchItem::getPixmap() const
{
    return mPixmap;
}

void SearchItem::onImageReadFinished(QString, QImage image)
{
    mPixmap.convertFromImage(image);

    emit changed();
}

void SearchItem::readPixmap()
{
    mPixmap = QPixmap(QSize(mDefaultSize, mDefaultSize));
    mPixmap.fill(Qt::gray);

    startImageRead();
}

void SearchItem::startImageRead()
{
    std::auto_ptr<ImageReadRunnable> readRunnable(
            new ImageReadRunnable(mFilename));

    connect( readRunnable.get(), SIGNAL(readFinished(QString, QImage)),
            this, SLOT(onImageReadFinished(QString, QImage)) );

    QThreadPool::globalInstance()->start(readRunnable.get());
    readRunnable.release();
}

}
