#ifndef SIMPLE_SEARCH_ENGINE_H
#define SIMPLE_SEARCH_ENGINE_H

#include <QStringList>

#include "SearchEngine.h"

namespace gui
{
class SimpleSearchEngine: public SearchEngine
{
public:
    virtual ~SimpleSearchEngine();

    virtual bool setDirectory(const QString &path);
    virtual bool setSearchStr(const QString &str);

    virtual const QStringList &getResults() const;

private:
    void updateResults();

    bool isSearched(const QString &filename) const;

private:
    QStringList mFilenames;
    QStringList mResults;

    QString mSearchStr;
};
}

#endif//SIMPLE_SEARCH_ENGINE_H
