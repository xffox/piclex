#include "Sentence.h"

#include <sstream>

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

const std::string makeString(const Sentence &sentence)
{
    //TODO: optimize

    std::stringstream result;
    for(size_t i = 0; i < sentence.size(); ++i)
    {
        result<<makeString(sentence[i]);
    }
    return result.str();
}
}
