#ifndef PARSE_NODE_H
#define PARSE_NODE_H

#include "Symbol.h"
#include "Sentence.h"

namespace search
{
class ParseNode
{
public:
    ParseNode(const Symbol &symbol, size_t beginPosition,
            size_t size);

    const Symbol &getSymbol() const;

    size_t getBeginPosition() const;
    size_t getSize() const;

private:
    Symbol mSymbol;

    size_t mBeginPosition;
    size_t mSize;
};

}

#endif//
