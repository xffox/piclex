#include "SimpleSearchEngine.h"

#include <QDir>

#include "Logger.h"

using namespace base;

namespace gui
{
SimpleSearchEngine::~SimpleSearchEngine()
{
}

bool SimpleSearchEngine::setDirectory(const QString &path)
{
    QDir dir(path);
    if(!dir.exists())
    {
        Log().warning("SimpleSearchEngine: set directory failed: directory doesn't"
                "exist '%s'",
                qPrintable(path));
        return false;
    }

    Log().debug("SimpleSearchEngine: set directory '%s'", qPrintable(path));

    QFileInfoList fileInfoList = dir.entryInfoList(
            QDir::Files);

    mFilenames.clear();

    QFileInfoList::const_iterator iter = fileInfoList.begin();
    for(; iter != fileInfoList.end(); ++iter)
        mFilenames.append(iter->absoluteFilePath());

    updateResults();

    return true;
}

bool SimpleSearchEngine::setSearchStr(const QString &str)
{
    mSearchStr = str;

    Log().debug("SimpleSearchEngine: set search str '%s'", qPrintable(str));

    updateResults();

    return true;
}

const QStringList &SimpleSearchEngine::getResults() const
{
    return mResults;
}

void SimpleSearchEngine::updateResults()
{
    mResults.clear();

    QStringList::const_iterator iter = mFilenames.begin();
    for(; iter != mFilenames.end(); ++iter)
        if(isSearched(*iter))
            mResults.append(*iter);
}

bool SimpleSearchEngine::isSearched(const QString &filename) const
{
    return mSearchStr.isEmpty() || filename.contains(mSearchStr);
}

}
