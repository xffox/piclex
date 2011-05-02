#ifndef SEARCH_ITEM_H
#define SEARCH_ITEM_H

#include <QPixmap>

#include "BaseExceptions.h"

namespace gui
{
class SearchModel;

class SearchItem: public QObject
{
    Q_OBJECT

public:
    SearchItem(SearchModel *searchModel, const QString &filename);

    const QString &getFilename() const;
    const QPixmap &getPixmap() const;

signals:
    void changed();

public slots:
    void onImageReadFinished(QString filename, QImage image);

private:
    void readPixmap();

    void startImageRead();

private:
    SearchModel *mSearchModel;

    QString mFilename;
    QPixmap mPixmap;

    int mDefaultSize;
};
}

#endif//SEARCH_ITEM_H
