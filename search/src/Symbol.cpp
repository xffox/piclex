#include "Symbol.h"

namespace search
{
Symbol::Symbol(SymbolType type, SymbolValue value)
    :mType(type), mValue(value)
{
}

Symbol::Symbol(char c)
    :mType(TERMINAL), mValue(c)
{
}

bool Symbol::operator==(const Symbol &that)
{
    return mType == that.mType && mValue == that.mValue;
}

SymbolType Symbol::getType() const
{
    return mType;
}

SymbolValue Symbol::getValue() const
{
    return mValue;
}

void Symbol::setValue(SymbolValue value)
{
    mValue = value;
}
}
