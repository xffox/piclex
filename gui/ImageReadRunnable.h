#ifndef PIXMAP_READ_RUNNABLE_H
#define PIXMAP_READ_RUNNABLE_H

#include <QObject>
#include <QRunnable>
#include <QString>
#include <QImage>

class QImageReader;
class QSize;

namespace gui
{
class ImageReadRunnable: public QObject, public QRunnable
{
    Q_OBJECT

public:
    ImageReadRunnable(const QString &filename);

    virtual void run();

signals:
    void readFinished(QString filename, QImage pixmap);

private:
    void read();

    QSize getScaledImageSize(const QImageReader &imageReader) const;

private:
    QString mFilename;
    QImage mImage;

    int mImageMaxSize;
};
}

#endif//PIXMAP_READ_RUNNABLE_H
