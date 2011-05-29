#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

class QString;
class QStringList;

namespace gui
{
//! An interface for the search engine objects
class SearchEngine
{
public:
    virtual ~SearchEngine() {}

    virtual bool setDirectory(const QString &path) = 0;
    virtual bool setSearchStr(const QString &str) = 0;

    virtual const QStringList &getResults() const = 0;

    virtual bool isValidSearchStr() const = 0;
};

}

#endif//SEARCH_ENGINE_H
