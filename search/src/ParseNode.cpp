#include "ParseNode.h"

namespace search
{
ParseNode::ParseNode(const Symbol &symbol, size_t beginPosition,
            size_t size)
    :mSymbol(symbol)
    ,mBeginPosition(beginPosition), mSize(size)

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

size_t ParseNode::getSize() const
{
    return mSize;
}

}
