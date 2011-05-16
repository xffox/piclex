#ifndef SEARCH_MODEL_H
#define SEARCH_MODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "BaseExceptions.h"
#include "SearchItem.h"
#include "Mapper.h"

class QImage;

namespace gui
{
class SearchEngine;

class SearchModel: public QAbstractListModel
{
    Q_OBJECT
        
    typedef Mapper<QString, QImage> ImageMapper;

public:
    SearchModel(SearchEngine *searchEngine, QObject *parent = 0);
    ~SearchModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
            int role = Qt::DisplayRole) const;

    ImageMapper &getImageMapper();

    const QImage &getDefaultImage() const;

public slots:
    bool setDirectory(const QString &path);
    bool setSearchStr(const QString &str);

    void onItemChanged();

private:
    void updateResults();

    void setResults(const QStringList &results);
    
    void addItem(const QString &filename);
    void removeItem(SearchItem *item);

    void clearItems();

    void deleteItems();

    QModelIndex getIndex(SearchItem *item) const;

private:
    SearchEngine *mSearchEngine;

    QVector<SearchItem*> mResultItems;

    QString mSearchStr;

    ImageMapper mImageMapper;

    QImage mDefaultImage;
    int mDefaultImageSize;
};

}

#endif//SEARCH_MODEL_H
