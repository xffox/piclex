#include "MockSearchEngine.h"

#include <cassert>

#include "Logger.h"

#include "Searcher.h"
#include "mock/SimpleDocProvider.h"
//#include "mock/WordDocProcessor.h"
#include "ImageDocProcessor.h"

using namespace search;

namespace gui
{
MockSearchEngine::MockSearchEngine()
    :mSearcher(NULL)
{
    DocProvider *docProvider = new SimpleDocProvider();

    DocProcessor *docProcessor = new ImageDocProcessor();
    DocProcessor *queryProcessor = new ImageDocProcessor();

    mSearcher = new Searcher(docProvider, docProcessor, queryProcessor);
}

MockSearchEngine::~MockSearchEngine()
{
    delete mSearcher;
}

bool MockSearchEngine::setDirectory(const QString &path)
{
    base::Log().debug("MockSearchEngine: set directory '%s'", qPrintable(path));

    assert(mSearcher);

    mSearcher->setPath(qPrintable(path));

    updateResults();

    return true;
}

bool MockSearchEngine::setSearchStr(const QString &str)
{
    base::Log().debug("MockSearchEngine: set search str '%s'", qPrintable(str));

    mSearchStr = str;

    updateResults();

    return true;
}

const QStringList &MockSearchEngine::getResults() const
{
    return mResults;
}

void MockSearchEngine::updateResults()
{
    std::vector<std::string> results = mSearcher->search(qPrintable(
                mSearchStr));

    mResults.clear();
    std::vector<std::string>::const_iterator resultsIter = results.begin();
    for(; resultsIter != results.end(); ++resultsIter)
        mResults.append( QString(resultsIter->c_str()) );
}

}
