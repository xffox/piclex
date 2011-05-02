#include "ImageReadRunnable.h"

#include <QImageReader>

namespace gui
{
ImageReadRunnable::ImageReadRunnable(const QString &filename)
    :mFilename(filename)
    ,mImageMaxSize(300)
{

}

void ImageReadRunnable::run()
{
    read();

    emit readFinished(mFilename, mImage);
}

void ImageReadRunnable::read()
{
    QImageReader imageReader(mFilename);

    QSize scaledSize = getScaledImageSize(imageReader);

    imageReader.setScaledSize(scaledSize);

    mImage = imageReader.read();
}

QSize ImageReadRunnable::getScaledImageSize(const QImageReader &imageReader
        ) const
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
