#include "SearchItem.h"

#include <QThreadPool>
#include <QImageReader>

#include "SearchModel.h"

namespace gui
{
SearchItem::SearchItem(SearchModel *searchModel, const QString &filename)
    :QObject(searchModel), mSearchModel(searchModel), mFilename(filename)
//    ,mDefaultImageSize(300)
//    ,mLoaded(false)
    ,mMutex(QMutex::Recursive)
    ,mImageMapperCallback(this)
{
    QImageReader reader(filename);
    if(!reader.canRead())
        throw InvalidImageFile();
}

SearchItem::~SearchItem()
{
    if(mSearchModel)
        mSearchModel->getImageMapper().cancel(mFilename, &mImageMapperCallback);
}

const QString &SearchItem::getFilename() const
{
    return mFilename;
}

const QImage SearchItem::getImage() const
{
//    QMutexLocker locker(&mMutex);

//    if(mLoaded)
//        return mImage;

    QImage image;
    if(mSearchModel)
    {
        if(mSearchModel->getImageMapper().mapStored(image, mFilename))
            return image; 

        mSearchModel->getImageMapper().map(mFilename, &mImageMapperCallback);

        return mSearchModel->getDefaultImage();
    }

//    if(mLoaded)
//        return mImage;

    return QImage();
}

void SearchItem::set(const QString&, const QImage&)
{
//    QMutexLocker locker(&mMutex);
//
//    mImage = image;
//    mLoaded = true;

    emit changed();
}

SearchItem::ImageMapperCallback::ImageMapperCallback(SearchItem *obj)
    :mObj(obj)
{
}

SearchItem::ImageMapperCallback::~ImageMapperCallback()
{
}

void SearchItem::ImageMapperCallback::call(const QString &in,
        const QImage &out)
{
    if(mObj)
        mObj->set(in, out);
}

}
