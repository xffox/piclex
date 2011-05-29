#include "DocDescriptionGatherer.h"

#include "SubsentenceGatherer.h"
#include "TreeIterator.h"
#include "BaseExceptions.h"
#include "DocDescription.h"
#include "Logger.h"

namespace search
{
DocDescriptionGatherer::DocDescriptionGatherer(DocDescription *docDescription,
        const std::string &str,
        const Symbol &objectSymbol, const Symbol &relationSymbol,
        const Symbol &descriptionSymbol)
    :mDocDescription(docDescription), mStr(str)
    ,mObjectSymbol(objectSymbol), mRelationSymbol(relationSymbol)
    ,mDescriptionSymbol(descriptionSymbol)
{
    if(!docDescription)
        throw base::InvalidArgument();
}

DocDescriptionGatherer::~DocDescriptionGatherer()
{
}

void DocDescriptionGatherer::visit(const TreeIterator<ParseNode> &iterator)
{
    if((*iterator).getSymbol() == mDescriptionSymbol)
    {
        SubsentenceGatherer objectGatherer(mStr, mObjectSymbol);
        iterator.accept(&objectGatherer);

        base::Log().debug("doc description gathered %zu objects",
                objectGatherer.getSubsentences().size());

        if(objectGatherer.getSubsentences().size() == 2)
        {
            SubsentenceGatherer relationGatherer(mStr, mRelationSymbol);
            iterator.accept(&relationGatherer);

            base::Log().debug("doc description gathered %zu relations",
                    relationGatherer.getSubsentences().size());

            if(relationGatherer.getSubsentences().size() == 1)
            {
                mDocDescription->addRelation(
                        objectGatherer.getSubsentences()[0],
                        objectGatherer.getSubsentences()[1],
                        relationGatherer.getSubsentences()[0]);

                base::Log().debug("add gathered doc description: %s %s %s",
                        objectGatherer.getSubsentences()[0].c_str(),
                        relationGatherer.getSubsentences()[0].c_str(),
                        objectGatherer.getSubsentences()[1].c_str());
            }
        }
    }
}

}
