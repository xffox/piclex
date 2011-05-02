#include "SearchModel.h"

#include <cassert>
#include <memory>

#include "Logger.h"
#include "Searcher.h"

using namespace base;

namespace gui
{
SearchModel::SearchModel(Searcher *searcher, QObject *parent)
    :QAbstractListModel(parent)
    ,mSearcher(searcher)
{
    if(searcher == NULL)
        throw InvalidArgument();
}

SearchModel::~SearchModel()
{
    delete mSearcher;

    deleteItems();
}

int SearchModel::rowCount(const QModelIndex &parent) const
{
    return mResultItems.size();
}

QVariant SearchModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= mResultItems.size())
        return QVariant();

    if(role == Qt::DisplayRole)
        return mResultItems[index.row()]->getFilename();
    if(role == Qt::DecorationRole)
        return mResultItems[index.row()]->getPixmap();

    return QVariant();
}

QVariant SearchModel::headerData(int section, Qt::Orientation orientation,
        int role) const
{
    return QVariant();
}

bool SearchModel::setDirectory(const QString &path)
{
    assert(mSearcher);
    if(mSearcher->setDirectory(path))
    {
        updateResults();
        return true;
    }
    return false;
}

bool SearchModel::setSearchStr(const QString &str)
{
    if(str != mSearchStr)
    {
        mSearchStr = str;

        assert(mSearcher);
        if(mSearcher->setSearchStr(str))
        {
            updateResults();
            return true;
        }
        return false;
    }
    return true;
}

void SearchModel::onItemChanged()
{
    QModelIndex changedIndex = getIndex( qobject_cast<SearchItem*>(sender()) );
    if(changedIndex.isValid())
    {
        emit dataChanged(changedIndex, changedIndex);
        emit layoutChanged();
    }
}

void SearchModel::updateResults()
{
    setResults(mSearcher->getResults());
}

void SearchModel::setResults(const QStringList &results)
{
    Log().debug("SearchModel: set results count= %d", results.size());

    clearItems();

    QStringList::const_iterator iter = results.begin();
    for(; iter != results.end(); ++iter)
    {
        try
        {
            addItem(*iter);
        }
        catch(InvalidPixmap &exc)
        {
            Log().warning( "SearchModel: add failed: invalid pixmap '%s'",
                    qPrintable(exc.getFilename()) );
        }
    }

    Log().debug("SearchModel: items count= %d", mResultItems.size());
}

void SearchModel::clearItems()
{
    if(mResultItems.size() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, mResultItems.size()-1);

        deleteItems();

        endRemoveRows();
    }

    Log().debug("SearchModel: cleared");
}

void SearchModel::addItem(const QString &filename)
{
    insertItem(filename);

    Log().debug("SearchModel: added '%s'", qPrintable(filename));
}

void SearchModel::insertItem(const QString &filename)
{
    beginInsertRows(QModelIndex(), mResultItems.size(), mResultItems.size());

    std::auto_ptr<SearchItem> item(new SearchItem(this, filename));

    connect( item.get(), SIGNAL(changed()), this, SLOT(onItemChanged()) );

    mResultItems.append(item.get());
    item.release();

    endInsertRows();
}

void SearchModel::deleteItems()
{
    while(mResultItems.size() > 0)
    {
        delete mResultItems.back();
        mResultItems.pop_back();
    }
}

QModelIndex SearchModel::getIndex(SearchItem *item) const
{
    int position = mResultItems.indexOf(item);
    if(position != -1)
        return createIndex(position, 0);
    return QModelIndex();
}

}
