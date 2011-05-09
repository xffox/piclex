#ifndef IMAGE_MAP_FUNC_H
#define IMAGE_MAP_FUNC_H

class QString;
class QImage;
class QSize;
class QImageReader;

namespace gui
{
class ImageMapFunc
{
public:
    ImageMapFunc();

    void operator()(QImage &image, const QString &filename) const;

private:
    void read(QImage &image, const QString &filename) const;
private:
    const int mImageMaxSize;
};

}

#endif//IMAGE_MAP_FUNC_H
