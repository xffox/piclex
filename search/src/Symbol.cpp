#include "Symbol.h"

#include <sstream>

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

bool Symbol::operator==(const Symbol &that) const
{
    return mType == that.mType && mValue == that.mValue;
}

bool Symbol::operator!=(const Symbol &that) const
{
    return !(*this == that);
}

bool Symbol::operator<(const Symbol &that) const
{
    if(mType < that.mType)
    {
        return true;
    }
    else if(mType == that.mType)
    {
        if(mValue < that.mValue)
            return true;
    }
    return false;
}

SymbolType Symbol::getType() const
{
    return mType;
}

SymbolValue Symbol::getValue() const
{
    return mValue;
}

bool Symbol::isTerminal() const
{
    return mType == TERMINAL;
}

bool Symbol::isNonterminal() const
{
    return mType == NONTERMINAL;
}

void Symbol::setValue(SymbolValue value)
{
    mValue = value;
}

const std::string makeString(const Symbol &symbol)
{
    std::stringstream result;
    if(symbol.isTerminal())
    {
        result<<"[";
        if( std::isprint(symbol.getValue()) )
            result<<static_cast<char>(symbol.getValue());
        else
            result<<static_cast<unsigned long>(symbol.getValue());
        result<<"]";
    }
    else
    {
        result<<"(";
        result<<static_cast<unsigned long>(symbol.getValue());
        result<<")";
    }

    return result.str();
}
}
