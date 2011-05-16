#ifndef MOCK_SEARCH_ENGINE_H
#define MOCK_SEARCH_ENGINE_H

#include <QStringList>

#include "SearchEngine.h"

namespace search
{
    class DocProvider;
    class DocProcessor;
    class Searcher;
}

namespace gui
{
class MockSearchEngine: public SearchEngine
{
public:
    MockSearchEngine();
    virtual ~MockSearchEngine();

    virtual bool setDirectory(const QString &path);
    virtual bool setSearchStr(const QString &str);

    virtual const QStringList &getResults() const;

private:
    void updateResults();

private:
    search::Searcher *mSearcher;

    QStringList mResults;

    QString mSearchStr;
};

}

#endif//MOCK_SEARCH_ENGINE_H
