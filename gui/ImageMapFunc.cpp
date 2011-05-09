#include "ImageMapFunc.h"

#include <QImage>
#include <QImageReader>

#include "Logger.h"
#include "GuiDefines.h"

namespace gui
{
ImageMapFunc::ImageMapFunc()
    :mImageMaxSize(IMAGE_PREVIEW_SIZE)
{

}

void ImageMapFunc::operator()(QImage &image, const QString &filename) const
{
    read(image, filename);

    base::Log().debug("Load image '%s'", qPrintable(filename));
}

void ImageMapFunc::read(QImage &image, const QString &filename) const
{
    QImageReader imageReader(filename);

    QSize imageSize = imageReader.size();
    if(qMax(imageSize.width(), imageSize.height()) > mImageMaxSize)
        imageSize.scale(mImageMaxSize, mImageMaxSize, Qt::KeepAspectRatio);

    imageReader.setScaledSize(imageSize);

//    image = imageReader.read().copy(0, 0, mImageMaxSize, mImageMaxSize);
    image = imageReader.read();
}

}
