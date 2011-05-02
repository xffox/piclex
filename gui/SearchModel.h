#ifndef SEARCH_MODEL_H
#define SEARCH_MODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "BaseExceptions.h"
#include "SearchItem.h"

namespace gui
{
class Searcher;

class InvalidPixmap: public base::BaseException
{
public:
    InvalidPixmap(const QString &filename)
        :mFilename(filename)
    {
    }

    const QString &getFilename() const
    {
        return mFilename;
    }

private:
    QString mFilename;
};

class SearchModel: public QAbstractListModel
{
    Q_OBJECT
        
public:
    SearchModel(Searcher *searcher, QObject *parent = 0);
    ~SearchModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
            int role = Qt::DisplayRole) const;

public slots:
    bool setDirectory(const QString &path);
    bool setSearchStr(const QString &str);

    void onItemChanged();

private:
    void updateResults();

    void setResults(const QStringList &results);
    
    void addItem(const QString &filename);

    void clearItems();
    void insertItem(const QString &filename);

    void deleteItems();

    QModelIndex getIndex(SearchItem *item) const;

private:
    Searcher *mSearcher;

    QVector<SearchItem*> mResultItems;

    QString mSearchStr;
};

}

#endif//SEARCH_MODEL_H
