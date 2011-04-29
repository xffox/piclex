#include "ParseNode.h"

namespace search
{
ParseNode::ParseNode(const Symbol &symbol, size_t beginPosition,
            size_t endPosition)
    :mSymbol(symbol)
    ,mBeginPosition(beginPosition), mEndPosition(endPosition)

{
}

const Symbol &ParseNode::getSymbol() const
{
    return mSymbol;
}

size_t ParseNode::getBeginPosition() const
{
    return mBeginPosition;
}

size_t ParseNode::getEndPosition() const
{
    return mEndPosition;
}

}
