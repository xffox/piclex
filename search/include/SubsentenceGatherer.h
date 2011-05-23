#ifndef SUBSENTENCE_GATHERER_H
#define SUBSENTENCE_GATHERER_H

#include <set>
#include <string>

#include "ParseNode.h"
#include "TreeVisitor.h"
#include "Symbol.h"

namespace search
{
class SubsentenceGatherer: public TreeVisitor<ParseNode>
{
public:
    SubsentenceGatherer(const std::string &str,
            const Symbol &gatheredSymbol);
    virtual ~SubsentenceGatherer();

    virtual void visit(const TreeIterator<ParseNode> &iterator);

    const std::set<std::string> &getSubsentences() const;

    void clear();

private:
    std::string mStr;

    Symbol mGatheredSymbol;

    std::set<std::string> mSubsentences;
};

}

#endif//SUBSENTENCE_GATHERER_H
