#ifndef DOC_DESCRIPTION_GATHERER_H
#define DOC_DESCRIPTION_GATHERER_H

#include "TreeVisitor.h"
#include "ParseNode.h"

namespace search
{
class DocDescription;

class DocDescriptionGatherer: public TreeVisitor<ParseNode>
{
public:
    DocDescriptionGatherer(DocDescription *docDescription,
            const std::string &str,
            const Symbol &objectSymbol, const Symbol &relationSymbol,
            const Symbol &objectsRelationSymbol);
    virtual ~DocDescriptionGatherer();

    virtual void visit(const TreeIterator<ParseNode> &iterator);

private:
    DocDescription *mDocDescription;

    std::string mStr;

    Symbol mObjectSymbol;
    Symbol mRelationSymbol;
    Symbol mDescriptionSymbol;
};

}

#endif//DOC_DESCRIPTION_GATHERER_H
