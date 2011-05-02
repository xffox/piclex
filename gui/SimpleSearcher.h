#ifndef SIMPLE_SEARCHER_H
#define SIMPLE_SEARCHER_H

#include <QStringList>

#include "Searcher.h"

namespace gui
{
class SimpleSearcher: public Searcher
{
public:
    virtual ~SimpleSearcher();

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

#endif//SIMPLE_SEARCHER_H
