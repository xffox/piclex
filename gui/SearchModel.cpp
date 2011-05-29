#include "SearchModel.h"

#include <cassert>
#include <memory>

#include <QStringList>

#include "Logger.h"
#include "SearchEngine.h"
#include "ImageMapFunc.h"
#include "GuiDefines.h"

using namespace base;

namespace gui
{
SearchModel::SearchModel(SearchEngine *searchEngine, QObject *parent)
    :QAbstractListModel(parent)
    ,mSearchEngine(searchEngine)
    ,mImageMapper(ImageMapFunc())
    ,mDefaultImageSize(IMAGE_PREVIEW_SIZE)
{
    if(searchEngine == NULL)
        throw InvalidArgument();

    mDefaultImage = QImage(QSize(mDefaultImageSize, mDefaultImageSize),
            QImage::Format_RGB888);
    mDefaultImage.fill(IMAGE_DEFAULT_COLOR);
}

SearchModel::~SearchModel()
{
    delete mSearchEngine;

    deleteItems();
}

int SearchModel::rowCount(const QModelIndex &) const
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
        return mResultItems[index.row()]->getImage();
//    if(role == Qt::SizeHintRole)
//        return QSize(mDefaultImageSize, mDefaultImageSize);

    return QVariant();
}

QVariant SearchModel::headerData(int, Qt::Orientation,
        int) const
{
    return QVariant();
}

SearchModel::ImageMapper &SearchModel::getImageMapper()
{
    return mImageMapper;
}

const QImage &SearchModel::getDefaultImage() const
{
    return mDefaultImage;
}

bool SearchModel::setDirectory(const QString &path)
{
    assert(mSearchEngine);
    if(mSearchEngine->setDirectory(path))
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

        assert(mSearchEngine);
        bool res = mSearchEngine->setSearchStr(str);
        updateResults();
        return res;
    }
    return mSearchEngine->isValidSearchStr();
}

void SearchModel::onItemChanged()
{
    SearchItem *searchItem = qobject_cast<SearchItem*>(sender());
    if(!searchItem)
        return;

    if(!searchItem->getImage().isNull())
    {
        QModelIndex changedIndex = getIndex(searchItem);
        if(changedIndex.isValid())
        {
            //        emit layoutAboutToBeChanged();

            //        if(searchItem->getImage().isValid())
            emit dataChanged(changedIndex, changedIndex);

            //TODO: probably slow
            //        emit layoutChanged();
        }
    }
    else
    {
        Log().debug( "SearchModel: invalid image '%s'",
                qPrintable(searchItem->getFilename()) );

        removeItem(searchItem);
    }
}

void SearchModel::updateResults()
{
    setResults(mSearchEngine->getResults());
}

void SearchModel::setResults(const QStringList &results)
{
    Log().debug("SearchModel: set results count= %d", results.size());

    clearItems();

    QStringList::const_iterator iter = results.begin();
    for(; iter != results.end(); ++iter)
    {
        addItem(*iter);
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
    std::auto_ptr<SearchItem> item;
    try
    {
        item = std::auto_ptr<SearchItem>(new SearchItem(this, filename));
    }
    catch(InvalidImageFile &exc)
    {
        Log().warning("model: invalid image file '%s'",
                qPrintable(filename));
        return;
    }

    connect( item.get(), SIGNAL(changed()), this, SLOT(onItemChanged()) );

    beginInsertRows(QModelIndex(), mResultItems.size(), mResultItems.size());

    mResultItems.append(item.get());
    item.release();

    endInsertRows();

    Log().debug("SearchModel: added '%s'", qPrintable(filename));
}

void SearchModel::removeItem(SearchItem *item)
{
    assert(item);

    QModelIndex removeIndex = getIndex(item);
    if(removeIndex.isValid())
    {
        beginRemoveRows(QModelIndex(), removeIndex.row(), removeIndex.row());

        mResultItems.remove(removeIndex.row());

        endRemoveRows();

        Log().debug( "SearchModel: removed '%s'",
                qPrintable(item->getFilename()) );
        delete item;
    }
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
