#ifndef SEARCHER_H
#define SEARCHER_H

class QString;
class QStringList;

namespace gui
{
class Searcher
{
public:
    virtual ~Searcher() {}

    virtual bool setDirectory(const QString &path) = 0;
    virtual bool setSearchStr(const QString &str) = 0;

    virtual const QStringList &getResults() const = 0;
};

}

#endif//SEARCHER_H
