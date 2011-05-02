#include "SimpleSearcher.h"

#include <QDir>

#include "Logger.h"

using namespace base;

namespace gui
{
SimpleSearcher::~SimpleSearcher()
{
}

bool SimpleSearcher::setDirectory(const QString &path)
{
    QDir dir(path);
    if(!dir.exists())
    {
        Log().warning("SimpleSearcher: set directory failed: directory doesn't"
                "exist '%s'",
                qPrintable(path));
        return false;
    }

    Log().debug("SimpleSearcher: set directory '%s'", qPrintable(path));

    QFileInfoList fileInfoList = dir.entryInfoList(
            QDir::Files);

    mFilenames.clear();

    QFileInfoList::const_iterator iter = fileInfoList.begin();
    for(; iter != fileInfoList.end(); ++iter)
        mFilenames.append(iter->absoluteFilePath());

    updateResults();

    return true;
}

bool SimpleSearcher::setSearchStr(const QString &str)
{
    mSearchStr = str;

    Log().debug("SimpleSearcher: set search str '%s'", qPrintable(str));

    updateResults();

    return true;
}

const QStringList &SimpleSearcher::getResults() const
{
    return mResults;
}

void SimpleSearcher::updateResults()
{
    mResults.clear();

    QStringList::const_iterator iter = mFilenames.begin();
    for(; iter != mFilenames.end(); ++iter)
        if(isSearched(*iter))
            mResults.append(*iter);
}

bool SimpleSearcher::isSearched(const QString &filename) const
{
    return mSearchStr.isEmpty() || filename.contains(mSearchStr);
}

}
