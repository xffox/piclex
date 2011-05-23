#include "SubsentenceGatherer.h"

#include "TreeIterator.h"

namespace search
{
SubsentenceGatherer::SubsentenceGatherer(const std::string &str,
        const Symbol &gatheredSymbol)
    :mStr(str), mGatheredSymbol(gatheredSymbol)
{
}

SubsentenceGatherer::~SubsentenceGatherer()
{
}

void SubsentenceGatherer::visit(const TreeIterator<ParseNode> &iterator)
{
    if((*iterator).getSymbol() == mGatheredSymbol)
    {
        size_t begin = (*iterator).getBeginPosition();
        size_t size = (*iterator).getSize();
        mSubsentences.insert(mStr.substr(begin, size));
    }
}

const std::set<std::string> &SubsentenceGatherer::getSubsentences() const
{
    return mSubsentences;
}

void SubsentenceGatherer::clear()
{
    mSubsentences.clear();
}

}
