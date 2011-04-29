#include "Sentence.h"

#include <sstream>

#include "BaseExceptions.h"

namespace search
{
Sentence sentence(const std::string &str)
{
    //TODO: optimize

    Sentence s;
    for(size_t i = 0; i < str.size(); ++i)
        s.push_back(Symbol(str[i]));
    return s;
}

std::string makeString(const Sentence &sentence)
{
    return makeString(sentence, 0, sentence.size());
}

std::string makeString(const Sentence &sentence,
        size_t begin, size_t end)
{
    if(begin > end)
        throw base::InvalidArgument();
    if(begin > sentence.size())
        throw base::OutOfBoundError(begin, sentence.size());
    if(end > sentence.size())
        throw base::OutOfBoundError(end, sentence.size());

    //TODO: optimize

    std::stringstream result;
    for(size_t i = begin; i < end; ++i)
    {
        result<<makeString(sentence[i]);
    }
    return result.str();
}
}
