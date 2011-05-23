#include "Rule.h"

#include "BaseExceptions.h"

namespace search
{
Rule::Rule()
{
}


Rule::Rule(const Symbol &head, const Sentence &body)
    :mHead(head), mBody(body)
{
}

bool Rule::operator==(const Rule &that) const
{
    return mHead == that.mHead && mBody == that.mBody;
}

bool Rule::operator!=(const Rule &that) const
{
    return !(*this == that);
}

const Symbol &Rule::getHead() const
{
    return mHead;
}

const Symbol &Rule::getBody(size_t index) const
{
    if(index < mBody.size())
        return mBody[index];
    throw base::OutOfBoundError(index, mBody.size());
}

const Sentence &Rule::getRuleBody() const
{
    return mBody;
}

size_t Rule::getBodyLength() const
{
    return mBody.size();
}
}
