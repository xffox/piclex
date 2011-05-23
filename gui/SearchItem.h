#ifndef SEARCH_ITEM_H
#define SEARCH_ITEM_H

#include <QImage>
#include <QMutex>
#include <QMutexLocker>

#include "BaseExceptions.h"
#include "MapperCallback.h"

namespace gui
{
class SearchModel;

class InvalidImageFile: public base::BaseException
{
};

class SearchItem: public QObject
{
    Q_OBJECT

    class ImageMapperCallback: public MapperCallback<QString, QImage>
    {
    public:
        ImageMapperCallback(SearchItem *obj);

        virtual ~ImageMapperCallback();

        virtual void call(const QString &in, const QImage &out);

    private:
        SearchItem *mObj;
    };

public:
    SearchItem(SearchModel *searchModel, const QString &filename);
    ~SearchItem();

    const QString &getFilename() const;
    const QImage getImage() const;

    void set(const QString &filename, const QImage &image);

signals:
    void changed();

private:
    SearchModel *mSearchModel;

    QString mFilename;
//    QImage mImage;

//    int mDefaultImageSize;
//    QImage mDefaultImage;

//    bool mLoaded;

    mutable QMutex mMutex;

    mutable ImageMapperCallback mImageMapperCallback;
};
}

#endif//SEARCH_ITEM_H
